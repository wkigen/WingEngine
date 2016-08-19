#include "matrix44.h"

namespace WingCore
{

	Matrix44::Matrix44()
	{
		memset(mData.data, 0, sizeof(mData.data));
		mData._data[0][0] = 1;
		mData._data[1][1] = 1;
		mData._data[2][2] = 1;
		mData._data[3][3] = 1;
	}

	Matrix44::Matrix44(float n)
	{
		mData.data[0] = n;
		mData.data[1] = n;
		mData.data[2] = n;
		mData.data[3] = n;

		mData.data[4] = n;
		mData.data[5] = n;
		mData.data[6] = n;
		mData.data[7] = n;

		mData.data[8] = n;
		mData.data[9] = n;
		mData.data[10] = n;
		mData.data[11] = n;

		mData.data[12] = n;
		mData.data[13] = n;
		mData.data[14] = n;
		mData.data[15] = n;
	}

	Matrix44::Matrix44(float m[4][4])
	{
		memcpy(mData.data, m, sizeof(mData.data));
	}

	Matrix44::Matrix44(const Matrix44& m)
	{
		memcpy(mData.data, m.mData.data, sizeof(mData.data));
	}

	Matrix44::Matrix44(float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p)
	{
		mData.data[0] = a;
		mData.data[1] = b;
		mData.data[2] = c;
		mData.data[3] = d;

		mData.data[4] = e;
		mData.data[5] = f;
		mData.data[6] = g;
		mData.data[7] = h;

		mData.data[8] = i;
		mData.data[9] = j;
		mData.data[10] = k;
		mData.data[11] = l;

		mData.data[12] = m;
		mData.data[13] = n;
		mData.data[14] = o;
		mData.data[15] = p;
	}

}