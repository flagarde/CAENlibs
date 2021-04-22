project(CAENDigitizer VERSION 2.16.2 DESCRIPTION "CAEN Digitizer Library" HOMEPAGE_URL "https://www.caen.it/products/caendigitizer-library/" LANGUAGES NONE)

if(WIN32)
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Windows/${ARCH}")
else()
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Unix/${ARCH}")
endif()

add_custom_target(COPY_CAENDigitizer)
if(WIN32)
  add_custom_command(TARGET COPY_CAENDigitizer 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENDigitizer.lib" "${CMAKE_INSTALL_FULL_LIBDIR}/CAENDigitizer.lib" 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENDigitizer.dll" "${CMAKE_INSTALL_FULL_BINDIR}/CAENDigitizer.dll"
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/CAENDigitizer.lib;${CMAKE_INSTALL_FULL_BINDIR}/CAENDigitizer.dll")
else()
  add_custom_command(TARGET COPY_CAENDigitizer 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/libCAENDigitizer.so" "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENDigitizer.so" 
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENDigitizer.so")
endif()

add_library(__CAENDigitizer INTERFACE)
add_dependencies(__CAENDigitizer COPY_CAENDigitizer)
target_include_directories(__CAENDigitizer INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/CAEN>)
if(WIN32)
  target_link_libraries(__CAENDigitizer INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/CAENDigitizer.lib" INTERFACE CAENComm::CAENComm)
else()
  target_link_libraries(__CAENDigitizer INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENDigitizer.so" INTERFACE CAENComm::CAENComm)
endif()
set_target_properties(__CAENDigitizer PROPERTIES PUBLIC_HEADER "include/CAENDigitizerType.h;include/CAENDigitizer.h")
install(TARGETS __CAENDigitizer)

add_library(CAENDigitizer::CAENDigitizer ALIAS __CAENDigitizer)
