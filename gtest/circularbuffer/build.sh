#!/bin/sh
build_dir="build"

rm -rf $build_dir

mkdir $build_dir && cd $build_dir
#cmake ..
#cmake -DCMAKE_INSTALL_PREFIX=stage ..
#cmake -Dtest=ON ..
cmake -Dtest=ON -Dget_gtest=ON -Dgen_test_main=ON ..
#make
#make install
