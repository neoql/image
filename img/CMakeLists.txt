project(image)

aux_source_directory(. IMG_SRC)

add_library(img SHARED ${IMG_SRC})