cmake_minimum_required(VERSION 3.16)

set(This PathTests)

set(Sources
        path_test.cpp
        utils_test.cpp
        )

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
        gtest_main
        ${PROJECT_NAME}
        )

add_test(
        NAME ${This}
        COMMAND ${This}
)
