import numpy as np
from test_modules.test_modules as test


def test_return_by_ref():
  a = test.ClassForReturn()
  assert(id(a.returnByRef) == id(a.returnByRef))

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
