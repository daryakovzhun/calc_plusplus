#!/bin/sh

OS=$(uname)

cd build
$1 ../source/Calculator.pro
make
if [ ${OS} = Linux ]; then
    cp Calculator ../calc/
elif [ ${OS} = Darwin ]; then
    cp -r Calculator* ../calc/
else
    echo "\nWindows install is not supported"
fi
