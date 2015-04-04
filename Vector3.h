/*
 * Vector3.h
 *
 *  Created on: 22 Dec 2010
 *      Author: Mohab
 */

#ifndef VECTOR3_H_
#define VECTOR3_H_

class Vector3
{
public:
	float x, y, z;

	Vector3();
	Vector3(float xCoord, float yCoord, float zCoord);

	void operator +=(Vector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
	friend Vector3 operator +(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}
	void operator -=(Vector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
	friend Vector3 operator -(const Vector3& v1, const Vector3& v2)
	{
		return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}
};

#endif /* VECTOR3_H_ */
