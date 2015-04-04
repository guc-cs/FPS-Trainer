#include <GL/glut.h>
#include "GUI.h"

GUI gui;

Point::Point()
{
}

Point::Point(float posX, float posY)
{
	x = posX;
	y = posY;
}

MenuItem::MenuItem()
{
}

MenuItem::MenuItem(char* str)
{
	s = str;
}

MenuItem::MenuItem(char* str, Point p1, Point p2, Point p3, Point p4)
{
	s = str;
	one = p1;
	two = p2;
	three = p3;
	four = p4;
}

void MenuItem::drawItem()
{
	glBegin(GL_LINE_LOOP);
	glColor3f(1,0,0);
	glVertex2f(one.x, one.y);
	glVertex2f(two.x, two.y);
	glVertex2f(three.x, three.y);
	glVertex2f(four.x, four.y);
	glEnd();
}

StartMenu::StartMenu()
{
	Point p1 = Point(300,440), p2 = Point(300,500), p3 = Point(500,500), p4 = Point(500,440);
	Point p5 = Point(300,240), p6 = Point(300,300), p7 = Point(500,300), p8 = Point(500,240);

	startGame = MenuItem("Start Game", p1, p2, p3, p4);
	exit = MenuItem("E X I T", p5, p6, p7, p8);
}

void StartMenu::drawMenu()
{
	gui.draw2D();
	startGame.drawItem();
	glPushMatrix();
	glLineWidth(5);
	glColor3f(0.13, 0.54, 0.13);
	glTranslated(startGame.one.x + 8, (startGame.one.y + startGame.two.y)/2 - 10, 0);
	glScaled(0.25, 0.25, 0.25);
	gui.print(startGame.s, GLUT_STROKE_ROMAN);
	glPopMatrix();
	exit.drawItem();
	glPushMatrix();
	glLineWidth(5);
	glColor3f(0.13, 0.54, 0.13);
	glTranslated(exit.one.x + 30, (exit.one.y + exit.two.y)/2 - 10, 0);
	glScaled(0.25, 0.25, 0.25);
	gui.print(exit.s, GLUT_STROKE_ROMAN);
	glPopMatrix();
}

PauseMenu::PauseMenu()
{
	Point p1 = Point(300,440), p2 = Point(300,500), p3 = Point(500,500), p4 = Point(500,440);
	Point p5 = Point(300,320), p6 = Point(300,380), p7 = Point(500,380), p8 = Point(500,320);
	Point p9 = Point(300,200), p10 = Point(300,260), p11 = Point(500,260), p12 = Point(500,200);

	resumeGame = MenuItem("Resume", p1, p2, p3, p4);
	back = MenuItem("Main Menu", p5, p6, p7, p8);
	exit = MenuItem("E X I T", p9, p10, p11, p12);
}

void PauseMenu::drawMenu()
{
	gui.draw2D();
	resumeGame.drawItem();
	glPushMatrix();
	glLineWidth(5);
	glColor3f(0.13, 0.54, 0.13);
	glTranslated(resumeGame.one.x + 40, (resumeGame.one.y + resumeGame.two.y)/2 - 10, 0);
	glScaled(0.25, 0.25, 0.25);
	gui.print(resumeGame.s, GLUT_STROKE_ROMAN);
	glPopMatrix();
	back.drawItem();
	glPushMatrix();
	glLineWidth(5);
	glColor3f(0.13, 0.54, 0.13);
	glTranslated(back.one.x + 15, (back.one.y + back.two.y)/2 - 10, 0);
	glScaled(0.25, 0.25, 0.25);
	gui.print(back.s, GLUT_STROKE_ROMAN);
	glPopMatrix();
	exit.drawItem();
	glPushMatrix();
	glLineWidth(5);
	glColor3f(0.13, 0.54, 0.13);
	glTranslated(exit.one.x + 30, (exit.one.y + exit.two.y)/2 - 10, 0);
	glScaled(0.25, 0.25, 0.25);
	gui.print(exit.s, GLUT_STROKE_ROMAN);
	glPopMatrix();
}

PlayMenu::PlayMenu()
{
	name = MenuItem("Training");
	bullets = MenuItem("Bullets:");
	message = MenuItem("");
	cursor = MenuItem(".");
}

void PlayMenu::drawMenu(int nBullets)
{
	gui.draw2D();
	glPushMatrix();
	glLineWidth(5);
	glColor3f(0.13, 0.54, 0.13);
	glTranslated(30, 550, 0);
	glScaled(0.25, 0.25, 0.25);
	gui.print(name.s, GLUT_STROKE_ROMAN);
	glPopMatrix();
	glPushMatrix();
	glLineWidth(5);
	glColor3f(0.13, 0.54, 0.13);
	glTranslated(650, 550, 0);
	glScaled(0.25, 0.25, 0.25);
	char *buffer = new char[2];
	//char *text = itoa(nBullets, buffer, 10);
	gui.print(bullets.s, GLUT_STROKE_ROMAN);
	//gui.print(text, GLUT_STROKE_ROMAN);
	glPopMatrix();
	glPushMatrix();
	glLineWidth(5);
	glColor3f(0.13, 0.54, 0.13);
	glTranslated(300, 550, 0);
	glScaled(0.25, 0.25, 0.25);
	gui.print(message.s, GLUT_STROKE_ROMAN);
	glPopMatrix();
	glPushMatrix();
	glLineWidth(5);
	glColor3f(0.13, 0.54, 0.13);
	glTranslated(400, 300, 0);
	glScaled(0.25, 0.25, 0.25);
	gui.print(cursor.s, GLUT_STROKE_ROMAN);
	glPopMatrix();

	draw3D();

}

void PlayMenu::draw3D()
{
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2.0*70/54.0, 2.0*70/54.0, -2.0, 2.0, 0.1, 200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

GUI::GUI()
{
}


void GUI::draw2D()
{
	glDisable( GL_TEXTURE_2D );
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	glMatrixMode(GL_MODELVIEW);
}

void GUI::print(char* string, void *font)
{
	char* c;
	for (c=string; *c != '\0'; c++)
		glutStrokeCharacter(font, *c);
}


