#include <pybind11/pybind11.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <string>
#include <iostream>

#include "ndarray_converter.h"

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

cv::Mat passthru(cv::Mat image)
{
    return image;
}

cv::Mat cloneimg(cv::Mat image)
{
    return image.clone();
}

PYBIND11_PLUGIN(_example) 
{
    NDArrayConverter::init_numpy();
    
    py::module m("example", "pybind11 opencv example plugin");
    m.def("read_image", &read_image, "A function that read an image", 
        py::arg("image"));

    m.def("show_image", &show_image, "A function that show an image", 
        py::arg("image"));
        
    m.def("passthru", &passthru, "Passthru function", py::arg("image"));
    m.def("clone", &cloneimg, "Clone function", py::arg("image"));

    return m.ptr();
}

