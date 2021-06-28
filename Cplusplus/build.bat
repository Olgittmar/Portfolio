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
    if not exist "debug" (
        mkdir debug
    )
    if not exist "release" (
        mkdir release
    )
    popd
)
if not exist "install" (
    mkdir install
    pushd install
    if not exist "debug" (
        mkdir debug
    )
    if not exist "release" (
        mkdir release
    )
    popd
)
if {%1}=={debug} goto :BUILDDEBUG
if {%1}=={all} goto :BUILDDEBUG
if {%1}=={} goto :BUILDDEBUG
:DEBUGBUILT
if {%1}=={release} goto :BUILDRELEASE
if {%1}=={all} goto :BUILDRELEASE
if {%1}=={} goto :BUILDRELEASE
:RELEASEBUILT
goto :eof

:BUILDDEBUG
echo installing dependencies...
conan install ./conan --install-folder ./build/debug --profile ./conan/debug_profile.txt --build=outdated
if %ERRORLEVEL% NEQ 0 goto :ERROR
echo configuring...
conan build ./conan --configure --build-folder ./build/debug -sf . -if ./build/debug --package-folder ./install/debug
if %ERRORLEVEL% NEQ 0 goto :ERROR
echo building...
conan build ./conan --build --build-folder ./build/debug -sf . -if ./build/debug --package-folder ./install/debug
if %ERRORLEVEL% NEQ 0 goto :ERROR
echo testing...
conan build ./conan --test --build-folder ./build/debug -sf . -if ./build/debug --package-folder ./install/debug
if %ERRORLEVEL% NEQ 0 goto :ERROR
echo installing...
conan build ./conan --install --build-folder ./build/debug -sf . -if ./build/debug --package-folder ./install/debug
if %ERRORLEVEL% NEQ 0 goto :ERROR
goto :DEBUGBUILT

:BUILDRELEASE
conan install ./conan --install-folder ./build/release --profile ./conan/release_profile.txt --build=missing
if %ERRORLEVEL% NEQ 0 goto :ERROR
conan config init
if %ERRORLEVEL% NEQ 0 goto :ERROR
conan build ./conan --configure --build-folder ./build/release -sf . -if ./build/release --package-folder ./install/release
if %ERRORLEVEL% NEQ 0 goto :ERROR
conan build ./conan --build --build-folder ./build/release -sf . -if ./build/release --package-folder ./install/release
if %ERRORLEVEL% NEQ 0 goto :ERROR
conan build ./conan --test --build-folder ./build/release -sf . -if ./build/release --package-folder ./install/release
if %ERRORLEVEL% NEQ 0 goto :ERROR
conan build ./conan --install --build-folder ./build/release -sf . -if ./build/release --package-folder ./install/release
if %ERRORLEVEL% NEQ 0 goto :ERROR
goto :RELEASEBUILT

:ERROR
echo An error occured!
echo %ERRORLEVEL%
goto :eof