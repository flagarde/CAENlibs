project(CAENComm VERSION 1.4.1 DESCRIPTION "CAEN Comm Library" HOMEPAGE_URL "https://www.caen.it/products/caencomm-library/" LANGUAGES NONE)

if(WIN32)
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Windows/${ARCH}")
else()
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Unix/${ARCH}")
endif()

add_custom_target(COPY_CAENComm)
if(WIN32)
  add_custom_command(TARGET COPY_CAENComm 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENComm.lib" "${CMAKE_INSTALL_FULL_LIBDIR}/CAENComm.lib" 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENComm.dll" "${CMAKE_INSTALL_FULL_BINDIR}/CAENComm.dll"
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/CAENComm.lib;${CMAKE_INSTALL_FULL_BINDIR}/CAENComm.dll")
else()
  add_custom_command(TARGET COPY_CAENComm 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/libCAENComm.so" "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENComm.so" 
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENComm.so")
endif()

add_library(__CAENComm INTERFACE)
add_dependencies(__CAENComm COPY_CAENComm)
target_include_directories(__CAENComm INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/CAEN>)
if(WIN32)
  target_link_libraries(__CAENComm INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/CAENComm.lib" INTERFACE CAENVME::CAENVME)
else()
  target_link_libraries(__CAENComm INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENComm.so" INTERFACE CAENVME::CAENVME)
endif()
set_target_properties(__CAENComm PROPERTIES PUBLIC_HEADER "include/CAENComm.h")
add_library(CAENComm::CAENComm ALIAS __CAENComm)
install(TARGETS __CAENComm EXPORT CAENCommTargets PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/CAEN")
install(EXPORT CAENCommTargets
  FILE CAENCommTargets.cmake
  NAMESPACE CAENComm::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CAENlibs)
