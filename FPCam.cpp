#include <GL/glut.h>

#include "Camera.h"
#include "Terrain.h"
#include "Core.h"
#include "GUI.h"
#include "CollisionEngine.h"
#include "PhysicsEngine.h"
#include "Md2Model.h"


Camera camera;
Terrain terrain;

StartMenu startMenu;
PauseMenu pauseMenu;
PlayMenu playMenu;

CollisionEngine* cEngine = new CollisionEngine(1024*1024/64 + 10000);
PhysicsEngine* pEngine;

Model gun;

int menuState = 0;

// Centre of the Screen
int CenterX(400), CenterY(300);

Target targets[100];
int bullets = 10;

int getClosestAim()
{
	float distance = 1024;
	int closest = -1;
	for(int i = 0; i < 100; i++)
	{
		if(!targets[i].isDestroyed)
		{
			float tDist = camera.isTarget(targets[i]);
			if(tDist < distance)
			{
				distance = tDist;
				targets[i].isSelected = true;
				closest = i;
			}
			else
				targets[i].isSelected = false;
		}
	}
	return (closest==-1)? 0 : closest;
}

void Initialize()
{
	camera.Rotation = Vector3(0,90,0);
	camera.Position = Vector3(10, 7,10);
	camera.Update();

	gun.LoadModel("army_weapon.md2");
	gun.LoadSkin("army_weapon.pcx");
	gun.SetAnim(0);
	gun.ScaleModel(0.1);

	terrain.skip = 8;
	terrain.Create("Terrain/thf2.raw", "Terrain/TerrainTexture2.raw", 1024, 1024);

	pEngine = new PhysicsEngine(terrain.heightField ,10 ,&camera);
	for(int i = 0 ; i < 1024 ; i+=terrain.skip){

		for(int j = 0 ; j < 1024 ; j+= terrain.skip){
			cEngine->registerBarrier(i,terrain.heightField[i][j],j,5);

		}

	}

	for(int i = 0; i < 100; i++)
	{
		int x = (rand() % 1024), z = (rand() % 1024);
		targets[i] = Target(x, terrain.heightField[x][z] + 10, z, "terrorist.raw");
		cEngine->registerBarrier(x,terrain.heightField[x][z] + 10, z, 2);
	}
}

void renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1);

	if(menuState == 0)
		startMenu.drawMenu();
	else if(menuState == 2)
		pauseMenu.drawMenu();
	else
	{
		pEngine->frame();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45, 4/3, 0.1, 1000);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(camera.Position.x, camera.Position.y, camera.Position.z, //  Camera position
				camera.target.x, camera.target.y, camera.target.z, // Target position
				0.0f, 1.0f, 0.0f); // Up vector

		terrain.Render();

		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(camera.Position.x + camera.Forward.x, camera.Position.y-1, camera.Position.z + camera.Forward.z);
		glRotatef(-camera.Rotation.x, 1, 0, 0);
		glRotatef(camera.Rotation.y-40, 0, 1, 0);
		glRotatef(camera.Rotation.z, 0, 0, 1);
		glScalef(0.8,0.8,0.8);
		gun.DrawModel(0);
		glPopMatrix();

		getClosestAim();
		for(int i = 0; i < 100; i++)
			if(!targets[i].isDestroyed)
			{
				if(targets[i].isShot)
					targets[i].destroyTarget();
				targets[i].draw();
			}

		if(getClosestAim())
		{
			playMenu.draw3D();
			glPushMatrix();
			glColor3f(1,0,0);
			glTranslated(-1,2,1);
			glutSolidCube(0.3);
			glPopMatrix();
		}

		/*else
		{
			playMenu.draw3D();
			glPushMatrix();
			glTranslated(-1,2,1);
			miniOgre.DrawModel(timesec/2);
			glPopMatrix();
		}*/

		playMenu.drawMenu(bullets);

		glEnable(GL_DEPTH_TEST);
	}

	glutSwapBuffers();
}

void changeSize(int w, int h)
{

	// Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = 1.0 * w / h;

	// Update the Centre of the Screen
	CenterX = w / 2;
	CenterY = h / 2;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45, ratio, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.Position.x, camera.Position.y, camera.Position.z, //  Camera position
			camera.target.x, camera.target.y, camera.target.z, // Target position
			0.0f, 1.0f, 0.0f); // Up vector
}

