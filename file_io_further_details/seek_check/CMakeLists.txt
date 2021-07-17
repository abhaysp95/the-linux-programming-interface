add_executable(seek_check src/main.c)
add_dependencies(seek_check tlpi_library)
target_link_libraries(seek_check PUBLIC tlpi_library)
