#########################################################
#            CMakeLists.txt to build CAENlibs           #
#                @author LAGARDE Francois               #
#########################################################

cmake_minimum_required(VERSION 3.15)

project(CAENlibs VERSION "1.0.0.0" DESCRIPTION "CAEN libraries" HOMEPAGE_URL "https://www.caen.it/subfamilies/software-libraries/" LANGUAGES C CXX)

if(APPLE)
  string(ASCII 27 Esc)
  message(WARNING "${Esc}[1;33m## MacOS is not suported by CAENlibs ##${Esc}[m")
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/dumb.c" "int main(){}")
  add_library(dump STATIC "${CMAKE_CURRENT_BINARY_DIR}/dumb.c")
  install(TARGETS dump ARCHIVE DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
  return()
endif()

include(GNUInstallDirs)
include(InstallRequiredSystemLibraries)
set(CMAKE_INSTALL_UCRT_LIBRARIES TRUE)
include(CMakePackageConfigHelpers)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(detect-arch)

option(BUILD_TESTS "Build the tests" ON)

add_subdirectory(CAENVME)

add_subdirectory(CAENComm)

add_subdirectory(CAENHV)

add_subdirectory(CAENDigitizer)

add_subdirectory(CAENDPP)

if(BUILD_TESTS)
  include(CTest)
  add_subdirectory(tests)
endif()

find_package(LibUSB)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CAENlibsConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/CAENlibsConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CAENlibs)
  
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/CAENlibsConfigVersion.cmake"
  VERSION "${CAENlibs_VERSION}"
  COMPATIBILITY AnyNewerVersion
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/CAENlibsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/CAENlibsConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CAENlibs)
