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
#include(GetCMakeMM)
   
#cmmm(VERSION "main" REPOSITORY "flagarde/CMakeMM" PROVIDER "gitlab" VERBOSITY VERBOSE DESTINATION "CMakeMM")

#cmmm_modules_list(REPOSITORY "flagarde/CMakeCM" PROVIDER "gitlab" DESTINATION "Modules" BRANCH "main")

#include(CPM)
#cpm()

#if(NOT DEFINED SYSTEMDETECT_REPOSITORY)
#  set(SYSTEMDETECT_REPOSITORY "https://github.com/flagarde/SystemDetect")
#endif()

#if(NOT DEFINED SYSTEMDETECT_VERSION)
#  set(SYSTEMDETECT_VERSION "v0.9")
#endif()

#declare_option(REPOSITORY SystemDetect OPTION BUILD_EXAMPLES VALUE OFF)
#declare_option(REPOSITORY SystemDetect OPTION BUILD_TESTS VALUE OFF)
#print_options(REPOSITORY  SystemDetect)

#CPMAddPackage(NAME SystemDetect
#              GIT_REPOSITORY ${SYSTEMDETECT_REPOSITORY}
#              GIT_TAG ${SYSTEMDETECT_VERSION}
#              FETCHCONTENT_UPDATES_DISCONNECTED ${IS_OFFLINE}
#              OPTIONS "${SystemDetect_OPTIONS}")

set(CMAKE_MACOSX_RPATH TRUE)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
#link_directories("${CMAKE_INSTALL_FULL_LIBDIR}")

add_subdirectory(CAENVME)

add_subdirectory(CAENComm)

add_subdirectory(CAENHV)

add_subdirectory(CAENDigitizer)

add_subdirectory(CAENDPP)

if(BUILD_TESTS)
  include(CTest)
  add_subdirectory(tests)
endif()
