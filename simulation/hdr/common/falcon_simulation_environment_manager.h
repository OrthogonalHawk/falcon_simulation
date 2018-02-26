/******************************************************************************
 *
 * MIT License
 *
 * Copyright (c) 2018 OrthogonalHawk
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * @file     falcon_simulation_environment_manager.h
 * @author   OrthogonalHawk
 * @date     25-Feb-2018
 *
 * @brief    FALCON Simulation Environment manager definition.
 *
 * @section  DESCRIPTION
 *
 * Defines an FALCON simulation environment manager class that coordinates
 *  component interaction while a simulation is executing.
 *
 * @section  HISTORY
 *
 * 25-Feb-2018  OrthogonalHawk  File created.
 *
 *****************************************************************************/

#ifndef __FALCON_SIMULATION_ENVIRONMENT_MANAGER_H__
#define __FALCON_SIMULATION_ENVIRONMENT_MANAGER_H__

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <stdint.h>
#include <list>
#include <memory>

#include "common/falcon_simulation_environment_component.h"

/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

/******************************************************************************
 *                              ENUMS & TYPEDEFS
 *****************************************************************************/

enum class FALCON_MANAGER_STATUS_ENUM : uint32_t
{
    SUCCESS = 0,
    INITIALIZATION_FAILED,
    UNSUPPORTED_TIMESTEP_ADVANCE_TIME,
    NUMBER_OF_STATUS_CODES
};

enum class FALCON_MANAGER_STATE_ENUM : uint32_t
{
    UNINITIALIZED = 0,
    INITIALIZED,
    RUNNING_SIMULATION,
    SHUTDOWN_COMPLETE,
    NUMBER_OF_STATES
};

/******************************************************************************
 *                                  MACROS
 *****************************************************************************/

/******************************************************************************
 *                              CLASS DECLARATION
 *****************************************************************************/

class falcon_simulation_environment_manager
{
public:

    falcon_simulation_environment_manager(void);
    virtual ~falcon_simulation_environment_manager(void);

    FALCON_MANAGER_STATUS_ENUM initialize(int argc, char ** pArgv);
    FALCON_MANAGER_STATUS_ENUM run_simulation(void);
    FALCON_MANAGER_STATUS_ENUM shutdown(void);

    FALCON_MANAGER_STATE_ENUM get_manager_state(void);

    const char * get_manager_state_str(FALCON_MANAGER_STATE_ENUM state) const;
    const char * get_manager_status_str(FALCON_MANAGER_STATUS_ENUM status_code) const;

private:

    FALCON_MANAGER_STATUS_ENUM transition(FALCON_COMPONENT_STATE_ENUM new_state);

    FALCON_MANAGER_STATE_ENUM      m_manager_state;
    static const char *            manager_state_names[static_cast<uint32_t>(FALCON_MANAGER_STATE_ENUM::NUMBER_OF_STATES)];
    static const char *            manager_status_names[static_cast<uint32_t>(FALCON_MANAGER_STATUS_ENUM::NUMBER_OF_STATUS_CODES)];

    FalconComponentList            m_active_components;
};

#endif // __FALCON_SIMULATION_ENVIRONMENT_MANAGER_H__
