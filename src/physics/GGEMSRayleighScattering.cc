/*!
  \file GGEMSRayleighScattering.cc

  \brief Rayleigh scattering process using Livermore model

  \author Julien BERT <julien.bert@univ-brest.fr>
  \author Didier BENOIT <didier.benoit@inserm.fr>
  \author LaTIM, INSERM - U1101, Brest, FRANCE
  \version 1.0
  \date Tuesday April 14, 2020
*/

#include "GGEMS/materials/GGEMSMaterials.hh"
#include "GGEMS/maths/GGEMSMathAlgorithms.hh"
#include "GGEMS/physics/GGEMSRayleighScattering.hh"
#include "GGEMS/physics/GGEMSParticleCrossSectionsStack.hh"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GGEMSRayleighScattering::GGEMSRayleighScattering(std::string const& primary_particle, bool const& is_secondary)
: GGEMSEMProcess()
{
  GGcout("GGEMSRayleighScattering", "GGEMSRayleighScattering", 3) << "Allocation of GGEMSRayleighScattering..." << GGendl;

  process_name_ = "Rayleigh";

  // Check type of primary particle
  if (primary_particle != "gamma") {
    std::ostringstream oss(std::ostringstream::out);
    oss << "For Rayleigh scattering, incident particle has to be a 'gamma'";
    GGEMSMisc::ThrowException("GGEMSRayleighScattering", "GGEMSRayleighScattering", oss.str());
  }

  // Checking secondaries
  if (is_secondary == true) {
    GGwarn("GGEMSRayleighScattering", "GGEMSRayleighScattering", 0) << "There is no secondary during Rayleigh process!!! Secondary flag set to false" << GGendl;
  }

  process_id_ = RAYLEIGH_SCATTERING;
  primary_particle_ = "gamma";
  is_secondaries_ = false;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GGEMSRayleighScattering::~GGEMSRayleighScattering(void)
{
  GGcout("GGEMSRayleighScattering", "~GGEMSRayleighScattering", 3) << "Deallocation of GGEMSRayleighScattering..." << GGendl;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

GGfloat GGEMSRayleighScattering::ComputeCrossSectionPerAtom(GGfloat const& energy, GGuchar const& atomic_number) const
{
  // Energy in range [250 eV; 100 GeV]
  if (energy < 250e-6f || energy > 100e3f) return 0.0f;

  GGuint const kStart = GGEMSRayleighTable::kCrossSectionCumulativeIntervals[atomic_number];
  GGuint const kStop = kStart + 2 * (GGEMSRayleighTable::kCrossSectionNumberOfIntervals[atomic_number]-1);

  GGuint pos = kStart;
  for (; pos < kStop; pos += 2) {
    if (GGEMSRayleighTable::kCrossSection[pos] >= static_cast<GGfloat>(energy)) break;
  }

  if (energy < 1e3f) { // 1 GeV
    return static_cast<GGfloat>(1.0e-22 * LogLogInterpolation(
      energy,
      static_cast<GGfloat>(GGEMSRayleighTable::kCrossSection[pos-2]), static_cast<GGfloat>(GGEMSRayleighTable::kCrossSection[pos-1]),
      static_cast<GGfloat>(GGEMSRayleighTable::kCrossSection[pos]), static_cast<GGfloat>(GGEMSRayleighTable::kCrossSection[pos+1])));
  }
  else {
    return static_cast<GGfloat>(1.0e-22 * GGEMSRayleighTable::kCrossSection[pos-1]);
  }
}
