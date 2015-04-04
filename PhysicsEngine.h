/*
 * Cursor.h
 *
 *  Created on: 22 Dec 2010
 *      Author: Mohsen
 */

#pragma once
#include "Camera.h"
class PhysicsEngine
{
private:
	int **landMap; //data of the land the model is in
	int gravity; //gravity of the environment
	Camera * character;
	float currentSpeed ;
	bool isJumping;
	bool movingVertically;
	float verticalDistanceMoved;
	float originalY;
	float previousY;
	float height;
	bool ducking;
	bool unducking;
	bool isDucked;
public:
	PhysicsEngine(int heightMap[1024][1024],int gravity, Camera * camera){
		this->landMap = new int*[1024];
		for(int i = 0 ; i < 1024 ; i++){
			landMap[i] = new int[1024];
		}

		for(int i = 0 ; i < 1024 ; i++){
			for(int j = 0 ; j < 1024 ; j++){
				landMap[i][j] = heightMap[i][j];
			}
		}
		this->currentSpeed = 0;
		this->gravity = gravity;
		this->character = camera;
		previousY = camera->Position.y;
		isJumping = false;
		movingVertically = false;
		verticalDistanceMoved = 0.0f;
		height = 16.0f;
		ducking = false;
		unducking = false;
		isDucked = false;
	}

	void duck(){
		if(!ducking&&!unducking){
			if(isDucked){
				verticalDistanceMoved = height/3;
				movingVertically = true;
				unducking = true;
				isDucked = false;
				gravity = gravity/2.0f;
			}
			else{
				verticalDistanceMoved = -height/3;
				movingVertically = true;
				ducking = true;
				isDucked = true;
				gravity = gravity*2.0f;
			}


		}
	}

	void setGravity(int gravity){
		this->gravity = gravity;
	}

	void jump(){
		 if(isJumping){
			 return;
		 }
		 isJumping = true;
		 originalY = character->Position.y;
		 currentSpeed = 1;
	}
	float getYAt(float x , float z){
		if(x<0||x>1023||z<0||z>1023){
			return 0;
		}
		return landMap[(int)x][(int)z]+height;
	}

	float abs(float num){
		return num<0?-num:num;
	}

	void move(){
		if(movingVertically){
			return;
		}

		int newX = character->Position.x;
		int newZ = character->Position.z;
		if(newX<0||newX>1023||newZ<0||newZ>1023){
			return;
		}else{

			 
				movingVertically = true;tempDistance = 0;
				this->verticalDistanceMoved = landMap[newX][newZ]+height-previousY;
				previousY = landMap[newX][newZ]+height;
				//character->Position.y = this->landMap[newX][newZ]+12;
				 
			 

			  
		}
		 //character->Update();
	}
	float tempDistance;
	void frame(){

	 	if(movingVertically){
			character->Position.y += this->verticalDistanceMoved/20;
			tempDistance+= verticalDistanceMoved/20;
			 
			character->Update();
			if(abs(tempDistance)>= abs(verticalDistanceMoved)){
				movingVertically = false;
				ducking = false;
				unducking = false;
			}
		}


		if(!isJumping){
			return;
		}
		if(currentSpeed>-1.0f && character->Position.y >= originalY){
		currentSpeed -= 0.5*gravity*3/1000;
		character->Position.y +=currentSpeed;
		character->Update();
		}
		else{
			currentSpeed = 0;
			character->Position.y = originalY;
			character->Update();
			isJumping = false;
		}


		 
	}

	~PhysicsEngine(void);
};

