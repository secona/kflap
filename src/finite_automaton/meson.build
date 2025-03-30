finite_automaton_src = files('canvas.cpp', 'core.cpp')
kflap_src += finite_automaton_src

finite_automaton_lib = static_library(
  'finite_automaton',
  finite_automaton_src,
  include_directories: include_dir,
)
