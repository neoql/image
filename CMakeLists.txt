cmake_minimum_required(VERSION 3.5.1)

project(image)

include_directories(
        ${PROJECT_SOURCE_DIR}
)

link_directories(
        ${PROJECT_BINARY_DIR}/lib
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

add_subdirectory(img)
add_subdirectory(fmt)
add_subdirectory(util)
add_subdirectory(filter)
add_subdirectory(transform)
add_subdirectory(tests)