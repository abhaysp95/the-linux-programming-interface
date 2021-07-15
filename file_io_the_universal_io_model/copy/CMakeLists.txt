add_executable(copy src/main.c)
add_dependencies(copy tlpi_library)
target_link_libraries(copy PUBLIC tlpi_library)

configure_file(input.txt "${CMAKE_CURRENT_BINARY_DIR}/input.txt")
