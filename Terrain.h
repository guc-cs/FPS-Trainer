/*
 * Terrain.h
 *
 *  Created on: 15 Dec 2010
 *      Author: Mohab
 */

class Vertex
{
	public:
		float x;
		float y;
		float z;
};

class TexCoord
{
	public:
		float u;
		float v;
};

class Terrain
{
	private:
		int terHeight;
		int terWidth;

		int vertexCount;
		Vertex *vertices;
		TexCoord *texCoords;
		unsigned int texture;

	public:
		bool
		Create(char *hFileName, char *textureName, int hWidth, int hHeight);
		void Render(void);
		unsigned int LoadTexture(const char * filename, int width, int height);
		unsigned char byteHeightField[1024][1024];
		int heightField[1024][1024];
		int skip;
};
