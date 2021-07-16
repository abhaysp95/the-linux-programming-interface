# The Linux Programming Interface

## Build

```sh
$ git clone https://github.com/coolabhays/the-linux-programming-interface.git
$ cd the-linux-programming-interface
$ mkdir build  # make build_debug, if you want to build with debug option
```

### Simple Build
```sh
$ cmake -S . -B build  # builds with no debug and "Unix Makefiles" as generator
```

### Change Generator
```sh
$ cmake -GNinja -S . -B build  # if you want to use Ninja
```

### Change Compiler

I've added commented `cmake variables` in `CMakeLists.txt` of _project_source_directory_. You can change compiler and compiling flags from there. If you want to do it from command line, you can do it in following way:
```sh
$ cmake -DCMAKE_C_COMPILER="/usr/bin/clang" -DCMAKE_C_FLAGS="-Wall -std=c99" -DCMAKE_C_FLAGS_DEBUG="-ggdb" -S . -B build
```

### Build with Debug
```sh
$ cmake -DCMAKE_BUILD_TYPE=Debug -S . -B build_debug
```

### Generate 'compile_commands.json'

Useful when you are using an IDE(or some language server) to code

```sh
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build
```

I've added the logic to create a symlink to `build*/compile_commands.json` file to `project source directory`. Though it'll not happen on first build. I can't find any option/way(probably there's isn't official way) to execute that logic(in _CMakeLists.txt_ in project source directory) after the creation of `compile_commands.json` file.

So, either you can first make a build using above command, and create a symlink manually, like:
```sh
$ ln -s build/compile_commands.json compile_commands.json
```

or you can just run the build command again, like(after running the above build command ofcourse):
```sh
$ cmake -S . -B build
```

So, you can just do something like this after all:
```sh
$ cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Debug -S . -B build
$ cmake -S . -B build
```

## Running a target(project)

```sh
$ cd build
$ make -j<n> <target_name>  # if you're not sure of <target_name>, do "make help"
```
