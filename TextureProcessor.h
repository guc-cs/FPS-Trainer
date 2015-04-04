/*
 * TextureProcessor.h
 *
 *  Created on: 17 Dec 2010
 *      Author: Mohab
 */

#ifndef TEXTUREPROCESSOR_H_
#define TEXTUREPROCESSOR_H_


#include <list>
#include <string>
#include <GL/glut.h>

class CTexture
{
public:
	// constructors/destructor
	CTexture( void ) { }
	CTexture( const char *texname ) { m_name = texname; }
	CTexture( unsigned int texid, const char *texname )	{ m_id = texid; m_name = texname; }
	~CTexture( void ) { glDeleteTextures( 1, &m_id ); m_name.erase(); }

	unsigned int	GetTexId( void ) { return m_id; }
	const char		*GetName( void ) { return m_name.c_str(); }


public:
	// members variables
	unsigned int	m_id;			// texture id
	std::string		m_name;			// texture name

};

class CTextureManager
{
protected:
	// constructor/destructor
	CTextureManager( void ) { Initialize(); }
	virtual ~CTextureManager( void ) { CleanAllTextures(); }

public:
	// singleton functions
	static CTextureManager	*GetInstance( void );
	static void				FreeInstance( void );


	// functions
	void			Initialize( void );
	unsigned int	LoadTexture( const char *filename );
	void			DeleteTexture( unsigned int id );
	void			CleanAllTextures( void );


private:
	// linked texture list
	typedef std::list<CTexture *>	TextureList;
	typedef TextureList::iterator	TListItor;

	TextureList						m_texlist;

	// singleton
	static CTextureManager			*m_singleton;

};

// global function using the texture manager
inline unsigned int LoadTexture( const char *filename )
{
	return CTextureManager::GetInstance()->LoadTexture( filename );
}


#endif /* TEXTUREPROCESSOR_H_ */
