from __future__ import print_function

import example as eb
import copy

a = eb.read_image("test.png")
print('init a: 0x%x' % id(a))
eb.show_image(a)  # work

# Proves that it's still the same thing
b = eb.passthru(a)
print('same b: 0x%x' % id(b))

# Make a copy
c = eb.clone(b)
print('diff c: 0x%x' % id(c))

d=copy.deepcopy(c)
eb.show_image(d)  # still works
print('diff d: 0x%x' % id(d))
