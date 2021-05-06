import numpy as np
from .test_module import test_module as test


def test_return_by_ref():
  a = test.ClassForReturn()
  assert(id(a.returnByRef()) == id(a.returnByRef()))

def test_return_by_value():
  a = test.ClassForReturn()
  assert(id(a.returnByValue()) != id(a.returnByValue()))

def test_return_by_pointer():
  a = test.ClassForReturn()
  assert(id(a.returnByPointer()) == id(a.returnByPointer()))

def test_return_by_argument_by_ref():
  pass

def test_return_by_argument_by_value():
  pass

def test_return_by_argument_by_pointer():
  pass
