#include "SphereBarrier.h"


	SphereBarrier::SphereBarrier(float x,float y,float z,float radius){
		this->x = x;
		this->y = y;
		this->z = z;
		this->radius = radius;
	}

	//Getters of x,y,z and radius
	float SphereBarrier:: getX(){
		return x;
	}
	float SphereBarrier:: getY(){
		return y;
	}
	float SphereBarrier:: getZ(){
		return z;
	}
	float SphereBarrier:: getRadius(){
		return radius;
	}

	//setters of x,y,z and radius
	void SphereBarrier:: setX(float x){
		this->x = x;
	}
	void SphereBarrier:: setY(float y){
		this->y = y;
	}
	void SphereBarrier:: setZ(float z){
		this->z = z;
	}
	void SphereBarrier:: setRadius(float radius){
		this->radius = radius;
	}
