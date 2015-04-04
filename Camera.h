/*
 * Camera.h
 *
 *  Created on: 15 Dec 2010
 *      Author: Mohab
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <math.h>

#include "Vector3.h"
#include "Core.h"

#define PI 3.14159265358979323846

class Camera
{
public:
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Forward;
	Vector3 Left;
	Vector3 Right;
	Vector3 target;

	Camera();
	void Update();
	float isTarget(Target t);
};

#endif
