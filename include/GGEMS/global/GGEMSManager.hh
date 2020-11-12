#ifndef GUARD_GGEMS_GLOBAL_GGEMSMANAGER_HH
#define GUARD_GGEMS_GLOBAL_GGEMSMANAGER_HH

// ************************************************************************
// * This file is part of GGEMS.                                          *
// *                                                                      *
// * GGEMS is free software: you can redistribute it and/or modify        *
// * it under the terms of the GNU General Public License as published by *
// * the Free Software Foundation, either version 3 of the License, or    *
// * (at your option) any later version.                                  *
// *                                                                      *
// * GGEMS is distributed in the hope that it will be useful,             *
// * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
// * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
// * GNU General Public License for more details.                         *
// *                                                                      *
// * You should have received a copy of the GNU General Public License    *
// * along with GGEMS.  If not, see <https://www.gnu.org/licenses/>.      *
// *                                                                      *
// ************************************************************************

/*!
  \file GGEMSManager.hh

  \brief GGEMS class managing the GGEMS simulation

  \author Julien BERT <julien.bert@univ-brest.fr>
  \author Didier BENOIT <didier.benoit@inserm.fr>
  \author LaTIM, INSERM - U1101, Brest, FRANCE
  \version 1.0
  \date Monday September 30, 2019
*/

#ifdef _MSC_VER
#pragma warning(disable: 4251) // Deleting warning exporting STL members!!!
#endif

#include <cstdint>
#include <string>
#include <vector>

#include "GGEMS/global/GGEMSExport.hh"

#include "GGEMS/tools/GGEMSTypes.hh"

/*!
  \class GGEMSManager
  \brief GGEMS class managing the complete simulation
*/
class GGEMS_EXPORT GGEMSManager
{
  private:
    /*!
      \brief Unable the constructor for the user
    */
    GGEMSManager(void);

    /*!
      \brief Unable the destructor for the user
    */
    ~GGEMSManager(void);

  public:
    /*!
      \fn static GGEMSManager& GetInstance(void)
      \brief Create at first time the Singleton
      \return Object of type GGEMSManager
    */
    static GGEMSManager& GetInstance(void)
    {
      static GGEMSManager instance;
      return instance;
    }

    /*!
      \fn GGEMSManager(GGEMSManager const& ggems_manager) = delete
      \param ggems_manager - reference on the ggems manager
      \brief Avoid copy of the class by reference
    */
    GGEMSManager(GGEMSManager const& ggems_manager) = delete;

    /*!
      \fn GGEMSManager& operator=(GGEMSManager const& ggems_manager) = delete
      \param ggems_manager - reference on the ggems manager
      \brief Avoid assignement of the class by reference
    */
    GGEMSManager& operator=(GGEMSManager const& ggems_manager) = delete;

    /*!
      \fn GGEMSManager(GGEMSManager const&& ggems_manager) = delete
      \param ggems_manager - rvalue reference on the ggems manager
      \brief Avoid copy of the class by rvalue reference
    */
    GGEMSManager(GGEMSManager const&& ggems_manager) = delete;

    /*!
      \fn GGEMSManager& operator=(GGEMSManager const&& ggems_manager) = delete
      \param ggems_manager - rvalue reference on the ggems manager
      \brief Avoid copy of the class by rvalue reference
    */
    GGEMSManager& operator=(GGEMSManager const&& ggems_manager) = delete;

    /*!
      \fn void Initialize(void)
      \brief Initialization of the GGEMS simulation and check parameters
    */
    void Initialize(void);

    /*!
      \fn void Run(void)
      \brief run the GGEMS simulation
    */
    void Run(void);

    /*!
      \fn void SetSeed(GGuint const& seed)
      \param seed - seed for the random generator
      \brief Set the seed of random for the simulation
    */
    void SetSeed(GGuint const& seed);

    /*!
      \fn inline GGuint GetSeed(void) const
      \return the seed given by the user or generated by GGEMS
      \brief Get the general seed for the simulation
    */
    inline GGuint GetSeed(void) const {return seed_;};

    /*!
      \fn void SetOpenCLVerbose(bool const& is_opencl_verbose)
      \param is_opencl_verbose - flag for opencl verbosity
      \brief set the flag for OpenCL verbosity
    */
    void SetOpenCLVerbose(bool const& is_opencl_verbose);

    /*!
      \fn void SetMaterialDatabaseVerbose(bool const& is_material_database_verbose)
      \param is_material_database_verbose - flag for material database verbosity
      \brief set the flag for material database verbosity
    */
    void SetMaterialDatabaseVerbose(bool const& is_material_database_verbose);

    /*!
      \fn void SetSourceVerbose(bool const& is_source_verbose)
      \param is_source_verbose - flag for source verbosity
      \brief set the flag for source verbosity
    */
    void SetSourceVerbose(bool const& is_source_verbose);

