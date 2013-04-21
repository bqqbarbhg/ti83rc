#include "player.h"

#include <GL/glfw.h>

player::player(const vec2& pos)
	: pos(pos), vel(0.0f, 0.0f), rot(0.0f)
{
}

void player::update(float elapsed)
{
	if (glfwGetKey(GLFW_KEY_LEFT))
		rot -= elapsed * ROTATION_SPEED;
	if (glfwGetKey(GLFW_KEY_RIGHT))
		rot += elapsed * ROTATION_SPEED;

	vec2 dir = vec2(cos(rot), sin(rot)), right = dir.right();
	vec2 move;

	if (glfwGetKey('W'))
		move.y++;
	if (glfwGetKey('A'))
		move.x--;
	if (glfwGetKey('S'))
		move.y--;
	if (glfwGetKey('D'))
		move.x++;
	move.normalize_if_not_zero();

	vel += (move.y * dir + move.x * right) * elapsed * 4.0f;
	vel *= 1.0f - elapsed * 5.0f;
	pos += vel * elapsed * 10.0f;
}