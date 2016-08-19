#ifndef _IKAROS_POINT_H_
#define _IKAROS_POINT_H_

#include "vector.h"

namespace WingCore
{
	template<class T>
	class Point
	{
	public:
		Point(T x=0, T y=0, T z=0)
			:x(x),y(y),z(z){}

		~Point(){}

		template<class u>
		inline Point<T> operator+(const Vector<u> &v) const;

		template<class u>
		inline Point<T>& operator+=(const Vector<u> &v);

		template<class u>
		inline Point<T> operator-(const Vector<u> &v) const;

		template<class u>
		inline Point<T>& operator-=(const Vector<u> &v);

		template<class u>
		inline Point<T> operator*(u n);

		template<class u>
		inline Point<T>& operator*=(u n);

		inline Vector<T> operator-(const Point<T> &p) const;

		T x, y, z;
	};


	//--------------------------------------

	//--------------------------------------

	template<class T>
	template<class u>
	inline Point<T> Point<T>::operator+(const Vector<u> &v) const
	{
		return Point<T>(x + v.x, y + v.y, z + v.z);
	}

	template<class T>
	template<class u>
	inline Point<T>& Point<T>::operator+=(const Vector<u> &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	template<class T>
	template<class u>
	inline Point<T> Point<T>::operator-(const Vector<u> &v) const
	{
		return Point<T>(x - v.x, y - v.y, z - v.z);
	}

	template<class T>
	template<class u>
	inline Point<T>& Point<T>::operator-=(const Vector<u> &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template<class T>
	template<class u>
	inline Point<T> Point<T>::operator*(u n)
	{
		return Point<T>(x * n, y * n, z * n);
	}

	template<class T>
	template<class u>
	inline Point<T>& Point<T>::operator*=(u n)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	template<class T>
	inline Vector<T> Point<T>::operator-(const Point<T> &p) const
	{
		return Vector<T>(x - p.x, y - p.y, z - p.z);
	}

	typedef Point<int> Pointi;
	typedef Point<float> Pointf;

}


#endif