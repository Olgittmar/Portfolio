target_sources(Utils
    PRIVATE
        StringUtils.cpp
    PUBLIC
        StringUtils.h
)

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_LIST_DIR})