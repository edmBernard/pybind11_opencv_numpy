import numpy as np
from tests import test_module as tm
from tests.utils import generate_matrix, check_matrix_content

def test_return_by_value():
  a = tm.ClassForReturn()
  assert(id(a.returnByValue()) != id(a.returnByValue()))
  mat = a.returnByValue()
  a.changeInternal()
  assert(np.any(mat != a.returnByValue()))


def test_return_by_ref_but_copy():
  a = tm.ClassForReturn()
  assert(id(a.returnByRef()) != id(a.returnByRef()))
  mat = a.returnByRef()
  a.changeInternal()
  assert(np.any(mat != a.returnByValue()))


def test_return_by_ref():
  a = tm.ClassForReturn()
  assert(id(a.returnByRef()) != id(a.returnByRef()))
  mat = a.viewMatrix()
  a.changeInternal()
  assert(np.all(mat == a.returnByValue()))


def test_return_by_pointer():
  a = tm.ClassForReturn()
  assert(id(a.returnByPointer()) != id(a.returnByPointer()))
  mat = a.returnByPointer()
  a.changeInternal()
  assert(np.all(mat == a.returnByValue()))



def test_return_by_argument_by_value():
  mat = generate_matrix()
  tm.returnByArgumentValue(mat)

  # Not intuitive Argument passed by value can be changed by cpp
  # because the cast between from numpy.drarray to cv::Mat avoid copy by passing buffer
  assert(not check_matrix_content(mat))


def test_return_by_argument_by_ref():
  mat = generate_matrix()
  tm.returnByArgumentRef(mat)
  assert(np.any(mat != generate_matrix()))
  assert(not check_matrix_content(mat))


def test_return_by_argument_by_pointer():
  mat = generate_matrix()
  tm.returnByArgumentPointer(mat)
  assert(not check_matrix_content(mat))
