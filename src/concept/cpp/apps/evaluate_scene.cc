#include "rocs/ml.h"

using namespace rocs;
using namespace rocs::ml;

int main(int argc, char **argv)
{
	VariableClassSet vcs;
	FactorClassSet fcs;

	VariableClass v1 = vcs.addVariableClass(ml::VVT_BOOL);
	VariableClass v2 = vcs.addVariableClass(ml::VVT_BOOL);

	cv::Mat potentials;
	FactorClass f1 = fcs.addFactorClass(v1, v2, potentials);


}
