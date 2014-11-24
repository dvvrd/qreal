#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"


cp    $BIN_DIR/plugins/tools/kitPlugins/robots-ev3-interpreter.dll   $PWD/../data/plugins/tools/kitPlugins/
cp    $BIN_DIR/qextserialport.dll                                    $PWD/../data
