import numpy as np
import example.example as eb
import copy

# Read from c++
a = eb.read_image("test.png")
print('init a: 0x%x' % id(a))
eb.show_image(a)  # work

# Check continuous problem from old version
b = a[:, :, 0]
eb.show_image(b)  # work no more continous problem
print('diff b: 0x%x' % id(b))

c = copy.deepcopy(b)
eb.show_image(c)  # still works
print('diff c: 0x%x' % id(c))


# Proves that it's still the same thing
d = eb.passthru(a)
print('same d: 0x%x' % id(b))

# Make a copy
e = eb.clone(d)
print('diff e: 0x%x' % id(e))


# different allocator
f = np.zeros(shape=(100, 100), dtype=np.uint8)
print('\ninit e: 0x%x' % id(f))

g = eb.passthru(f)
print('same f: 0x%x' % id(g))


# example of class
my_class = eb.AddClass(1)
h = my_class.add(f)
print(f[0, 0])  # expected 0
print(h[0, 0])  # expected 1
