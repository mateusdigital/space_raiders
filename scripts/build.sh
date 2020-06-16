#!/usr/bin/env bash
##~---------------------------------------------------------------------------##
##                        _      _                 _   _                      ##
##                    ___| |_ __| |_ __ ___   __ _| |_| |_                    ##
##                   / __| __/ _` | '_ ` _ \ / _` | __| __|                   ##
##                   \__ \ || (_| | | | | | | (_| | |_| |_                    ##
##                   |___/\__\__,_|_| |_| |_|\__,_|\__|\__|                   ##
##                                                                            ##
##  File      : build.sh                                                      ##
##  Project   : spaceraiders                                                  ##
##  Date      : Mar 29, 2020                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : stdmatt <stdmatt@pixelwizards.io>                             ##
##  Copyright : stdmatt 2020                                                  ##
##                                                                            ##
##  Description :                                                             ##
##---------------------------------------------------------------------------~##

##----------------------------------------------------------------------------##
## Imports                                                                    ##
##----------------------------------------------------------------------------##
source /usr/local/src/stdmatt/shellscript_utils/main.sh


##----------------------------------------------------------------------------##
## Constants                                                                  ##
##----------------------------------------------------------------------------##
PROJECT_NAME="space-raiders";
PROJECT_PKG_NAME="$(pw_string_replace "$PROJECT_NAME" "-" "_")";


##----------------------------------------------------------------------------##
## Vars                                                                       ##
##----------------------------------------------------------------------------##
## Dirs
SCRIPT_DIR="$(pw_get_script_dir)";
PROJECT_ROOT=$(pw_abspath "$SCRIPT_DIR/..");
BUILD_DIR=$(pw_abspath "$PROJECT_ROOT/build");
DIST_DIR=$(pw_abspath "$PROJECT_ROOT/dist");

## Info
MODE="debug";
PLATFORM="$(pw_os_get_simple_name)";
PROJECT_VERSION="$(bump-the-version  \
    "${PROJECT_ROOT}/game/Version.h" \
    "#define GAME_VERSION"           \
    "show")";


##----------------------------------------------------------------------------##
## Functions                                                                  ##
##----------------------------------------------------------------------------##
##------------------------------------------------------------------------------
show_help()
{
    cat << END_TEXT
Usage:
    build.sh
      --help                        - Show this info.
      --clean                       - Cleans the build files.
      --win32                       - Build win32 binary on WSL.
      --mode <*debug | release>     - Compile mode.
      --dist                        - Generate the release zip file.

    Options marked with * is assumed to be the default if none is given.
END_TEXT

    exit $1
}

##------------------------------------------------------------------------------
clean()
{
    pw_func_log "Cleaning files...";

    pw_func_log "   Build path: $(pw_FC $BUILD_DIR)";
    rm -rf "${BUILD_DIR}";

    pw_func_log "   Dist path: $(pw_FC $DIST_DIR)";
    rm -rf "${DIST_DIR}"
}


##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
cd "${PROJECT_ROOT}";

##
## Parse the command line arguments.
if [ -n "$(pw_getopt_exists "--clean" "$@")" ]; then
    clean;
    exit 0;
fi;

## Mode.
MODE=$(pw_getopt_arg "--mode" "$@");
test -n "$MODE" \
    && test -z "$(pw_string_in "$MODE" "release" "debug")" \
    && pw_log_fatal "Invalid build mode: ($MODE)";

## Platform.
if [ -n "$(pw_getopt_exists "--win32" "$@")" ]; then
    test ! "${PLATFORM}" == "$(PW_OS_WSL)" \
        && pw_log_fatal "Windows version can just be built on WSL...";
    PLATFORM="win32";
fi;

if [ "${PLATFORM}" == "$(PW_OS_WSL)" ]; then
    PLATFORM="$(PW_OS_GNU_LINUX)";
fi;


##
## Build ;D
echo "Bulding (${PROJECT_NAME})";
echo "Build Script directory : $(pw_FC $SCRIPT_DIR     )";
echo "Build directory        : $(pw_FC $BUILD_DIR      )";
echo "Dist  directory        : $(pw_FC $DIST_DIR       )";
echo "Compile mode           : $(pw_FC $MODE           )";
echo "Current version        : $(pw_FC $PROJECT_VERSION)";
echo "";

mkdir -p "$BUILD_DIR";

## Windows build...
if [ "$PLATFORM" == "win32" ]; then
    ## needs to use relative paths otherwise cmd.exe complains
    pw_pushd "${SCRIPT_DIR}";
        cmd.exe /c build_windows.cmd
    pw_popd;

    ## We need to copy the SDL DLL...
    SDL_DLL="libs/third_party/win32/SDL2-2.0.12/lib/x64/SDL2.dll";
    WIN32_BUILD="build_win32/Release";
    cp "$SDL_DLL" "$WIN32_BUILD";

    mkdir "$BUILD_DIR/win32";
    cp -r "$WIN32_BUILD"/* "$BUILD_DIR/win32";
## Current Platform Build...
else
    mkdir -p "build_${PLATFORM}";
    pw_pushd "build_${PLATFORM}";
        cmake ..
        cmake --build . --config Release
    pw_popd;

    mkdir -p "${BUILD_DIR}/${PLATFORM}";
    cp "build_${PLATFORM}/${PROJECT_NAME}" "${BUILD_DIR}/${PLATFORM}";
fi;


##
## Create the distribution file.
if [ -n "$(pw_getopt_exists "--dist" "$@")" ]; then
    echo "Packaging (${PROJECT_NAME}) version: (${PROJECT_VERSION}) for platform: (${PLATFORM})";

    PACKAGE_NAME="${PROJECT_PKG_NAME}_${PLATFORM}_${PROJECT_VERSION}";
    PACKAGE_DIR="${DIST_DIR}/${PACKAGE_NAME}";

    ## Clean the directory.
    rm    -rf "${PACKAGE_DIR}";
    mkdir -p  "${PACKAGE_DIR}";

    cp    "${BUILD_DIR}/${PLATFORM}/"* "$PACKAGE_DIR";
    cp -r "${PROJECT_ROOT}/res"        "$PACKAGE_DIR";

    pw_pushd "${DIST_DIR}"
        zip -r "${PACKAGE_NAME}.zip" "./${PACKAGE_NAME}";
    pw_popd;
fi;
