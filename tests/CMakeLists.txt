add_executable(CAENVME CAENVME.cpp)
target_link_libraries(CAENVME PRIVATE CAENVME::CAENVME)
install(TARGETS CAENVME)
add_test(NAME CAENVME COMMAND CAENVME)

add_executable(CAENComm CAENComm.cpp)
target_link_libraries(CAENComm PRIVATE CAENComm::CAENComm)
install(TARGETS CAENComm)
add_test(NAME CAENComm COMMAND CAENComm)

add_executable(CAENDigitizer CAENDigitizer.cpp)
target_link_libraries(CAENDigitizer PRIVATE CAENDigitizer::CAENDigitizer)
install(TARGETS CAENDigitizer)
add_test(NAME CAENDigitizer COMMAND CAENDigitizer)

add_executable(CAENHV CAENHV.cpp)
target_link_libraries(CAENHV PRIVATE CAENHV::CAENHV)
install(TARGETS CAENHV)
add_test(NAME CAENHV COMMAND CAENHV)

add_executable(CAENDPP CAENDPP.cpp)
target_link_libraries(CAENDPP PRIVATE CAENDPP::CAENDPP)
install(TARGETS CAENDPP)
add_test(NAME CAENDPP COMMAND CAENDPP)
