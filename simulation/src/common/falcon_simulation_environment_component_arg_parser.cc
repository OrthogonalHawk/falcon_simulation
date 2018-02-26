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
 * @file     falcon_arg_parser.cc
 * @author   OrthogonalHawk
 * @date     25-Feb-2018
 *
 * @brief    Basic command-line argument parser for FALCON simulation
 *            environment components.
 *
 * @section  DESCRIPTION
 *
 * Implements a basic command-line argument parsing class for FALCON simulation
 *  environment components. Handles arguments common to all components and
 *  provides hooks for a further derived class to handle component-specific
 *  arguments.
 *
 * @section  HISTORY
 *
 * 25-Feb-2018  OrthogonalHawk  File created.
 *
 *****************************************************************************/

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <iostream>
#include <sstream>
#include <stdint.h>
#include <stdlib.h>

#include "common/falcon_simulation_environment_component_arg_parser.h"

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

/*
 * @brief  Class constructor
 */
falcon_simulation_environment_component_arg_parser::falcon_simulation_environment_component_arg_parser(void)
  : m_duration(0)
{
    /* no action needed */
}

/*
 * @brief  Class destructor
 */
falcon_simulation_environment_component_arg_parser::~falcon_simulation_environment_component_arg_parser(void)
{
    /* no action needed */
}

/*
 * @brief Provides access to the simulation duration
 *
 * @return Simulation duration in seconds
 */
uint64_t falcon_simulation_environment_component_arg_parser::get_simulation_duration_in_secs(void)
{
    return m_duration;
}

/*
 * @brief  Handle application-specific arguments
 *
 * @param  option The option argument to parse.
 * @param  value  The corresponding option value
 *
 * @return True if the argument was parsed/handled; false otherwise.
 */
bool falcon_simulation_environment_component_arg_parser::derived_class_parse(std::string &option, std::string &value)
{
    bool ret = false;

    /* arguments are split by the base class into the option and value
     *  parameters. use these directly to handle command-line arguments */
    if (option == "-d" || option == "--duration")
    {
        int64_t tmp_duration = strtol(value.c_str(), nullptr, 10);
        if (tmp_duration >= 0)
        {
            m_duration = tmp_duration;
            ret = true;
        }
    }

    return ret;
}

/*
 * @brief  Contribute to the 'help' output
 *
 * @return Usage information as a preformatted string
 */
std::string falcon_simulation_environment_component_arg_parser::get_derived_class_usage(void)
{
    std::stringstream ret;

    ret << "  -d,--duration" << std::endl;
    ret << "                       simulation duration in seconds" << std::endl;
    ret << std::endl;

    return ret.str();
}
