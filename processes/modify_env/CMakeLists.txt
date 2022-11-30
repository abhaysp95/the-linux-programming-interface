add_executable(modify_env src/main.c)
add_dependencies(modify_env tlpi_library)
target_link_libraries(modify_env PUBLIC tlpi_library)
