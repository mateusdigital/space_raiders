##~---------------------------------------------------------------------------##
##                               *       +                                    ##
##                         '                  |                               ##
##                     ()    .-.,="``"=.    - o -                             ##
##                           '=/_       \     |                               ##
##                        *   |  '=._    |                                    ##
##                             \     `=./`,        '                          ##
##                          .   '=.__.=' `='      *                           ##
##                 +                         +                                ##
##                      O      *        '       .                             ##
##                                                                            ##
##  File      : build_windows.cs                                              ##
##  Project   : Space Raiders                                                 ##
##  Date      : 2024-03-10                                                    ##
##  License   : See project's COPYING.TXT for full info.                      ##
##  Author    : mateus.digital <hello@mateus.digital>                         ##
##  Copyright : mateus.digital - 2024                                         ##
##                                                                            ##
##  Description :                                                             ##
##   Builds the project using Microsoft compiler for Windows.                 ##
##                                                                            ##
##   The requirements it to them in the path, which can be complicated        ##
##   depending on the setup - fortunately there's a PS module that            ##
##   enables us to bring the compiler dependencies quite easily.              ##
##                                                                            ##
##   Posh-VS                                                                  ##
##      https://github.com/olegsych/posh-vs                                   ##
##      1 - Install-Module posh-vs -Scope CurrentUser (one time only)         ##
##      2 - Install-PoshVs                            (to bring the deps)     ##
##      3 - . $profile                                (make them usable)      ##
##      4 - ./scripts/build_windows.ps1               (run the build)         ##
##                                                                            ##
##      Install-PoshVs && . $profile && ./scripts/build_windows.ps1           ##
##---------------------------------------------------------------------------~##

$OUTPUT_FOLDER = "build-pc-Release";
$EXE_NAME      = "space-raiders.exe";

## Clean output...
if(Test-Path "$OUTPUT_FOLDER") {
    Remove-Item -Path "$OUTPUT_FOLDER" -Force -Recurse;
}

New-Item -ItemType Directory -Path "$OUTPUT_FOLDER";

# Build the game.
cl.exe /EHsc /DUNICODE /D_UNICODE /Zc:wchar_t /Fe:$EXE_NAME `
    (Get-ChildItem -Path . -Filter *.cpp -Recurse -ErrorAction SilentlyContinue -Force) `
    /link User32.lib

## Clean up the obj files.
Remove-Item (Get-ChildItem -Path . -Filter *.obj -Recurse -ErrorAction SilentlyContinue -Force)

## Move the .exe to the build folder.
Move-Item -Path "$EXE_NAME" -Destination "$OUTPUT_FOLDER/$EXE_NAME";
