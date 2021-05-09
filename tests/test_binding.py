import numpy as np
from tests import test_module as tm
from tests.utils import generate_matrix, check_matrix_content


def test_pass_py2cpp():
  mat = generate_matrix()
  assert(mat.shape == (10, 10, 3))
  assert(mat.flags['C_CONTIGUOUS'])
  assert(mat.dtype == np.uint16)
  assert(tm.check_matrix_content(mat))


def test_pass_cpp2py():
  mat =  tm.generate_matrix()
  assert(mat.shape == (10, 10, 3))
  assert(mat.flags['C_CONTIGUOUS'])
  assert(mat.dtype == np.uint16)
  assert(check_matrix_content(mat))


def test_passthough_cpp2cpp():
  mat =  tm.generate_matrix()
  assert(mat.shape == (10, 10, 3))
  assert(mat.flags['C_CONTIGUOUS'])
  assert(check_matrix_content(mat))
  assert(tm.check_matrix_content(mat))


def test_passthough_py2py():
  mat =  generate_matrix()
  returned_mat = tm.passthru(mat)
  assert(mat.flags['C_CONTIGUOUS'])
  assert(mat.shape == (10, 10, 3))
  assert(check_matrix_content(mat))




def test_slice():
  pass



def test_pointer():
  pass

def test_slicing():
  pass

def test_class_member():
  pass


def test_return_by_ref():
  pass

def test_return_by_value():
  pass

def test_return_by_pointer():
  pass

def test_return_by_argument_by_ref():
  pass

def test_return_by_argument_by_value():
  pass

def test_return_by_argument_by_pointer():
  pass



# # Read from c++
# a = test.read_image("test.png")
# print('init a: 0x%x' % id(a))
# test.show_image(a)  # work

# # Check continuous problem from old version
# b = a[:, :, 0]
# test.show_image(b)  # work no more continous problem
# print('diff b: 0x%x' % id(b))

# c = copy.deepcopy(b)
# test.show_image(c)  # still works
# print('diff c: 0x%x' % id(c))


# # Proves that it's still the same thing
# d = test.passthru(a)
# print('same d: 0x%x' % id(d))

# # Make a copy
# e = test.clone(d)
# print('diff e: 0x%x' % id(e))


# # different allocator
# f = np.zeros(shape=(100, 100), dtype=np.uint8)
# print('\ninit e: 0x%x' % id(f))

# g = test.passthru(f)
# print('same f: 0x%x' % id(g))


# # example of class
# my_class = test.AddClass(1)
# h = my_class.add(f)
# print(f[0, 0])  # expected 0
# print(h[0, 0])  # expected 1
