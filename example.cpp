#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <string>
#include <iostream>

#include "pybind11_opencv_typecaster_v2.h"

namespace py = pybind11;

void show_image(cv::Mat image)
{
    cv::imshow("image_from_Cpp", image);
    cv::waitKey(0);
}

cv::Mat read_image(std::string image_name)
{
    cv::Mat image = cv::imread(image_name, CV_LOAD_IMAGE_COLOR);
    return image;
}

PYBIND11_PLUGIN(eb) 
{
    py::module m("eb", "pybind11 eb plugin");
    m.def("read_image", &read_image, "A function that read an image", 
        py::arg("image"));

    m.def("show_image", &show_image, "A function that show an image", 
        py::arg("image"));

    return m.ptr();
}

