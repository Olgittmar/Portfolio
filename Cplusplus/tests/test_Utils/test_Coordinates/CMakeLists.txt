message(STATUS "Generating tests for Coordinates component...")
target_sources(test_all PUBLIC
    test_Point.cpp
    test_Line.cpp
    test_Polygon.cpp
)
message(STATUS "Finished generating tests for Coordinates.")