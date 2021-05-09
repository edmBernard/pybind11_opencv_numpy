try:
  # windows
  from build.Release import test_module
except:
  # linux
  from build import test_module
