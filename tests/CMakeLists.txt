project(image)

add_executable(test_bmp test_bmp.c)
target_link_libraries(test_bmp image)