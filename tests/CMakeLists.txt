project(image)

add_executable(test_bmp test_bmp.c)
target_link_libraries(test_bmp image)

add_executable(test_gaussian test_gauss.c)
target_link_libraries(test_gaussian image)

add_executable(test_median test_median.c)
target_link_libraries(test_median image)

add_executable(test_bitstring test_bitstring.c)
target_link_libraries(test_bitstring image)