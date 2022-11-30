add_executable(t_longjmp src/main.c)
add_dependencies(t_longjmp tlpi_library)
target_link_libraries(t_longjmp PUBLIC tlpi_library)
