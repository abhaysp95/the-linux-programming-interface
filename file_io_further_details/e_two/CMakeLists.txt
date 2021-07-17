add_executable(e_two src/main.c)
add_dependencies(e_two tlpi_library)
target_link_libraries(e_two PUBLIC tlpi_library)
