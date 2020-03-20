#!/bin/sh -e

export COLOR=0 # my eyes o.0
export VERBOSE=1 # cmake
export CTEST_OUTPUT_ON_FAILURE=1 # unity

BUILD_FOLDER="build"

clean()
{
	echo "clean build directory"
	rm -r $BUILD_FOLDER
}

generate()
{
	echo "generate makes"
	mkdir -p $BUILD_FOLDER
	cd $BUILD_FOLDER
	cmake -DCMAKE_BUILD_TYPE=Debug ..
	make
}

build()
{
	echo "building..."
	make
}

_test()
{
	echo "testing..."
	make test
}

clean
generate
build
_test
