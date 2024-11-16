add_executable(automata_app main.cpp)
target_compile_features(automata_app PRIVATE cxx_std_17)

target_link_libraries(automata_app PRIVATE automata_lib)
