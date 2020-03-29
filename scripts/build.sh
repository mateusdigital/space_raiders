#!/usr/bin/env bash

##----------------------------------------------------------------------------##
## Imports                                                                    ##
##----------------------------------------------------------------------------##
source /usr/local/src/stdmatt/shellscript_utils/main.sh

##----------------------------------------------------------------------------##
## Constants                                                                  ##
##----------------------------------------------------------------------------##
PROJECT_NAME="space-raiders";


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
PLATFORM="desktop";
PLATFORM_BUILD_SCRIPT="";
PROJECT_VERSION="$(bump-the-version  \
    "${PROJECT_ROOT}/game/Version.h" \
    "#define GAME_VERSION"           \
    "show")";

DIST_FILES="                   \
    ${BUILD_DIR}/$PROJECT_NAME \
    ${PROJECT_ROOT}/assets/    \
";


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

MODE=$(pw_getopt_arg "--mode" "$@");
test -n "$MODE" \
    && test -z "$(pw_string_in "$MODE" "release" "debug")" \
    && pw_log_fatal "Invalid build mode: ($MODE)";

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

CURR_OS="$(pw_os_get_simple_name)";
## Windows build...
if [ -n "$(pw_getopt_exists "--win32" "$@")" ]; then
    test ! "${CURR_OS}" == "$(PW_OS_WSL)" \
        && pw_log_fatal "Windows version can just be built on WSL...";

    pw_pushd "${PROJECT_ROOT}";
        ## @notice(stdmatt): We need a separated script to handle the
        ## shit from windows that need to import a file to the compiler
        ## to work...
        ##
        ## Furthermore the CL.EXE has A LOT of strange options that I'll not
        ## dwell currently, so we need a lot of hackie stuff to make the
        ## things sane...
        powershell.exe  -F "${SCRIPT_DIR}/build_windows.ps1";
        find . -iname "*.obj" | xargs rm;

        mkdir -p "${BUILD_DIR}/win32";
        mv *.exe "${BUILD_DIR}/win32/space-raiders.exe";
        cp "${PROJECT_ROOT}/libs/third_party/SDL2-2.0.12/lib/x86/SDL2.dll" "${BUILD_DIR}/win32";
        cp ${PROJECT_ROOT}/res/* "${BUILD_DIR}/win32";
    pw_popd;
## Current Platform Build...
else
    # mkdir -p "${BUILD_DIR}/${CURR_OS}";
    # GCC_OPT="-O3";
    # if [ $"MODE" == "debug" ]; then
    #     GCC_OPT="-g";
    # fi

    g++ -std=c++14 ${GCC_OPT}  -g                    \
        $(sdl2-config --cflags)                    \
        ${PROJECT_ROOT}/game/*.cpp                 \
        $(sdl2-config --static-libs)               \
        -o "${BUILD_DIR}/${CURR_OS}/${PROJECT_NAME}";

    cp ${PROJECT_ROOT}/res/* "${BUILD_DIR}/${CURR_OS}";
fi;

##
## Create the distribution file.
if [ -n "$(pw_getopt_exists "--dist" "$@")" ]; then
    PLATFORM=$(pw_os_get_simple_name);
    echo "Packaging (${PROJECT_NAME}) version: (${PROJECT_VERSION}) for platform: (${PLATFORM})";

    PACKAGE_NAME="${PROJECT_NAME}_${PLATFORM}_${PROJECT_VERSION}";
    PACKAGE_DIR="${DIST_DIR}/${PACKAGE_NAME}";

    ## Clean the directory.
    rm    -rf "${PACKAGE_DIR}";
    mkdir -p  "${PACKAGE_DIR}";

    ## Copy the files to the directory.
    for ITEM in $DIST_FILES; do
        cp -R "$ITEM" "${PACKAGE_DIR}";
    done;

    cd "${DIST_DIR}"
    zip -r "${PACKAGE_NAME}.zip" "./${PACKAGE_NAME}";
    cd -
fi;
