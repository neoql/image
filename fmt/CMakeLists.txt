project(image)

aux_source_directory(. FMT_SRC)

add_library(fmt SHARED ${FMT_SRC})
target_link_libraries(fmt img transform util)