#ifndef GUARD_GGEMS_SYSTEMS_GGEMSCTSYSTEM_HH
#define GUARD_GGEMS_SYSTEMS_GGEMSCTSYSTEM_HH

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
  \file GGEMSCTSystem.hh

  \brief Child GGEMS class managing CT/CBCT detector in GGEMS

  \author Julien BERT <julien.bert@univ-brest.fr>
  \author Didier BENOIT <didier.benoit@inserm.fr>
  \author LaTIM, INSERM - U1101, Brest, FRANCE
  \date Monday October 19, 2020
*/

#include <string>
#include <memory>

#include "GGEMS/global/GGEMSExport.hh"
#include "GGEMS/tools/GGEMSTypes.hh"
#include "GGEMS/navigators/GGEMSSystem.hh"

/*!
  \class GGEMSCTSystem
  \brief Child GGEMS class managing CT/CBCT detector in GGEMS
*/
class GGEMS_EXPORT GGEMSCTSystem : public GGEMSSystem
{
  public:
    /*!
      \param ct_system_name - name of the CT system
      \brief GGEMSCTSystem constructor
    */
    explicit GGEMSCTSystem(std::string const& ct_system_name);

    /*!
      \brief GGEMSCTSystem destructor
    */
    ~GGEMSCTSystem(void);

    /*!
      \fn GGEMSCTSystem(GGEMSCTSystem const& ct_system_name) = delete
      \param ct_system_name - reference on the GGEMS ct system name
      \brief Avoid copy by reference
    */
    GGEMSCTSystem(GGEMSCTSystem const& ct_system_name) = delete;

    /*!
      \fn GGEMSCTSystem& operator=(GGEMSCTSystem const& ct_system_name) = delete
      \param ct_system_name - reference on the GGEMS ct system name
      \brief Avoid assignement by reference
    */
    GGEMSCTSystem& operator=(GGEMSCTSystem const& ct_system_name) = delete;

    /*!
      \fn GGEMSCTSystem(GGEMSCTSystem const&& ct_system_name) = delete
      \param ct_system_name - rvalue reference on the GGEMS ct system name
      \brief Avoid copy by rvalue reference
    */
    GGEMSCTSystem(GGEMSCTSystem const&& ct_system_name) = delete;

    /*!
      \fn GGEMSCTSystem& operator=(GGEMSCTSystem const&& ct_system_name) = delete
      \param ct_system_name - rvalue reference on the GGEMS ct system name
      \brief Avoid copy by rvalue reference
    */
    GGEMSCTSystem& operator=(GGEMSCTSystem const&& ct_system_name) = delete;

  private:
    std::string ct_scanner_type_; /*!< Type of CT scanner, here: flat or curved */
};

/*!
  \fn GGEMSPhantom* create_ggems_ct_system(char const* ct_system_name)
  \param ct_system_name - name of ct system
  \return the pointer on the ct system
  \brief Get the GGEMSCTSystem pointer for python user.
*/
extern "C" GGEMS_EXPORT GGEMSCTSystem* create_ggems_ct_system(char const* ct_system_name);

/*!
  \fn void set_number_of_modules_ggems_ct_system(GGEMSCTSystem* ct_system, GGuint const module_x, GGuint const module_y)
  \param ct_system - pointer on voxelized phantom
  \param module_x - Number of module in X (local axis of detector)
  \param module_y - Number of module in Y (local axis of detector)
  \brief set the number of module in X, Y of local axis of detector
*/
extern "C" GGEMS_EXPORT void set_number_of_modules_ggems_ct_system(GGEMSCTSystem* ct_system, GGuint const module_x, GGuint const module_y);

#endif // End of GUARD_GGEMS_SYSTEMS_GGEMSSYSTEM_HH