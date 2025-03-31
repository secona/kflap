project('kflap', 'cpp', default_options: ['cpp_std=c++23', 'optimization=2'])

pugixml_dep = dependency('pugixml')
raylib_dep = dependency('raylib')
gtest_dep = dependency('gtest')
gtest_main_dep = dependency('gtest_main')

include_dir = include_directories('include')

kflap_src = []

subdir('src')

executable(
  'kflap',
  kflap_src,
  dependencies: [raylib_dep, pugixml_dep],
  include_directories: include_dir,
)
