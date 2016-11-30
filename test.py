import build.eb as eb
import copy

a = eb.read_image("test.png")
eb.show_image(a)  # work

b=a[:,:,0]
eb.show_image(b)  # don't work continous problem

c=copy.deepcopy(b)
eb.show_image(c)  # work
