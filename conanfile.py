from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps
import os


class clrppRecipe(ConanFile):
    name = "clrpp"
    version = "0.0.1"
    package_type = "library"

    # Optional metadata
    license = "Apache-2.0"
    author = "Oonak Kanoo"
    url = "https://github.com/ooonak/clrpp"
    description = "C++ client library for the caller framework"
    topics = ("IPC", "RPC")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them to the recipe
    exports_sources = ".clang-tidy", ".clang-format", "CppCheckSuppressions.txt", "CMakeLists.txt", "example/*", "include/*", "src/*", "tests/*"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")
        self.options["capnproto"].with_openssl = False
        self.options["capnproto"].with_zlib = False

    def layout(self):
        cmake_layout(self)

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

        # Run tests after building if not skipped
        if not self.conf.get("tools.build:skip_test", default=False):
            self.run("ctest --output-on-failure", cwd=self.build_folder)

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["clrpp"]

    def requirements(self):
        self.requires("spdlog/1.15.0")
        self.requires("capnproto/1.1.0")

    def build_requirements(self):
        self.test_requires("gtest/1.15.0")
