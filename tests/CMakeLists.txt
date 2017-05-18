project(image)

add_executable(test_bmp test_bmp.c)
target_link_libraries(test_bmp image)

add_executable(test_gaussian test_gaussian.c)
target_link_libraries(test_gaussian image)

add_executable(test_median test_median.c)
target_link_libraries(test_median image)