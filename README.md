# Sudoker

A simple Sudoku solver framework written in C++.

## Compile
In order to compile the source the, apart from the basic development environment (like a compiler), the
following two packages are required:
  * [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page), minimum version 3.1.2
  * [CMake](http://www.cmake.org/)

In case of a debian system you would need to run the following command:
```
sudo apt-get install libeigen3-dev cmake
```

Once you have the required packages installed you run the following commands to compile the source:
```
mkdir build
cd build
cmake ..
make
```

## Running
----------
After successfully compiling the source, you can run the solver by:
```
cd build
./sudoker <input file.csv> <output file.csv>
```

