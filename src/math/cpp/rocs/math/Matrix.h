#ifndef MATRIX_H_
#define MATRIX_H_

/* openCV includes */
#include <opencv/cv.h>
#include <opencv/cxcore.hpp>
// rename the opencv namespace not to collide with rocs::cv
namespace opencv = cv;

/* definitions */
#define MAT_DECOMP_LU		2//DECOMP_LU
#define MAT_DECOMP_CHOLESKY	DECOMP_CHOLESKY

#include "rocs/core/Core.h"
#include "rocs/math/ElemMath.h"
#include "rocs/core/Types.h"

namespace rocs {
namespace math {

/*!
 * the Matrix class declaration
 *
 * It is NOT templated. For the templated version of the matrices, cf Matrix_.h
 *
 * Here is the whole inheritance scheme :
 *
 *   cv::Mat
 *
 *      |
 *      |
 *      V
 *
 *   Matrix    ------------> Vector   (contains a subset of functions of Matrix)
 *
 *      |                       |
 *      |                       |
 *      V                       V
 *
 *  Matrix_<...>             Vector_<...>
 *
 */
class Matrix: private opencv::Mat {
public:
	/* constructors and destructors */
	//	Matrix(cv::Mat cv_matrix) {	};

	/*! an empty constructor */
	Matrix() :
		opencv::Mat() {
	}

	/*!
	 * the constructor for a given size
	 *
	 * \param rows number of rows
	 * \param cols number of columns
	 * \param type the data_type of data : MAT_8U -> MAT_64F
	 * \return
	 */
	Matrix(int rows, int cols, int type);

	/*! the destructor */
	~Matrix();

	/* data access */
	/*! \return the type of data stored inside the matrix */
	inline int getDataType() const {
		return data_type;
	}

	/*! a cast to the opencv underlying matrix */
	const opencv::Mat asConstOpenCvMat() const {
		return (const opencv::Mat) (*this);
	}

	/*! a cast to the opencv underlying matrix */
	inline opencv::Mat* asOpenCvMat() {
		return (opencv::Mat*) this;
	}

	/*! the number of channels in the matrix */
	inline int channels() const {
		return MAT_MAT_CN(flags);
	}

	// size
	/*! the number of columns */
	int nbCols() const;
	/*! the number of rows */
	int nbRows() const;
	//	inline CvSize size() {
	//		return cvSize(nbCols(), nbRows());
	//	}

	//	const char* infoCString() const {
	//		const char answer[500];
	//		sprintf(answer, "Matrix:%ix%i, data_type:%i, channel:%i, depth:%i", nbCols(), nbRows(), getDataType(), channels(), depth());
	//		return answer;
	//	}

	/*!
	 * Create a string of information about the Matrix : its size, type...
	 * \return    the created string
	 */
	string infoString() const {
		ostringstream m;
		m << "Matrix:";
		m << nbCols() << 'x' << nbRows() << ", ";
		m << "data_type:" << getDataType() << ", ";
		m << "channels:" << channels() << ", ";
		m << "depth:" << depth();
		return m.str().c_str();
	}

	/*!
	 * if DEBUG mode,
	 * check if the given arguments are within the range of the matrix
	 * and triggers an error if this fails
	 * \param row
	 *          the row to check
	 * \param col
	 *          the col to check
	 */
	inline void dbgAssertRangeCheck(const int row, const int col) const {
		//debugPrintf_lvl3("dbgAssertRangeCheck(%i, %i)", row, col);
		DbgAssert( row >= 0 && row < nbRows() && col >=0 && col < nbCols());
	}

	/*!
	 * get one of the values
	 *
	 * \param row the row where to get the value
	 * \param col the column where to get the value
	 * \return the value at (row, col)
	 */
	//	template<typename _T> _T get(const int row, const int col) const {
	template<typename _T> _T get(int row, int col) const {
		dbgAssertRangeCheck(row, col);
		return at<_T> (row, col);
	}

	/**
	 * change one of the values of the matrix
	 *
	 * \param row the row where to change the value
	 * \param col the column where to change the value
	 * \param value the new value
	 */
	template<typename _T>
	inline void set(int row, int col, _T value) {
		dbgAssertRangeCheck(row, col);
		this->at<_T> (row, col) = value;
	}

