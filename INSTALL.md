Installation Instructions
=========================

Please follow the instructions for your operating system.
CMake is used as a build system for ROCS.


Linux
-----

#### To configure ROCS, use the following commands:
    mkdir BUILD
    cd BUILD
    ccmake ..
In ccmake, select compilation options (e.g. the modules that should be compiled). 
Moreover, use the ${ROCS_DIR} variable to specify the directory to which ROCS should be installed.
ROCS can be installed to the directory where the source code is located or any other directory in the system.
Alternatively, you can run the configure.sh script.

#### To compile and install ROCS use
    make install -C BUILD
from the root source directory. ROCS will be installed to ${ROCS_DIR}.
Alternatively, you can run the make.sh script.

Windows
-------