#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <string>

#include "ndarray_converter.h"

namespace py = pybind11;

cv::Mat read_image(std::string image_name) {
#if CV_MAJOR_VERSION < 4
  cv::Mat image = cv::imread(image_name, CV_LOAD_IMAGE_COLOR);
#else
  cv::Mat image = cv::imread(image_name, cv::IMREAD_COLOR);
#endif
  return image;
}

void show_image(cv::Mat image) {
  cv::imshow("image_from_Cpp", image);
  cv::waitKey(0);
}

constexpr int kWidth = 12;
constexpr int kHeight = 10;
constexpr int kChannel = 3;


// Return the depth of the matrice element
// cf. https://docs.opencv.org/master/d3/d63/classcv_1_1Mat.html#a8da9f853b6f3a29d738572fd1ffc44c0
std::string checkDepth(const cv::Mat& mat) {
  int depth = mat.depth();
  switch (depth) {
    case CV_8U:
      return "CV_8U";
    case CV_8S:
      return "CV_8S";
    case CV_16U:
      return "CV_16U";
    case CV_16S:
      return "CV_16S";
    case CV_32S:
      return "CV_32S";
    case CV_32F:
      return "CV_32F";
    case CV_64F:
      return "CV_64F";
    default:
      throw std::runtime_error("Unknown element type");
  }
}

std::tuple<int, int, int> getShape(const cv::Mat& mat) {
  cv::Size s = mat.size();
  return {s.height, s.width, mat.channels()};
}


// Generate buffer for a matrix 10x10x3
std::vector<uint16_t> generateBuffer() {
  std::vector<uint16_t> matrice;
  const uint16_t size = kWidth * kHeight * kChannel;
  matrice.reserve(size);
  for (uint16_t i = 0; i < size; ++i) {
    matrice.push_back(i);
  }
  return matrice;
}


// Generate matrix 10x10x3
// Example of function that return a matrix by value
cv::Mat generateMatrix() {
  const std::vector<uint16_t> buffer = generateBuffer();
  return cv::Mat(buffer, true).reshape(kChannel, {kHeight, kWidth});
}

// Example of function that take a matrix as argument
bool checkMatrixContent(const cv::Mat& mat) {
  // I don't compare buffer from the matrix with expected buffer to correctly manage non contiguous matrices.
  const std::vector<uint16_t> expectedBuffer = generateBuffer();

  auto [height, width, channel] = getShape(mat);
  assert(height * width * channel == expectedBuffer.size());

  bool match = true;
  for (uint16_t i = 0; i < height; ++i) {
    for (uint16_t j = 0; j < width; ++j) {
      for (uint16_t c = 0; c < channel; ++c) {
        const cv::Vec3w values = mat.at<cv::Vec3w>(cv::Point(j,i));
         match &= values(c) == expectedBuffer[i * width * channel + j * channel + c];
      }
    }
  }

  return match;
}

// Convert the matrice in a vector to compare
std::vector<uint16_t> getContentAsVector(const cv::Mat &mat) {
  auto [height, width, channel] = getShape(mat);
  int size = height*width*channel;
  std::vector<uint16_t> buffer;
  buffer.reserve(size);
  for (uint16_t i = 0; i < height; ++i) {
    for (uint16_t j = 0; j < width; ++j) {
      for (uint16_t c = 0; c < channel; ++c) {
        uint16_t value;
        switch(channel) {
          case 1:
            value = mat.at<uint16_t>(cv::Point(j,i));
            break;
          case 2:
            value = mat.at<cv::Vec2w>(cv::Point(j,i))(c);
            break;
          case 3:
            value = mat.at<cv::Vec3w>(cv::Point(j,i))(c);
            break;
          default:
            throw std::runtime_error("This helper function only work with Channel = 1, 2, or 3");
        }
        buffer.push_back(value);
      }
    }
  }
  return buffer;
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
    m_image = generateMatrix();
  }

  cv::Mat& returnByRef() { return m_image; };
  const cv::Mat& viewMatrix() { return m_image; };

  cv::Mat* returnByPointer() { return &m_image; };

  cv::Mat returnByValue() { return m_image; };

  void returnInArgumentByRef(cv::Mat& image) {};

  void returnInArgumentByPointer(cv::Mat* image) {};

  void changeInternal() {
    m_image.at<cv::Vec3w>(0, 0) = cv::Vec3w(4,5,6);
  }

private:
  cv::Mat m_image;
};

void returnByArgumentValue(cv::Mat mat) {
  mat.at<cv::Vec3w>(0, 0) = cv::Vec3w(4,5,6);
}

void returnByArgumentRef(cv::Mat & mat) {
  mat.at<cv::Vec3w>(0, 0) = cv::Vec3w(4,5,6);
}

void returnByArgumentPointer(cv::Mat *mat) {
  mat->at<cv::Vec3w>(0, 0) = cv::Vec3w(4,5,6);
}

void returnByArgumentValueWithAllocation(cv::Mat mat) {
  mat = cv::Mat::ones(cv::Size(3, 3), CV_8UC1);
}

void returnByArgumentRefWithAllocation(cv::Mat & mat) {
  mat = cv::Mat::ones(cv::Size(3, 3), CV_8UC1);
}

PYBIND11_MODULE(test_module, m) {

  NDArrayConverter::init_numpy();

  m.def("generate_matrix", &generateMatrix, "A function that generate a image");

  m.def("check_matrix_content", &checkMatrixContent, "A function that check the content a an image",
        py::arg("image"));

  m.def("check_depth", &checkDepth, "A function that return the type of the matrice element",
        py::arg("image"));

  m.def("get_shape", &getShape, "A function that return the shape of the matrice",
        py::arg("image"));

  m.def("get_content_as_list", &getContentAsVector, "A function that return the content as a list",
        py::arg("image"));


  m.def("passthru", &passthru, "Passthru function", py::arg("image"));
  m.def("clone", &cloneimg, "Clone function", py::arg("image"));


  m.def("read_image", &read_image, "A function that read an image",
        py::arg("image"));


  m.def("show_image", &show_image, "A function that show an image",
        py::arg("image"));


  py::class_<ClassForReturn>(m, "ClassForReturn")
    .def(py::init<>())
    .def("changeInternal", &ClassForReturn::changeInternal)
    .def("returnByValue", &ClassForReturn::returnByValue)
    .def("returnByRefButCopy", &ClassForReturn::returnByRef)
    .def("returnByRef", &ClassForReturn::returnByRef, py::return_value_policy::reference_internal)
    .def("viewMatrix", &ClassForReturn::returnByRef, py::return_value_policy::reference_internal)
    .def("returnByPointer", &ClassForReturn::returnByPointer, py::return_value_policy::reference_internal)
    .def("returnInArgumentByRef", &ClassForReturn::returnInArgumentByRef)
    .def("returnInArgumentByPointer", &ClassForReturn::returnInArgumentByPointer)
    ;

  m.def("returnByArgumentValue", &returnByArgumentValue, py::return_value_policy::copy);

  m.def("returnByArgumentRef", &returnByArgumentRef);

  m.def("returnByArgumentPointer", &returnByArgumentPointer);

  m.def("returnByArgumentValueWithAllocation", &returnByArgumentValueWithAllocation);

  m.def("returnByArgumentRefWithAllocation", &returnByArgumentRefWithAllocation);

}
