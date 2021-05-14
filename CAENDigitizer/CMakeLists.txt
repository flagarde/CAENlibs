project(CAENDigitizer VERSION 2.16.2 DESCRIPTION "CAEN Digitizer Library" HOMEPAGE_URL "https://www.caen.it/products/caendigitizer-library/" LANGUAGES NONE)

if(WIN32 OR MSYS)
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Windows/${ARCH}")
else()
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Unix/${ARCH}")
endif()

add_custom_target(COPY_CAENDigitizer)
if(WIN32 OR MSYS)
  file(MAKE_DIRECTORY "${CMAKE_INSTALL_FULL_LIBDIR}")
  add_custom_command(TARGET COPY_CAENDigitizer 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENDigitizer.lib" "${CMAKE_INSTALL_FULL_LIBDIR}/CAENDigitizer.lib" 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENDigitizer.dll" "${CMAKE_INSTALL_FULL_BINDIR}/CAENDigitizer.dll"
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/CAENDigitizer.lib;${CMAKE_INSTALL_FULL_BINDIR}/CAENDigitizer.dll")
else()
  add_custom_command(TARGET COPY_CAENDigitizer 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/libCAENDigitizer.so" "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENDigitizer.so" 
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENDigitizer.so")
endif()

add_library(CAENDigitizer INTERFACE)
add_dependencies(CAENDigitizer COPY_CAENDigitizer)
target_include_directories(CAENDigitizer INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/CAEN>)
if(WIN32 OR MSYS)
  target_link_libraries(CAENDigitizer INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/CAENDigitizer.lib" INTERFACE CAENComm::CAENComm)
else()
  target_link_libraries(CAENDigitizer INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENDigitizer.so" INTERFACE CAENComm::CAENComm)
endif()
set_target_properties(CAENDigitizer PROPERTIES PUBLIC_HEADER "include/CAENDigitizerType.h;include/CAENDigitizer.h")
add_library(CAENDigitizer::CAENDigitizer ALIAS CAENDigitizer)

install(TARGETS CAENDigitizer EXPORT CAENDigitizerTargets PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/CAEN")
install(EXPORT CAENDigitizerTargets
        FILE CAENDigitizerTargets.cmake
        NAMESPACE CAENDigitizer::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CAENlibs)
