/*
 * Types.h
 *
 * The different types of data we can store
 *
 *  Created on: Jun 18, 2010
 *      Author: arnaud
 */

#ifndef TYPES_H_
#define TYPES_H_

/* **** short defs from openCV */
#define  CV_1F            0x3f800000
#define CV_8U   0
#define CV_8S   1
#define CV_16U  2
#define CV_16S  3
#define CV_32S  4
#define CV_32F  5
#define CV_64F  6
/* *****/

#define MAT_UNKNOWN -1 // for unknown Types (shouldn't happen)
#define MAT_1U		CV_1F //10 // bool(true/false)
#define MAT_8U		CV_8U // uchar - 8-bit unsigned integers ( 0..255 )
#define MAT_8S		CV_8S // char - 8-bit signed integers ( -128..127 )
#define MAT_16U		CV_16U // unsigned short int - 16-bit unsigned integers ( 0..65535 )
#define MAT_16S		CV_16S // short int - 16-bit signed integers ( -32768..32767 )
#define MAT_32U		11 // unsigned int - 32-bit unsigned integers ( 0..4294967295 )
#define MAT_32S		CV_32S // int - 32-bit signed integers ( -2147483648..2147483647 )
#define MAT_32F		CV_32F // float - 32-bit floating-point numbers ( -FLT_MAX..FLT_MAX, INF, NAN )
#define MAT_64F		CV_64F // double - 64-bit floating-point numbers ( -DBL_MAX..DBL_MAX, INF, NAN )
//
// multi channel types - coming from OpenCV
#define MAT_CN_SHIFT             3
/** the functions to extract the depth from a type */
#define MAT_DEPTH_MAX            (1 << MAT_CN_SHIFT)
#define MAT_MAT_DEPTH_MASK       (MAT_DEPTH_MAX - 1)
#define MAT_MAT_DEPTH(flags)     ((flags) & MAT_MAT_DEPTH_MASK)
/** the functions to automatically build multi channel types */
#define MAT_MAKETYPE(depth,cn)   (MAT_MAT_DEPTH(depth) + (((cn)-1) << MAT_CN_SHIFT))
#define MAT_MAKE_TYPE            MAT_MAKETYPE
/** the functions to extract the number of channels from a type */
#define MAT_CN_MAX     64
#define MAT_MAT_CN_MASK          ((MAT_CN_MAX - 1) << MAT_CN_SHIFT)
#define MAT_MAT_CN(flags)        ((((flags) & MAT_MAT_CN_MASK) >> MAT_CN_SHIFT) + 1)

#define MAT_8UC1   MAT_MAKETYPE(MAT_8U,1)
#define MAT_8UC2   MAT_MAKETYPE(MAT_8U,2)
#define MAT_8UC3   MAT_MAKETYPE(MAT_8U,3)
#define MAT_8UC4   MAT_MAKETYPE(MAT_8U,4)
#define MAT_8UC(n) MAT_MAKETYPE(MAT_8U,(n))

#define MAT_8SC1   MAT_MAKETYPE(MAT_8S,1)
#define MAT_8SC2   MAT_MAKETYPE(MAT_8S,2)
#define MAT_8SC3   MAT_MAKETYPE(MAT_8S,3)
#define MAT_8SC4   MAT_MAKETYPE(MAT_8S,4)
#define MAT_8SC(n) MAT_MAKETYPE(MAT_8S,(n))

#define MAT_16UC1   MAT_MAKETYPE(MAT_16U,1)
#define MAT_16UC2   MAT_MAKETYPE(MAT_16U,2)
#define MAT_16UC3   MAT_MAKETYPE(MAT_16U,3)
#define MAT_16UC4   MAT_MAKETYPE(MAT_16U,4)
#define MAT_16UC(n) MAT_MAKETYPE(MAT_16U,(n))

#define MAT_16SC1   MAT_MAKETYPE(MAT_16S,1)
#define MAT_16SC2   MAT_MAKETYPE(MAT_16S,2)
#define MAT_16SC3   MAT_MAKETYPE(MAT_16S,3)
#define MAT_16SC4   MAT_MAKETYPE(MAT_16S,4)
#define MAT_16SC(n) MAT_MAKETYPE(MAT_16S,(n))

#define MAT_32SC1   MAT_MAKETYPE(MAT_32S,1)
#define MAT_32SC2   MAT_MAKETYPE(MAT_32S,2)
#define MAT_32SC3   MAT_MAKETYPE(MAT_32S,3)
#define MAT_32SC4   MAT_MAKETYPE(MAT_32S,4)
#define MAT_32SC(n) MAT_MAKETYPE(MAT_32S,(n))

#define MAT_32FC1   MAT_MAKETYPE(MAT_32F,1)
#define MAT_32FC2   MAT_MAKETYPE(MAT_32F,2)
#define MAT_32FC3   MAT_MAKETYPE(MAT_32F,3)
#define MAT_32FC4   MAT_MAKETYPE(MAT_32F,4)
#define MAT_32FC(n) MAT_MAKETYPE(MAT_32F,(n))

