add_executable(large_file2 src/main.c)
add_dependencies(large_file2 tlpi_library)
target_link_libraries(large_file2 PUBLIC tlpi_library)
