if(ROCS_BUILD_THIRDPARTY_BOOST_PROPERTY_TREE)
	install(DIRECTORY boost/property_tree DESTINATION include/boost)
	# Make available to others
	include_directories(.)
endif(ROCS_BUILD_THIRDPARTY_BOOST_PROPERTY_TREE)