set(Sources
        PathPlanning.cpp
        Path.cpp
        PathLeft.cpp
        PathRight.cpp
        PathEmpty.cpp
        utils.cpp
        )

add_library(${PROJECT_NAME} ${Sources})