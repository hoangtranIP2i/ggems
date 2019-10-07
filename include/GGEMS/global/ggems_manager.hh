#ifndef GUARD_GGEMS_GLOBAL_GGEMSMANAGER_HH
#define GUARD_GGEMS_GLOBAL_GGEMSMANAGER_HH

/*!
  \file ggems_manager.hh

  \brief GGEMS class managing the complete simulation

  \author Julien BERT <julien.bert@univ-brest.fr>
  \author Didier BENOIT <didier.benoit@inserm.fr>
  \author LaTIM, INSERM - U1101, Brest, FRANCE
  \version 1.0
  \date Monday September 30, 2019
*/

#include <cstdint>
#include <string>
#include <vector>

#include "GGEMS/global/ggems_export.hh"

class Particle;

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

  private:
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

  public:
    /*!
      \fn void Initialize()
      \brief Initialization of the GGEMS simulation and check parameters
    */
    void Initialize();

  private:
    /*!
      \fn void CheckParameters()
      \brief check the mandatory parameters for the GGEMS simulation
    */
    void CheckParameters();

  public: // Seed
    /*!
      \fn void SetSeed(uint32_t const& seed)
      \param seed - seed for the random generator
      \brief Set the seed of random for the simulation
    */
    void SetSeed(uint32_t const& seed);

    /*!
      \fn inline uint32_t GetSeed() const
      \return the seed given by the user or generated by GGEMS
      \brief Get the general seed for the simulation
    */
    inline uint32_t GetSeed() const {return seed_;};

  private:
    /*!
      \fn uint32_t GenerateSeed() const
      \return the seed computed by GGEMS
      \brief generate a seed by GGEMS and return it
    */
    uint32_t GenerateSeed() const;

  public:
    /*!
      \fn inline std::string GetVersion() const
      \brief Get the version of GGEMS
    */
    inline std::string GetVersion() const {return version_;};

  public: // Particles
    /*!
      \fn void SetNumberOfParticles(uint64_t const& number_of_particles)
      \param number_of_particles - number of particles to simulate
      \brief Set the number of particles to simulate during the simulation
    */
    void SetNumberOfParticles(uint64_t const& number_of_particles);

    /*!
      \fn inline uint64_t GetNumberOfParticles() const
      \brief Get the number of simulated particles
      \return the number of simulated particles
    */
    inline uint64_t GetNumberOfParticles() const {return number_of_particles_;};

    /*!
      \fn inline uint64_t GetNumberOfParticlesInFirstBatch() const
      \brief Get the number of particles in the first batch
      \return the number of particles in the first batch
    */
    inline uint64_t GetNumberOfParticlesInFirstBatch() const
    {
      return v_number_of_particles_in_batch_.front();
    }

    /*!
      \fn void SetNumberOfBatchs(uint32_t const& number_of_batchs)
      \param number_of_batchs - number of batch of particles
      \brief Set the number of batchs of particles
    */
    void SetNumberOfBatchs(uint32_t const& number_of_batchs);

    /*!
      \fn inline uint32_t GetNumberOfBatchs() const
      \brief Get the number of particles in batch
      \return the number of simulated particles in batch
    */
    inline uint32_t GetNumberOfBatchs() const
    {
      return static_cast<uint32_t>(v_number_of_particles_in_batch_.size());
    }

  public:
    /*!
      \fn void SetProcess(char const* process_name)
      \param process_name - name of the process to activate
      \brief activate a specific process
    */
    void SetProcess(char const* process_name);

    /*!
      \fn void SetParticleCut(char const* particle_name, double const& distance)
      \param particle_name - Name of the particle
      \param distance - Cut in distance
      \brief Set the cut in distance for a specific particle
    */
    void SetParticleCut(char const* particle_name, double const& distance);

    /*!
      \fn void SetParticleSecondary(char const* particle_name, uint32_t const& level)
      \param particle_name - Name of the particle
      \param level - Level of the secondary particle
      \brief set the particle to activate to follow the secondaries with a specific level
    */
    void SetParticleSecondaryAndLevel(char const* particle_name,
      uint32_t const& level);

    /*!
      \fn void SetGeometryTolerance(double const& distance)
      \param distance - geometry distance
      \brief Set the geometry tolerance in distance
    */
    void SetGeometryTolerance(double const& distance);

  private:
    /*!
      \fn void ComputeNumberOfParticlesInBatch
      \brief Compute the number of particles in batch
    */
    void ComputeNumberOfParticlesInBatch();

  public: // Cross section part
    /*!
      \fn void SetCrossSectionTableNumberOfBins(uint32_t const& number_of_bins)
      \param number_of_bins - Number of bins in the cross section table
      \brief set the number of bins in the cross section table
    */
    void SetCrossSectionTableNumberOfBins(uint32_t const& number_of_bins);

    /*!
      \fn void SetCrossSectionTableEnergyMin(double const& min_energy)
      \param min_energy - Min. energy in the cross section table
      \brief set min. energy in the cross section table
    */
    void SetCrossSectionTableEnergyMin(double const& min_energy);

    /*!
      \fn void SetCrossSectionTableEnergyMax(double const& max_energy)
      \param max_energy - Max. energy in the cross section table
      \brief set max. energy in the cross section table
    */
    void SetCrossSectionTableEnergyMax(double const& max_energy);

  private:
    /*!
      \fn void PrintInfos() const
      \brief print infos about the GGEMS simulation
    */
    void PrintInfos() const;

  private: // Global simulation parameters
    uint32_t seed_; /*!< Seed for the random generator */
    std::string version_; /*!< Version of GGEMS */
    uint64_t number_of_particles_; /*!< Number of particles */
    std::vector<uint64_t> v_number_of_particles_in_batch_; /*!< Number of particles in batch */
    std::vector<bool> v_physics_list_; /*!< Vector storing the activated physics list */
    std::vector<bool> v_secondaries_list_; /*!< Vector storing the secondaries list */
    double photon_distance_cut_; /*!< Photon distance cut */
    double electron_distance_cut_; /*!< Electron distance cut */
    double geometry_tolerance_; /*!< Geometry tolerance */
    uint32_t photon_level_secondaries_; /*!< Level of the secondaries */
    uint32_t electron_level_secondaries_; /*!< Level of the secondaries */
    uint32_t cross_section_table_number_of_bins_; /*!< Number of bins in the cross section table */
    double cross_section_table_energy_min_; /*!< Min. energy for the cross section table */
    double cross_section_table_energy_max_; /*!< Max. energy for the cross section table */

  private: // Particles management
    Particle* p_particle_; /*!< Pointer on particle management */
};

