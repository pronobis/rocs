/*
 * ElemMath.h
 *
 */

#ifndef ELEMMATH_H_
#define ELEMMATH_H_

namespace rocs {
namespace math {

/*! Returns minimum of two values. */
template<class T>
inline T aMin(T val1, T val2) {
	if (val1 < val2)
		return val1;
	return val2;
}

/*! Returns maximum of two values. */
template<class T>
inline T aMax(T val1, T val2) {
	if (val1 < val2)
		return val2;
	return val1;
}

/*!
 * returns true if the argument is a space or a tab or a newline
 * \param c
 *          the char to analyze
 * \return <code>true</code> if the argument is a space or a tab or a newline
 */
inline bool aIsWhiteChar(char c) {
	return (c == ' ') || (c == '\n') || (c == '\t');
}

/*!
 * returns true if the argument is a newline
 * \param c
 *          the char to analyze
 * \return <code>true</code> if the argument is a newline
 */
inline bool aIsNewLine(char c) {
	return (c == '\n');
}

/*!
 * round a double to the closest integer
 * \param x
 *          the double to round
 * \return
 *          the closest integer
 */
inline int aRound(double x) {
	return int(x > 0.0 ? x + 0.5 : x - 0.5);
}

} // end namespace math
} // end namespace rocs

#endif /* ELEMMATH_H_ */
