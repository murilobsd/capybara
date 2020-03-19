#!/bin/sh -e

BUILD_FOLDER="build"

clean()
{
	echo "clean build directory"
	rm -r $BUILD_FOLDER
}

build()
{
	echo "building..."
	mkdir -p $BUILD_FOLDER
	cd $BUILD_FOLDER
	cmake ..
	make
	make test
}

clean
build
