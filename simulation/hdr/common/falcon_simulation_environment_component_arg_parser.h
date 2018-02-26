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
 * @file     falcon_simulation_environment_component_arg_parser.h
 * @author   OrthogonalHawk
 * @date     25-Feb-2018
 *
 * @brief    Basic command-line argument parser for FALCON simulation
 *            environment components.
 *
 * @section  DESCRIPTION
 *
 * Defines a basic command-line argument parsing class for FALCON simulation
 *  environment components. Handles arguments common to all components and
 *  provides hooks for a further derived class to handle component-specific
 *  arguments.
 *
 * @section  HISTORY
 *
 * 25-Feb-2018  OrthogonalHawk  File created.
 *
 *****************************************************************************/

#ifndef __FALCON_SIMULATION_ENVIRONMENT_COMPONENT_ARG_PARSER_H__
#define __FALCON_SIMULATION_ENVIRONMENT_COMPONENT_ARG_PARSER_H__

/******************************************************************************
 *                               INCLUDE_FILES
 *****************************************************************************/

#include <string>

#include "falcon_arg_parser.h"

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
 *                              CLASS DECLARATION
 *****************************************************************************/

class falcon_simulation_environment_component_arg_parser : falcon_arg_parser
{
public:

    falcon_simulation_environment_component_arg_parser(void);
    virtual ~falcon_simulation_environment_component_arg_parser(void);

    uint64_t get_simulation_duration_in_secs(void);

protected:

    bool derived_class_parse(std::string &option, std::string &value) override;
    std::string get_derived_class_usage(void) override;

private:

    uint64_t    m_duration;;
};

#endif // __FALCON_SIMULATION_ENVIRONMENT_COMPONENT_ARG_PARSER_H__
