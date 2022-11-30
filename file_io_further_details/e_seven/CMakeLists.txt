add_executable(e_seven src/main.c)
add_dependencies(e_seven tlpi_library)
target_link_libraries(e_seven PUBLIC tlpi_library)
