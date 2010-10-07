/*
 * CCrfh.h
 *
 * Contains declaration of the CCrfh class.
 */

#ifndef CCRFH_H_
#define CCRFH_H_

// STD includes
#include <vector>
using std::vector;
#include <sstream>
using std::ostream;
#include <map>
using std::map;

// type declaration
typedef std::map<int, double> MapType;

namespace rocs {

namespace math {
template<typename _T> class Matrix_;
}

namespace cv {

class CDescriptorList;

/*!
 * Node of a libsvm sparse vector.
 */
//struct CSvmNode {
//	int index;
//	double value;
//};
typedef std::pair<int, double> CSvmNode;

class CCrfh: public MapType {

public:

	/*! Constructor. Creates a histogram from a set of
	 outputs of descriptors. */
	CCrfh(vector<math::Matrix_<double> *> outputs, const CDescriptorList &descrList,
			int skipBorderPixels);

	/*! Zeroes small values in the histogram. The function removes those
	 values that divided by maximum value are smaller than min_val. */
	void filter(double min_val);

	/*! Normalizes the histogram - divides each bin by the sum of all. */
	void normalize();

	/*! Serializes the histogram to a file in the libSVM format. */
	void serialize(ostream &stream);

	/*! Returns a libSVM compatible sparse vector containing the histogram. */
	CSvmNode *getLibSvmVector();

private:

	/*! Sum of all values before normalization. */
	double _sum;

	/*! Maximal value before normalization. */
	double _max;

};

} // end namespace cv
} // end namespace rocs

#endif /* CCRFH_H_ */
