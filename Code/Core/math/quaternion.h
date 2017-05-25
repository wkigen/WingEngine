#ifndef _QUATERNION_H_
#define _QUATERNION_H_

#include "matrix44.h"
#include "vector.h"

namespace WingCore
{
	class Quaternion
	{
	public:

		Quaternion(real _x = 0, real _y = 0, real _z = 0, real _w = 0)
			:x(_x), y(_y), z(_z) ,w(_w){}

		Quaternion(Vectorf v,real angle)
		{
			fromAxisAngle(v, angle);
		}

		~Quaternion() {}

		inline void fromAxisAngle(const Vectorf v, float angle);

		inline Quaternion operator*(const Quaternion &q) const;
		inline Quaternion operator*=(const Quaternion &q);

		inline real length() const;
		inline void normalize();


		inline Matrix44 toMatrix() const;


		real x, y, z, w;
	};


	inline void Quaternion::fromAxisAngle(const Vectorf v, real angle)
	{
		real radians = Math<real>::toRad(angle);

		real sinThetaDiv2 = (real)Math<real>::sin(real(radians / 2.0f));

		x = v.x * sinThetaDiv2;
		y = v.y * sinThetaDiv2;
		z = v.z * sinThetaDiv2;

		w = (real)Math<real>::cos(real(radians / 2.0f));
	}

	inline Quaternion Quaternion::operator*(const Quaternion &q) const
	{
		Quaternion r;

		r.x = w * q.x + x * q.w + y * q.z - z * q.y;
		r.y = w * q.y - x * q.z + y * q.w + z * q.x;
		r.z = w * q.z + x * q.y - y * q.x + z * q.w;
		r.w = w * q.w - x * q.x - y * q.y - z * q.z;

		return r;
	}

	inline Quaternion Quaternion::operator*=(const Quaternion &q)
	{
		real tx, ty, tz, tw;
		tx = w * q.x + x * q.w + y * q.z - z * q.y;
		ty = w * q.y - x * q.z + y * q.w + z * q.x;
		tz = w * q.z + x * q.y - y * q.x + z * q.w;
		tw = w * q.w - x * q.x - y * q.y - z * q.z;

		x = tx;
		y = ty;
		z = tz;
		w = tw;
		return (*this);
	}


	inline real Quaternion::length() const
	{
		return Math<real>::sqrt(x * x + y * y + z * z + w * w);
	}

	inline void Quaternion::normalize()
	{
		float len = length();
		x /= len;
		y /= len;
		z /= len;
		w /= len;
	}

	inline Matrix44 Quaternion::toMatrix() const
	{
		Matrix44 mat(
			1.0f - 2.0f * y * y - 2.0f * z * z, 2.0f * x * y - 2.0f * z * w, 2.0f * x * z + 2.0f * y * w, 0.0f,
			2.0f * x * y + 2.0f * z * w, 1.0f - 2.0f * x * x - 2.0f * z * z, 2.0f * y * z - 2.0f * x * w, 0.0f,
			2.0f * x * z - 2.0f * y * w, 2.0f * y * z + 2.0f * x * w, 1.0f - 2.0f * x * x - 2.0f * y * y, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		return mat;
	}

}


#endif // !_QUATERNION_H_