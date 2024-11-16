# Note that headers are optional, and do not affect add_library, but they will not
# show up in IDEs unless they are listed in add_library.

# Optionally glob, but only for CMake 3.12 or later:
# file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${Automata_SOURCE_DIR}/include/automata/*.hpp")
set(HEADER_LIST 
				"${Automata_SOURCE_DIR}/include/automata/grid.h"
				"${Automata_SOURCE_DIR}/include/automata/cellular_automata_base.h"
				"${Automata_SOURCE_DIR}/include/automata/random_mt.h"
				"${Automata_SOURCE_DIR}/include/automata/lodepng.h"
				)

set(SOURCES_LIST
				"grid.cpp"
				"cellular_automata_base.cpp"
				"lodepng.cpp"
				)

# Make an automatic library - will be static or dynamic based on user setting
add_library(automata_lib ${SOURCES_LIST} ${HEADER_LIST})

# We need this directory, and users of our library will need it too
target_include_directories(automata_lib PUBLIC ../include)

# All users of this library will need at least C++11
target_compile_features(automata_lib PUBLIC cxx_std_11)

# IDEs should put the headers in a nice place
source_group(
  TREE "${PROJECT_SOURCE_DIR}/include"
  PREFIX "Header Files"
  FILES ${HEADER_LIST})
