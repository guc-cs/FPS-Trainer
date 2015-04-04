/*
 * Cursor.h
 *
 *  Created on: 22 Dec 2010
 *      Author: Wallas
 */

#ifndef CORE_H_
#define CORE_H_

#include <stdio.h>
#include <queue>
#include <string>
#include <GL/glut.h>
#include "Vector3.h"
using namespace std;

class Weapon
{
public:
	unsigned char maxBullets;
	string name;
	unsigned char bulletsRemaining;
	unsigned char ammoRemaining;
	float damageFactor;

	Weapon()
	{
		maxBullets = 7;
		name = "Hand Gun";
		bulletsRemaining = 7;
		ammoRemaining = 0;
		damageFactor = 0;
	}

	Weapon(string n, unsigned char maxB)
	{
		name = n;
		maxBullets = maxB;
		bulletsRemaining = maxB;
		ammoRemaining = 0;
		damageFactor = 0;
	}

	float shoot(void)
	{
		if (bulletsRemaining != 0)
		{
			--bulletsRemaining;
			return damageFactor;
		}
		return -1.0;
	}

	void reload(void)
	{
		if (ammoRemaining >= maxBullets)
		{
			bulletsRemaining = maxBullets;
			ammoRemaining -= maxBullets;
		}
	}
};

class Player
{
public:
	string name;
	char health;
	char armor;
	Weapon currentWeapon;
	queue<Weapon> weapons;
	int highScore;
	int currentScore;

	Player(string n)
	{
		name = n;
		health = 100;
		armor = 0;
		weapons.push(*(new Weapon()));
		currentWeapon = weapons.front();
		highScore = 0;
		currentScore = 0;
	}

	Player(string n, int highS)
	{
		name = n;
		health = 100;
		armor = 0;
		weapons.push(*(new Weapon()));
		currentWeapon = weapons.front();
		currentScore = 0;
		highScore = highS;
	}

	float shoot(void)
	{
		return currentWeapon.shoot();
	}

	void reload(void)
	{
		currentWeapon.reload();
	}

	bool giveWeapon(Weapon w)
	{
		Weapon* ptr;
		Weapon currElem;
		ptr = &weapons.front();
		for (unsigned char i = 0; i < weapons.size(); ++i)
		{
			currElem = *ptr;
			if (currElem.name == w.name)
				return false;
			ptr++;
		}
		weapons.push(w);
		return true;
	}

	void updateHighScore(void)
	{
		highScore = (currentScore > highScore) ? currentScore : highScore;
	}

	void plusScore(int x)
	{
		currentScore += x;
	}

	void giveHealth(char h)
	{
		health = ((health + h) >= 100) ? 100 : health + h;
	}

	void giveArmor(char a)
	{
		armor = ((armor + a) >= 100) ? 100 : armor + a;
	}

};

class Target
{
public:
	int bounty;
	int distFromObserver;
	int health;
	int angle;
	bool isShot;
	bool isDestroyed;
	Vector3 position;
	bool isSelected;
	unsigned int texture;


	Target()
	{
	}

	Target(int posX, int posY, int posZ, char * filename)
	{
		isSelected = false;
		isShot = false;
		isDestroyed = false;
		angle = 0;
		//distFromObserver = d;
		bounty = 5 * distFromObserver;
		health = 0;
		position.x = posX;
		position.y = posY;
		position.z = posZ;

		texture = LoadTexture(filename, 204, 363);
	}

	/*Target(int d, int h)
	 {
	 distFromObserver = d;
	 health = h;
	 bounty = h * distFromObserver * 5;
	 }*/

	void destroyTarget(void)
	{
		if(angle == 90)
			isDestroyed = true;
		else
			angle+=2;
	}

	unsigned int LoadTexture(const char * filename, int width, int height)
	{
		unsigned char * data;
		FILE * file;
		file = fopen(filename, "rb");
		if (file == NULL)
			return 0;

		data = (unsigned char *) malloc(width * height * 3);// assign the necessary memory for the texture

		fread(data, width * height * 3, 1, file);
		fclose(file);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
				GL_UNSIGNED_BYTE, data);
		free(data);

		return texture;
	}

	void draw()
	{

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture);
		if(isSelected)
			glColor3f(1,0,0);
		else
			glColor3f(1,1,1);

		glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		//glutSolidCube(5);
		glTranslatef(0, -10, 0);
		glRotatef(angle, 1, 0, 1);
		glTranslatef(0, 10, 0);
		glBegin(GL_POLYGON);
		glTexCoord2f(1, 1);
		glVertex3f(-5,-10,0);
		glTexCoord2f(0, 1);
		glVertex3f( 5,-10,0);
		glTexCoord2f(0, 0);
		glVertex3f( 5, 10,0);
		glTexCoord2f(1, 0);
		glVertex3f(-5, 10,0);
		glEnd();
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}
};

class Engine
{
public:
	static Player currentPlayer;
	static queue<Target> targets;
	static unsigned char difficulty;
	static void initPlayer(string n)
	{
		currentPlayer = *(new Player(n));
	}

	static void setDifficulty(unsigned char d)
	{
		difficulty = d;
	}

	static void initTargets(void)
	{
		//Loops on the targets Queue and sets their health to difficulty.
		//However, I need the fixed (FOR NOW) distances from the observer to init a target.
	}

	static void shootTarget(Target t)
	{
		float dmgFac = currentPlayer.shoot();
		if (dmgFac != -1.0)
		{
			//t.giveDamage(dmgFac);
			currentPlayer.plusScore(t.bounty);
		}
	}

	static void reload()
	{
		currentPlayer.reload();
	}

	static void updateHighScore(void)
	{
		currentPlayer.updateHighScore();
	}

	static void pickHealth(char x)
	{
		currentPlayer.giveHealth(x);
	}

	static void pickArmor(char x)
	{
		currentPlayer.giveArmor(x);
	}

	static bool pickWeapon(Weapon w)
	{
		return currentPlayer.giveWeapon(w);
	}
};

#endif
