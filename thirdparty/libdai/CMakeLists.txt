include_directories(include)

set(SOURCES 
  src/graph.cpp src/dag src/bipgraph.cpp src/varset.cpp 
  src/daialg.cpp src/alldai.cpp src/clustergraph.cpp 
  src/factor.cpp src/factorgraph.cpp src/properties.cpp 
  src/regiongraph src/util.cpp src/weightedgraph.cpp 
  src/exceptions.cpp src/exactinf.cpp src/evidence.cpp 
  src/emalg.cpp src/io.cpp src/bp.cpp src/fbp.cpp 
  src/trwbp.cpp src/mf.cpp src/hak.cpp src/lc.cpp 
  src/treeep.cpp src/jtree.cpp src/mr.cpp src/gibbs.cpp 
  src/bbp.cpp src/cbp.cpp src/bp_dual.cpp)

add_library(dai SHARED ${SOURCES})

# Remove deprecated includes messages
set_property(TARGET dai PROPERTY COMPILE_FLAGS "-Wno-deprecated")

# Installation
install(TARGETS dai LIBRARY DESTINATION ${ROCS_DIR}/lib ARCHIVE DESTINATION lib)
install(DIRECTORY include/dai DESTINATION ${ROCS_DIR}/include)

