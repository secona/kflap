project('kflap', 'cpp', default_options: ['cpp_std=c++23', 'optimization=2'])

raylib_dep = dependency('raylib')

include_dir = include_directories('include')

kflap_src = []

subdir('src')

executable(
  'kflap',
  kflap_src,
  dependencies: raylib_dep,
  include_directories: include_dir,
)
