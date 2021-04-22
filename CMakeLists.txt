#########################################################
#            CMakeLists.txt to build CAENlibs           #
#                @author LAGARDE Francois               #
#########################################################

cmake_minimum_required(VERSION 3.15)

project(CAENlibs VERSION "1.0.0.0" DESCRIPTION "CAEN libraries" HOMEPAGE_URL "https://www.caen.it/subfamilies/software-libraries/" LANGUAGES C CXX)

include(GNUInstallDirs)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(detect-arch)

option(BUILD_TESTS "Build the tests" ON)

set(CMAKE_MACOSX_RPATH TRUE)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_subdirectory(CAENVME)

add_subdirectory(CAENComm)

add_subdirectory(CAENHV)

add_subdirectory(CAENDigitizer)

add_subdirectory(CAENDPP)

if(BUILD_TESTS)
  include(CTest)
  add_subdirectory(tests)
endif()
