cd ..

mkdir build_win32
cd build_win32

"C:\Program Files\CMake\bin\cmake.exe" -G "Visual Studio 16 2019" ..
"C:\Program Files\CMake\bin\cmake.exe" --build . --config Release
