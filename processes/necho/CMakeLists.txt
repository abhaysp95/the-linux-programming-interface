add_executable(necho src/main.c)
add_dependencies(necho tlpi_library)
target_link_libraries(necho PUBLIC tlpi_library)
