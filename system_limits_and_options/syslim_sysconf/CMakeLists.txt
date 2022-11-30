add_executable(syslim_sysconf ./src/main.c)
add_dependencies(syslim_sysconf tlpi_library)
target_link_libraries(syslim_sysconf PUBLIC tlpi_library)
