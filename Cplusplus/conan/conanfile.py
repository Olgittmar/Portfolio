import os
import shutil
from conans import ConanFile, CMake, RunEnvironment, tools
from conans.errors import ConanException

class CPlusPlusConan(ConanFile):
    settings = "os","compiler","build_type","arch"
    requires = "qt/[>=6.1.1]" # "catch2/[>=2.13.4]",
    # The 'qt' generator creates the qt.conf file, which is needed to find several required qt components
    generators = "qt", "cmake", "cmake_find_package", "cmake_paths", "CMakeToolchain", "CMakeDeps"
    default_options = {"*:shared": True}
    short_paths = False # Using Python 3.x on win10, short paths unecessary

    def build_requirements(self):
        self.build_requires("cmake/[>=3.20.2]")

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="lib", src="lib")
        self.copy("*.so*", dst="bin", src="lib")
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)
    
    def build(self):
        env_build = RunEnvironment(self)
        with tools.environment_append(env_build.vars):
            cmake = CMake(self, set_cmake_flags=True) #, generator="Ninja", perhaps append_vcvars=True?
            if self.should_configure:
                cmake.configure()
            if self.should_build:
                cmake.build()
            if self.should_test:
                cmake.test( output_on_failure=True )
                # cmake.test( target="test_all", output_on_failure=True)
            if self.should_install:
                cmake.install()