	//	/*
	//	 * get a pointer to a chosen row of the matrix
	//	 *
	//	 * \param     i the row index
	//	 * \return    a pointer to the row
	//	 */
	// TODO write function
	//	Matrix row_(int i) const {
	//		cv::Mat ans = (static_cast<const cv::Mat*> (this))->row(i);
	//		//		return (Matrix) this->row(i);
	//	}

	/*!
	 * copy the content of the matrix into another one
	 *
	 * \param   dst
	 *           the matrix where you want to copy the values.
	 * 			 They have to be of the same kind.
	 *           However the size does not matter,
	 *           dst will be resized if needed.
	 */
	void copyTo(Matrix dst) const;

	template<typename _Tsrc, typename _Tdst>
	void copyTo_(Matrix dst) {
		debugPrintf_lvl3("copyTo_(%s, %s)", infoString().c_str(), dst.infoString().c_str());

		/* resize if needed */
		if (dst.nbCols() != nbCols() || dst.nbRows() != nbRows()) {
			//			char msg[300];
			//			sprintf(
			//					msg,
			//					"The sizes (%ix%i) and (%ix%i) are different. Crashing now !",
			//					nbRows(), nbCols(), dst.nbRows(), dst.nbCols());
			//			Error (-1, msg);
			// bug - resize not working
			debugPrintf_lvl3("Resizing the target to %ix%i", nbRows(), nbCols());
			dst.resize(nbRows(), nbCols());
		}

		for (int i = 0; i < nbRows(); ++i)
			for (int j = 0; j < nbCols(); ++j)
				dst.set<_Tdst> (i, j, get<_Tsrc> (i, j));
	}

	/*!
	 * fill the matrix with a given value
	 *
	 * \param value the value to fill with
	 */
	template<typename _T>
	inline void fill(_T value) {
		for (int col = 0; col < nbCols(); ++col) {
			for (int row = 0; row < nbRows(); ++row) {
				set<_T> (row, col, value);
				//at<_T> (row, col) = value;
			}
		}
	}

	/*! return the length of the data inside the matrix */
	template<typename _T>
	inline long dataLength() {
		return sizeof(_T) * nbCols() * nbRows();
	}

	/*!
	 * a method to fill quickly the matrix with 0.
	 * It relies on memset, faster than a for loop
	 * (cf http://www.cppreference.com/wiki/c/string/memset )
	 */
	template<typename _T>
	inline void fillWithZeros() {
		memset((static_cast<opencv::Mat*> (this))->data, '\0',
				dataLength<_T> ());
	}

	/*! Returns true if the matrix is empty. */
	inline bool isEmpty() const {
		return (static_cast<const opencv::Mat*> (this))->empty();
	}

	/*! the depth of the data  */
	inline int depth() const {
		return (static_cast<const opencv::Mat*> (this))->depth();
	}

	/** Resizes the matrix if the current size if different than given. */
	inline void resize(int rows, int cols) {
		debugPrintf_lvl3("resize(%ix%i)", rows, cols);
		asOpenCvMat()->create(rows, cols, getDataType());
		debugPrintf_lvl3("new format(%s)", infoString().c_str());
	}

	/* sub matrices */
	//	const Matrix<_T> subMatrix(int r, int c, int w, int h);

	/*! equality operators */
	bool operator ==(const Matrix &m) const;
	bool operator !=(const Matrix &m) const;

	/*! + operator */
	Matrix* operator +(const Matrix &m) const;
	//Matrix* operator +=(const Matrix &m);

	/*! - operator */
	Matrix* operator -(const Matrix &m) const;

	/*! * operator */
	Matrix* operator *(const Matrix &m) const;

	/*! / operator */
	bool operator /=(double factor);

	// transpose
	/*!
	 * TODO does not work for int matrices
	 *
	 * \return the determinant of the matrix
	 */
	double det();

	/*!
	 * \return a new Matrix corresponding to the transposed current
	 */
	Matrix* transpose() const;