#define MAT_64FC1   MAT_MAKETYPE(MAT_64F,1)
#define MAT_64FC2   MAT_MAKETYPE(MAT_64F,2)
#define MAT_64FC3   MAT_MAKETYPE(MAT_64F,3)
#define MAT_64FC4   MAT_MAKETYPE(MAT_64F,4)
#define MAT_64FC(n) MAT_MAKETYPE(MAT_64F,(n))

namespace rocs {
namespace core {

/*!
 *
 * Define the traits that will be used to determine the best data type to work with.
 *
 * partly taken from the library CImg
 */
template<typename T> class Type {
public:
	static const char* string() {
		static const char* s[] = { "unknown", "unknown8", "unknown16",
				"unknown24", "unknown32", "unknown40", "unknown48",
				"unknown56", "unknown64", "unknown72", "unknown80",
				"unknown88", "unknown96", "unknown104", "unknown112",
				"unknown120", "unknown128" };
		return s[(sizeof(T) < 17) ? sizeof(T) : 0];
	}
	static bool isFloat() {
		return false;
	}
	static T min() {
		return (T) -1 > 0 ? (T) 0 : (T) -1 << (8 * sizeof(T) - 1);
	}
	static T max() {
		return (T) -1 > 0 ? (T) -1 : ~((T) -1 << (8 * sizeof(T) - 1));
	}
	static T defaultValue() {
		return min();
	}
	static T cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (T) val;
	}
	static const char* format() {
		return "%s";
	}
	static const char* format(const T val) {
		static const char * const s = "unknown";
		return s;
	}
	static int type_() {
		return MAT_UNKNOWN;
	}
	static T parse(char* value) {
		// TODO better than a stupid cast ?
		return (T) value;
	}
};

template<> class Type<bool> {
public:
	static const char* string() {
		static const char * const s = "bool";
		return s;
	}
	static bool isFloat() {
		return false;
	}
	static bool min() {
		return false;
	}
	static bool max() {
		return true;
	}
	static bool defaultValue() {
		return false;
	}
	static bool cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (bool) val;
	}
	static const char* format() {
		return "%s";
	}
	static const char* format(const bool val) {
		//static const char* s[] = { "false", "true" };
		//return s[val ? 1 : 0];
		return (val ? "true" : "false");
	}
	static int type_() {
		return MAT_1U;
	}
};

template<> class Type<unsigned char> {
public:
	static const char* string() {
		static const char * const s = "unsigned char";
		return s;
	}
	static bool isFloat() {
		return false;
	}
	static unsigned char min() {
		return 0;
	}
	static unsigned char max() {
		return (unsigned char) ~0U;
	}
	static unsigned char defaultValue() {
		return min();
	}
	static unsigned char cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (unsigned char) val;
	}
	static const char* format() {
		return "%u";
	}
	static unsigned int format(const unsigned char val) {
		return (unsigned int) val;
	}
	static int type_() {
		return MAT_8U;
	}
};

template<> class Type<char> {
public:
	static const char* string() {
		static const char * const s = "char";
		return s;
	}
	static bool isFloat() {
		return false;
	}
	static char min() {
		return (char) (-1L << (8 * sizeof(char) - 1));
	}
	static char max() {
		return ~((char) (-1L << (8 * sizeof(char) - 1)));
	}
	static char defaultValue() {
		return ' ';
	}
	static char cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (char) val;
	}
	static const char* format() {
		return "%d";
	}
	static int format(const char val) {
		return (int) val;
	}
	static int type_() {
		return MAT_8S; // TODO is it this ?
	}
};

template<> class Type<signed char> {
public:
	static const char* string() {
		static const char * const s = "signed char";
		return s;
	}
	static bool isFloat() {
		return false;
	}
	static signed char min() {
		return (signed char) (-1L << (8 * sizeof(signed char) - 1));
	}
	static signed char max() {
		return ~((signed char) (-1L << (8 * sizeof(signed char) - 1)));
	}
	static signed char defaultValue() {
		return ' ';
	}
	static signed char cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (signed char) val;
	}
	static const char* format() {
		return "%d";
	}
	static unsigned int format(const signed char val) {
		return (int) val;
	}
	static int type_() {
		return MAT_8S;
	}
};

template<> class Type<unsigned short> {
public:
	static const char* string() {
		static const char * const s = "unsigned short";
		return s;
	}
	static bool isFloat() {
		return false;
	}
	static unsigned short min() {
		return 0;
	}
	static unsigned short max() {
		return (unsigned short) ~0U;
	}
	static unsigned short defaultValue() {
		return 0;
	}
	static unsigned short cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (unsigned short) val;
	}
	static const char* format() {
		return "%u";
	}
	static unsigned int format(const unsigned short val) {
		return (unsigned int) val;
	}
	static int type_() {
		return MAT_16U;
	}
};

