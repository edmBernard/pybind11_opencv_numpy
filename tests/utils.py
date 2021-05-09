import numpy as np


def generate_matrix():
  return np.arange(10*12*3, dtype=np.uint16).reshape((10, 12, 3))


def check_matrix_content(mat):
  return np.all(generate_matrix() == mat)
