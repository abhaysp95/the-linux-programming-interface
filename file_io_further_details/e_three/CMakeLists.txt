add_executable(e_three src/main.c)
add_dependencies(e_three tlpi_library)
target_link_libraries(e_three PUBLIC tlpi_library)
