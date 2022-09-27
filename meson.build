project(
  'fdsac',
  'c',
  version: '0.1.0',
  license: 'MIT',
  default_options : ['warning_level=3']
)

src = [
  'src/array.c',
  'src/list.c',
  'src/set.c',
]

inc = include_directories('include')

fdsac_lib = library(
  'fdsac',
  src,
  include_directories: include_directories('include/fdsac'),
)

fdsac_dep = declare_dependency(link_with: fdsac_lib, include_directories: inc)

subdir('test')
