#include "rocs/ml.h"

//#include <opencv2/core/core.hpp>

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
	double p[2][2] = {{1,2}, {3,4}};
	cv::Mat potentials(2, 2, CV_64F, p);
	FactorClass fc1 = fcs.addFactorClass(vc1, vc2, potentials);

	// Variables
	Variable v1 = fg.addVariable(vc1);
	Variable v2 = fg.addVariable(vc1);
	Variable v3 = fg.addVariable(vc2);

	// Factors
	double p1[2] = {10,11};
	cv::Mat potentials2(2, 0, CV_64F, p1);
	Factor f1 = fg.addFactor(v2, potentials2);
	Factor f2 = fg.addFactor(v1, v2, fc1);
	Factor f3 = fg.addFactor(v2, v3, fc1);


	DaiBpFactorGraphSolver solver(&fg);
	solver.solve();

	solver.saveDaiGraph("test.fg");

}
