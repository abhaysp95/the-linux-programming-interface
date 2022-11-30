add_executable(procfs_pidmax src/main.c)
add_dependencies(procfs_pidmax tlpi_library)
target_link_libraries(procfs_pidmax PUBLIC tlpi_library)
