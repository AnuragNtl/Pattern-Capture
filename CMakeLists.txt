cmake_minimum_required(VERSION 3.10)

project(PatternCapture VERSION 1.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(
    ${CMAKE_SOURCE_DIR}
    )

add_library(CommonUtils SHARED CommonUtils.cpp)

add_subdirectory(googletest)

add_subdirectory(yaml-cpp)


add_executable(PatternCapture Dependencies.cpp PatternCapture.cpp core/engine/graphparser/GraphParser.cpp core/engine/graphparser/JsonGraphParser/JsonGraphParser.cpp core/engine/graphparser/YamlGraphParser/YamlGraphParser.cpp core/scheduler/Scheduler.cpp core/scheduler/SchedulerFactory.cpp core/scheduler/ContinuousScheduler.cpp core/scheduler/OnceScheduler.cpp core/scheduler/CronScheduler.cpp core/engine/graphparser/GraphParserFactory.cpp core/engine/hooks/Hooks.cpp core/scheduler/HookServer.cpp ccronexpr/ccronexpr.c)


target_link_libraries(PatternCapture boost_system boost_filesystem dl pthread CommonUtils yaml-cpp)

target_link_libraries(CommonUtils boost_system boost_filesystem pthread)

target_include_directories(PatternCapture PUBLIC "${PROJECT_BINARY_DIR}" )

add_library(Hooks SHARED core/engine/hooks/Hooks.cpp core/engine/graphparser/GraphParser.cpp)

add_subdirectory(Capture)

add_subdirectory(common)

add_subdirectory(hooks)

add_subdirectory(transform)



