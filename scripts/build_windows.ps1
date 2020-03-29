$project_root=pwd;

## Start the Development Console.
Import-Module "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\Common7\Tools\Microsoft.VisualStudio.DevShell.dll";
Enter-VsDevShell eee160e5

cd "$project_root";

## Compile...
## @todo(stdmatt): Would be nice to make this output quieter...
cl /O2 /I./libs/third_party/SDL2-2.0.12/include ./game/*.cpp ./libs/third_party/SDL2-2.0.12/lib/x86/SDL2.lib
