#!/bin/sh

echo "Hello"
cd build
sed -i.bak "s/--parents//g" Makefile
make dist
mv Calculator1.0.0.tar.gz ../