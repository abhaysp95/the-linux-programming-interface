add_executable(setjmp_vars src/main.c)
set_target_properties(setjmp_vars PROPERTIES COMPILE_FLAGS "-save-temps -Wextra")

# I've added it in main CMakeLists.txt to make this project with either Release with "-O3" flag

#set(MY_DEBUG_OPTIONS "-O")
#target_compile_options(setjmp_vars PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