	/*!
	 * \return a new Matrix corresponding to the inversed current
	 */
	Matrix* inverse(int method = MAT_DECOMP_LU) const;

	/*! Convolves the matrix with another matrix.
	 * The size of the matrix remains identical (as in case
	 * of matlabs conv2(,,'same').
	 *
	 * \param m
	 *          the matrix to convolove with
	 */
	template<typename _T>
	void convolveWith(const Matrix &m) {
		debugPrintf_lvl3("convolveWith(m:%s)", m.infoString().c_str());

		/* Do noting for empty matrices or kernels */
		if ((isEmpty()) || (m.isEmpty()))
			return;

		/* Get some info about the filter */
		int mRows = m.nbRows();
		int mCols = m.nbCols();

		int mPreMidRow = (mRows - 1) / 2;
		int mPreMidCol = (mCols - 1) / 2;
		int mPostMidRow = mRows - 1 - mPreMidRow;
		int mPostMidCol = mCols - 1 - mPreMidCol;

		/* Create new data */
		//double *newData = aMalloc<double> (_rows * _cols);
		//double *newDataPtr = newData;
		//Matrix* mC = new Matrix(mRows, mCols, m.getDataType());
		Matrix* mC = new Matrix(nbRows(), nbCols(), getDataType());

		/* Compute convolution */
		for (int i = 0; i < nbRows(); ++i)
			for (int j = 0; j < nbCols(); ++j) {
				int startRow = aMax<int> (i - mPreMidRow, 0);
				int endRow = aMin<int> (i + mPostMidRow, nbRows() - 1);
				int startCol = aMax<int> (j - mPreMidCol, 0);
				int endCol = aMin<int> (j + mPostMidCol, nbCols() - 1);

				//(*newDataPtr) = 0;
				double newData = 0;

				for (int k = startRow; k <= endRow; ++k)
					for (int l = startCol; l <= endCol; ++l)
						// TODO check formula
						//					(*newDataPtr) += get(k, l) * m.get(mPreMidRow - (i
						//							- k), mPreMidCol - (j - l));
						newData += this->get<_T> (k, l) * m.get<_T> (mPreMidRow
								- (i - k), mPreMidCol - (j - l));
				mC->set<_T> (i, j, newData);

				//++newDataPtr;
			}

		/* Substitute the old data with the new data */
		//		cout << "mC:" << mC->toString() << endl;
		mC->copyTo(*this);
		delete mC;
		//aFree( _data);
		//this->data = newData;
	}

	//void convolveWithFft(const Matrix &m);

	/*!
	 * Convolves two matrices. The size of the resulting
	 * matrix will be the same as the size of the matrix A.
	 * (as in case of matlabs conv2(,,'same').
	 *
	 * \param mA
	 *          the first matrix to convolve
	 * \param mB
	 *          the second matrix to convolve
	 * \param mC
	 *          the result matrix to populate (optional)
	 * \return
	 *          A convolved with B
	 */
	template<typename _T>
	static Matrix *convolve(const Matrix &mA, const Matrix &mB, Matrix *mC = 0) {
		debugPrintf_lvl3("convolve(mA:%s, mB:%s)", mA.infoString().c_str(), mB.infoString().c_str() );
		// Do noting for empty matrices
		if (mA.isEmpty() || mB.isEmpty())
			return mC;

		// Get some info about the filter
		int mARows = mA.nbRows();
		int mACols = mA.nbCols();
		int mBRows = mB.nbRows();
		int mBCols = mB.nbCols();

		int mBPreMidRow = (mBRows - 1) / 2;
		int mBPreMidCol = (mBCols - 1) / 2;
		int mBPostMidRow = mBRows - 1 - mBPreMidRow;
		int mBPostMidCol = mBCols - 1 - mBPreMidCol;

		// Create the resulting matrix
		if (mC) {
			if (mC->nbCols() == mACols && mC->nbRows() == mARows) {
				debugPrint_lvl3("mC of the good size.");
			} else {
				debugPrint_lvl3("resizing mC...");
				mC->resize(mARows, mACols);
			}
		} else { //mC = null
			debugPrint_lvl3("Creating mC...");
			//int data_type  = mA.getDataType();
			mC = new Matrix(mARows, mACols, mA.getDataType());
		}
		//double *newDataPtr = mC->getRawData();

		// Compute convolution
		for (int i = 0; i < mARows; ++i)
			for (int j = 0; j < mACols; ++j) {
				int startRow = aMax<int> (i - mBPreMidRow, 0);
				int endRow = aMin<int> (i + mBPostMidRow, mARows - 1);
				int startCol = aMax<int> (j - mBPreMidCol, 0);
				int endCol = aMin<int> (j + mBPostMidCol, mACols - 1);

				//(*newDataPtr) = 0;
				double newData = 0;

				for (int k = startRow; k <= endRow; ++k)
					for (int l = startCol; l <= endCol; ++l) {
						//						debugPrintf_lvl3("-(%i,%i) : add %f", k, l, mA.get<_T> (k, l) * mB.get<_T> (mBPreMidRow
						//										- (i - k), mBPreMidCol - (j - l)));
						newData += mA.get<_T> (k, l) * mB.get<_T> (mBPreMidRow
								- (i - k), mBPreMidCol - (j - l));
					}

				//				debugPrintf_lvl3("(%i,%i) : set %f", i, j, newData);
				mC->set<_T> (i, j, newData);
				//++newDataPtr;
			}

		//		debugPrint_lvl3("deleting mC...");
		//		delete mC;

		debugPrint_lvl3("convolve() finished");
		return mC;
	}

