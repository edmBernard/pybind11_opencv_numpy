import numpy as np
from tests import test_module as tm
import copy


def test_old():
  # Read from c++
  a =  tm.generate_matrix()

  # Check continuous problem from old version
  b = a[:, :, 0]
  assert(id(a) != id(b))

  c = copy.deepcopy(b)
  assert(id(b) != id(c))

  # Proves that it's still the same thing
  d = tm.passthru(a)
  assert(id(a) == id(d))

  # Make a copy
  e = tm.clone(d)
  assert(id(d) != id(e))

  # different allocator
  f = np.zeros(shape=(100, 100), dtype=np.uint8)
  g = tm.passthru(f)
  assert(id(f) == id(g))
