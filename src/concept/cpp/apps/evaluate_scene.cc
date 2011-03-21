#include "rocs/ml.h"

using namespace rocs;
using namespace rocs::ml;

int main(int argc, char **argv)
{
	// Sets and graphs
	VariableClassSet vcs;
	FactorClassSet fcs;
	FactorGraph fg;

	// Variable classes
	VariableClass vc1 = vcs.addVariableClass(ml::VVT_BOOL);
	VariableClass vc2 = vcs.addVariableClass(ml::VVT_BOOL);

	// Factor classes
	cv::Mat potentials;
	FactorClass fc1 = fcs.addFactorClass(vc1, vc2, potentials);

	// Variables
	Variable v1 = fg.addVariable(vc1);
	Variable v2 = fg.addVariable(vc1);
	Variable v3 = fg.addVariable(vc2);

	// Factors
	Factor f1 = fg.addFactor(fc1, v1);
	Factor f2 = fg.addFactor(fc1, v1, v2);
	Factor f3 = fg.addFactor(fc1, v2, v3);
}
