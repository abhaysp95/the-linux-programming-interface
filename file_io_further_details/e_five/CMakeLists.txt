add_executable(e_five src/main.c)
add_dependencies(e_five tlpi_library)
target_link_libraries(e_five PUBLIC tlpi_library)
