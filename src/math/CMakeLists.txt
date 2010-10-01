# C++
## Dependencies
depend_on_boost(1.40.0 COMPONENTS program_options property_tree USEDBY "Module Math")

## Definition of the module
add_rocs_cpp_module(math
	SOURCES ElemMath.cc Matrix_.cc Matrix.cc SparseMatrix.cc Vector_.cc Vector.cc
	HEADERS Matrix_.h  Matrix.h ElemMath.h SparseMatrix.h Vector_.h Vector.h
	)