void handleMouseInput(int button, int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(menuState == 0)
		{
			if((x <= 500 && x >= 300) && (y <= 160 && y >= 100))
				menuState = 1;
			else if((x <= 500 && x >= 300) && (y <= 360 && y >= 300))
				exit(0);
		}
		else if(menuState == 1)
		{
			if(bullets > 0)
			{
				int ind = getClosestAim();
				if(ind)
					targets[ind].isShot = true;
				bullets --;
			}
		}
		else if (menuState == 2)
		{
			if((x <= 500 && x >= 300) && (y <= 160 && y >= 100))
				menuState = 1;

			else if((x <= 500 && x >= 300) && (y <= 280 && y >= 220))
				menuState = 0;

			else if((x <= 500 && x >= 300) && (y <= 400 && y >= 340))
				exit(0);
		}
	}
}

void handlePassiveMotion(int x, int y)
{
	if(menuState == 1)
	{
		if (x > 400)
		{
			camera.Rotation.y -= 0.5;
			camera.Update();
			glutWarpPointer(400, 300);
		}
		else if (x < 400)
		{
			camera.Rotation.y += 0.5;
			camera.Update();
			glutWarpPointer(400, 300);
		}

		if (y > 300)
		{
			camera.Rotation.x -= 0.5;
			camera.Update();
			glutWarpPointer(400, 300);
		}
		else if (y < 300)
		{
			camera.Rotation.x += 0.5;
			camera.Update();
			glutWarpPointer(400, 300);
		}

		glutSetCursor(GLUT_CURSOR_NONE);
	}
	else
		glutSetCursor(1);
}

void handleKeyInput(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:
			if(menuState == 1)
				menuState = 2;
			else if(menuState == 2)
				menuState = 1;
			else exit(0);
			break;
		case 32 : pEngine->jump(); break;
		case 'c': pEngine->duck(); break;
		case 'r': bullets = 10; break;
		case 'w':
		{
			Vector3 temp = camera.Position ;
			temp.x+= camera.Forward.x;
			temp.z+= camera.Forward.z;
			temp.y = pEngine->getYAt(temp.x,temp.z);
			if(cEngine->moveSphere(0,temp.x,temp.y,temp.z)==-1)
			{
				camera.Position.x += camera.Forward.x;
				camera.Position.z += camera.Forward.z;
				pEngine->move();
				//camera.Update();
			}
			break;
		}
		case 's':
		{
			Vector3 temp = camera.Position;
			temp.x-= camera.Forward.x;
			temp.z-= camera.Forward.z;
			temp.y = pEngine->getYAt(temp.x,temp.z);

			if(cEngine->moveSphere(0,temp.x,temp.y,temp.z)==-1)
			{
				camera.Position.x -= camera.Forward.x;
				camera.Position.z -= camera.Forward.z;
				pEngine->move();
				//camera.Update();
			}
			break;
		}
		case 'a':
		{
			Vector3 temp = camera.Position;
			temp.x+= camera.Left.x;
			temp.z+= camera.Left.z;
			temp.y = pEngine->getYAt(temp.x,temp.z);
			if(cEngine->moveSphere(0,temp.x,temp.y,temp.z)==-1)
			{
				camera.Position.x += camera.Left.x;
				camera.Position.z += camera.Left.z;
				pEngine->move();
				//camera.Update();
			}
			break;
		}
		case 'd':
		{
			Vector3 temp = camera.Position;
			temp.x+= camera.Right.x;
			temp.z+= camera.Right.z;
			temp.y = pEngine->getYAt(temp.x,temp.z);
			if(cEngine->moveSphere(0,temp.x,temp.y,temp.z)==-1){
				camera.Position.x += camera.Right.x;
				camera.Position.z += camera.Right.z;
				pEngine->move();
			}
			break;
		}
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	// Window position and size
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);

	// Create the Window
	glutCreateWindow("First Person Camera");

	//glutFullScreen();

	Initialize();

	// Setting the display and idle functions
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	// Setting the reshape function
	glutReshapeFunc(changeSize);

	// Setting the Mouse Input
	glutMouseFunc(handleMouseInput);

	// Setting the Mouse Motion functions
	glutMotionFunc(handlePassiveMotion);
	glutPassiveMotionFunc(handlePassiveMotion);

	// Setting the Keyboard function
	glutKeyboardFunc(handleKeyInput);

	// Enabling Depth Testing
	glEnable(GL_DEPTH_TEST);

	// Enters an infinite loop until the application exits
	glutMainLoop();
	return 0;
}
