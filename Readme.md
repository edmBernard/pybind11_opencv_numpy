# pybind11_opencv_numpy

An example of pybind11 for cv::Mat <-> np.array

```bash
/project folder
├── build
├── example
│   ├── exemple.so  # generate with make
│   └── example.cpython-36m-x86_64-linux-gnu.so  # generate with setup.py
├── CMakeLists.txt
├── setup.py
└── ...
```

## Generation with make

We use [vcpkg](https://github.com/Microsoft/vcpkg) to install [pybind11](https://github.com/pybind/pybind11) library

*Note* : This method support opencv 2.4, opencv 3 and opencv 4.

```
./vcpkg install pybind11
```

### Compile

```bash
mkdir build
cd build
# configure make with vcpkg toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=${VCPKG_DIR}/scripts/buildsystems/vcpkg.cmake
# generate the example.so library
make
# move example.so library in example folder
make install
```

### Run
```bash
python3 test.py
```

## Generation with setup.py


### install pybind11

```
pip3 install pybind11
```

### Compile

#### Opencv2.4+, Opencv3+

```
python3 setup.py build
```

#### Opencv4

In Opencv4, there a extra folder level for header (ex: `opencv4/opencv2/core/core.hpp`). To be able to compile with `setup.py` we need a extra command to indicate header location.

```
python3 setup.py build_ext --include-dirs "/usr/local/include/opencv4"
python3 setup.py build
```

### Install

```
python3 setup.py install
```

or

```
mv build/lib.linux-x86_64-3.5/example/example.cpython-36m-x86_64-linux-gnu.so example/example.cpython-36m-x86_64-linux-gnu.so
```

### Run

```
python3 test.py
```
