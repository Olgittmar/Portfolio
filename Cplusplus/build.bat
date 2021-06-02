@echo off
if {%1}=={debug} goto :DEBUG
if {%1}=={release} goto :RELEASE
if {%1}=={light} goto :COMPILE
if {%1}=={all} goto :DEBUG
goto :eof

:DEBUG
if not exist "build" (
    mkdir build
)
cd build
if not exist "debug" (
    mkdir debug
)
cd debug
cmake ../.. -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=C:\\Qt\\5.15.2\\msvc2019\\bin
if %ERRORLEVEL% NEQ 0 cd ../.. goto :eof
ninja && ninja install
if %ERRORLEVEL% NEQ 0 cd ../.. goto :eof
cd ../..
if not {%1}=={all} goto :eof

:RELEASE
if not exist "build" (
    mkdir build
)
cd build
if not exist "release" (
    mkdir release
)
cd release
cmake ../.. -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=C:\\Qt\\5.15.2\\msvc2019\\bin
if %ERRORLEVEL% NEQ 0 cd ../.. goto :eof
ninja && ninja install
cd ../..
goto :eof


:COMPILE