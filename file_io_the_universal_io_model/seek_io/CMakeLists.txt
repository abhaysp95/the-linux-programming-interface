add_executable(seek_io src/main.c)
add_dependencies(seek_io tlpi_library)
target_link_libraries(seek_io PUBLIC tlpi_library)

configure_file(input.txt "${CMAKE_CURRENT_BINARY_DIR}/input.txt")
