/*
 * Cursor.h
 *
 *  Created on: 22 Dec 2010
 *      Author: Mohsen
 */

#include "SphereBarrier.h"
#include <math.h>

class CollisionEngine
{
private:
	int barriersCount;
	int maximum;
	SphereBarrier** sphereBarriers;


public:

	 
	//Maximum is the maximum number of spheres in the collision engine
	//Maximim has to be more than 1
	CollisionEngine(int maximum){
		this->maximum = maximum-1;
		this->barriersCount = 0;
		this->sphereBarriers = new SphereBarrier*[maximum];
	}

	//Adds a barrier to the collision system , the method returns
	//the id of that sphere in the system
	int registerBarrier(float x,float y, float z, float radius){
		SphereBarrier* newBarrier = new SphereBarrier(x,y,z,radius);
		this->sphereBarriers[maximum-1] = newBarrier;
		
		if(doesCollide(maximum-1)==-1){
			this->sphereBarriers[barriersCount] = newBarrier;
			barriersCount++;
			return barriersCount-1;
		}
		else{
			return -1; //indicates an error
		}

	}

	/*
	* moveSphere :
	* id = Id of the sphere to move
	* x,y,z = New coordinates of the center of the sphere
	* method returns a number , if there is no collision , then it returns -1,
	* and the move is registered. if the number is not -1, that means there is a collision
	* with a sphere of a certain id( the value returned)
	*/
	int moveSphere(int sphereId, float x , float y, float z){

		float savedX = sphereBarriers[sphereId]->getX();
		float savedY = sphereBarriers[sphereId]->getY();
		float savedZ = sphereBarriers[sphereId]->getZ();

		sphereBarriers[sphereId]->setX(x);
		sphereBarriers[sphereId]->setY(y);
		sphereBarriers[sphereId]->setZ(z);

		int collisionResult = doesCollide(sphereId);

		if(collisionResult!=-1){
			sphereBarriers[sphereId]->setX(savedX);
			sphereBarriers[sphereId]->setY(savedY);
			sphereBarriers[sphereId]->setZ(savedZ);
		}

		return collisionResult;

	}

	//Returns the id of the sphere that the sphere with id sphereId
	//collides with , if there is no collision , -1 is returned
	int doesCollide(int sphereId){

		for(int i = 0 ; i<this->barriersCount ; i++){

			if(i==sphereId){
				continue;
			}
			else{
				float difX = sphereBarriers[i]->getX() - sphereBarriers[sphereId]->getX();
				float difY = sphereBarriers[i]->getY() - sphereBarriers[sphereId]->getY();
				float difZ = sphereBarriers[i]->getZ() - sphereBarriers[sphereId]->getZ();

				//Get the minimum accepted distance between the 2 spheres
				float minDistance = sphereBarriers[i]->getRadius() + sphereBarriers[sphereId]->getRadius();

				//Get the actual distance between the 2 spheres
				float distance = sqrt(difX*difX + difY*difY + difZ*difZ);

				if(distance<minDistance){
					return i;
				}

			}

		}

		return -1; //-1 indicates no collisions
	}

	~CollisionEngine(void);
};

