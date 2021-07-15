add_executable(test_tlpi src/main.c)
add_dependencies(test_tlpi tlpi_library)
target_link_libraries(test_tlpi PUBLIC tlpi_library)
