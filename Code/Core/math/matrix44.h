#ifndef _IAKROS_MATRIX44_H_
#define _IAKROS_MATRIX44_H_

#include <memory>
#include "vector.h"
#include "point.h"
#include "math\math.h"
#include "common\defines.h"

namespace WingCore
{
	typedef union _matrix_data
	{
		real _data[4][4];
		real data[16];
	}matrix_data;

	class WING_CORE_API Matrix44
	{
	public:
		Matrix44();

		Matrix44(real n);

		Matrix44(real m[4][4]);

		Matrix44(const Matrix44& m);

		Matrix44(real a, real b, real c, real d,
			real e, real f, real g, real h,
			real i, real j, real k, real l,
			real m, real n, real o, real p);

		~Matrix44(){}
		
		Matrix44& operator=(const Matrix44 &m);

		inline real operator[](int i) const;

		inline const Matrix44& operator *= (const Matrix44 &m);

		inline Matrix44 operator*(const Matrix44 &m);

		inline Matrix44 operator*(const real &v);

		template <class T>
		inline Vector<T> operator*(const Vector<T> &v);

		template <class T>
		const Matrix44 &    setAxisAngle(const Vector<T>& ax, T ang);

		template <class T>
		const Matrix44 &    setRotate(const Vector<T> &r);

		template <class T>
		const Matrix44 &    setScale(const Vector<T> s);

		template <class T>
		const Matrix44 &    setTranslation(const Vector<T> &t);

		//×ªÖÃ
		inline const Matrix44 &	transpose() const;
		//Äæ
		inline const bool	inverse(Matrix44 &m) const;

		//--------------------------------------
		// static

		inline static void multiply(const Matrix44 &a, const Matrix44 &b, Matrix44& c);

		template<class T>
		inline static void multiply(const Matrix44 &m, const Vector<T> &src, Vector<T> &det);



		matrix_data mData;
	};


	//--------------------------------------

	//--------------------------------------

	inline Matrix44& Matrix44::operator=(const Matrix44 &m)
	{
		memcpy(mData.data, m.mData.data, sizeof(mData.data));
		return *this;
	}

	inline real Matrix44::operator[](int i) const
	{
		return mData.data[i];
	}

	inline const Matrix44& Matrix44::operator *= (const Matrix44 &m)
	{
		Matrix44 tmp(0.0f);

		multiply(*this, m, tmp);
		*this = tmp;

		return *this;
	}

	inline Matrix44 Matrix44::operator*(const Matrix44 &m)
	{
		Matrix44 tmp(0.0f);

		multiply(*this, m, tmp);

		return tmp;
	}

	inline Matrix44 Matrix44::operator*(const real &v)
	{
		Matrix44 tmp(*this);
		for (uint8 i = 0; i < 16; i++)
		{
			tmp.mData.data[i] = tmp.mData.data[i] * v;
		}
		return tmp;
	}

	template <class T>
	inline Vector<T> Matrix44::operator*(const Vector<T> &v)
	{
		Vector<T> des;
		multiply(*this, v, des);
		return des;
	}

	template <class T>
	const Matrix44 & Matrix44::setAxisAngle(const Vector<T>& ax, T ang)
	{
		Vector<T> unit(ax.normalize());
		T sine = Math<T>::sin(ang);
		T cosine = Math<T>::cos(ang);

		mData._data[0][0] = unit[0] * unit[0] * (1 - cosine) + cosine;
		mData._data[0][1] = unit[0] * unit[1] * (1 - cosine) + unit[2] * sine;
		mData._data[0][2] = unit[0] * unit[2] * (1 - cosine) - unit[1] * sine;
		mData._data[0][3] = 0;

		mData._data[1][0] = unit[0] * unit[1] * (1 - cosine) - unit[2] * sine;
		mData._data[1][1] = unit[1] * unit[1] * (1 - cosine) + cosine;
		mData._data[1][2] = unit[1] * unit[2] * (1 - cosine) + unit[0] * sine;
		mData._data[1][3] = 0;

		mData._data[2][0] = unit[0] * unit[2] * (1 - cosine) + unit[1] * sine;
		mData._data[2][1] = unit[1] * unit[2] * (1 - cosine) - unit[0] * sine;
		mData._data[2][2] = unit[2] * unit[2] * (1 - cosine) + cosine;
		mData._data[2][3] = 0;

		mData._data[3][0] = 0;
		mData._data[3][1] = 0;
		mData._data[3][2] = 0;
		mData._data[3][3] = 1;

		return *this;
	}

