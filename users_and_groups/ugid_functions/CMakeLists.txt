add_executable(ugid_functions
	src/main.c
	src/ugid_functions_util.c
	inc/ugid_functions_util.h)
add_dependencies(ugid_functions tlpi_library)
target_link_libraries(ugid_functions PUBLIC tlpi_library)
