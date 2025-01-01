cmake_minimum_required(VERSION 4.0)
project(demo)

set(CMAKE_CXX_STANDARD 20)

add_executable(demo
        main.cpp
)

include(FetchContent)

FetchContent_Declare(
        SVGDiagram
        # GIT_REPOSITORY https://github.com/CyberZHG/SVGDiagram.git
        GIT_REPOSITORY git@github.com:CyberZHG/SVGDiagram.git
        GIT_TAG v1.0.0
)

FetchContent_MakeAvailable(SVGDiagram)

target_link_libraries(demo PRIVATE SVGDiagram)