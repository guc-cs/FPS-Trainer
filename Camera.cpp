/*
 * Camera.cpp
 *
 *  Created on: 15 Dec 2010
 *      Author: Mohab
 */

#include "Camera.h"

Vector3::Vector3()
{
}
;

Vector3::Vector3(float xCoord, float yCoord, float zCoord)
{
	x = xCoord;
	y = yCoord;
	z = zCoord;
}

Camera::Camera()
{
	Position = Vector3(0, 0, 0);
	Rotation = Vector3(0, 0, 0);
	Forward = Vector3(0, 0, 1);
	Left = Vector3(-1, 0, 0);
	Right = Vector3(1, 0, 0);
	target = Vector3(0, 0, 0);
}

void Camera::Update()
{
	target.x = 5 * cos(PI * Rotation.x / 180) * sin(PI * Rotation.y / 180)
			+ Position.x;
	target.y = 5 * sin(PI * Rotation.x / 180) + Position.y;
	target.z = 5 * cos(PI * Rotation.x / 180) * cos(PI * Rotation.y / 180)
			+ Position.z;
	Forward.x = (target.x - Position.x) / 5;
	Forward.y = (target.y - Position.y) / 5;
	Forward.z = (target.z - Position.z) / 5;
	Left.x = sin(PI * ((Rotation.y + 90) / 180));
	Left.z = cos(PI * ((Rotation.y + 90) / 180));
	Right.x = sin(PI * ((Rotation.y - 90) / 180));
	Right.z = cos(PI * ((Rotation.y - 90) / 180));
}

float Camera::isTarget(Target t)
{
	Vector3 diff = Position - t.position;
	float dist = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
	Vector3 viewPt;
	viewPt.x = dist * cos(PI * Rotation.x / 180) * sin(PI * Rotation.y / 180)
			+ Position.x;
	viewPt.y = dist * sin(PI * Rotation.x / 180) + Position.y;
	viewPt.z = dist * cos(PI * Rotation.x / 180) * cos(PI * Rotation.y / 180)
			+ Position.z;
	viewPt -= t.position;
	float dif = sqrt(pow(viewPt.x, 2) + pow(viewPt.y, 2) + pow(viewPt.z, 2));
	if (dif <= 10)
		return dist;
	return 1024;
}
