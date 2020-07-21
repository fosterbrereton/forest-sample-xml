cmake_minimum_required (VERSION 3.0)

project (forest-sample-xml)

set(GCC_COVERAGE_COMPILE_FLAGS "-stdlib=libc++ -std=c++17")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

file(GLOB APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)

get_filename_component(STLAB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/stlab ABSOLUTE)

# get_filename_component(APP_HEADERS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/headers ABSOLUTE)

include_directories(forest-sample-xml AFTER
                    ${STLAB_PATH}
                    # ${APP_HEADERS_PATH}
                    )

add_executable(forest-sample-xml ${APP_SRC})

set_target_properties(forest-sample-xml PROPERTIES XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD c++17)
set_target_properties(forest-sample-xml PROPERTIES XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY libc++)
