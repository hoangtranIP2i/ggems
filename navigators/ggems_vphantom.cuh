// GGEMS Copyright (C) 2015

/*!
 * \file ggems_vphantom.cuh
 * \brief
 * \author J. Bert <bert.jul@gmail.com>
 * \version 0.1
 * \date 18 novembre 2015
 *
 *
 *
 */

#ifndef GGEMS_VPHANTOM_CUH
#define GGEMS_VPHANTOM_CUH

#include "global.cuh"
#include "particles.cuh"
#include "prng.cuh"
#include "fun.cuh"
#include "materials.cuh"
#include "photon.cuh"

class GGEMSVPhantom {
    public:
        GGEMSVPhantom() {}
        ~GGEMSVPhantom() {}
        // Tracking from outside to the phantom broder
        virtual void track_to_in(ParticleStack &particles_h, ParticleStack &particles_d) = 0;
        // Photons tracking inside the phantom until the phantom border
        virtual void track_to_out_photon(ParticleStack &particles_h, ParticleStack &particles_d,
                                         MaterialsTable materials_h, MaterialsTable materials_d,
                                         PhotonCrossSectionTable photon_CS_table_h, PhotonCrossSectionTable photon_CS_table_d) = 0;
        // Photons and electrons tracking within the phantom
        virtual void track_to_out_photon_electron() = 0;
        // Init
        virtual void initialize(GlobalSimulationParameters params) = 0;
        // Get list of materials
        virtual std::vector<std::string> get_materials_list() = 0;
        // Get data that contains materials index
        virtual ui16* get_data_materials_indices() = 0;
        // Get the size of data that compose this phantom (indices)
        virtual ui32 get_data_size() = 0;

    private:

};

#endif
