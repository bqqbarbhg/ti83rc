#ifndef _TI83RC_TEX_H
#define _TI83RC_TEX_H

struct texture {
	unsigned int width, height;
	const unsigned char *data;
};

extern const struct texture tex_wall;

#endif