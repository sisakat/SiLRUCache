cmake_minimum_required(VERSION 3.5)

project(SiLruCache VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    silrucache.cpp
    silrucache.h
    test.cpp
    external/catch2/catch_amalgamated.cpp
)

add_executable(SiLruCache ${PROJECT_SOURCES})
target_include_directories(SiLruCache PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    external)

include(GNUInstallDirs)
install(TARGETS SiLruCache
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

