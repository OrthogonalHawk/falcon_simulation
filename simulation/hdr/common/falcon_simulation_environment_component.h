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
 * @file     falcon_simulation_environment_component.h
 * @author   OrthogonalHawk
 * @date     24-Feb-2018
 *
 * @brief    FALCON Simulation Environment component definition.
 *
 * @section  DESCRIPTION
 *
 * Defines an abstract base class for components that run within the FALCON
 *  Simulation Environment. As a base class, it serves to define the interfaces
 *  and standardizes functionality across various derived components.
 *
 * @section  HISTORY
 *
 * 24-Feb-2018  OrthogonalHawk  File created.
 *
 *****************************************************************************/

#ifndef __FALCON_SIMULATION_ENVIRONMENT_COMPONENT_H__
#define __FALCON_SIMULATION_ENVIRONMENT_COMPONENT_H__

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <stdint.h>
#include <list>
#include <memory>

/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

/******************************************************************************
 *                              ENUMS & TYPEDEFS
 *****************************************************************************/

/* forward declaration(s) */
class falcon_simulation_environment_component;

typedef uint32_t FalconComponentId;
typedef std::list<FalconComponentId> FalconComponentIdList;
typedef std::list<std::shared_ptr<falcon_simulation_environment_component>> FalconComponentList;

enum class FALCON_COMPONENT_STATUS_ENUM : uint32_t
{
    SUCCESS = 0,
    INITIALIZATION_FAILED,
    UNSUPPORTED_TIMESTEP_ADVANCE_TIME,
    UNSUPPORTED_TIMESTEP_ADVANCE_DEPENDENCY,
    UNSUPPORTED_COMPONENT_STATE,
    UNSUPPORTED_COMPONENT_STATE_TRANSITION,
    FAILURE,
    NUMBER_OF_STATUS_CODES
};

enum class FALCON_COMPONENT_STATE_ENUM : uint32_t
{
    UNINITIALIZED = 0,
    INITIALIZED,
    WAITING_FOR_TIMESTEP_ADVANCE,
    TIMESTEP_ADVANCED,
    READY_FOR_SHUTDOWN,
    SHUTDOWN_COMPLETE,
    NUMBER_OF_STATES
};

/******************************************************************************
 *                                  MACROS
 *****************************************************************************/

/******************************************************************************
 *                              CLASS DECLARATION
 *****************************************************************************/

class falcon_simulation_environment_component
{
public:

    falcon_simulation_environment_component(void);
    virtual ~falcon_simulation_environment_component(void);

    FalconComponentIdList get_initialization_dependency_ids(void);
    FalconComponentIdList get_timestep_advance_dependency_ids(void);
    FalconComponentIdList get_shutdown_dependency_ids(void);

    virtual FALCON_COMPONENT_STATUS_ENUM initialize(FalconComponentList &dependencies) = 0;
    FALCON_COMPONENT_STATUS_ENUM next_timestep_started(void);
    virtual FALCON_COMPONENT_STATUS_ENUM advance_timestep(uint32_t &current_timestep, FalconComponentList dependencies) = 0;
    virtual FALCON_COMPONENT_STATUS_ENUM shutdown(FalconComponentList &dependencies) = 0;
    virtual int32_t get_timestep_reward(void) = 0;

    FALCON_COMPONENT_STATE_ENUM get_component_state(void);

    const char * get_component_state_str(FALCON_COMPONENT_STATE_ENUM state) const;
    const char * get_component_status_str(FALCON_COMPONENT_STATUS_ENUM status_code) const;

protected:

    FALCON_COMPONENT_STATUS_ENUM set_initialization_dependencies(FalconComponentIdList &dependency_id_list);
    FALCON_COMPONENT_STATUS_ENUM set_timestep_advance_dependencies(FalconComponentIdList &dependency_id_list);
    FALCON_COMPONENT_STATUS_ENUM set_shutdown_dependencies(FalconComponentIdList &dependency_id_list);

    FALCON_COMPONENT_STATUS_ENUM transition(FALCON_COMPONENT_STATE_ENUM new_state);

private:

    FALCON_COMPONENT_STATE_ENUM    m_component_state;
    static const char *            component_state_names[static_cast<uint32_t>(FALCON_COMPONENT_STATE_ENUM::NUMBER_OF_STATES)];
    static const char *            component_status_names[static_cast<uint32_t>(FALCON_COMPONENT_STATUS_ENUM::NUMBER_OF_STATUS_CODES)];

    FalconComponentIdList          m_initialization_dependency_ids;
    FalconComponentIdList          m_timestep_advance_dependency_ids;
    FalconComponentIdList          m_shutdown_dependency_ids;
};

#endif // __FALCON_SIMULATION_ENVIRONMENT_COMPONENT_H__
