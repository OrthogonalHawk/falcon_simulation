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
 * @file     falcon_simulation_environment_component.cc
 * @author   OrthogonalHawk
 * @date     24-Feb-2018
 *
 * @brief    FALCON Simulation Environment component implementation.
 *
 * @section  DESCRIPTION
 *
 * Implements part of an abstract base class for components that run within the
 *  FALCON Simulation Environment. As a base class, it serves to define the
 *  interfaces and standardizes functionality across various derived components.
 *
 * @section  HISTORY
 *
 * 24-Feb-2018  OrthogonalHawk  File created.
 *
 *****************************************************************************/

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include "falcon_log.h"

#include "common/falcon_simulation_environment_component.h"

/******************************************************************************
 *                                 CONSTANTS
 *****************************************************************************/

/******************************************************************************
 *                              ENUMS & TYPEDEFS
 *****************************************************************************/

/******************************************************************************
 *                                  MACROS
 *****************************************************************************/

/******************************************************************************
 *                            CLASS IMPLEMENTATION
 *****************************************************************************/

/* must be kept in sync with FALCON_COMPONENT_STATE_ENUM */
const char * falcon_simulation_environment_component::component_state_names[static_cast<uint32_t>(FALCON_COMPONENT_STATE_ENUM::NUMBER_OF_STATES)] =
{
    "UNINITIALIZED",
    "INITIALIZED",
    "WAITING_FOR_TIMESTEP_ADVANCE",
    "TIMESTEP_ADVANCED",
    "READY_FOR_SHUTDOWN",
    "SHUTDOWN_COMPLETE"
};

/* must be kept in sync with FALCON_COMPONENT_STATUS_ENUM */
const char * falcon_simulation_environment_component::component_status_names[static_cast<uint32_t>(FALCON_COMPONENT_STATUS_ENUM::NUMBER_OF_STATUS_CODES)] =
{
    "SUCCESS",
    "INITIALIZATION_FAILED",
    "UNSUPPORTED_TIMESTEP_ADVANCE_TIME",
    "UNSUPPORTED_TIMESTEP_ADVANCE_DEPENDENCY",
    "UNSUPPORTED_COMPONENT_STATE",
    "UNSUPPORTED_COMPONENT_STATE_TRANSITION",
    "FAILURE"
};

falcon_simulation_environment_component::falcon_simulation_environment_component(void)
  : m_component_state(FALCON_COMPONENT_STATE_ENUM::UNINITIALIZED)
{
    /* no action required at this time */
}

falcon_simulation_environment_component::~falcon_simulation_environment_component(void)
{
    /* no action required at this time */
}

FalconComponentIdList falcon_simulation_environment_component::get_initialization_dependency_ids(void)
{
    return m_initialization_dependency_ids;
}

FalconComponentIdList falcon_simulation_environment_component::get_timestep_advance_dependency_ids(void)
{
    return m_timestep_advance_dependency_ids;
}

FalconComponentIdList falcon_simulation_environment_component::get_shutdown_dependency_ids(void)
{
    return m_shutdown_dependency_ids;
}

/*
 * @brief  Invoked by external manager to indicate that the next timestep is starting
 */
FALCON_COMPONENT_STATUS_ENUM falcon_simulation_environment_component::next_timestep_started(void)
{
    return transition(FALCON_COMPONENT_STATE_ENUM::WAITING_FOR_TIMESTEP_ADVANCE);
}

FALCON_COMPONENT_STATE_ENUM falcon_simulation_environment_component::get_component_state(void)
{
    return m_component_state;
}

const char * falcon_simulation_environment_component::get_component_state_str(FALCON_COMPONENT_STATE_ENUM state) const
{
    /* assumes that UNINITIALIZED is the first valid state */
    if (state >= FALCON_COMPONENT_STATE_ENUM::UNINITIALIZED &&
        state <  FALCON_COMPONENT_STATE_ENUM::NUMBER_OF_STATES)
    {
        return component_status_names[static_cast<uint32_t>(state)];
    }

    return nullptr;
}

const char * falcon_simulation_environment_component::get_component_status_str(FALCON_COMPONENT_STATUS_ENUM status_code) const
{
    /* assumes that SUCCESS is the first valid status */
    if (status_code >= FALCON_COMPONENT_STATUS_ENUM::SUCCESS &&
        status_code <  FALCON_COMPONENT_STATUS_ENUM::NUMBER_OF_STATUS_CODES)
    {
        return component_status_names[static_cast<uint32_t>(status_code)];
    }

    return nullptr;
}

FALCON_COMPONENT_STATUS_ENUM falcon_simulation_environment_component::set_initialization_dependencies(FalconComponentIdList &dependency_id_list)
{
    m_initialization_dependency_ids = dependency_id_list;
    return FALCON_COMPONENT_STATUS_ENUM::SUCCESS;
}

FALCON_COMPONENT_STATUS_ENUM falcon_simulation_environment_component::set_timestep_advance_dependencies(FalconComponentIdList &dependency_id_list)
{
    m_timestep_advance_dependency_ids = dependency_id_list;
    return FALCON_COMPONENT_STATUS_ENUM::SUCCESS;
}

FALCON_COMPONENT_STATUS_ENUM falcon_simulation_environment_component::set_shutdown_dependencies(FalconComponentIdList &dependency_id_list)
{
    m_shutdown_dependency_ids = dependency_id_list;
    return FALCON_COMPONENT_STATUS_ENUM::SUCCESS;
}

FALCON_COMPONENT_STATUS_ENUM falcon_simulation_environment_component::transition(FALCON_COMPONENT_STATE_ENUM new_state)
{
    FALCON_COMPONENT_STATUS_ENUM ret = FALCON_COMPONENT_STATUS_ENUM::SUCCESS;

    if (m_component_state != FALCON_COMPONENT_STATE_ENUM::SHUTDOWN_COMPLETE)
    {
        switch (new_state)
        {
        case FALCON_COMPONENT_STATE_ENUM::INITIALIZED:
        case FALCON_COMPONENT_STATE_ENUM::WAITING_FOR_TIMESTEP_ADVANCE:
        case FALCON_COMPONENT_STATE_ENUM::TIMESTEP_ADVANCED:
        case FALCON_COMPONENT_STATE_ENUM::READY_FOR_SHUTDOWN:
        case FALCON_COMPONENT_STATE_ENUM::SHUTDOWN_COMPLETE:
            break;

        case FALCON_COMPONENT_STATE_ENUM::UNINITIALIZED:
        default:
            ret = FALCON_COMPONENT_STATUS_ENUM::UNSUPPORTED_COMPONENT_STATE;
            break;
        }
    }
    else
    {
        /* once the SHUTDOWN_COMPLETE state has been entered it cannot be left */
        ret = FALCON_COMPONENT_STATUS_ENUM::UNSUPPORTED_COMPONENT_STATE_TRANSITION;
    }

    if (ret == FALCON_COMPONENT_STATUS_ENUM::SUCCESS)
    {
        m_component_state = new_state;
    }

    return ret;
}
