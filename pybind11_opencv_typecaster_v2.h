
#include <pybind11/numpy.h>
#include <opencv2/core/core.hpp>
#include <stdexcept>

namespace pybind11 { namespace detail {

template <> struct type_caster<cv::Mat> {
    public:
        /**
         * This macro establishes the name 'inty' in
         * function signatures and declares a local variable
         * 'value' of type inty
         */
        PYBIND11_TYPE_CASTER(cv::Mat, _("numpy.ndarray"));

        /**
         * Conversion part 1 (Python->C++): convert a PyObject into a inty
         * instance or return false upon failure. The second argument
         * indicates whether implicit conversions should be applied.
         */
        bool load(handle src, bool) 
        {
            if (!isinstance<array>(src))
                return false;
            array arr = reinterpret_borrow<array>(src);

            int ndims = arr.ndim();

            decltype(CV_32F) dtype_cv; 

            // const auto &api = npy_api::get();
            // if (api.PyArray_EquivTypes_(arr.dtype(), dtype::of<float>())) {
            if (arr.dtype() == dtype(format_descriptor<float>::format())) {
                if (ndims == 3) {
                    dtype_cv = CV_32FC3;
                } else {
                    dtype_cv = CV_32FC1;
                }
            } else if (arr.dtype() == dtype(format_descriptor<double>::format())) {
                if (ndims == 3) {
                    dtype_cv = CV_64FC3;
                } else {
                    dtype_cv = CV_64FC1;
                }
            } else if (arr.dtype() == dtype(format_descriptor<unsigned char>::format())) { 
                if (ndims == 3) {
                    dtype_cv = CV_8UC3;
                } else {
                    dtype_cv = CV_8UC1;
                }
            } else { 
                throw std::logic_error("Unsupported type");
                return false;
            }

            const size_t* shape = arr.shape();

            value = cv::Mat(cv::Size(shape[1], shape[0]), dtype_cv, arr.mutable_data(), cv::Mat::AUTO_STEP);
            return true;
        }

        /**
         * Conversion part 2 (C++ -> Python): convert an inty instance into
         * a Python object. The second and third arguments are used to
         * indicate the return value policy and parent object (for
         * ``return_value_policy::reference_internal``) and are generally
         * ignored by implicit casters.
         */
        static handle cast(const cv::Mat &m, return_value_policy, handle defval) 
        {
            std::string format = format_descriptor<unsigned char>::format();
            size_t elemsize = sizeof(unsigned char);
            int dim; 
            switch(m.type()) {
                case CV_8U: 
                    format = format_descriptor<unsigned char>::format();
                    elemsize = sizeof(unsigned char);
                    dim = 2;
                    break; 
                case CV_8UC3: 
                    format = format_descriptor<unsigned char>::format();
                    elemsize = sizeof(unsigned char);
                    dim = 3;
                    break; 
                case CV_32F: 
                    format = format_descriptor<float>::format(); 
                    elemsize = sizeof(float);
                    dim = 2;
                    break;
                case CV_64F: 
                    format = format_descriptor<double>::format();
                    elemsize = sizeof(double);
                    dim = 2;
                    break;
                default: 
                    throw std::logic_error("Unsupported type");
            }

            std::vector<size_t> bufferdim;
            std::vector<size_t> strides;
            if (dim == 2) {
                bufferdim = {(size_t) m.rows, (size_t) m.cols};
                strides = {elemsize * (size_t) m.cols, elemsize};
            } else if (dim == 3) {
                bufferdim = {(size_t) m.rows, (size_t) m.cols, (size_t) 3};
                strides = {(size_t) elemsize * m.cols * 3, (size_t) elemsize * 3, (size_t) elemsize};
            }
            return array(buffer_info(
                m.data,         /* Pointer to buffer */
                elemsize,       /* Size of one scalar */
                format,         /* Python struct-style format descriptor */
                dim,            /* Number of dimensions */
                bufferdim,      /* Buffer dimensions */
                strides         /* Strides (in bytes) for each index */
                )).release();
        }

    };
}} // namespace pybind11::detail
