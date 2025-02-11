$ mkdir clrpp
$ cd clrpp
$ conan config install https://github.com/ooonak/conanconf.git -t git --args="-b main" -sf=templates -tf=templates/command/new
$ conan new my_cmake_lib -d name=clrpp -d version=0.0.1 -d requires=spdlog/1.15.0 -d requires=capnproto/1.1.0

