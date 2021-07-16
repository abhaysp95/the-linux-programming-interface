add_executable(t_readv src/main.c)
add_dependencies(t_readv tlpi_library)
target_link_libraries(t_readv PUBLIC tlpi_library)
