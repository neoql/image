project(image)

if(UNIX)
    LINK_LIBRARIES("m")
endif()

aux_source_directory(. TRANSFORM_SRC)

add_library(transform SHARED ${TRANSFORM_SRC})