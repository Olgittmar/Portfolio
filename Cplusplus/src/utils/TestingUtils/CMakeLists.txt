target_sources(Utils
    PRIVATE
        MyTestCase.cpp
    PUBLIC
        MyTestCase.h
)

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_LIST_DIR})