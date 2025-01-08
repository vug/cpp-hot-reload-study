First build the executable

```
mkdir build
cd build
cmake ..
cmake --build .
```

run it

```
cd build/Debug
hot_reload_study.exe
```

then change library code, `calculate` function, and

```
cmake --build . --target reloadable_library
```

observe the hot-reload

```
aExists: true, bExists: false
Newest library: reloadable_library_a.dll
calculate(2, 3) = 5

aExists: true, bExists: true
Newest library: reloadable_library_a.dll
calculate(2, 3) = 6

aExists: true, bExists: true
Newest library: reloadable_library_a.dll
calculate(2, 3) = 8

...
```