	template <class T>
	const Matrix44& Matrix44::setRotate(const Vector<T> &r)
	{
		T cos_rz, sin_rz, cos_ry, sin_ry, cos_rx, sin_rx;
		T m00, m01, m02;
		T m10, m11, m12;
		T m20, m21, m22;

		cos_rz = Math<T>::cos(r[2]);
		cos_ry = Math<T>::cos(r[1]);
		cos_rx = Math<T>::cos(r[0]);

		sin_rz = Math<T>::sin(r[2]);
		sin_ry = Math<T>::sin(r[1]);
		sin_rx = Math<T>::sin(r[0]);

		m00 = cos_rz *  cos_ry;
		m01 = sin_rz *  cos_ry;
		m02 = -sin_ry;
		m10 = -sin_rz *  cos_rx + cos_rz * sin_ry * sin_rx;
		m11 = cos_rz *  cos_rx + sin_rz * sin_ry * sin_rx;
		m12 = cos_ry *  sin_rx;
		m20 = -sin_rz * -sin_rx + cos_rz * sin_ry * cos_rx;
		m21 = cos_rz * -sin_rx + sin_rz * sin_ry * cos_rx;
		m22 = cos_ry *  cos_rx;

	

		mData._data[0][0] = mData._data[0][0] * m00 + mData._data[1][0] * m01 + mData._data[2][0] * m02;
		mData._data[0][1] = mData._data[0][1] * m00 + mData._data[1][1] * m01 + mData._data[2][1] * m02;
		mData._data[0][2] = mData._data[0][2] * m00 + mData._data[1][2] * m01 + mData._data[2][2] * m02;
		mData._data[0][3] = mData._data[0][3] * m00 + mData._data[1][3] * m01 + mData._data[2][3] * m02;

		mData._data[1][0] = mData._data[0][0] * m10 + mData._data[1][0] * m11 + mData._data[2][0] * m12;
		mData._data[1][1] = mData._data[0][1] * m10 + mData._data[1][1] * m11 + mData._data[2][1] * m12;
		mData._data[1][2] = mData._data[0][2] * m10 + mData._data[1][2] * m11 + mData._data[2][2] * m12;
		mData._data[1][3] = mData._data[0][3] * m10 + mData._data[1][3] * m11 + mData._data[2][3] * m12;

		mData._data[2][0] = mData._data[0][0] * m20 + mData._data[1][0] * m21 + mData._data[2][0] * m22;
		mData._data[2][1] = mData._data[0][1] * m20 + mData._data[1][1] * m21 + mData._data[2][1] * m22;
		mData._data[2][2] = mData._data[0][2] * m20 + mData._data[1][2] * m21 + mData._data[2][2] * m22;
		mData._data[2][3] = mData._data[0][3] * m20 + mData._data[1][3] * m21 + mData._data[2][3] * m22;

		return *this;
	}

	template<class T>
	const Matrix44& Matrix44::setScale(const Vector<T> s)
	{
		memset(mData.data, 0, sizeof(mData.data));
		mData._data[0][0] = s[0];
		mData._data[1][1] = s[1];
		mData._data[2][2] = s[2];
		mData._data[3][3] = 1;

		return *this;
	}

