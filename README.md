```
mkdir build
cd build
cmake ..
cmake --build .
```

then change library code and

```
cmake --build .. --target reloadable_library
```