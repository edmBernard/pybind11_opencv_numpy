// portions borrowed from https://github.com/edmBernard/pybind11_opencv_numpy/blob/master/pybind11_opencv_typecaster_v2.h

#include <pybind11/numpy.h>
#include <opencv2/core/core.hpp>

#include "ndarray_converter.h"

namespace pybind11 { namespace detail {
    
template <> struct type_caster<cv::Mat> {
public:
    
    PYBIND11_TYPE_CASTER(cv::Mat, _("numpy.ndarray"));
    
    bool load(handle src, bool) {
        return NDArrayConverter::toMat(src.ptr(), value);
    }
    
    static handle cast(const cv::Mat &m, return_value_policy, handle defval) {
        return handle(NDArrayConverter::toNDArray(m));
    }
};
    
    
}} // namespace pybind11::detail
