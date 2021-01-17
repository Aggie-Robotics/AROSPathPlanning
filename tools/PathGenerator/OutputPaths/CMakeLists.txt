file(GLOB route_data
        "*.txt")


foreach (df ${route_data})
    file(COPY ${df} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach ()