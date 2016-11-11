#ifndef _TEXT_H_
#define _TEXT_H_

// FreeType Headers
#include <ft2build.h>
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftoutln.h>
#include <freetype/fttrigon.h>

#include <vector>
#include <string>

// OpenGL Headers
#include <windows.h>                                      // (The GL Headers Need It)
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdexcept>
#pragma warning(disable: 4786)

// Wrap Everything In A Namespace, That Way We Can Use A Common
// Function Name Like "print" Without Worrying About
// Overlapping With Anyone Else's Code.
namespace freetype
{

	// Inside Of This Namespace, Give Ourselves The Ability
	// To Write Just "vector" Instead Of "std::vector"
	using std::vector;

	// Ditto For String.
	using std::string;

	// This Holds All Of The Information Related To Any
	// FreeType Font That We Want To Create. 
	struct font_data
	{
		float h;                                        // Holds The Height Of The Font.
		GLuint * textures;                                  // Holds The Texture Id's
		GLuint list_base;                                   // Holds The First Display List Id

															// The Init Function Will Create A Font With
															// The Height h From The File fname.
		void init(const char * fname, unsigned int h);

		// Free All The Resources Associated With The Font.
		void clean();
	};

	void print(const font_data &ft_font, float x, float y, const char *fmt, ...);

}

#endif // !_TEXT_H_
