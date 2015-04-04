/*
 * Cursor.h
 *
 *  Created on: 22 Dec 2010
 *      Author: Mohsen
 */

class SphereBarrier
{
	//x,y,z are the coordinates of the sphere , radius is the radius

private:
	float x;
	float y;
	float z;
	float radius;


public:
	SphereBarrier(float x,float y,float z,float radius);

	//Getters of x,y,z and radius
	float getX();
	float getY();
	float getZ();
	float getRadius();

	//setters of x,y,z and radius
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setRadius(float radius);

	 
};

