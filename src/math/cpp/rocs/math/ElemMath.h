/*
 * ElemMath.h
 *
 */

#ifndef ELEMMATH_H_
#define ELEMMATH_H_

namespace rocs {

namespace math {

/** Returns minimum of two values. */
template <class T>
inline T aMin(T val1, T val2)
  { if (val1<val2) return val1; return val2; }


/** Returns maximum of two values. */
template <class T>
inline T aMax(T val1, T val2)
  { if (val1<val2) return val2; return val1; }


inline bool aIsWhiteChar(char c)
  { return (c==' ') || (c=='\n') || (c=='\t'); }

inline bool aIsNewLine(char c)
  { return (c=='\n'); }


inline int aRound(double x)
{
   return int(x > 0.0 ? x + 0.5 : x - 0.5);
}

class ElemMath {
public:
};

}

}

#endif /* ELEMMATH_H_ */
