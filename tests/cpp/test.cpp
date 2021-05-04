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

  m.def("passthru", &passthru, "Passthru function", py::arg("image"));
  m.def("clone", &cloneimg, "Clone function", py::arg("image"));


  py::class_<ClassForReturn>(m, "ClassForReturn")
    .def(py::init<>())
    .def("returnByRef", &ClassForReturn::returnByRef)
    .def("returnByPointer", &ClassForReturn::returnByPointer)
    .def("returnByValue", &ClassForReturn::returnByValue)
    .def("returnInArgumentByRef", &ClassForReturn::returnInArgumentByRef)
    .def("returnInArgumentByPointer", &ClassForReturn::returnInArgumentByPointer)
    ;
}
