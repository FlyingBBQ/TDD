#!/bin/sh
build_dir="build"

rm -r $build_dir

mkdir $build_dir && cd $build_dir
cmake ..
#cmake -DCMAKE_INSTALL_PREFIX=stage ..
#cmake -Dtest=ON ..
#make
#make install
