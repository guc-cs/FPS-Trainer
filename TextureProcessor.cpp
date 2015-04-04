/*
 * TextureProcessor.cpp
 *
 *  Created on: 17 Dec 2010
 *      Author: Mohab
 */

#include "TextureProcessor.h"
#include "pcx.h"
#include <string.h>
#include <stdio.h>

#include <GL/glut.h>

// Initialise the singleton
CTextureManager	*CTextureManager::m_singleton = 0;

CTextureManager *CTextureManager::GetInstance( void )
{
	if( m_singleton == 0 )
		m_singleton = new CTextureManager;

	return ((CTextureManager *)m_singleton);
}

void CTextureManager::FreeInstance( void )
{
	if( m_singleton != 0 )
	{
		delete m_singleton;
		m_singleton = 0;
	}
}

void CTextureManager::Initialize( void )
{
	// this is the first texture loaded. If a texture
	// can't be loaded, we use this instead

	// Initialise only once!
	if( (*m_texlist.begin()) == (*m_texlist.end()) )
	{
		CTexture *tex = new CTexture( "default" );

		// create and initialise the texture
		glGenTextures( 1, &tex->m_id );
		glBindTexture( GL_TEXTURE_2D, tex->m_id );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		m_texlist.push_back( tex );


		// create a checker for the default texture
		int i, j, c;				// temporary variable
		unsigned char *checker;		// texture data

		checker = new unsigned char[ 64 * 64 * 4 ];

		for( i = 0; i < 64; i++ )
		{
			for( j = 0; j < 64; j++ )
			{
				c = ( !(i & 8) ^ !(j & 8)) * 255;

				checker[ (i * 256) + (j * 4) + 0 ] = (unsigned char)c;
				checker[ (i * 256) + (j * 4) + 1 ] = (unsigned char)c;
				checker[ (i * 256) + (j * 4) + 2 ] = (unsigned char)c;
				checker[ (i * 256) + (j * 4) + 3 ] = (unsigned char)255;

			}
		}


		glTexImage2D( GL_TEXTURE_2D, 0, 4, 64, 64, 0, GL_RGBA, GL_UNSIGNED_BYTE, checker );

		delete [] checker;
	}
}

unsigned int CTextureManager::LoadTexture( const char *filename )
{
	unsigned int	id = 0;
	unsigned char	*texels = 0;
	int				width, height;
	int				success;


	for( TListItor itor = m_texlist.begin(); itor != m_texlist.end(); ++itor )
	{
		if( strcmp( (*itor)->GetName(), filename ) == 0 )
			return (*itor)->GetTexId();
	}

	success = LoadFilePCX( filename, &texels, &width, &height, true );


	if( success > 0 )
	{
		// create and initialise new texture
		glGenTextures( 1, &id );
		glBindTexture( GL_TEXTURE_2D, id );

		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

		gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, texels );

		// create a new CTexture object and push it at the end of the linked list
		CTexture *tex = new CTexture( id, filename );
		m_texlist.push_back( tex );
	}
	else
	{
		// can't load the texture, use default texture
		id = (*m_texlist.begin())->GetTexId();
	}


	if( texels )
		delete [] texels;


	return id;
}

void CTextureManager::DeleteTexture( unsigned int id )
{
	for( TListItor itor = m_texlist.begin(); itor != m_texlist.end(); ++itor )
	{
		if( (*itor)->GetTexId() == id )
		{
			delete (*itor);
			itor = m_texlist.erase( itor );
		}
	}
}

void CTextureManager::CleanAllTextures( void )
{
	for( TListItor itor = m_texlist.begin(); itor != m_texlist.end(); ++itor )
	{
		delete (*itor);
		itor = m_texlist.erase( itor );
	}
}
