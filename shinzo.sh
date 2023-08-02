#!/bin/bash

ACTION="build"
NEED_TARGET=true
TARGET="x86_64"
TARGET_TMP=""

usage(){

  echo "Usage: $0 [action] [options]"
  echo ""
  echo "Options:"
  echo "    -b, --build    Build shinzo"
  echo "    -c, --clean    Clean all build files"
  echo "    -d, --debug    Start the virtual machine for debug"
  echo "    -h, --help     Show usage"
  echo "    -t=, --target= Target arch : x86, x86_64, aarch64"
  echo "    -r, --run      Start the virtual machine"
  echo ""
  exit 1
}

eval_arch(){
    if [[ $TARGET_TMP == "x86" ]] || [[ $TARGET_TMP == "x86_64" ]] || [[ $TARGET_TMP == "aarch64" ]]; then
        TARGET=$TARGET_TMP
    else
        echo "Unknown target 'TARGET_TMP'!"
        echo ""
    fi
}

eval_arg(){
    case $1 in
        "-b" | "--build")
        ACTION=build
        NEED_TARGET=true
        ;;

        "-c" | "--clean")
        ACTION=clean
        NEED_TARGET=true
        ;;

        "-d" | "--debug")
        ACTION="debug"
        NEED_TARGET=true
        ;;

        "--deps")
        ACTION="deps"
        NEED_TARGET=false
        ;;

        "-h" | "--help")
        usage
        ;;

        "-t="* | "--target="*)
        TARGET_TMP=${1#*=}
        eval_arch
        ;;

        "-r" | "--run")
        ACTION=run
        NEED_TARGET=true
        ;;

        *)
        echo "Unknown option '$1'!"
        echo ""
        usage
        ;;
    esac
}

if ! [ -z "$1" ]; then
    while [[ $1 == "-"* ]]; do
        eval_arg $1
        shift
    done
fi

if ! $NEED_TARGET ; then
    make $ACTION
else
    echo "$ACTION shinzo with the following target : $TARGET"

    cd build/arch/$TARGET && make $ACTION
fi