    /*!
      \fn void SetNavigatorVerbose(bool const is_navigator_verbose)
      \param is_navigator_verbose - flag for navigator verbosity
      \brief set the flag for navigator verbosity
    */
    void SetNavigatorVerbose(bool const& is_navigator_verbose);

    /*!
      \fn void SetMemoryRAMVerbose(bool const& is_memory_ram_verbose)
      \param is_memory_ram_verbose - flag for memory RAM verbosity
      \brief set the flag for memory RAM verbosity
    */
    void SetMemoryRAMVerbose(bool const& is_memory_ram_verbose);

    /*!
      \fn void SetProcessVerbose(bool const& is_process_verbose)
      \param is_process_verbose - flag for process verbosity
      \brief set the flag for process verbosity
    */
    void SetProcessVerbose(bool const& is_process_verbose);

    /*!
      \fn void SetRangeCutsVerbose(bool const& is_range_cuts_verbose)
      \param is_range_cuts_verbose - flag for range cuts verbosity
      \brief set the flag for range cuts verbosity
    */
    void SetRangeCutsVerbose(bool const& is_range_cuts_verbose);

    /*!
      \fn void SetRandomVerbose(bool const& is_random_verbose)
      \param is_random_verbose - flag for random verbosity
      \brief set the flag for random verbosity
    */
    void SetRandomVerbose(bool const& is_random_verbose);

    /*!
      \fn void SetKernelVerbose(bool const& is_kernel_verbose)
      \param is_kernel_verbose - flag for kernel timer verbosity
      \brief set the flag for kernel timer verbosity
    */
    void SetKernelVerbose(bool const& is_kernel_verbose);

    /*!
      \fn bool IsKernelVerbose(void) const
      \return state of kernel verbosity flag
      \brief get the kernel verbosity flag
    */
    inline bool IsKernelVerbose(void) const {return is_kernel_verbose_;};

    /*!
      \fn void SetTrackingVerbose(bool const& is_tracking_verbose, GGint const& particle_tracking_id)
      \param is_tracking_verbose - flag for tracking verbosity
      \param particle_tracking_id - particle id for tracking
      \brief set the flag for tracking verbosity and an index for particle tracking
    */
    void SetTrackingVerbose(bool const& is_tracking_verbose, GGint const& particle_tracking_id);

    /*!
      \fn bool IsTrackingVerbose(void) const
      \return state of tracking verbosity flag
      \brief get the tracking verbosity flag
    */
    inline bool IsTrackingVerbose(void) const {return is_tracking_verbose_;};

    /*!
      \fn GGint GetParticleTrackingID(void) const
      \return id of the particle to track
      \brief get the id of the particle to track
    */
    inline GGint GetParticleTrackingID(void) const {return particle_tracking_id_;};

  private:
    /*!
      \fn void PrintBanner(void) const
      \brief Print GGEMS banner
    */
    void PrintBanner(void) const;

    /*!
      \fn void CheckParameters(void)
      \brief check the mandatory parameters for the GGEMS simulation
    */
    void CheckParameters(void);

    /*!
      \fn GGuint GenerateSeed(void) const
      \return the seed computed by GGEMS
      \brief generate a seed by GGEMS and return it
    */
    GGuint GenerateSeed(void) const;

  private: // Global simulation parameters
    GGuint seed_; /*!< Seed for the random generator */
    bool is_opencl_verbose_; /*!< Flag for OpenCL verbosity */
    bool is_material_database_verbose_; /*!< Flag for material database verbosity */
    bool is_source_verbose_; /*!< Flag for source verbosity */
    bool is_navigator_verbose_; /*!< Flag for navigator verbosity */
    bool is_memory_ram_verbose_; /*!< Flag for memory RAM verbosity */
    bool is_process_verbose_; /*!< Flag for processes verbosity */
    bool is_range_cuts_verbose_; /*!< Flag for range cuts verbosity */
    bool is_random_verbose_; /*!< Flag for random verbosity */
    bool is_tracking_verbose_; /*!< Flag for tracking verbosity */
    bool is_kernel_verbose_; /*!< Flag for kernel time verbosity */
    GGint particle_tracking_id_; /*!< Particle if for tracking */
};

/*!
  \fn GGEMSManager* get_instance_ggems_manager(void)
  \return the pointer on the singleton
  \brief Get the GGEMSManager pointer for python user.
*/
extern "C" GGEMS_EXPORT GGEMSManager* get_instance_ggems_manager(void);

/*!
  \fn void set_seed_ggems_manager(GGEMSManager* ggems_manager, GGuint const seed)
  \param ggems_manager - pointer on the singleton
  \param seed - seed given by the user
  \brief Set the seed for the simulation
*/
extern "C" void GGEMS_EXPORT set_seed_ggems_manager(GGEMSManager* ggems_manager, GGuint const seed);

/*!
  \fn void initialize_ggems_manager(GGEMSManager* ggems_manager)
  \param ggems_manager - pointer on the singleton
  \brief Initialize GGEMS simulation
*/
extern "C" GGEMS_EXPORT void initialize_ggems_manager(GGEMSManager* ggems_manager);

