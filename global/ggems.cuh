// GGEMS Copyright (C) 2015

/*!
 * \file ggems.cuh
 * \brief Main header of GGEMS lib
 * \author J. Bert <bert.jul@gmail.com>
 * \version 0.1
 * \date 13 novembre 2015
 *
 * Header of the main GGEMS lib
 *
 */

#ifndef GGEMS_CUH
#define GGEMS_CUH

#include "global.cuh"
#include "ggems_source.cuh"
#include "ggems_phantom.cuh"
#include "particles.cuh"
#include "cross_sections.cuh"
#include "materials.cuh"

#include "testing.cuh"

#include "ggems_detector.cuh"
#include "ct_detector.cuh"

#include "point_source.cuh"
#include "cone_beam_CT_source.cuh"
#include "geom_source.cuh"
#include "phasespace_source.cuh"
#include "beamlet_source.cuh"
#include "linac_source.cuh"

#include "mesh_phan_linac_nav.cuh"
#include "vox_phan_dosi_nav.cuh"
#include "vox_phan_img_nav.cuh"
#include "vox_phan_iort_nav.cuh"
#include "vox_phan_gtrack_nav.cuh"

class GGEMS
{
public:
    GGEMS();
    ~GGEMS();

    // Setting parameters    
    void set_hardware_target ( std::string value );
    void set_GPU_ID ( ui32 valid );
    void set_GPU_block_size ( ui32 val );
    void set_process ( std::string process_name );
    void set_secondary ( std::string pname );
    void set_particle_cut ( std::string pname, f32 E );

    void set_number_of_particles ( ui64 nb );
    void set_size_of_particles_batch ( ui64 nb );

    void set_CS_table_nbins ( ui32 valbin );
    void set_CS_table_E_min ( f32 valE );
    void set_CS_table_E_max ( f32 valE );
    void set_electron_cut ( f32 valE );
    void set_photon_cut ( f32 valE );
    void set_secondaries_level ( ui32 level );
    void set_geometry_tolerance ( f32 tolerance );

    void set_seed ( ui32 vseed );

    // Setting simulation objects
    void set_source ( GGEMSSource* aSource );
    void set_phantom ( GGEMSPhantom* aPhantom );
    void set_detector( GGEMSDetector* aDetector );

    // Utils
    void set_display_run_time( bool flag );
    void set_display_memory_usage( bool flag );
    void set_display_in_color( bool flag );
    void set_display_energy_cuts( bool flag );
    void set_verbose( bool flag );
    void print_stack( ui32 n );

    // Main functions
    void init_simulation();
    void start_simulation();

private:
    // Particles handler
    ParticleManager m_particles_manager;

    // Source manager
    GGEMSSource* m_source;

    // Phantom manager
    GGEMSPhantom* m_phantom;
    std::vector< GGEMSPhantom* > m_phantoms;

    // TODO Detector manager
    GGEMSDetector* m_detector;

    // Main parameters
    bool m_check_mandatory();    
    void m_copy_parameters_cpu2gpu();
    GlobalSimulationParameters m_parameters;
    bool m_flag_init;    

};



#endif
