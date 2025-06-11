# Bug description

`target_link_libraries(myapp PUBLIC MKL::MKL_SYCL)` fails on Aurora when using
MPI wrapper compilers with the following error:
```sh
-- Configuring done (0.6s)
CMake Error at CMakeLists.txt:8 (target_link_libraries):
  Target "myapp" links to:

    MKL::MKL_SYCL

  but the target was not found.  Possible reasons include:

    * There is a typo in the target name.
    * A find_package call is missing for an IMPORTED target.
    * An ALIAS target is missing.
```

This is possibly due to the following lines in the `MKLConfig.cmake`:
```cmake
if(CXX_COMPILER_NAME STREQUAL "dpcpp" OR CXX_COMPILER_NAME STREQUAL "dpcpp.exe"
    OR CXX_COMPILER_NAME STREQUAL "icpx" OR CXX_COMPILER_NAME STREQUAL "icx.exe")
  set(SYCL_COMPILER ON)
endif()
```

# Steps to reproduce
```sh
cmake -S . -B build -DCMAKE_CXX_COMPILER=mpicxx
```

The following workaround by Colleen Bertoni (bertoni@anl.gov) fixes the issue:
```sh
cmake -S . -B build -DCMAKE_CXX_COMPILER=mpicxx -DSYCL_COMPILER=ON
```
