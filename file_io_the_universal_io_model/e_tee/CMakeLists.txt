add_executable(e_tee src/main.c)
add_dependencies(e_tee tlpi_library)
target_link_libraries(e_tee PUBLIC tlpi_library)
