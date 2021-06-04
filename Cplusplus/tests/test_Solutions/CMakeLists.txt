message(STATUS "Generating tests for Solutions library...")
target_sources(test_all PUBLIC
    test_PointInPolygon.cpp
)
message(STATUS "Finished generating tests for Solutions lib.")