	template <class T>
	const Matrix44& Matrix44::setTranslation(const Vector<T> &t)
	{
		mData._data[0][0] = 1;
		mData._data[0][1] = 0;
		mData._data[0][2] = 0;
		mData._data[0][3] = 0;

		mData._data[1][0] = 0;
		mData._data[1][1] = 1;
		mData._data[1][2] = 0;
		mData._data[1][3] = 0;

		mData._data[2][0] = 0;
		mData._data[2][1] = 0;
		mData._data[2][2] = 1;
		mData._data[2][3] = 0;

		mData._data[3][0] = t[0];
		mData._data[3][1] = t[1];
		mData._data[3][2] = t[2];
		mData._data[3][3] = 1;

		return *this;
	}

	inline void Matrix44::multiply(const Matrix44 &a, const Matrix44 &b, Matrix44& c)
	{
		const float* ap = a.mData.data;
		const float* bp = b.mData.data;
		float* cp = c.mData.data;

		cp[0] = ap[0] * bp[0] + ap[1] * bp[4] + ap[2] * bp[8] + ap[3] * bp[12];
		cp[1] = ap[0] * bp[1] + ap[1] * bp[5] + ap[2] * bp[9] + ap[3] * bp[13];
		cp[2] = ap[0] * bp[2] + ap[1] * bp[6] + ap[2] * bp[10] + ap[3] * bp[14];
		cp[3] = ap[0] * bp[3] + ap[1] * bp[7] + ap[2] * bp[11] + ap[3] * bp[15];

		cp[4] = ap[4] * bp[0] + ap[5] * bp[4] + ap[6] * bp[8] + ap[7] * bp[12];
		cp[5] = ap[4] * bp[1] + ap[5] * bp[5] + ap[6] * bp[9] + ap[7] * bp[13];
		cp[6] = ap[4] * bp[2] + ap[5] * bp[6] + ap[6] * bp[10] + ap[7] * bp[14];
		cp[7] = ap[4] * bp[3] + ap[5] * bp[7] + ap[6] * bp[11] + ap[7] * bp[15];

		cp[8] = ap[8] * bp[0] + ap[9] * bp[4] + ap[10] * bp[8] + ap[11] * bp[12];
		cp[9] = ap[8] * bp[1] + ap[9] * bp[5] + ap[10] * bp[9] + ap[11] * bp[13];
		cp[10] = ap[8] * bp[2] + ap[9] * bp[6] + ap[10] * bp[10] + ap[11] * bp[14];
		cp[11] = ap[8] * bp[3] + ap[9] * bp[7] + ap[10] * bp[11] + ap[11] * bp[15];

		cp[12] = ap[12] * bp[0] + ap[13] * bp[4] + ap[14] * bp[8] + ap[15] * bp[12];
		cp[13] = ap[12] * bp[1] + ap[13] * bp[5] + ap[14] * bp[9] + ap[15] * bp[13];
		cp[14] = ap[12] * bp[2] + ap[13] * bp[6] + ap[14] * bp[10] + ap[15] * bp[14];
		cp[15] = ap[12] * bp[3] + ap[13] * bp[7] + ap[14] * bp[11] + ap[15] * bp[15];
	}

	template<class T>
	inline void Matrix44::multiply(const Matrix44 &m, const Vector<T> &src, Vector<T>& det)
	{
		T x, y, z, w;
	
		x = src[0] * m.mData._data[0][0] + src[1] * m.mData._data[1][0] + src[2] * m.mData._data[2][0] + m.mData._data[3][0];
		y = src[0] * m.mData._data[0][1] + src[1] * m.mData._data[1][1] + src[2] * m.mData._data[2][1] + m.mData._data[3][1];
		z = src[0] * m.mData._data[0][2] + src[1] * m.mData._data[1][2] + src[2] * m.mData._data[2][2] + m.mData._data[3][2];
		w = src[0] * m.mData._data[0][3] + src[1] * m.mData._data[1][3] + src[2] * m.mData._data[2][3] + m.mData._data[3][3];

		det.x = x / w;
		det.y = y / w;
		det.z = z / w;
	}


