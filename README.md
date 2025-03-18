This is a password hashing library for C++. It uses libxcrypt, and so probably
won't work on windows without some extra effort. To use it just add the cpp
file to the list of files to compile, and make sure to link `crypt`.  
e.g.
```
g++ -I./pass_hash example.cpp pass_hash/pass_hash.cpp
```

this can be downloaded with CMake like this:
```cmake
include(FetchContent)

FetchContent_Declare(
  pass_hash
  GIT_REPOSITORY https://github.com/leftarrowkey/PassHash.git
  GIT_TAG        origin/main
)

FetchContent_MakeAvailable(pass_hash)

# or whatever your executable is
add_executable(cmake_test main.cpp)

target_link_libraries(cmake_test PassHash)

```
