project(image)

aux_source_directory(. IMG_SRCS)

add_library(image SHARED ${IMG_SRCS})