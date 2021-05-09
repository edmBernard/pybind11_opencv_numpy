import numpy as np
from tests import test_module as tm


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


def test_return_by_argument_by_ref():
  pass

def test_return_by_argument_by_value():
  pass

def test_return_by_argument_by_pointer():
  pass
