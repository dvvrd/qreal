#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

cp     $INSTALLER_ROOT/licenses/QextSerialPort-license*.txt              $PWD


mkdir -p $PWD/../data/plugins/tools/kitPlugins
mkdir -p $PWD/../data/examples
cp -r  $BIN_DIR/examples/nxt                                             $PWD/../data/examples
