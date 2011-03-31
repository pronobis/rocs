#include "rocs/concept.h"
#include "rocs/ml.h"

//#include <opencv2/core/core.hpp>

using namespace rocs;
using namespace rocs::ml;
using namespace rocs::concept;

int main(int argc, char **argv)
{
/*	// Sets and graphs
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
	Factor f3 = fg.addFactor(v2, v3, fc1);*/


	FactorGraph fg;
	ObjectRelationGraphGenerator orgg(&fg);
	orgg.addObject("A");
	orgg.addObject("B");
	orgg.addObject("T");
	orgg.addInRelationException("T","");
	orgg.addOnRelationException("T","");
	orgg.addOntRelationException("T","");
	orgg.addOnRelationObservation("B", "A", 0.05);
	orgg.addOnRelationObservation("A", "B", 0.8);
	orgg.addOnRelationObservation("B", "T", 0.8);
	orgg.addOnRelationObservation("A", "T", 0.05);
	orgg.addInRelationObservation("B", "A", 0.05);
	orgg.addInRelationObservation("A", "B", 0.05);
	orgg.addInRelationObservation("B", "T", 0);
	orgg.addInRelationObservation("A", "T", 0);
	orgg.generate();

	cout <<fg;

	DaiBpFactorGraphSolver solver(&fg);
	solver.solveMP();

	solver.saveDaiGraph("test.fg");

	vector<size_t> map = solver.getMAP();
	int i=0;
	for (FactorGraph::ConstVariableIterator it = fg.variableBegin(); it!=fg.variableEnd(); ++it)
	{
		cout << it->name() << " " << map[i] << endl;
		i++;
	}



	solver.solve();

	// Display results
	cout << "In:" << endl;
	for (size_t i=0; i<orgg.inRelations().size(); ++i)
	{
		const ObjectRelationGraphGenerator::Relation &r = orgg.inRelations()[i];
		dai::Factor f = solver.getMarginal(*r.variable);
		cout << r.object1Id << " IN " << r.object2Id << " " << f[1] << endl;
	}
	cout << "On:" << endl;
	for (size_t i=0; i<orgg.inRelations().size(); ++i)
	{
		const ObjectRelationGraphGenerator::Relation &r = orgg.onRelations()[i];
		dai::Factor f = solver.getMarginal(*r.variable);
		cout << r.object1Id << " ON " << r.object2Id << " " << f[1] << endl;
	}
	cout << "Ont:" << endl;
	for (size_t i=0; i<orgg.inRelations().size(); ++i)
	{
		const ObjectRelationGraphGenerator::Relation &r = orgg.ontRelations()[i];
		dai::Factor f = solver.getMarginal(*r.variable);
		cout << r.object1Id << " ONT " << r.object2Id << " " << f[1] << endl;
	}

}