	/*!
	 * @return a string version of the matrix values
	 */
	string toString();

private:
	/*! the data_type of data inside the matrix */
	int data_type;

	///// operators
	/*! templated == operator */
	template<typename _T>
	inline bool equals(const Matrix &m) const {
		// sizes check
		if (!(nbCols() == m.nbCols() && nbRows() == m.nbRows()))
			return false;

		//	 check we have the same types
		if (data_type != m.data_type)
			return false;

		// check for every value
		for (int i = 0; i < nbRows(); ++i) {
			for (int j = 0; j < nbCols(); ++j) {
				if (get<_T> (i, j) != m.get<_T> (i, j))
					return false;
			}
		}
		// we reach here ? Seems they are really identical
		return true;
	}

	/*! templated + operator */
	template<typename _T>
	inline Matrix* plus(const Matrix &m) const {
		// size check
		DbgAssert( (nbCols() == m.nbCols() && nbRows() == m.nbRows()) );

		Matrix* ans = new Matrix(nbRows(), nbCols(), data_type);
		/// check for every value
		for (int i = 0; i < nbRows(); ++i) {
			for (int j = 0; j < nbCols(); ++j) {
				ans->set<_T> (i, j, get<_T> (i, j) + m.get<_T> (i, j));
			}
		}
		return ans;
	}

	/*! templated - operator */
	template<typename _T>
	inline Matrix* minus(const Matrix &m) const {
		// size check
		DbgAssert( (nbCols() == m.nbCols() && nbRows() == m.nbRows()) );

		Matrix* ans = new Matrix(nbRows(), nbCols(), data_type);
		/// check for every value
		for (int i = 0; i < nbRows(); ++i) {
			for (int j = 0; j < nbCols(); ++j) {
				ans->set<_T> (i, j, get<_T> (i, j) - m.get<_T> (i, j));
			}
		}
		return ans;
	}

	/*! templated * operator */
	template<typename _T>
	inline Matrix* times(const Matrix &m) const {
		// size check
		DbgAssert( nbCols() == m.nbRows() );

		Matrix* ans = new Matrix(nbRows(), nbCols(), data_type);
		/// check for every value
		for (int j = 0; j < m.nbCols(); j++) {
			for (int i = 0; i < nbRows(); i++) {
				double sum = 0;
				for (int k = 0; k < nbCols(); k++)
					sum += get<_T> (i, k) * m.get<_T> (k, j);
				ans->set(j, i, sum);
			} // end loop j
		} // end loop i
		return ans;
	}

};

} // end namespace math
} // end namespace rocs

#endif /* MATRIX_H_ */
