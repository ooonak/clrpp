# Caller C++ client

[![Build and test](https://github.com/ooonak/clrpp/actions/workflows/ci.yaml/badge.svg)](https://github.com/ooonak/clrpp/actions/workflows/ci.yaml)
[![Static analysis](https://github.com/ooonak/clrpp/actions/workflows/static-analysis.yaml/badge.svg)](https://github.com/ooonak/clrpp/actions/workflows/static-analysis.yaml)
[![Dynamic analysis](https://github.com/ooonak/clrpp/actions/workflows/dynamic-analysis.yaml/badge.svg)](https://github.com/ooonak/clrpp/actions/workflows/dynamic-analysis.yaml)
![Coverage](https://badgen.net/badge/coverage/85%25/green)

## Develop

### Build

```
$ conan install . --profile=x86_64-clang-18-debug --build=missing
$ cmake --preset conan-debug
$ cd build/Debug
$ cmake --build .
$ ctest
```

Analysis

```
$ find src include -type f \( -name '*.cpp' -o -name '*.hpp' \) | xargs clang-tidy -p build/Debug -header-filter='^$(pwd)/src/|^$(pwd)/include/'
$ cppcheck --suppressions-list=CppCheckSuppressions.txt --project=build/Debug/compile_commands.json --error-exitcode=1 --suppress=missingIncludeSystem --quiet

$ valgrind --leak-check=full --track-origins=yes --trace-children=yes build/Debug/tests/clrppTests
```
