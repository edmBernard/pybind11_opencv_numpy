import numpy as np
from tests import test_module as tm
from tests.utils import generate_matrix, check_matrix_content


def test_noslicing():
  mat = generate_matrix()
  assert(mat.shape == (10, 12, 3))
  assert(mat.flags['C_CONTIGUOUS'])
  assert(mat.dtype == np.uint16)
  assert(tm.get_shape(mat) == (10, 12, 3))


def test_slicing_width():
  mat = generate_matrix()[:,:3,:]
  assert(mat.shape == (10, 3, 3))
  assert(not mat.flags['C_CONTIGUOUS'])
  assert(mat.dtype == np.uint16)
  assert(tm.get_shape(mat) == (10, 3, 3))
  assert(np.all(tm.get_content_as_list(mat) == mat.flatten()))


def test_slicing_channel():
  mat = generate_matrix()[:,:,0]
  assert(mat.shape == (10, 12))
  assert(not mat.flags['C_CONTIGUOUS'])
  assert(mat.dtype == np.uint16)
  assert(tm.get_shape(mat) == (10, 12, 1))
  assert(np.all(tm.get_content_as_list(mat) == mat.flatten()))
