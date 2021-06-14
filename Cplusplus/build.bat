@echo off
if {%1}=={} (
    if not exist "build" goto :BUILD
    pushd build
    goto :COMPILE
)
if {%1}=={debug} goto :BUILD
if {%1}=={release} goto :BUILD
if {%1}=={all} goto :BUILD
goto :eof


:BUILD
if not exist "build" (
    mkdir build
    pushd build
    mkdir debug
    mkdir release
    popd
)
if not exist "install" (
    mkdir install
    pushd install
    mkdir debug
    mkdir release
    popd
)
pushd build
if {%1}=={debug} goto :BUILDDEBUG
if {%1}=={all} goto :BUILDDEBUG
if {%1}=={} goto :BUILDDEBUG
:DEBUGBUILT
if {%1}=={release} goto :BUILDRELEASE
if {%1}=={all} goto :BUILDRELEASE
if {%1}=={} goto :BUILDRELEASE
:RELEASEBUILT
:COMPILE
if {%1}=={debug} goto :COMPILEDEBUG
if {%1}=={all} goto :COMPILEDEBUG
if {%1}=={} goto :COMPILEDEBUG
:DEBUGCOMPILED
if {%1}=={release} goto :COMPILERELEASE
if {%1}=={all} goto :COMPILERELEASE
if {%1}=={} goto :COMPILERELEASE
:RELEASECOMPILED
popd
goto :eof

:BUILDDEBUG
if not exist "debug" mkdir debug
pushd debug
conan install ../../conan --profile ../../conan/debug_profile.txt --build=missing
cmake ../.. -G Ninja -DCMAKE_PREFIX_PATH=C:\\Qt\\5.15.2\\msvc2019\\bin -DCMAKE_INSTALL_PREFIX=..\\..\\install\\debug
if %ERRORLEVEL% NEQ 0 (
    echo An error occured while building Debug!
    popd
    popd
    goto :eof
)
popd
goto :DEBUGBUILT

:COMPILEDEBUG
if not exist "debug" goto :BUILDDEBUG
pushd debug
ninja && ninja install
if %ERRORLEVEL% NEQ 0 (
    echo An error occured while attempting to compile and install Debug!
    popd
    popd
    goto :eof
)
popd
goto :DEBUGCOMPILED

:BUILDRELEASE
if not exist "release" mkdir release
pushd release
conan install ../../conan --profile ../../conan/release_profile.txt
cmake ../.. -G Ninja -DCMAKE_PREFIX_PATH=C:\\Qt\\5.15.2\\msvc2019\\;C:\\Users\\olgit\\.conan\\data -DCMAKE_INSTALL_PREFIX=..\\..\\install\\release
if %ERRORLEVEL% NEQ 0 (
    echo An error occured while building Release!
    popd
    popd
    goto :eof
)
popd
goto :RELEASEBUILT

:COMPILERELEASE
if not exist "release" goto :BUILDRELEASE
pushd release
ninja && ninja install
if %ERRORLEVEL% NEQ 0 (
    echo An error occured while attempting to compile and install Release!
    popd
    popd
    goto :eof
)
popd
goto :RELEASECOMPILED