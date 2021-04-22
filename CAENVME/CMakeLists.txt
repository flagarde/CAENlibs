project(CAENVME VERSION 3.2.0 DESCRIPTION "CAEN VME library" HOMEPAGE_URL "https://www.caen.it/products/caenvmelib-library/" LANGUAGES NONE)

if(WIN32)
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Windows/${ARCH}")
  set(OUTPUT_DEFINITIONS WIN32)
else()
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Unix/${ARCH}")
  set(OUTPUT_DEFINITIONS LINUX)
endif()

add_custom_target(COPY_CAENVME)
if(WIN32)
  add_custom_command(TARGET COPY_CAENVME 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENVMELib.lib" "${CMAKE_INSTALL_FULL_LIBDIR}/CAENVMELib.lib" 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENVMElib.dll" "${CMAKE_INSTALL_FULL_BINDIR}/CAENVMElib.dll"
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/PlxApi.dll" "${CMAKE_INSTALL_FULL_BINDIR}/PlxApi.dll" 
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/CAENVMELib.lib;${CMAKE_INSTALL_FULL_BINDIR}/CAENVMElib.dll;${CMAKE_INSTALL_FULL_BINDIR}/PlxApi.dll")
else()
  add_custom_command(TARGET COPY_CAENVME 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/libCAENVME.so" "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENVME.so" 
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENVME.so")
endif()

add_library(__CAENVME INTERFACE)
add_dependencies(__CAENVME COPY_CAENVME)
target_include_directories(__CAENVME INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/CAEN>)
if(WIN32)
  target_link_libraries(__CAENVME INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/CAENVMELib.lib")
else()
  target_link_libraries(__CAENVME INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENVME.so")
endif()
set_target_properties(__CAENVME PROPERTIES PUBLIC_HEADER "include/CAENVMEoslib.h;include/CAENVMEtypes.h;include/CAENVMElib.h")
target_compile_definitions(__CAENVME INTERFACE ${OUTPUT_DEFINITIONS})
install(TARGETS __CAENVME)

add_library(CAENVME::CAENVME ALIAS __CAENVME)






