cmake_minimum_required(VERSION 4.0)
project(SVGDiagram)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SVG_DIAGRAM_ENABLE_PANGO_CAIRO "Enable PangoCairo for computing SVG text sizes" OFF)
option(SVG_DIAGRAM_ENABLE_TESTS "Build tests" OFF)
option(SVG_DIAGRAM_ENABLE_STRICT "Use strict compile options" OFF)
option(SVG_DIAGRAM_ENABLE_COVERAGE "Enable coverage reporting" OFF)

if(APPLE)
    set(ENV{PKG_CONFIG_PATH} "/opt/homebrew/lib/pkgconfig:$ENV{PKG_CONFIG_PATH}")
endif()

if(SVG_DIAGRAM_ENABLE_STRICT)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(
                -Wall
                -Wextra
                -Werror
                -Wpedantic
                -Wmissing-include-dirs
                -Wundef
                -Wredundant-decls
        )
    endif()
endif()

if(SVG_DIAGRAM_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        add_compile_options(--coverage -O0 -g)
        add_link_options(--coverage)
    endif()
endif()

add_library(SVGDiagram STATIC
        include/svg_diagram.h
        src/svg_diagram.cpp
        include/svg_text_size.h
        src/svg_text_size.cpp
        include/svg_nodes.h
        src/svg_nodes.cpp
        include/attribute_utils.h
        src/attribute_utils.cpp
        include/svg_draw.h
        src/svg_draw.cpp
        include/geometry_utils.h
        src/geometry_utils.cpp
        include/xml_element.h
        src/xml_element.cpp
)

target_include_directories(SVGDiagram
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)


if (SVG_DIAGRAM_ENABLE_PANGO_CAIRO)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(CAIRO REQUIRED cairo)
    pkg_check_modules(PANGO REQUIRED pango pangocairo)

    target_include_directories(SVGDiagram
            PRIVATE ${CAIRO_INCLUDE_DIRS}
            PRIVATE ${PANGO_INCLUDE_DIRS}
    )

    target_link_directories(SVGDiagram
            PUBLIC ${CAIRO_LIBRARY_DIRS}
            PUBLIC ${PANGO_LIBRARY_DIRS}
    )

    target_link_libraries(SVGDiagram
            PUBLIC ${CAIRO_LIBRARIES}
            PUBLIC ${PANGO_LIBRARIES}
    )

    target_compile_options(SVGDiagram
            PUBLIC ${CAIRO_CFLAGS_OTHER}
            PUBLIC ${PANGO_CFLAGS_OTHER})

    target_compile_definitions(SVGDiagram
            PUBLIC SVG_DIAGRAM_ENABLE_PANGO_CAIRO
    )
endif()

if(SVG_DIAGRAM_ENABLE_TESTS)
    enable_testing()

    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.17.0
    )

    FetchContent_MakeAvailable(googletest)

    add_executable(runTests
            tests/test_main.cpp
            tests/test_svg_text_size.cpp
            tests/test_attribute_utils.cpp
            tests/svg_draw/test_comment.cpp
            tests/svg_draw/test_circle.cpp
            tests/svg_draw/test_text.cpp
            tests/svg_draw/test_line.cpp
            tests/svg_node/test_circle.cpp
            tests/test_utils.cpp
            tests/test_utils.h
            tests/svg_edge/test_line.cpp
            tests/svg_edge/test_spline.cpp
            tests/example/test_example_pentagon.cpp
            tests/example/test_example_pentagram.cpp
            tests/test_geometry_utils.cpp
            tests/svg_node/test_rect.cpp
            tests/example/test_example_sequential.cpp
            tests/test_xml_element.cpp
            tests/svg_node/test_ellipse.cpp
            tests/example/test_example_subgraph.cpp
            tests/test_graph.cpp
            tests/svg_node/test_node.cpp
            tests/svg_node/test_double_circle.cpp
    )

    target_link_libraries(runTests
            PRIVATE SVGDiagram
            PRIVATE gtest gtest_main
    )

    add_test(NAME SVGDiagramTests COMMAND runTests)
endif()
