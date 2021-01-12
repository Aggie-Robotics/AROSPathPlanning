set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        PathBottom.cpp
        PathTop.cpp
        utils.cpp
        )

add_library(${BINARY}_lib ${SOURCES})