template<> class Type<short> {
public:
	static const char* string() {
		static const char * const s = "short";
		return s;
	}
	static bool isFloat() {
		return false;
	}
	static short min() {
		return (short) (-1L << (8 * sizeof(short) - 1));
	}
	static short max() {
		return ~((short) (-1L << (8 * sizeof(short) - 1)));
	}
	static short defaultValue() {
		return 0;
	}
	static short cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (short) val;
	}
	static const char* format() {
		return "%d";
	}
	static int format(const short val) {
		return (int) val;
	}
	static int type_() {
		return MAT_16S;
	}
};

template<> class Type<unsigned int> {
public:
	static const char* string() {
		static const char * const s = "unsigned int";
		return s;
	}
	static bool isFloat() {
		return false;
	}
	static unsigned int min() {
		return 0;
	}
	static unsigned int defaultValue() {
		return 0;
	}
	static unsigned int max() {
		return (unsigned int) ~0U;
	}
	static unsigned int cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (unsigned int) val;
	}
	static const char* format() {
		return "%u";
	}
	static unsigned int format(const unsigned int val) {
		return val;
	}
	static int type_() {
		return MAT_32U;
	}
};

template<> class Type<int> {
public:
	static const char* string() {
		static const char * const s = "int";
		return s;
	}
	static bool isFloat() {
		return false;
	}
	static int min() {
		return (int) (-1L << (8 * sizeof(int) - 1));
	}
	static int max() {
		return ~((int) (-1L << (8 * sizeof(int) - 1)));
	}
	static int defaultValue() {
		return 0;
	}
	static int cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (int) val;
	}
	static const char* format() {
		return "%d";
	}
	static int format(const int val) {
		return val;
	}
	static int type_() {
		return MAT_32S;
	}
};

//template<> class data_Type<unsigned long> {
//	public:static const char* string() {
//		static const char * const s = "unsigned long";
//		return s;
//	}
//	static bool isFloat() {
//		return false;
//	}
//	static unsigned long min() {
//		return 0;
//	}
//	static unsigned long max() {
//		return (unsigned long) ~0UL;
//	}
//static unsigned long defaultValue() {
//	return 0;
//}
//	static unsigned long cut(const double val) {
//		return val < (double) min() ? min() : val > (double) max() ? max()
//				: (unsigned long) val;
//	}
//	static const char* format() {
//		return "%lu";
//	}
//	static unsigned long format(const unsigned long val) {
//		return val;
//	}
//};
//
//template<> class data_Type<long> {
//	public:static const char* string() {
//		static const char * const s = "long";
//		return s;
//	}
//	static bool isFloat() {
//		return false;
//	}
//	static long min() {
//		return (long) (-1L << (8 * sizeof(long) - 1));
//	}
//	static long max() {
//		return ~((long) (-1L << (8 * sizeof(long) - 1)));
//	}
//static long defaultValue() {
//	return 0;
//}
//	static long cut(const double val) {
//		return val < (double) min() ? min() : val > (double) max() ? max()
//				: (long) val;
//	}
//	static const char* format() {
//		return "%ld";
//	}
//	static long format(const long val) {
//		return val;
//	}
//};

template<> class Type<float> {
public:
	static const char* string() {
		static const char * const s = "float";
		return s;
	}
	static bool isFloat() {
		return true;
	}
	static float min() {
		return -3.4E38f;
	}
	static float max() {
		return 3.4E38f;
	}
	static float defaultValue() {
		return 0;
	}
	static float cut(const double val) {
		return val < (double) min() ? min() : val > (double) max() ? max()
				: (float) val;
	}
	static float inf() {
		return max() * max();
	}//(float)cimg::data_Type<double>::inf(); } // TODO
	static float nan() {
		return std::sqrt(-1.0);
	}//(float)cimg::data_Type<double>::nan(); } // TODO
	static const char* format() {
		return "%g";
	}
	static double format(const float val) {
		return (double) val;
	}
	static int type_() {
		return MAT_32F;
	}
};

template<> class Type<double> {
public:
	static const char* string() {
		static const char * const s = "double";
		return s;
	}
	static bool isFloat() {
		return true;
	}
	static double min() {
		return -1.7E308;
	}
	static double max() {
		return 1.7E308;
	}
	static double defaultValue() {
		return min();
	}
	static double cut(const double val) {
		return val < min() ? min() : val > max() ? max() : val;
	}
	static double inf() {
		return max() * max();
	}
	static double nan() {
		static const double v_nan = std::sqrt(-1.0);
		return v_nan;
	}
	static const char* format() {
		return "%g";
	}
	static double format(const double val) {
		return val;
	}
	static int type_() {
		return MAT_64F;
	}
};

template<> class Type<string> {
public:
	static const char* string() {
		static const char * const s = "string";
		return s;
	}
	static bool isFloat() {
		return false;
	}
	static const char* defaultValue() {
		return "";
	}
	static const char* format() {
		return "%s";
	}
};

} // namespace core
} // namespace rocs

#endif /* TYPES_H_ */
