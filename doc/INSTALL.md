Installation Instructions
=========================

# THIS DOCUMENT IS OUTDATED!

Please follow the instructions for your operating system.
CMake is used as a build system for ROCS.

Linux
-----

#### To compile ROCS, use the following commands:
    mkdir BUILD
    cd BUILD
    ccmake ..
In ccmake, select compilation options (e.g. the modules that should be compiled). 
Moreover, use the ${ROCS_DIR} variable to specify the directory to which ROCS should be installed.
ROCS can be installed to the directory where the source code is located or any other directory in the system.
Finally, type
    make


#### To install ROCS use
    make install
ROCS will be installed to ${ROCS_DIR}.


Windows
-------