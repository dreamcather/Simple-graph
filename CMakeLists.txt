cmake_minimum_required(VERSION 2.8.6)
project(SimpleGraph)

#
# Set configuration
#

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configurations" FORCE)
if(DEFINED CMAKE_BUILD_TYPE)
    set_property( CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES} )
endif()

if(CMAKE_GENERATOR MATCHES "Makefiles|Ninja" AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

option(COVERAGE "Build with coverage support" OFF)

#
# Setup output directories
#

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

foreach(cfg ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${cfg}" cfg)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_PDB_OUTPUT_DIRECTORY_${cfg} ${CMAKE_BINARY_DIR}/lib)
endforeach()

#
# Add compiler options: enable C++11, all warnings, fail on warnings
#

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror")
    if(COVERAGE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    endif()
endif()

#
# Include all modules
#
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/simple-graph")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/simple-graph")

#
# Cppcheck support
#

find_program(CPPCHECK_EXECUTABLE NAMES cppcheck)

#if(CPPCHECK_EXECUTABLE)
#    set(CPPCHECK_ARGS "")
#
#
#    list(APPEND CPPCHECK_ARGS "${CMAKE_CURRENT_SOURCE_DIR}/")
#
#    add_custom_target(
#        cppcheck "${CPPCHECK_EXECUTABLE}" "--enable=all" "--error-exitcode=1" ${CPPCHECK_ARGS}
#        COMMENT "Run cppcheck tool"
#        VERBATIM)
#endif()

#
# Report variables
#

message(STATUS "")
message(STATUS "General configuration for ${PROJECT_NAME}")
message(STATUS "==================================")
message(STATUS "")
message(STATUS "   Compiler:      ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "   Configuration: ${CMAKE_BUILD_TYPE}")
message(STATUS "   Coverage:      ${COVERAGE}")
# message(STATUS "   Code coverage:     ${WITH_CODE_COVERAGE}")
message(STATUS "   Detected modules:")
foreach(subdir ${SUBDIRS})
    get_filename_component(DIR_NAME ${subdir} NAME)
    message(STATUS "    - ${DIR_NAME}")
endforeach()
message(STATUS "")