	inline const Matrix44 & Matrix44::transpose() const
	{
		return Matrix44(
			mData._data[0][0], mData._data[1][0], mData._data[2][0], mData._data[3][0],
			mData._data[0][1], mData._data[1][1], mData._data[2][1], mData._data[3][1],
			mData._data[0][2], mData._data[1][2], mData._data[2][2], mData._data[3][2],
			mData._data[0][3], mData._data[1][3], mData._data[2][3], mData._data[3][3]);
	}

	inline const bool Matrix44::inverse(Matrix44 &inverse) const
	{
		real a0 = mData.data[0] * mData.data[5] - mData.data[1] * mData.data[4];
		real a1 = mData.data[0] * mData.data[6] - mData.data[2] * mData.data[4];
		real a2 = mData.data[0] * mData.data[7] - mData.data[3] * mData.data[4];
		real a3 = mData.data[1] * mData.data[6] - mData.data[2] * mData.data[5];
		real a4 = mData.data[1] * mData.data[7] - mData.data[3] * mData.data[5];
		real a5 = mData.data[2] * mData.data[7] - mData.data[3] * mData.data[6];
		real b0 = mData.data[8] * mData.data[13] - mData.data[9] * mData.data[12];
		real b1 = mData.data[8] * mData.data[14] - mData.data[10] * mData.data[12];
		real b2 = mData.data[8] * mData.data[15] - mData.data[11] * mData.data[12];
		real b3 = mData.data[9] * mData.data[14] - mData.data[10] * mData.data[13];
		real b4 = mData.data[9] * mData.data[15] - mData.data[11] * mData.data[13];
		real b5 = mData.data[10] * mData.data[15] - mData.data[11] * mData.data[14];


		real det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

		// ÊÇ·ñ¿ÉÄæ
		if (!det)
			return false;

		inverse.mData.data[0] = mData.data[5] * b5 - mData.data[6] * b4 + mData.data[7] * b3;
		inverse.mData.data[1] = -mData.data[1] * b5 + mData.data[2] * b4 - mData.data[3] * b3;
		inverse.mData.data[2] = mData.data[13] * a5 - mData.data[14] * a4 + mData.data[15] * a3;
		inverse.mData.data[3] = -mData.data[9] * a5 + mData.data[10] * a4 - mData.data[11] * a3;

		inverse.mData.data[4] = -mData.data[4] * b5 + mData.data[6] * b2 - mData.data[7] * b1;
		inverse.mData.data[5] = mData.data[0] * b5 - mData.data[2] * b2 + mData.data[3] * b1;
		inverse.mData.data[6] = -mData.data[12] * a5 + mData.data[14] * a2 - mData.data[15] * a1;
		inverse.mData.data[7] = mData.data[8] * a5 - mData.data[10] * a2 + mData.data[11] * a1;

		inverse.mData.data[8] = mData.data[4] * b4 - mData.data[5] * b2 + mData.data[7] * b0;
		inverse.mData.data[9] = -mData.data[0] * b4 + mData.data[1] * b2 - mData.data[3] * b0;
		inverse.mData.data[10] = mData.data[12] * a4 - mData.data[13] * a2 + mData.data[15] * a0;
		inverse.mData.data[11] = -mData.data[8] * a4 + mData.data[9] * a2 - mData.data[11] * a0;

		inverse.mData.data[12] = -mData.data[4] * b3 + mData.data[5] * b1 - mData.data[6] * b0;
		inverse.mData.data[13] = mData.data[0] * b3 - mData.data[1] * b1 + mData.data[2] * b0;
		inverse.mData.data[14] = -mData.data[12] * a3 + mData.data[13] * a1 - mData.data[14] * a0;
		inverse.mData.data[15] = mData.data[8] * a3 - mData.data[9] * a1 + mData.data[10] * a0;

		inverse = inverse *  (1.0f/det);

		return true;

	}
}

#endif
