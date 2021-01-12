cmake_minimum_required(VERSION 3.16)
project(AROSPathPlanning)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_subdirectory(src)

if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    add_subdirectory(lib/googletest)
    add_subdirectory(tests)
endif()

set(Headers
        include/utils.hpp
)

set(Sources
        src/utils.cpp
)
add_library(${PROJECT_NAME} ${Sources} ${Headers})
target_include_directories(${PROJECT_NAME} PUBLIC include)