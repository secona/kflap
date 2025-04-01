finite_automaton_src = files('canvas.cpp', 'core.cpp', 'simulator.cpp')
kflap_src += finite_automaton_src

finite_automaton_lib = static_library(
  'finite_automaton',
  finite_automaton_src,
  include_directories: include_dir,
)

finite_automaton_tests = executable(
  'finite_automaton_test',
  files('core_test.cpp'),
  include_directories: include_dir,
  link_with: [finite_automaton_lib],
  dependencies: [gtest_dep, gtest_main_dep, pugixml_dep],
)

test('Finite Automaton Tests', finite_automaton_tests)

finite_automaton_sim_tests = executable(
  'finite_automaton_sim_test',
  files('simulator_test.cpp'),
  include_directories: include_dir,
  link_with: [finite_automaton_lib],
  dependencies: [gtest_dep, gtest_main_dep, pugixml_dep],
)

test('Finite Automaton Simulator Tests', finite_automaton_sim_tests)
