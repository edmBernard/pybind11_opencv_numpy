#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

#include "ndarray_converter.h"

namespace py = pybind11;

void show_image(cv::Mat image) {
  cv::imshow("image_from_Cpp", image);
  cv::waitKey(0);
}

cv::Mat read_image(std::string image_name) {
#if CV_MAJOR_VERSION < 4
  cv::Mat image = cv::imread(image_name, CV_LOAD_IMAGE_COLOR);
#else
  cv::Mat image = cv::imread(image_name, cv::IMREAD_COLOR);
#endif
  return image;
}

constexpr int width = 10;
constexpr int height = 10;
constexpr int channel = 3;


// Generate buffer for a matrix 10x10x3
std::vector<uint8_t> generateBuffer() {
  std::vector<uint8_t> matrice;
  const int size = width * height * channel;
  matrice.reserve(size);
  for (int i = 0; i < size; ++i) {
    matrice.push_back(i);
  }
  return matrice;
}


// Generate matrix 10x10x3
// Example of function that return a matrix by value
cv::Mat generateMatrix() {
  const std::vector<uint8_t> buffer = generateBuffer();
  return cv::Mat(buffer, true).reshape(3, {10, 10});
}


// Example of function that take a matrix as argument
bool checkMatrixContent(const cv::Mat& mat) {
  // I don't compare buffer from the matrix with expected buffer to correctly manage slicing.
  const std::vector<uint8_t> expectedBuffer = generateBuffer();
  bool match = true;
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      const cv::Vec3b values = mat.at<cv::Vec3b>(cv::Point(i,j));
      match &= values(0) == expectedBuffer[j * width * 3 + i * 3 + 0];
      match &= values(1) == expectedBuffer[j * width * 3 + i * 3 + 1];
      match &= values(2) == expectedBuffer[j * width * 3 + i * 3 + 2];
    }
  }
  return match;
}



cv::Mat passthru(cv::Mat image) {
  return image;
}

cv::Mat cloneimg(cv::Mat image) {
  return image.clone();
}


class ClassForReturn {
public:
  ClassForReturn() {
    m_image = cv::Mat(2, 2, CV_8UC3, cv::Scalar(1,2,3));
  }

  cv::Mat& returnByRef() { return m_image; };

  cv::Mat* returnByPointer() { return &m_image; };

  cv::Mat returnByValue() { return m_image; };

  void returnInArgumentByRef(cv::Mat& image) {};

  void returnInArgumentByPointer(cv::Mat* image) {};

private:
  cv::Mat m_image;
};

PYBIND11_MODULE(test_module, m) {

  NDArrayConverter::init_numpy();

  m.def("read_image", &read_image, "A function that read an image",
        py::arg("image"));

  m.def("show_image", &show_image, "A function that show an image",
        py::arg("image"));


  m.def("generate_matrix", &generateMatrix, "A function that generate a image");

  m.def("check_matrix_content", &checkMatrixContent, "A function that check the content a an image",
        py::arg("image"));

  m.def("passthru", &passthru, "Passthru function", py::arg("image"));
  m.def("clone", &cloneimg, "Clone function", py::arg("image"));


  py::class_<ClassForReturn>(m, "ClassForReturn")
    .def(py::init<>())
    .def("returnByRef", &ClassForReturn::returnByRef, py::return_value_policy::reference_internal)
    .def("returnByPointer", &ClassForReturn::returnByPointer)
    .def("returnByValue", &ClassForReturn::returnByValue)
    .def("returnInArgumentByRef", &ClassForReturn::returnInArgumentByRef)
    .def("returnInArgumentByPointer", &ClassForReturn::returnInArgumentByPointer)
    ;
}
