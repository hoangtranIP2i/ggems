/*!
  \file GGEMSIonizationParamsMaterial.cc

  \brief GGEMS class managing some physical params for ionization process for material

  \author Julien BERT <julien.bert@univ-brest.fr>
  \author Didier BENOIT <didier.benoit@inserm.fr>
  \author LaTIM, INSERM - U1101, Brest, FRANCE
  \version 1.0
  \date Tuesday March 10, 2020
*/

#include <cmath>

#include "GGEMS/physics/GGEMSIonizationParamsMaterial.hh"
#include "GGEMS/physics/GGEMSMaterialsManager.hh"
#include "GGEMS/global/GGEMSConstants.hh"
#include "GGEMS/tools/GGEMSPrint.hh"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GGEMSIonizationParamsMaterial::GGEMSIonizationParamsMaterial(GGEMSSingleMaterial const* material)
: mean_excitation_energy_(0.0f),
  log_mean_excitation_energy_(0.0f),
  radiation_length_(0.0f),
  x0_density_(0.0f),
  x1_density_(0.0f),
  d0_density_(0.0f),
  c_density_(0.0f),
  a_density_(0.0f),
  m_density_(0.0f),
  f1_fluct_(0.0f),
  f2_fluct_(0.0f),
  energy0_fluct_(0.0f),
  energy1_fluct_(0.0f),
  energy2_fluct_(0.0f),
  log_energy1_fluct_(0.0f),
  log_energy2_fluct_(0.0f)
{
  GGcout("GGEMSIonizationParamsMaterial", "GGEMSIonizationParamsMaterial", 3) << "Allocation of GGEMSIonizationParamsMaterial..." << GGendl;

  material_ = material;

  // Compute params
  ComputeIonizationParameters();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GGEMSIonizationParamsMaterial::~GGEMSIonizationParamsMaterial(void)
{
  GGcout("GGEMSIonizationParamsMaterial", "~GGEMSIonizationParamsMaterial", 3) << "Deallocation of GGEMSIonizationParamsMaterial..." << GGendl;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void GGEMSIonizationParamsMaterial::ComputeIonizationParameters(void)
{
  GGcout("GGEMSIonizationParamsMaterial", "ComputeIonizationParameters", 3) << "Computing ionization parameters for ..." << GGendl;

  // Get the material manager
  GGEMSMaterialsManager& material_manager = GGEMSMaterialsManager::GetInstance();

  // Number of chemical elements in material
  GGuchar const kNumberOfChemicalElements = material_->nb_elements_;

  // Loop over the number of chemical elements
  GGfloat axZ = 0.0f;
  GGfloat total_number_of_electron_per_volume = 0.0f;
  for (GGuchar i = 0; i < kNumberOfChemicalElements; ++i) {
    // Get element by element
    GGEMSChemicalElement const& kChemicalElement = material_manager.GetChemicalElement(material_->chemical_element_name_[i]);
    axZ = static_cast<GGfloat>(static_cast<GGdouble>(GGEMSPhysicalConstants::AVOGADRO) / kChemicalElement.molar_mass_M_ * material_->density_ * material_->mixture_f_[i] * static_cast<GGdouble>(kChemicalElement.atomic_number_Z_));
    log_mean_excitation_energy_ += axZ * std::log(kChemicalElement.mean_excitation_energy_I_);
    total_number_of_electron_per_volume += axZ;
  }

  log_mean_excitation_energy_ /= total_number_of_electron_per_volume;
  mean_excitation_energy_ = std::exp(log_mean_excitation_energy_);

  // Compute density correction factor
  // define material state (approximation based on threshold)
  GGuchar state = GGEMSState::GAS;
  if (material_->density_ > GGEMSPhysicalConstants::GASTHRESHOLD) state = GGEMSState::SOLID;

  // Check if density effect data exist in the table
  // R.M. Sternheimer, Atomic Data and Nuclear Data Tables, 30: 261 (1984)
  //GGuchar const z0 = material_manager.GetChemicalElement(material_->chemical_element_name_[0]).atomic_number_Z_;
  GGshort index_density_correction = material_manager.GetChemicalElement(material_->chemical_element_name_[0]).index_density_correction_;

  // Checking material with only one element, and checking the index of density correction
  if(kNumberOfChemicalElements == 1 && index_density_correction > 0) {
    // Take parameters for the density effect correction from
    // R.M. Sternheimer et al. Density Effect For The Ionization Loss
    // of Charged Particles in Various Substances.
    // Atom. Data Nucl. Data Tabl. 30 (1984) 261-271.
    c_density_ = GGEMSDensityParams::data[index_density_correction][2];
    x0_density_ = GGEMSDensityParams::data[index_density_correction][3];
    x1_density_ = GGEMSDensityParams::data[index_density_correction][4];
    m_density_ = GGEMSDensityParams::data[index_density_correction][5];
    a_density_ = GGEMSDensityParams::data[index_density_correction][6];
    d0_density_ = GGEMSDensityParams::data[index_density_correction][7];
  }
  else { // Computing the density correction
    static constexpr GGfloat kCd2 = 4.0f * GGEMSPhysicalConstants::PI * GGEMSPhysicalConstants::HBARC_SQUARED * GGEMSPhysicalConstants::CLASSIC_ELECTRON_RADIUS;

    GGfloat const kPlasmaEnergy = std::sqrt(kCd2*total_number_of_electron_per_volume);

    // Compute parameters for the density effect correction in DE/Dx formula.
    // The parametrization is from R.M. Sternheimer, Phys. Rev.B,3:3681 (1971)
    GGuchar icase = 0;
    c_density_ = 1.0f + 2.0f*std::log(mean_excitation_energy_/kPlasmaEnergy);

    if (state == GGEMSState::SOLID) {
      static constexpr GGfloat kE100eV  = 100.f*GGEMSUnits::eV;
      static const GGfloat kClimiS[] = {3.681f, 5.215f};
      static const GGfloat kX0valS[] = {1.000f, 1.500f};
      static const GGfloat kX1valS[] = {2.000f, 3.000f};

      if (mean_excitation_energy_ < kE100eV) icase = 0;
      else icase = 1;

      if (c_density_ < kClimiS[icase]) x0_density_ = 0.2f;
      else x0_density_ = 0.326f * c_density_ - kX0valS[icase];

      x1_density_ = kX1valS[icase];
      m_density_ = 3.0f;
    }

    if (state == GGEMSState::GAS) {
      m_density_ = 3.0f;
      x1_density_ = 4.0f;

      if (c_density_ < 10.0f) {
        x0_density_ = 1.6f;
      }
      else if (c_density_ < 11.5f) {
        x0_density_ = 1.6f + 0.2f*(c_density_ - 10.0f);
      }
      else if ( c_density_ < 12.25f) {
        x0_density_ = 1.9f + (c_density_ - 11.5f) / 7.5f;
      }
      else if ( c_density_ < 13.804f) {
        x0_density_ = 2.0f;
        x1_density_ = 4.0f + (c_density_ - 12.25f) / 1.554f;
      }
      else {
        x0_density_ = 0.326f * c_density_ - 2.5f;
        x1_density_ = 5.0f;
      }
    }
  }

  // a density parameter can be fixed for not conductive materials
  if (d0_density_ == 0.0f) {
    static const GGfloat kTwoln10 = 2.0f * std::log(10.0f);
    GGfloat const kXa = c_density_ / kTwoln10;
    a_density_ = kTwoln10 * (kXa - x0_density_) / std::pow((x1_density_ - x0_density_), m_density_);
 }

  // needs an 'effective Z'
  GGfloat zeff = 0.0f;

  for (GGuchar i = 0; i < kNumberOfChemicalElements; ++i) {
    GGEMSChemicalElement const& kChemicalElement = material_manager.GetChemicalElement(material_->chemical_element_name_[i]);
    zeff += (material_->mixture_f_[i] * static_cast<GGfloat>(kChemicalElement.atomic_number_Z_));
  }

  if (zeff > 2.0f) f2_fluct_ = 2.0f / zeff;
  else f2_fluct_ = 0.0f;

  f1_fluct_          = 1.0f - f2_fluct_;
  energy2_fluct_     = 10.0f * zeff * zeff * GGEMSUnits::eV;
  log_energy2_fluct_ = std::log(energy2_fluct_);
  log_energy1_fluct_ = (log_mean_excitation_energy_ - f2_fluct_ * log_energy2_fluct_) / f1_fluct_;
  energy1_fluct_     = std::exp(log_energy1_fluct_);
  energy0_fluct_     = 10.f*GGEMSUnits::eV;
}