# Caller C++ client

### Initial project setup

```
$ mkdir clrpp; cd clrpp
$ conan config install https://github.com/ooonak/conanconf.git \
    -t git --args="-b main" -sf=templates -tf=templates/command/new
$ conan new my_cmake_lib -d name=clrpp -d version=0.0.1 \
    -d requires=spdlog/1.15.0 -d requires=capnproto/1.1.0
```

On Arch when GTest is installed system wide, it's tricky.
Instead of setting the path in the CMakeFile, the following is working for both install and build, not create.

```
CMAKE_PREFIX_PATH=$(conan cache path gtest/1.15.0) conan build .
```

