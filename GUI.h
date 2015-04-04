/*
 * GUI.h
 *
 *  Created on: Dec 21, 2010
 *      Author: Magued
 */

#ifndef GUI_H_
#define GUI_H_


#endif /* GUI_H_ */

#include <GL/glut.h>
#include <iostream>

using namespace std;

class Point
{
	public:
		float x, y;
		Point();
		Point(float posX, float posY);
};

class MenuItem
{
	public:
		char* s;
		Point one;
		Point two;
		Point three;
		Point four;
		MenuItem();
		MenuItem(char* str);
		MenuItem(char* str, Point p1, Point p2, Point p3, Point p4);
		void drawItem();
};

class StartMenu
{
	public:
		MenuItem startGame;
		MenuItem exit;
		StartMenu();
		void drawMenu();
};

class PauseMenu
{
	public:
		MenuItem resumeGame;
		MenuItem back;
		MenuItem exit;
		PauseMenu();
		void drawMenu();
};


class PlayMenu
{
	public:
		MenuItem name;
		MenuItem bullets;
		MenuItem message;
		MenuItem cursor;
		PlayMenu();
		void drawMenu(int nBullets);
		void draw3D();
};

class GUI
{
	public:
		GUI();
		void draw2D();
		void print(char*, void*);
};
