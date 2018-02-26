###############################################################################
# Makefile for the FALCON Simulation Environment
#
#     See ../falcon_makefiles/Makefile.apps for usage
#
###############################################################################

FALCON_PATH = $(PWD)/../submods/

PLATFORM_BUILD=1
export PLATFORM_BUILD

###############################################################################
# EXECUTABLE
###############################################################################

EXE=bin/falcon_simulation

###############################################################################
# SOURCES
###############################################################################

CC_SOURCES = \
    src/common/falcon_simulation_environment_component.cc \
    src/common/falcon_simulation_environment_component_arg_parser.cc \
    src/falcon_simulation_main.cc \
    
FALCON_LIBS = \
    falcon_log \
    falcon_utilities \

###############################################################################
# Include ../../falcon_makefiles/Makefile.apps for rules
###############################################################################

include $(FALCON_PATH)falcon_makefiles/Makefile.apps

###############################################################################
# Adjust *FLAGS and paths as necessary
###############################################################################

CPPFLAGS += -DBOOST_LOG_DYN_LINK
CPPFLAGS += -std=c++11

LIBS += -lboost_log_setup -lboost_log
