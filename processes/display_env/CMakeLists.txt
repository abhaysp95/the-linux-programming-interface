add_executable(display_env src/main.c)
add_dependencies(display_env tlpi_library)
target_link_libraries(display_env PUBLIC tlpi_library)
