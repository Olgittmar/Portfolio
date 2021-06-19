message(STATUS "Generating UserInterface...")
add_library(UserInterface STATIC)

target_include_directories(UserInterface PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/MyApp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow
    ${CMAKE_INSTALL_PREFIX}/include
    ${CMAKE_PREFIX_PATH}
)

target_link_directories(UserInterface PUBLIC
    ${CMAKE_PREFIX_PATH}
    ${CMAKE_INSTALL_PREFIX}/lib
)

target_sources(UserInterface
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/MyApp/MyApp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow/MainWindow.h
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow/MainWindow.ui
        ${CMAKE_CURRENT_SOURCE_DIR}/MyApp/MyApp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow/MainWindow.cpp
)

target_link_libraries(UserInterface
    Qt6::Core
    Qt6::Widgets
)

install(TARGETS UserInterface
    EXPORT UserInterfaceTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)
add_library(CPlusPlus::UserInterface ALIAS UserInterface)

message(STATUS "Finished generating UserInterface!")