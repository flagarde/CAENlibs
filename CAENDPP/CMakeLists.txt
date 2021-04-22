if(WIN32)
  set(CAENDPP_VERSION "1.9.1")
else()
  set(CAENDPP_VERSION "1.7.2")
endif()

project(CAENDPP VERSION ${CAENDPP_VERSION} DESCRIPTION "CAEN DPP Library" HOMEPAGE_URL "https://www.caen.it/products/caendpp-library/" LANGUAGES NONE)

if(WIN32)
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Windows/${ARCH}")
else()
  set(LIBRARY_PATH "${CMAKE_CURRENT_SOURCE_DIR}/lib/Unix/${ARCH}")
endif()

add_custom_target(COPY_CAENDPP)
if(WIN32)
  add_custom_command(TARGET COPY_CAENDPP 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/CAENDPPLib.lib" "${CMAKE_INSTALL_FULL_LIBDIR}/CAENDPPLib.lib" 
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/CAENDPPLib.lib")
else()
  add_custom_command(TARGET COPY_CAENDPP 
                     COMMAND ${CMAKE_COMMAND} -E copy "${LIBRARY_PATH}/libCAENDPPLib.so" "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENDPPLib.so" 
                     BYPRODUCTS "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENDPPLib.so")
endif()

add_library(__CAENDPP INTERFACE)
add_dependencies(__CAENDPP COPY_CAENDPP)
target_include_directories(__CAENDPP INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/CAEN>)
if(WIN32)
  target_link_libraries(__CAENDPP INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/CAENDPPLib.lib" INTERFACE CAENComm::CAENComm)
else()
  target_compile_definitions(__CAENDPP INTERFACE "UNIX")
  target_link_libraries(__CAENDPP INTERFACE "${CMAKE_INSTALL_FULL_LIBDIR}/libCAENDPPLib.so" INTERFACE CAENComm::CAENComm)
endif()
set_target_properties(__CAENDPP PROPERTIES PUBLIC_HEADER "include/CAENDPPLibTypes.h;include/CAENDPPLib.h")
install(TARGETS __CAENDPP PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/CAEN")

add_library(CAENDPP::CAENDPP ALIAS __CAENDPP)
