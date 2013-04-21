#ifndef _TI83RC_PLAYER_H
#define _TI83RC_PLAYER_H

#include "vec.h"

#define ROTATION_SPEED 4.0f

class player
{
public:
	player(const vec2& pos);
	void update(float elapsed);
	vec2 pos, vel;
	float rot;
};

#endif
