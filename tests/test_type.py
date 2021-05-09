import numpy as np
from tests import test_module as tm
from tests.utils import generate_matrix, check_matrix_content

def test_type_uint8_py2cpp():
  mat = generate_matrix().astype(np.uint8)
  assert(tm.check_depth(mat) == "CV_8U")


def test_type_int8_py2cpp():
  mat = generate_matrix().astype(np.int8)
  assert(tm.check_depth(mat) == "CV_8S")


def test_type_uint16_py2cpp():
  mat = generate_matrix().astype(np.uint16)
  assert(tm.check_depth(mat) == "CV_16U")


def test_type_float32_py2cpp():
  mat = generate_matrix().astype(np.float32)
  assert(tm.check_depth(mat) == "CV_32F")


def test_type_float64_py2cpp():
  mat = generate_matrix().astype(np.float64)
  assert(tm.check_depth(mat) == "CV_64F")
