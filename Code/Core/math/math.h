#ifndef _IAKROS_MATH_H_
#define _IAKROS_MATH_H_

#include <math.h>

namespace WingCore
{

#define PI 3.14159

#define MIN(x,y)	(x)>(y)?(y):(x)
#define MAX(x,y)	(x)>(y)?(x):(y)

	template <class T>
	struct Math
	{
		static T	acos(T x) { return ::acos(double(x)); }
		static T	asin(T x) { return ::asin(double(x)); }
		static T	atan(T x) { return ::atan(double(x)); }
		static T	atan2(T x, T y) { return ::atan2(double(x), double(y)); }
		static T	cos(T x) { return ::cos(double(x)); }
		static T	sin(T x) { return ::sin(double(x)); }
		static T	tan(T x) { return ::tan(double(x)); }
		static T	cosh(T x) { return ::cosh(double(x)); }
		static T	sinh(T x) { return ::sinh(double(x)); }
		static T	tanh(T x) { return ::tanh(double(x)); }
		static T	exp(T x) { return ::exp(double(x)); }
		static T	log(T x) { return ::log(double(x)); }
		static T	log10(T x) { return ::log10(double(x)); }
		static T	modf(T x, T *iptr)
		{
			double ival;
			T rval(::modf(double(x), &ival));
			*iptr = ival;
			return rval;
		}
		static T	pow(T x, T y) { return ::pow(double(x), double(y)); }
		static T	sqrt(T x) { return ::sqrt(double(x)); }
		static T	ceil(T x) { return ::ceil(double(x)); }
		static T	fabs(T x) { return ::fabs(double(x)); }
		static T	floor(T x) { return ::floor(double(x)); }
		static T	fmod(T x, T y) { return ::fmod(double(x), double(y)); }
		static T	hypot(T x, T y) { return ::hypot(double(x), double(y)); }
		static T	toRad(T x) { return x * PI / 180.0f; };
	};
}

#endif
