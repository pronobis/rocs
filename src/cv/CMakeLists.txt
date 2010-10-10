if(ROCS_BUILD_MODULE_CV)

	add_rocs_cpp_module(cv
		SOURCES FeatureExtractor.cc ImageIO.cc Img.cc Surf/SurfExtractor.cc Crfh/ChannelCache.cc Crfh/Crfh.cc Crfh/Descriptor.cc Crfh/DescriptorList.cc Crfh/FilterCache.cc Crfh/Filter.cc Crfh/ScaleSpaceCache.cc Crfh/System.cc Crfh/CrfhInterface.cc
		HEADERS FeatureExtractor.h ImageIO.h Img.h Surf/SurfExtractor.h Crfh/ChannelCache.h Crfh/Crfh.h Crfh/Descriptor.h Crfh/DescriptorList.h Crfh/FilterCache.h Crfh/Filter.h Crfh/rfh.h Crfh/ScaleSpaceCache.h Crfh/System.h Crfh/CrfhInterface.h
		LINK ${OPENCV_LIBRARIES}
		LINK_MODULES core math)

	# Tests
	add_rocs_cpp_test_suite(imageIo)

endif(ROCS_BUILD_MODULE_CV)


  


  
