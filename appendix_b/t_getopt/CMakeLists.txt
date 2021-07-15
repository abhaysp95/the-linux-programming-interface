add_executable(t_getopt src/main.c)
add_dependencies(t_getopt tlpi_library)
target_link_libraries(t_getopt PUBLIC tlpi_library)
