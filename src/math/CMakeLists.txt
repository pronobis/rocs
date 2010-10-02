if(ROCS_BUILD_MODULE_MATH)

	add_rocs_cpp_module(math
		SOURCES ElemMath.cc Matrix_.cc Matrix.cc SparseMatrix.cc Vector_.cc Vector.cc
		HEADERS Matrix_.h  Matrix.h ElemMath.h SparseMatrix.h Vector_.h Vector.h
		LINK ${OPENCV_LIBRARIES}
		LINK_MODULES core)

endif(ROCS_BUILD_MODULE_MATH)