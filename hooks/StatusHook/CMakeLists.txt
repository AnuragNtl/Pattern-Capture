add_library(StatusHook SHARED StatusHook.cpp)
target_link_libraries(StatusHook pthread Hooks)
