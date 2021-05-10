import numpy as np
from tests import test_module as tm
from tests.utils import generate_matrix, check_matrix_content


def test_return_by_value():
  a = tm.ClassForReturn()
  mat = a.returnByValue()
  a.changeInternal()
  assert(check_matrix_content(mat))
  changed_mat = a.returnByValue()
  assert(not check_matrix_content(changed_mat))


def test_return_by_ref_but_copy():
  a = tm.ClassForReturn()
  mat = a.returnByRef()
  a.changeInternal()
  assert(check_matrix_content(mat))
  changed_mat = a.returnByValue()
  assert(not check_matrix_content(changed_mat))


def test_return_by_ref():
  a = tm.ClassForReturn()
  mat = a.viewMatrix()
  a.changeInternal()
  # Currently return parameter perform a copy of the data, so the change is not repercuted to mat
  assert(check_matrix_content(mat))
  changed_mat = a.returnByValue()
  assert(not check_matrix_content(changed_mat))


def test_return_by_pointer():
  a = tm.ClassForReturn()
  mat = a.returnByPointer()
  a.changeInternal()
  # Currently return parameter perform a copy of the data, so the change is not repercuted to mat
  assert(check_matrix_content(mat))
  changed_mat = a.returnByValue()
  assert(not check_matrix_content(changed_mat))


def test_return_by_argument_by_value():
  mat = generate_matrix()
  tm.returnByArgumentValue(mat)

  # Not intuitive Argument passed by value can be changed by cpp
  # because the cast between from numpy.drarray to cv::Mat avoid copy by passing buffer
  assert(not check_matrix_content(mat))


def test_return_by_argument_by_ref():
  mat = generate_matrix()
  tm.returnByArgumentRef(mat)
  assert(not check_matrix_content(mat))


def test_return_by_argument_by_pointer():
  mat = generate_matrix()
  tm.returnByArgumentPointer(mat)
  assert(not check_matrix_content(mat))


def test_return_by_argument_by_value():
  mat = generate_matrix()
  # During allocation we create a new buffer the data are not linked anymore
  tm.returnByArgumentValueWithAllocation(mat)
  assert(check_matrix_content(mat))


def test_return_by_argument_by_ref():
  mat = generate_matrix()
  # During allocation we create a new buffer the data are not linked anymore
  tm.returnByArgumentRefWithAllocation(mat)
  assert(check_matrix_content(mat))
