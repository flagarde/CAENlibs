add_executable(CAENVME CAENVME.cpp)
target_link_libraries(CAENVME PRIVATE CAENVME::CAENVME)
install(TARGETS CAENVME)

add_executable(CAENComm CAENComm.cpp)
target_link_libraries(CAENComm PRIVATE CAENComm::CAENComm)
install(TARGETS CAENComm)
