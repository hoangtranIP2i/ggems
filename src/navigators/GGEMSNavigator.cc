/*!
  \file GGEMSNavigator.cc

  \brief GGEMS mother class for navigation

  \author Julien BERT <julien.bert@univ-brest.fr>
  \author Didier BENOIT <didier.benoit@inserm.fr>
  \author LaTIM, INSERM - U1101, Brest, FRANCE
  \version 1.0
  \date Tuesday February 11, 2020
*/

#include "GGEMS/navigators/GGEMSNavigatorManager.hh"
#include "GGEMS/geometries/GGEMSSolid.hh"
#include "GGEMS/physics/GGEMSCrossSections.hh"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GGEMSNavigator::GGEMSNavigator(GGEMSNavigator* navigator)
: navigator_name_(""),
  geometry_tolerance_(GGEMSTolerance::GEOMETRY),
  position_xyz_(MakeFloat3Zeros()),
  navigator_id_(-1)
{
  GGcout("GGEMSNavigator", "GGEMSNavigator", 3) << "Allocation of GGEMSNavigator..." << GGendl;

  // Store the phantom navigator in phantom navigator manager
  GGEMSNavigatorManager::GetInstance().Store(navigator);

  // Allocation of materials
  materials_.reset(new GGEMSMaterials());

  // Allocation of cross sections including physics
  cross_sections_.reset(new GGEMSCrossSections());
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GGEMSNavigator::~GGEMSNavigator(void)
{
  GGcout("GGEMSNavigator", "~GGEMSNavigator", 3) << "Deallocation of GGEMSNavigator..." << GGendl;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::SetNavigatorName(std::string const& navigator_name)
{
  navigator_name_ = navigator_name;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::SetGeometryTolerance(GGfloat const& distance, std::string const& unit)
{
  geometry_tolerance_ = GGEMSUnits::DistanceUnit(distance, unit);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::SetPosition(GGfloat const& position_x, GGfloat const& position_y, GGfloat const& position_z, std::string const& unit)
{
  position_xyz_.s[0] = GGEMSUnits::DistanceUnit(position_x, unit);
  position_xyz_.s[1] = GGEMSUnits::DistanceUnit(position_y, unit);
  position_xyz_.s[2] = GGEMSUnits::DistanceUnit(position_z, unit);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::SetNavigatorID(std::size_t const& navigator_id)
{
  navigator_id_ = navigator_id;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::CheckParameters(void) const
{
  GGcout("GGEMSNavigator", "CheckParameters", 3) << "Checking the mandatory parameters..." << GGendl;

  // Checking the navigator name
  if (navigator_name_.empty()) {
    std::ostringstream oss(std::ostringstream::out);
    oss << "You have to set a name for the navigator!!!";
    GGEMSMisc::ThrowException("GGEMSNavigator", "CheckParameters", oss.str());
  }

  // Checking id of the navigator
  if (navigator_id_ == -1) {
    std::ostringstream oss(std::ostringstream::out);
    oss << "Id of the navigator is not set!!!";
    GGEMSMisc::ThrowException("GGEMSNavigator", "CheckParameters", oss.str());
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::Initialize(void)
{
  GGcout("GGEMSNavigator", "Initialize", 3) << "Initializing a GGEMS phantom..." << GGendl;

  // Checking the parameters of phantom
  CheckParameters();

  // Initializing Solid for geometric navigation
  solid_->Initialize(materials_);
  solid_->SetGeometryTolerance(geometry_tolerance_);
  solid_->SetNavigatorID(navigator_id_);
  solid_->SetPosition(position_xyz_);

  // Loading the materials and building tables to OpenCL device and converting cuts
  materials_->Initialize();

  // Initialization of electromagnetic process and building cross section tables for each particles and materials
  cross_sections_->Initialize(materials_.get());
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::ParticleNavigatorDistance(void) const
{
  // Compute the distance between particles and navigator using the solid informations
  solid_->Distance();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::ParticleToNavigator(void) const
{
  // Particles are projected to entry of solid
  solid_->ProjectTo();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::ParticleThroughNavigator(void) const
{
  // Particles are tracked through a solid
  solid_->TrackThrough();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSNavigator::PrintInfos(void) const
{
  GGcout("GGEMSNavigator", "PrintInfos", 0) << GGendl;
  GGcout("GGEMSNavigator", "PrintInfos", 0) << "GGEMSNavigator Infos:" << GGendl;
  GGcout("GGEMSNavigator", "PrintInfos", 0) << "---------------------" << GGendl;
  GGcout("GGEMSNavigator", "PrintInfos", 0) << "*Phantom navigator name: " << navigator_name_ << GGendl;
  GGcout("GGEMSNavigator", "PrintInfos", 0) << "*Geometry tolerance: " << geometry_tolerance_/GGEMSUnits::mm << " mm" << GGendl;
  solid_->PrintInfos();
  materials_->PrintInfos();
  GGcout("GGEMSNavigator", "PrintInfos", 0) << GGendl;
}
