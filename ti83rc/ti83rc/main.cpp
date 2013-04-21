#include <GL/glfw.h>
#include "settings.h"
#include "os.h"
#include "rendering.h"
#include "map.h"
#include "player.h"
#include <cstdlib>

bool setup()
{
	if (!glfwInit()) {
		show_error("Unable to init GLFW");
		return false;
	}
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if (!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 0, 0, 0, GLFW_WINDOW)) {
		show_error("Unable to open window");
		return false;
	}
	glfwSetWindowTitle("TI83+");
	
	glPixelZoom(PIXEL_SCALE, PIXEL_SCALE);

	return true;
}

int main(int argc, char** argv)
{
	if (!setup()) {
		return 1;
	}

	map map(64, 64);
	map.cell(10, 10) = 1;
	map.cell(10, 11) = 1;
	map.cell(10, 12) = 1;
	map.cell(10, 13) = 1;
	map.cell(10, 14) = 1;
	map.cell(10, 15) = 1;

	player player(vec2(5.0f, 5.0f));


	rendering_init();
	float old_time = glfwGetTime();
	while (glfwGetWindowParam(GLFW_OPENED)) {
		float time = glfwGetTime();
		float elapsed = time - old_time;
		old_time = time;
		player.update(elapsed);
		map.raycast(player.pos, vec2(cos(player.rot), sin(player.rot)).normalized() * 2.0f);

		rendering_update();
		glfwSwapBuffers();
	}

	rendering_close();
}
