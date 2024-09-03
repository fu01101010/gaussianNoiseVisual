#! /bin/zsh
cd /users/ulysses/Desktop/source/projects/gaussianNoiseVisual
rm -rf build/
mkdir build
cd build
cmake ..
make install
//cd ../bin
//./gaussN
