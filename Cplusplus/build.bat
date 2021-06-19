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
:COMPILE
if {%1}=={debug} goto :COMPILEDEBUG
if {%1}=={all} goto :COMPILEDEBUG
if {%1}=={} goto :COMPILEDEBUG
:DEBUGCOMPILED
if {%1}=={release} goto :COMPILERELEASE
if {%1}=={all} goto :COMPILERELEASE
if {%1}=={} goto :COMPILERELEASE
:RELEASECOMPILED
goto :eof

:BUILDDEBUG
conan install ./conan --install-folder ./build/debug --profile ./conan/debug_profile.txt --build=missing
if %ERRORLEVEL% NEQ 0 goto :ERROR
conan build ./conan --configure --build-folder ./build/debug -sf . -if ./build/debug
if %ERRORLEVEL% NEQ 0 goto :ERROR
conan build ./conan --build --build-folder ./build/debug -sf . -if ./build/debug
if %ERRORLEVEL% NEQ 0 goto :ERROR
conan build ./conan --test --build-folder ./build/debug -sf . -if ./build/debug
if %ERRORLEVEL% NEQ 0 goto :ERROR
conan build ./conan --install --build-folder ./build/debug -sf . -if ./build/debug
if %ERRORLEVEL% NEQ 0 goto :ERROR
goto :DEBUGBUILT

:COMPILEDEBUG
ninja && ninja install
if %ERRORLEVEL% NEQ 0 goto :EROOR
goto :DEBUGCOMPILED

:BUILDRELEASE
@REM conan install ./conan --install-folder ./build/release --profile ./conan/profile.txt --build=missing
@REM if %ERRORLEVEL% NEQ 0 goto :ERROR
@REM conan build ./conan --build-folder ./build/release
@REM if %ERRORLEVEL% NEQ 0 goto :ERROR
goto :RELEASEBUILT

:COMPILERELEASE
@REM ninja && ninja install
@REM if %ERRORLEVEL% NEQ 0 goto :ERROR
goto :eof

:ERROR
echo An error occured!
goto :eof