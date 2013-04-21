#include "rendering.h"

GLubyte* rendering_buffer;

void rendering_init()
{
	rendering_buffer = new GLubyte[BACKBUFFER_WIDTH * BACKBUFFER_HEIGHT * 3];
}

void rendering_close()
{
	delete[] rendering_buffer;
}

void rendering_update()
{
	glDrawPixels(BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT, GL_RGB, GL_UNSIGNED_BYTE, rendering_buffer);
}