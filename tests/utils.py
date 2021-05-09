import numpy as np


def generate_matrix():
  return np.arange(10*10*3, dtype=np.uint16).reshape((10, 10, 3))


def check_matrix_content(mat):
  return np.any(generate_matrix() == mat)