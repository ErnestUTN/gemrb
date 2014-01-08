
#ifndef GLVideoDRIVER_H
#define GLVideoDRIVER_H

#include "SDL20Video.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define VERTEX_SIZE 2
#define TEX_SIZE 2
#define COLOR_SIZE 4

#define BLIT_EXTERNAL_MASK 0x100

namespace GemRB 
{
	class GLTextureSprite2D;

	class GLVideoDriver : public SDL20VideoDriver 
	{
	private:
		SDL_GLContext context; // opengl context
		// Shader programs
		GLuint program32; // shader program for 32bpp sprites
		GLuint programPal; // shader program for paletted sprites
		GLuint programPalGrayed; // shader program for paletted sprites with grayscale effect
		GLuint programPalSepia; // shader program for paletted sprites  with sepia effect
		GLuint programRect; // shader program for drawing rects and lines
		
		Uint32 spritesPerFrame; // sprites counter
		GLuint lastUsedProgram; // stores last used program to prevent switching if possible (switching may cause performance lack)

		void useProgram(GLuint program); // use this instead glUseProgram
		void createPrograms();
		void blitSprite(GLTextureSprite2D* spr, int x, int y, const Region* clip, unsigned int flags = 0, const Color* tint = NULL, GLTextureSprite2D* mask = NULL);
		void drawColoredRect(const Region& rgn, const Color& color);

	public:
		~GLVideoDriver();
		int SwapBuffers();
		int CreateDisplay(int w, int h, int b, bool fs, const char* title);
		bool SupportsBAMSprites() { return false; }
		void BlitSprite(const Sprite2D* spr, int x, int y, bool anchor = false,	const Region* clip = NULL, Palette* palette = NULL);
		void BlitGameSprite(const Sprite2D* spr, int x, int y, unsigned int flags, Color tint, SpriteCover* cover, Palette *palette = NULL,	const Region* clip = NULL, bool anchor = false);
		void BlitTile(const Sprite2D* spr, const Sprite2D* mask, int x, int y, const Region* clip, unsigned int flags);
		Sprite2D* CreateSprite(int w, int h, int bpp, ieDword rMask, ieDword gMask, ieDword bMask, ieDword aMask, void* pixels,	bool cK = false, int index = 0);
		Sprite2D* CreateSprite8(int w, int h, void* pixels,	Palette* palette, bool cK, int index);
		Sprite2D* CreatePalettedSprite(int w, int h, int bpp, void* pixels, Color* palette, bool cK = false, int index = 0);
		void DrawRect(const Region& rgn, const Color& color, bool fill = true, bool clipped = false);
		void DrawHLine(short x1, short y, short x2, const Color& color, bool clipped = false);
		void DrawVLine(short x, short y1, short y2, const Color& color, bool clipped = false);
	};
}

#endif