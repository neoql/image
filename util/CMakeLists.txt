project(image)

aux_source_directory(. UTIL_SRC)

add_library(util SHARED ${UTIL_SRC})