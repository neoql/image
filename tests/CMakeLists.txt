project(image)

add_executable(test_bmp test_bmp.c)
target_link_libraries(test_bmp fmt)

add_executable(test_gaussian test_gauss.c)
target_link_libraries(test_gaussian filter fmt)

add_executable(test_median test_median.c)
target_link_libraries(test_median filter fmt)

add_executable(test_bitstring test_bitstring.c)
target_link_libraries(test_bitstring util)

add_executable(test_jpeg test_jpeg.c)
target_link_libraries(test_jpeg fmt)