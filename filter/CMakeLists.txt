project(image)

aux_source_directory(. FILTER_SRC)

add_library(filter SHARED ${FILTER_SRC} filter.h)