/*!
  \fn void set_opencl_verbose_ggems_manager(GGEMSManager* ggems_manager, bool const is_opencl_verbose)
  \param ggems_manager - pointer on the singleton
  \param is_opencl_verbose - flag on opencl verbose
  \brief Set the OpenCL verbosity
*/
extern "C" GGEMS_EXPORT void set_opencl_verbose_ggems_manager(GGEMSManager* ggems_manager, bool const is_opencl_verbose);

/*!
  \fn void set_material_database_verbose_ggems_manager(GGEMSManager* ggems_manager, bool const is_material_database_verbose)
  \param ggems_manager - pointer on the singleton
  \param is_material_database_verbose - flag on material database verbose
  \brief Set the material database verbosity
*/
extern "C" GGEMS_EXPORT void set_material_database_verbose_ggems_manager(GGEMSManager* ggems_manager, bool const is_material_database_verbose);

/*!
  \fn void set_source_ggems_manager(GGEMSManager* ggems_manager, bool const is_source_verbose)
  \param ggems_manager - pointer on the singleton
  \param is_source_verbose - flag on source verbose
  \brief Set the source verbosity
*/
extern "C" GGEMS_EXPORT void set_source_ggems_manager(GGEMSManager* ggems_manager, bool const is_source_verbose);

/*!
  \fn void set_navigator_ggems_manager(GGEMSManager* ggems_manager, bool const is_navigator_verbose)
  \param ggems_manager - pointer on the singleton
  \param is_phantom_verbose - flag on navigator verbose
  \brief Set the navigator verbosity
*/
extern "C" GGEMS_EXPORT void set_navigator_ggems_manager(GGEMSManager* ggems_manager, bool const is_navigator_verbose);

/*!
  \fn void set_memory_ram_ggems_manager(GGEMSManager* ggems_manager, bool const is_memory_ram_verbose)
  \param ggems_manager - pointer on the singleton
  \param is_memory_ram_verbose - flag on memory RAM verbose
  \brief Set the memory RAM verbosity
*/
extern "C" GGEMS_EXPORT void set_memory_ram_ggems_manager(GGEMSManager* ggems_manager, bool const is_memory_ram_verbose);

/*!
  \fn void set_process_ggems_manager(GGEMSManager* ggems_manager, bool const is_process_verbose)
  \param ggems_manager - pointer on the singleton
  \param is_process_verbose - flag on processes verbose
  \brief Set the processes verbosity
*/
extern "C" GGEMS_EXPORT void set_process_ggems_manager(GGEMSManager* ggems_manager, bool const is_process_verbose);

/*!
  \fn void set_range_cuts_ggems_manager(GGEMSManager* ggems_manager, bool const is_range_cuts_verbose)
  \param ggems_manager - pointer on the singleton
  \param is_range_cuts_verbose - flag on range cuts verbose
  \brief Set the range cuts verbosity
*/
extern "C" GGEMS_EXPORT void set_range_cuts_ggems_manager(GGEMSManager* ggems_manager, bool const is_range_cuts_verbose);

/*!
  \fn void set_random_ggems_manager(GGEMSManager* ggems_manager, bool const is_random_verbose)
  \param ggems_manager - pointer on the singleton
  \param is_random_verbose - flag on random verbose
  \brief Set the random verbosity
*/
extern "C" GGEMS_EXPORT void set_random_ggems_manager(GGEMSManager* ggems_manager, bool const is_random_verbose);

/*!
  \fn void set_random_ggems_manager(GGEMSManager* ggems_manager, bool const is_kernel_verbose)
  \param ggems_manager - pointer on the singleton
  \param is_kernel_verbose - flag on kernel timer verbose
  \brief Set the kernel timer verbosity
*/
extern "C" GGEMS_EXPORT void set_kernel_ggems_manager(GGEMSManager* ggems_manager, bool const is_kernel_verbose);

/*!
  \fn void set_tracking_ggems_manager(GGEMSManager* ggems_manager, bool const is_tracking_verbose, GGint const particle_id_tracking)
  \param ggems_manager - pointer on the singleton
  \param is_tracking_verbose - flag on tracking verbose
  \param particle_id_tracking - particle id for tracking
  \brief Set the tracking verbosity
*/
extern "C" GGEMS_EXPORT void set_tracking_ggems_manager(GGEMSManager* ggems_manager, bool const is_tracking_verbose, GGint const particle_id_tracking);

/*!
  \fn void run_ggems_manager(GGEMSManager* ggems_manager)
  \param ggems_manager - pointer on the singleton
  \brief Run the GGEMS simulation
*/
extern "C" GGEMS_EXPORT void run_ggems_manager(GGEMSManager* ggems_manager);

#endif // End of GUARD_GGEMS_GLOBAL_GGEMSMANAGER_HH
