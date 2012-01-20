/*
 *  Lead Coder:     Taylor C. Richberger
 */

#ifndef FONT_BASE_HXX
#define FONT_BASE_HXX

#include <string>
#include <iostream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glfw.h>

#include <ft2build.h>
#include FT_FREETYPE_H

class FontBase
{
    protected:
        static FT_Library library;
        static FT_Face face;

        static FT_GlyphSlot slot;
        static FT_UInt glyph_index;
        static FT_Vector pen;                    /* untransformed origin  */
        static FT_Error error;
        struct Glyph
        {
            // All of the float values are ratios compared to the given size
            GLuint texture;
            GLfloat width;
            GLfloat height;
            GLfloat xAdvance;
            GLfloat yBearing;
            GLfloat xBearing;
        };
        static Glyph texGlyphs[127];

        static bool initiated;

        unsigned int i;
        unsigned int j;
        unsigned int k;

        static void DrawGlyph(FT_Bitmap* bitmap, GLubyte* image, unsigned int width, unsigned int height);

    public:
        FontBase();
        virtual ~FontBase();
        static bool Initiate();
        static void Cleanup();

        void DrawString(std::string text, GLfloat x, GLfloat y, GLfloat size);
};

#endif
