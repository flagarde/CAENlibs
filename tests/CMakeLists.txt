add_executable(CAENVME CAENVME.cpp)
target_link_libraries(CAENVME PRIVATE CAENVME::CAENVME)
install(TARGETS CAENVME)
