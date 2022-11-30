add_executable(syslim_fpathconf ./src/main.c)
add_dependencies(syslim_fpathconf tlpi_library)
target_link_libraries(syslim_fpathconf PUBLIC tlpi_library)
