import numpy as np
from tests import test_module as tm


def test_return_by_ref():
  a = tm.ClassForReturn()
  assert(id(a.returnByRef()) == id(a.returnByRef()))

def test_return_by_value():
  a = tm.ClassForReturn()
  assert(id(a.returnByValue()) != id(a.returnByValue()))

def test_return_by_pointer():
  a = tm.ClassForReturn()
  assert(id(a.returnByPointer()) == id(a.returnByPointer()))

def test_return_by_argument_by_ref():
  pass

def test_return_by_argument_by_value():
  pass

def test_return_by_argument_by_pointer():
  pass
