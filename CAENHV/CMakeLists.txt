if(WIN32 OR MSYS)
  set(CAENHV_VERSION "6.0")
else()
  set(CAENHV_VERSION "6.04")
endif()

project(CAENHV VERSION ${CAENHV_VERSION} DESCRIPTION "CAEN HV Wrapper Library" HOMEPAGE_URL "https://www.caen.it/products/caen-hv-wrapper-library/" LANGUAGES NONE)

if(WIN32 OR MSYS)
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Windows/${ARCH}")
else()
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Unix/${ARCH}")
endif()

add_custom_target(COPY_CAENHV)
if(WIN32 OR MSYS)
  file(MAKE_DIRECTORY "${CMAKE_INSTALL_FULL_LIBDIR}")
  add_custom_command(TARGET COPY_CAENHV 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENHVWrapper.lib" "${CMAKE_INSTALL_FULL_LIBDIR}/CAENHVWrapper.lib" 
                    COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENHVWrapper.dll" "${CMAKE_INSTALL_FULL_BINDIR}/CAENHVWrapper.dll" 
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/CAENHVWrapper.lib")
else()
  add_custom_command(TARGET COPY_CAENHV 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/libcaenhvwrapper.so" "${CMAKE_INSTALL_FULL_LIBDIR}/libcaenhvwrapper.so" 
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/libcaenhvwrapper.so")
endif()

add_library(CAENHV INTERFACE)
add_dependencies(CAENHV COPY_CAENHV)
target_include_directories(CAENHV INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/CAEN>)
if(WIN32 OR MSYS)
  if(MSYS)
    target_compile_definitions(CAENHV INTERFACE "MSYS")
  else()
    target_compile_definitions(CAENHV INTERFACE "WIN32")
  endif()
  target_link_libraries(CAENHV INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/CAENHVWrapper.lib" INTERFACE CAENComm::CAENComm)
else()
  target_compile_definitions(CAENHV INTERFACE "UNIX")
  target_link_libraries(CAENHV INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/libcaenhvwrapper.so" INTERFACE CAENComm::CAENComm)
endif()
set_target_properties(CAENHV PROPERTIES PUBLIC_HEADER "include/CAENHVWrapper.h")
add_library(CAENHV::CAENHV ALIAS CAENHV)

install(TARGETS CAENHV EXPORT CAENHVTargets PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/CAEN")
install(EXPORT CAENHVTargets
        FILE CAENHVTargets.cmake
        NAMESPACE CAENHV::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CAENlibs)