/*!
  \fn GGEMSManager* get_instance_ggems_manager(void)
  \brief Get the GGEMSManager pointer for python user.
*/
extern "C" GGEMS_EXPORT GGEMSManager* get_instance_ggems_manager(void);

/*!
  \fn void set_seed(GGEMSManager* ggems_manager, uint32_t const seed)
  \param ggems_manager - pointer on the singleton
  \param seed - seed given by the user
  \brief Set the seed for the simulation
*/
extern "C" GGEMS_EXPORT void set_seed(GGEMSManager* ggems_manager,
  uint32_t const seed);

/*!
  \fn void initialize_simulation(GGEMSManager* ggems_manager)
  \param ggems_manager - pointer on the singleton
  \brief Initialize GGEMS simulation
*/
extern "C" GGEMS_EXPORT void initialize_simulation(GGEMSManager* ggems_manager);

/*!
  \fn void set_number_of_particles(GGEMSManager* ggems_manager, uint64_t const number_of_particles)
  \param ggems_manager - pointer on the singleton
  \param number_of_particles - number of particles
  \brief Set the number of particles to simulate during the simulation
*/
extern "C" GGEMS_EXPORT void set_number_of_particles(
  GGEMSManager* ggems_manager, uint64_t const number_of_particles);

/*!
  \fn void set_number_of_batchs(GGEMSManager* ggems_manager, uint32_t const number_of_particles_in_batch)
  \param ggems_manager - pointer on the singleton
  \param number_of_particles_in_batch - number of particles in batch
  \brief Set the number of particles to simulate by batch
*/
extern "C" GGEMS_EXPORT void set_number_of_batchs(GGEMSManager* ggems_manager,
  uint32_t const number_of_batchs);

/*!
  \fn void set_process(GGEMSManager* ggems_manager, std::string const process_name)
  \param ggems_manager - pointer on the singleton
  \param process_name - name of the process to activate
  \brief activate a specific process
*/
extern "C" GGEMS_EXPORT void set_process(GGEMSManager* ggems_manager,
  char const* process_name);

/*!
  \fn void set_particle_cut(GGEMSManager* ggems_manager, char const* particle_name, double const distance)
  \param ggems_manager - pointer on the singleton
  \param particle_name - name of the particle
  \param distance - cut in distance for the particle
  \brief set a cut in distance for a specific particle
*/
extern "C" GGEMS_EXPORT void set_particle_cut(GGEMSManager* ggems_manager,
  char const* particle_name, double const distance);

/*!
  \fn void set_geometry_tolerance(GGEMSManager* ggems_manager, double const distance)
  \param ggems_manager - pointer on the singleton
  \param distance - geometry distance tolerance
  \brief set the geometry distance tolerance
*/
extern "C" GGEMS_EXPORT void set_geometry_tolerance(GGEMSManager* ggems_manager,
  double const distance);

/*!
  \fn void set_secondary_particle_and_level(GGEMSManager* ggems_manager, char const* particle_name, uint32_t const level)
  \param ggems_manager - pointer on the singleton
  \param particle_name - name of the particle
  \param level - level of the secondary
  \brief set the particle to follow secondary and set the level
*/
extern "C" GGEMS_EXPORT void set_secondary_particle_and_level(
  GGEMSManager* ggems_manager, char const* particle_name, uint32_t const level);

/*!
  \fn void set_cross_section_table_number_of_bins(GGEMSManager* ggems_manager, uint32_t const number_of_bins)
  \param ggems_manager - pointer on the singleton
  \param number_of_bins - number of the bins in the cross section table
  \brief set the number of bins in the cross section table
*/
extern "C" GGEMS_EXPORT void set_cross_section_table_number_of_bins(
  GGEMSManager* ggems_manager, uint32_t const number_of_bins);

/*!
  \fn void set_cross_section_table_energy_min(GGEMSManager* ggems_manager, double const min_energy)
  \param ggems_manager - pointer on the singleton
  \param min_energy - min. energy in the cross section table
  \brief set the min. energy in the cross section table
*/
extern "C" GGEMS_EXPORT void set_cross_section_table_energy_min(
  GGEMSManager* ggems_manager, double const min_energy);

/*!
  \fn void set_cross_section_table_energy_max(GGEMSManager* ggems_manager, double const min_energy)
  \param ggems_manager - pointer on the singleton
  \param max_energy - max. energy in the cross section table
  \brief set the max. energy in the cross section table
*/
extern "C" GGEMS_EXPORT void set_cross_section_table_energy_max(
  GGEMSManager* ggems_manager, double const max_energy);

#endif // End of GUARD_GGEMS_GLOBAL_GGEMSMANAGER_HH