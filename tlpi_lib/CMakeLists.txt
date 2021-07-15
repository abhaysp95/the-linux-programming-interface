add_library(lib_tlpi STATIC src/ename.c.inc src/error_functions.c src/get_num.c
	include/tlpi/tlpi_hdr.h include/tlpi/error_functions.h include/tlpi/get_num.h)

target_include_directories(lib_tlpi PUBLIC include)

target_compile_features(lib_tlpi PUBLIC c_std_99)
