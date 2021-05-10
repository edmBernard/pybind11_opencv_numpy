# pybind11_opencv_numpy

Binding between cv::Mat and np.array. And a small code example of how it work. The code work for `OpenCV 2.4`, `OpenCV 3+` and `OpenCV 4+`

The code in this repository create a simple binding, function in c++ are implemented in [`tests/cpp/test.cpp`](tests/cpp/test.cpp) file and python script that use them are in the tests folder like [`tests/test_binding.py`](tests/test_binding.py).

```bash
/project folder
├── CMakeLists.txt
├── setup.py
├── ndarray_converter.cpp  # Effective implementation of the binding
├── ndarray_converter.h    # Header for binding functions
└── ...
```

There is 3 way to build the project, more information can be found on pybind11 website [here](https://pybind11.readthedocs.io/en/stable/compiling.html#build-systems) :
  1. build with cmake : the basic, compiled library will be generated in build folder
  2. build with setup.py and cmake : install your module in python and dependency are managed by cmake/vcpkg (opencv and pybind11)
  3. build with setup.py and setuptools : install your module in python and dependency are managed by python package (opencv and pybind11) ***Soon***

## Build with cmake

*Note* : This method support opencv 2.4, opencv 3 and opencv 4.

### Step 1 : Install dependencies

We use [vcpkg](https://github.com/Microsoft/vcpkg) to install [pybind11](https://github.com/pybind/pybind11) library

```
./vcpkg install pybind11 opencv4
```

### Step 2 : Define the environnement variable to VCPKG Directory

on Linux
```
export VCPKG_DIR=/path/to/vcpkg/dir
```

on Windows
```
$Env:VCPKG_DIR="/path/to/vcpkg/dir"
```

*Note* : vcpkg dir should contain the following folder : `scripts/buildsystems/vcpkg.cmake`

### Step 3 : Compile

```bash
mkdir build
cd build
# configure make with vcpkg toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake
# on Windows : cmake.exe .. -DCMAKE_TOOLCHAIN_FILE="$Env:VCPKG_DIR/scripts/buildsystems/vcpkg.cmake"
# generate your library, in this poject it's the test_module
cmake --build . --config Release
```

#### Numpy header

In case of error like: `'numpy/ndarrayobject.h' : No such file or directory`

You have to be sure numpy is install on the computer either with `python -m pip install numpy` or `sudo apt-get install python-numpy` for linux.
Even if numpy is installed, CMake was not able to find correctly numpy header during configuration. Probably because numpy is install on the user package. Its possible the explicitly set the directory with the following command :

```bash
cmake .. -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake -DNUMPY_INCLUDE_DIR="${PYTHON_USER_DIR}/LocalCache/local-packages/Python39/site-packages/numpy/core/include/"
```

Numpy header location can be found with the following command :

```bash
python -c "import numpy as np; print(np.get_include())"
```

## Build with `setup.py` and cmake

*Note* : This method support opencv 2.4, opencv 3 and opencv 4.

You should first follow step 1 and 2 from the ***Build with cmake*** paragraph

### Step 3 : Compile

#### OpenCV 2.4+, OpenCV 3+, , OpenCV 4+

```bash
python3 -m pip install .
```

## Build with `setup.py` and setuptool

 ***in coming***


## Execute Tests

Tests use the binding module generate by cmake.

```bash
python -m pytest
```


## Limitation

Currently, the conversion between cv::Mat and Numpy.ndarray is done by copy.
