/*
 * Terrain.cpp
 *
 *  Created on: 15 Dec 2010
 *      Author: Mohab
 */
#include <stdio.h>
#include <GL/glut.h>
#include "Terrain.h"

bool Terrain::Create(char *hFileName, char *textureName, int Width, int Height)
{
	terHeight = Height;
	terWidth = Width;

	FILE *fp;
	fp = fopen(hFileName, "rb");
	fread(byteHeightField, 1, Width * Height, fp);
	fclose(fp);

	texture = LoadTexture(textureName, Width, Height);

	for(int i = 0; i < 1024; i++)
		for(int j = 0; j < 1024; j++)
			heightField[i][j] = (int)byteHeightField[i][j];

	int temp = heightField[0][0];
	for(int i = 0; i < 1024; i++)
		for(int j = 0; j < 1024; j++)
			heightField[i][j] -= temp;

	return true;
}

void Terrain::Render(void)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor3f(1,1,1);
	for (int hMapX = 0; hMapX < terWidth-skip; hMapX += skip)
	{
		for (int hMapZ = 0; hMapZ < terHeight-skip; hMapZ += skip)
		{
			glBegin(GL_TRIANGLE_STRIP);

			glTexCoord2f((float) hMapX / terWidth, (float) hMapZ / terHeight);
			glVertex3f(hMapX, heightField[hMapX][hMapZ], hMapZ);

			glTexCoord2f((float) hMapX / terWidth, (float) (hMapZ + skip)
					/ terHeight);
			glVertex3f(hMapX, heightField[hMapX][hMapZ + skip], hMapZ + skip);

			glTexCoord2f((float) (hMapX + skip) / terWidth, (float) hMapZ
					/ terHeight);
			glVertex3f(hMapX + skip, heightField[hMapX + skip][hMapZ], hMapZ);

			glTexCoord2f((float) (hMapX + skip) / terWidth, (float) (hMapZ
					+ skip) / terHeight);
			glVertex3f(hMapX + skip, heightField[hMapX + skip][hMapZ + skip],
					hMapZ + skip);
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);

	/*glBegin(GL_POINTS);
	 for (int hMapX = 0; hMapX < terWidth; hMapX++)
	 {
	 for (int hMapZ = 0; hMapZ < terHeight; hMapZ++)
	 {
	 glVertex3f(hMapX, heightField[hMapX][hMapZ], hMapZ);
	 glBegin(GL_TRIANGLE_STRIP);
	 glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);
	 glVertex3f(hMapX, hHeightField[hMapX][hMapZ + 1], hMapZ + 1);
	 glVertex3f(hMapX + 1, hHeightField[hMapX + 1][hMapZ], hMapZ);
	 glVertex3f(hMapX + 1, hHeightField[hMapX + 1][hMapZ + 1], hMapZ + 1);
	 glEnd();
	 }
	 }
	 glEnd();*/
}

unsigned int Terrain::LoadTexture(const char * filename, int width, int height)
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
