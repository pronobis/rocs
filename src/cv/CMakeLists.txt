if(ROCS_BUILD_MODULE_CV)

	add_rocs_cpp_module(cv
		SOURCES FeatureExtractor.cc ImageIO.cc Img.cc Surf/SurfExtractor.cc Crfh/CChannelCache.cc Crfh/CCrfh.cc Crfh/CDescriptor.cc Crfh/CDescriptorList.cc Crfh/CFilterCache.cc Crfh/CFilter.cc Crfh/CScaleSpaceCache.cc Crfh/CSystem.cc Crfh/CrfhInterface.cc
		HEADERS FeatureExtractor.h ImageIO.h Img.h Surf/SurfExtractor.h Crfh/CChannelCache.h Crfh/CCrfh.h Crfh/CDescriptor.h Crfh/CDescriptorList.h Crfh/CFilterCache.h Crfh/CFilter.h Crfh/Crfh.h Crfh/CScaleSpaceCache.h Crfh/CSystem.h Crfh/CrfhInterface.h
		LINK ${OPENCV_LIBRARIES}
		LINK_MODULES core math)

	# Tests
	add_rocs_cpp_test_suite(test1)

endif(ROCS_BUILD_MODULE_CV)


  


  
