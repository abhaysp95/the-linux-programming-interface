add_executable(free_and_sbrk src/main.c)
add_dependencies(free_and_sbrk tlpi_library)
target_link_libraries(free_and_sbrk PUBLIC tlpi_library)
