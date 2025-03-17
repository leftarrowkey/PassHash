This is a password hashing library for C++. It uses libxcrypt, and so probably
won't work on windows without some extra effort. To use it just add the cpp
file to the list of files to compile, and make sure to link `crypt`.  
e.g.
```
g++ -I./pass_hash example.cpp pass_hash/pass_hash.cpp
```
