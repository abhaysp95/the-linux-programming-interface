add_executable(large_file src/main.c)
add_dependencies(large_file tlpi_library)
target_link_libraries(large_file PUBLIC tlpi_library)
