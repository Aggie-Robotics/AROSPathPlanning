cmake_minimum_required(VERSION 3.16)
project(AROSPathPlanning)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_subdirectory(src)
#add_subdirectory(tools/PathGenerator/OutputPaths)

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    add_subdirectory(lib/googletest)
    add_subdirectory(tests)
endif()

file(GLOB route_data
        "gen_path*.txt")


foreach (df ${route_data})
    file(COPY ${df} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()