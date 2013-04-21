#include "map.h"
#include "settings.h"
#include "rendering.h"
#include "util.h"
#include "tex/tex.h"
#include <cstring>

static const texture *map_textures[] = {
	NULL,
	&tex_wall,
};

static const color map_colors[] = {
	COLOR_LIGHT,
	COLOR_WHITE,
};

map::map(int w, int h)
	: width(w), height(h), cells(new cell_t[w * h])
{
	memset(cells, 0, w * h * sizeof(cell_t));
}

map::~map()
{
	delete[] cells;
}

void map::raycast(const vec2& pos, const vec2& dir)
{
	vec2 right = dir.right().normalized();
	vec2 rDir = dir - right;
	vec2 rDirStep = right * 2.0f / BACKBUFFER_WIDTH;
	vec2 rPos = pos;
	int startMapX = pos.x, startMapY = pos.y;
	int stepX, stepY;
	bool xSide;
	for (int x = 0; x < BACKBUFFER_WIDTH; x++) {
		int mapX = startMapX, mapY = startMapY;
		float ratio = (rDir.y * rDir.y) / (rDir.x * rDir.x);
		vec2 delta = vec2(sqrt(1 + ratio), sqrt(1 + 1.0f / ratio));
		vec2 sideDist;
		if (rDir.x < 0) {
			stepX = -1;
			sideDist.x = (rPos.x - mapX) * delta.x;
		} else {
			stepX = 1;
			sideDist.x = (mapX + 1 - rPos.x) * delta.x;
		}
		if (rDir.y < 0) {
			stepY = -1;
			sideDist.y = (rPos.y - mapY) * delta.y;
		} else {
			stepY = 1;
			sideDist.y = (mapY + 1 - rPos.y) * delta.y;
		}
		cell_t hit = 0;
		while (true) {
			
			if (xSide = (sideDist.x < sideDist.y)) {
				sideDist.x += delta.x;
				mapX += stepX;
			} else {
				sideDist.y += delta.y;
				mapY += stepY;
			}
			if (mapX < 0 || mapY < 0 || mapX >= width || mapY >= height) {
				break;
			}
			if (cell(mapX, mapY) != 0) {
				hit = cell(mapX, mapY);
				break;
			}
		}

		if (hit) {
			vec2 hitVec((mapX - rPos.x + (1 - stepX) / 2) / rDir.x, (mapY - rPos.y + (1 - stepY) / 2) / rDir.y);
			float dist = fabs(xSide ? hitVec.x
									: hitVec.y);

			int height = min(abs((int)(BACKBUFFER_HEIGHT / dist / 2)), BACKBUFFER_HEIGHT / 2);
			int center = BACKBUFFER_HEIGHT / 2;

			float ftexX = xSide ? rPos.x + hitVec.y * rDir.x
				                : rPos.y + hitVec.x * rDir.y;
			ftexX -= floor(ftexX);
			const texture *tex = map_textures[hit];
			ftexX *= tex->width;

			int texX = ftexX;

			if (xSide) {
				if (rDir.x > 0) texX = tex->width - texX - 1;
			} else {
				if (rDir.y < 0) texX = tex->width - texX - 1;
			}

			int y = 0;
			for (int e = center - height; y < e; y++) {
				draw_pixel(x, y, COLOR_BLACK);
			}
			unsigned int texH = tex->height, texHHalf = texH / 2;
			for (int e = center + height; y < e; y++) {
				int d = y * texH - BACKBUFFER_HEIGHT * texHHalf + height * texH;
				int texY = ((d * texH) / height) / (texH * 2);

				unsigned int q = texX + texY * tex->width;
				draw_pixel(x, y, map_colors[tex->data[q]]);
			}
			for (int e = BACKBUFFER_HEIGHT; y < e; y++) {
				draw_pixel(x, y, COLOR_BLACK);
			}
		} else {
			for (int y = 0; y < BACKBUFFER_HEIGHT; y++) {
				draw_pixel(x, y, COLOR_BLACK);
			}
		}
		rDir += rDirStep;
	}
}
