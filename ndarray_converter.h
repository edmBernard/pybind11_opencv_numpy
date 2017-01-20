# ifndef __COVERSION_OPENCV_H__
# define __COVERSION_OPENCV_H__

#include <Python.h>
#include <opencv2/core/core.hpp>

class NDArrayConverter {
public:
    static bool init_numpy();
    
    static bool toMat(PyObject* o, cv::Mat &m);
    static PyObject* toNDArray(const cv::Mat& mat);
};

# endif
