project(image)

if(UNIX)
    LINK_LIBRARIES("m")
endif()

aux_source_directory(fmt FMT_SRCS)
aux_source_directory(filter FILTER_SRC)

add_library(image SHARED ${FMT_SRCS} ${FILTER_SRC} image.c bitstring.c mcu.c mat.c dct.c)