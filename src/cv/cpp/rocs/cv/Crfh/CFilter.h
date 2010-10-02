/*
 * CFilter.h
 *
 */

#ifndef CFILTER_H_
#define CFILTER_H_

#include "rocs/math/Matrix_.h"

namespace rocs {
namespace cv {

using rocs::math::Matrix_;
//template<typename _T> class Matrix_;

/** How many sigmas should the gaussian filter contain. */
#define GAUSSIAN_SIGMAS 3

enum FilterType {
	/** Unknown type. */
	FT_UNKNOWN = 0,

	/** Gaussian filter. */
	FT_GAUSSIAN,

	/** Cartesian filter. */
	FT_CARTESIAN,

};

/**
 * Interface of a class storing information about a filter.
 */
class CFilterInfo {

public:

	/** Constructor. */
	CFilterInfo(FilterType filterType) :
		_filterType(filterType) {
	}

	/** Returns filter type. */
	FilterType getFilterType() const {
		return _filterType;
	}

	/** Comparison operator. */
	inline virtual bool operator==(const CFilterInfo& fi) const {
		return fi._filterType == _filterType;
	}

private:

	/** Filter type. */
	FilterType _filterType;

};

/**
 * Interface of a class implementing a 2D filter.
 */
class CFilter {

public:

	/** Destructor. */
	inline virtual ~CFilter() {
		if (_filterInfo)
			delete _filterInfo;
	}

	/** Applies the filter to the input matrix. */
	virtual Matrix_<double> *apply(const Matrix_<double> &input,
			Matrix_<double> *result) const = 0;

	/** Returns the filter info. */
	inline const CFilterInfo &getFilterInfo() const {
		return *_filterInfo;
	}

public:

	/** Creates a filter of a given type. */
	static CFilter *createFilter(const CFilterInfo &fi);

protected:

	/** Constructor. */
	CFilter(CFilterInfo *filterInfo) :
		_filterInfo(filterInfo) {
	}

protected:

	/** Filter type. */
	CFilterInfo *_filterInfo;

};

/**
 * Gaussian filter info
 */
class CGaussianFilterInfo: public CFilterInfo {

public:

	/** Constructor. */
	CGaussianFilterInfo(double sigma2) :
		CFilterInfo(FT_GAUSSIAN), _sigma2(sigma2) {
	}

	/** Comparison operator. */
	inline virtual bool operator==(const CFilterInfo& fi) const {
		if (CFilterInfo::operator==(fi)) {
			if (reinterpret_cast<const CGaussianFilterInfo&> (fi)._sigma2
					== _sigma2)
				return true;
		}
		return false;
	}

	/** Returns sigma^2. */
	inline double getSigma2() const {
		return _sigma2;
	}

private:

	/** Sigma^2 */
	double _sigma2;

};

/**
 * Gaussian filter
 */
class CGaussianFilter: public CFilter {

public:

	/** Constructor. */
	inline CGaussianFilter(double sigma2) :
		CFilter(new CGaussianFilterInfo(sigma2)) {
		createGaussHorizontalKernel(sigma2);
		createGaussVerticalKernel(sigma2);
	}

	/** Applies the filter to the input matrix. */
	virtual Matrix_<double> *apply(const Matrix_<double> &input,
			Matrix_<double> *result) const;

	/** Returns the filter info. */
	const CGaussianFilterInfo *getFilterInfo() {
		return reinterpret_cast<CGaussianFilterInfo *> (_filterInfo);
	}

private:

	/** Creates vertical component of a separable Gaussian filter. */
	void createGaussVerticalKernel(double sigma2);

	/** Creates horizontal component of a separable Gaussian filter. */
	void createGaussHorizontalKernel(double sigma2);

private:

	/** Vertical component of a separable Gaussian filter. */
	Matrix_<double> _verticalKernel;

	/** Horizontal component of a separable Gaussian filter. */
	Matrix_<double> _horizontalKernel;

};

/**
 * Cartesian filter info
 */
class CCartesianFilterInfo: public CFilterInfo {

public:

	/** Constructor. */
	CCartesianFilterInfo(int dx, int dy) :
		CFilterInfo(FT_CARTESIAN), _dx(dx), _dy(dy) {
	}

	/** Comparison operator. */
	inline virtual bool operator==(const CFilterInfo& fi) const {
		if (CFilterInfo::operator==(fi)) {
			if ((reinterpret_cast<const CCartesianFilterInfo&> (fi)._dx == _dx)
					&& (reinterpret_cast<const CCartesianFilterInfo&> (fi)._dy
							== _dy))
				return true;
		}
		return false;
	}

	/** Returns the order of differentiation in the x axis. */
	inline int getDx() const {
		return _dx;
	}

	/** Returns the order of differentiation in the y axis. */
	inline int getDy() const {
		return _dy;
	}

private:

	int _dx;

	int _dy;
};

/**
 * Cartesian filter
 */
class CCartesianFilter: public CFilter {

public:

	/** Constructor. */
	inline CCartesianFilter(int dx, int dy) :
		CFilter(new CCartesianFilterInfo(dx, dy)) {
		createXKernel(dx);
		createYKernel(dy);
	}

	/** Applies the filter to the input matrix. */
	virtual Matrix_<double> *apply(const Matrix_<double> &input,
			Matrix_<double> *result) const;

	/** Returns the filter info. */
	const CCartesianFilterInfo *getFilterInfo() {
		return reinterpret_cast<CCartesianFilterInfo *> (_filterInfo);
	}

private:

	/** Creates horizontal kernel. */
	void createXKernel(int dx);

	/** Creates vertical kernel. */
	void createYKernel(int dy);

private:

	/** Horizontal kernel. */
	Matrix_<double> _xKernel;

	/** Vertical kernel. */
	Matrix_<double> _yKernel;

};

} // end namespace cv
} // end namespace rocs

#endif /* CFILTER_H_ */
