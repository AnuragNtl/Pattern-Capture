add_library(CommandLine SHARED CommandLine.cpp)
target_link_libraries(CommandLine boost_system pthread)

