#ifndef _TI83RC_MAP_H
#define _TI83RC_MAP_H

#include "vec.h"

class map
{
public:
	typedef unsigned char cell_t;

	map(int w, int h);
	~map();

	void raycast(const vec2& pos, const vec2& dir);

	cell_t& cell(unsigned int x, unsigned int y) {
		return cells[x + y * width];
	}

	int width;
	int height;
	cell_t* cells;
private:
	map(const map&);
	map&operator=(const map&)const;
};

#endif
