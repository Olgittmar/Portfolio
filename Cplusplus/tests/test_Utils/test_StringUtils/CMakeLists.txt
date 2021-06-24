message(STATUS "Generating tests for StringUtils component...")

add_executable(testStringUtilsExe test_StringUtils.cpp)
add_test(NAME test_string_utils COMMAND testStringUtilsExe)
target_link_libraries(testStringUtilsExe
  PUBLIC
    Qt6::Test
  PRIVATE
    CPlusPlus::Utils
)

message(STATUS "Finished generating tests for StringUtils.")