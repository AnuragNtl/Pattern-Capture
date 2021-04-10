add_library(HttpRelay SHARED HttpRelay.cpp)
target_link_libraries(HttpRelay pthread Hooks boost_system boost_regex)

