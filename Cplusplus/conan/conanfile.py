import os
from conans import ConanFile, CMake
from conan.tools.cmake import CMakeToolchain, CMakeDeps

class CPlusPlusConan(ConanFile):
    settings = "os","compiler","build_type","arch"
    requires = "catch2/[>=2.13.4]", "qt/[>=6.1.1]"
    generators = "CMakeToolchain", "CMakeDeps", "qt", "cmake"
    default_options = {"*:shared": True}
    short_paths = False # Using Python 3.x on win10, short paths unecessary

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.exe", dst="bin", src="bin")
        self.copy("*.dylib*", dst="lib", src="lib")
        self.copy("*.so*", dst="bin", src="lib")
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)
    
    # def generate(self):
    #     tc = CMakeToolchain(self) #, generator="Ninja"
    #     tc.generate()
    #     deps = CMakeDeps(self)
    #     deps.generate()
    
    def package_info(self):
        self.env_info.path.append(os.path.join(self.build_folder, "bin"))
        print(os.path.join(self.build_folder, "bin"))
        self.env_info.path.append(os.path.join(self.build_folder, "lib"))
    
    def build(self):
        cmake = CMake(self) #, generator="Ninja", perhaps append_vcvars=True?
        if self.should_configure:
            cmake.configure()
        if self.should_build:
            cmake.build()
        if self.should_test:
            cmake.test( target="test_all", output_on_failure=True)
        if self.should_install:
            cmake.install()