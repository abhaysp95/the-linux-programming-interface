add_executable(abusing_longjmp src/main.c)

# leave files from different compiler flags like, '-E', '-S' etc.
set_target_properties(abusing_longjmp PROPERTIES COMPILE_FLAGS "-save-temps")

add_dependencies(abusing_longjmp tlpi_library)
target_link_libraries(abusing_longjmp PUBLIC tlpi_library)
