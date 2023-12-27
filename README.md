CppUTest template project

Build instruction:

mkdir build ; cd build
cmake ../
make

Compile with the unit tests:

cmake -DUT=ON ../

from the root of your project:
mkdir release
cd release
cmake -DCMAKE_BUILD_TYPE=Release ..
make

for Debug (again from the root of your project):
mkdir debug
cd debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

