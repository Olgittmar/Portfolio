message(STATUS "Generating tests for StringUtils component...")
target_sources(test_all PUBLIC
    test_StringUtils.cpp
)
message(STATUS "Finished generating tests for StringUtils.")