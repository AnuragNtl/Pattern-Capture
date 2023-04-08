add_library(UdpRelay SHARED UdpRelay.cpp)
target_link_libraries(UdpRelay boost_system Hooks)

