#ifndef _IAKROS_VECTOR_H_
#define _IAKROS_VECTOR_H_

#include "common\platform.h"
#include "math.h"
#include "error\error.h"

namespace WingCore
{
	template<class T>
	class Vector
	{
	public:
		Vector(const Vector<T>& v);

		Vector(T _x = 0, T _y = 0, T _z = 0)
			:x(_x),y(_y),z(_z){}

		~Vector(){}

		inline Vector<T> operator+(const Vector<T> &v) const;

		inline Vector<T>& operator+=(const Vector<T> &v);

		inline Vector<T> operator-(const Vector<T> &v) const;

		inline Vector<T>& operator-=(const Vector<T> &v);

		template<class u>
		inline Vector<T> operator*(u n) const;

		template<class u>
		inline Vector<T>& operator*=(u n);

		template<class u>
		inline Vector<T> operator/(u n) const;

		template<class u>
		inline Vector<T>& operator/=(u n);

		inline T operator[](int n) const;

		inline float lengthSquared() const;

		inline float length() const;

		inline Vector<T>& normalize();

		inline Vector<T> normalize() const;

		inline T dot(const Vector<T> v);

		inline Vector<T> cross(const Vector<T> &v);

		inline Vector<T> abs();

		T x, y, z;
	};

	//--------------------------------------

	//--------------------------------------
	template<class T>
	Vector<T>::Vector(const Vector<T>& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	template<class T>
	inline Vector<T> Vector<T>::operator+(const Vector<T> &v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}

	template<class T>
	inline Vector<T>& Vector<T>::operator+=(const Vector<T> &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	template<class T>
	inline Vector<T> Vector<T>::operator-(const Vector<T> &v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}

	template<class T>
	inline Vector<T>& Vector<T>::operator-=(const Vector<T> &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	template<class T>
	template<class u>
	inline Vector<T> Vector<T>::operator*(u n) const
	{
		return Vector(x * n, y * n, z * n);
	}

	template<class T>
	template<class u>
	inline Vector<T>& Vector<T>::operator*=(u n)
	{
		x *= n;
		y *= n;
		z *= n;
		return *this;
	}

	template<class T>
	template<class u>
	inline Vector<T> Vector<T>::operator/(u n) const
	{
		WING_ASSERT(n != 0);
		return Vector(x / n, y / n, z / n);
	}

	template<class T>
	template<class u>
	inline Vector<T>& Vector<T>::operator/=(u n)
	{
		WING_ASSERT(n != 0);
		x /= n;
		y /= n;
		z /= n;
		return *this;
	}

	template<class T>
	inline T Vector<T>::operator[](int n) const
	{
		WING_ASSERT(n >= 0 && n<3);
		if (n == 0) return x;
		if (n == 1) return y;
		if (n == 2) return z;
	}

	template<class T>
	inline float Vector<T>::lengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	template<class T>
	inline float Vector<T>::length() const
	{
		return Math<T>::sqrt(lengthSquared());
	}

	template<class T>
	inline Vector<T>& Vector<T>::normalize()
	{
		T l = length();
		x /= l;
		y /= l;
		z /= l;
		return *this;
	}

	template<class T>
	inline Vector<T> Vector<T>::normalize() const
	{
		T l = length();

		return Vector<T>(x / l, y / l, z / l);
	}

	template<class T>
	inline T Vector<T>::dot(const Vector<T> v)
	{
		return x * v.x + y * v.y + z * v.z;
	}

	template<class T>
	inline Vector<T> Vector<T>::cross(const Vector<T> &v) {
		double v1x = x, v1y = y, v1z = z;
		double v2x = v.x, v2y = v.y, v2z = v.z;
		return Vector<T>((v1y * v2z) - (v1z * v2y), (v1z * v2x) - (v1x * v2z),
			(v1x * v2y) - (v1y * v2x));
	}

	template<class T>
	inline Vector<T> Vector<T>::abs() {
		return Vector<T>(ABS(x), ABS(y), ABS(z));
	}

	typedef Vector<real> Vectorf;
	typedef Vector<int> Vectori;

}



#endif
