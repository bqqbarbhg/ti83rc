#ifndef _TI83RC_RENDERING_H
#define _TI83RC_RENDERING_H

#include <GL/glfw.h>
#include "settings.h"

#define COLOR_BLACK (color(0x00, 0x00, 0x00))
#define COLOR_DARK  (color(0x44, 0x44, 0x44))
#define COLOR_LIGHT (color(0xaa, 0xaa, 0xaa))
#define COLOR_WHITE (color(0xff, 0xff, 0xff))

struct color {
	color(GLubyte r, GLubyte g, GLubyte b)
		: red(r), green(g), blue(b) { }
	GLubyte red, green, blue;
};

extern GLubyte* rendering_buffer;

void rendering_init();
void rendering_close();

void rendering_update();

inline void draw_pixel(unsigned int x, unsigned int y, color col)
{
	unsigned int idx = (x + (BACKBUFFER_HEIGHT - 1 - y) * BACKBUFFER_WIDTH) * 3;
	rendering_buffer[idx + 0] = col.red;
	rendering_buffer[idx + 1] = col.green;
	rendering_buffer[idx + 2] = col.blue;
}

#endif
