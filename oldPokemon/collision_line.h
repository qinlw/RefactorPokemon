#pragma once

#include <graphics.h>
#include <vector>


extern bool is_debug;

class CollisionLine {
public:
	struct LinePos {
		POINT pos_1;
		POINT pos_2;
	};

	LinePos line_pos;

	void on_draw() const {
		if (is_debug) {
			setlinecolor(RGB(255, 0, 0));	//ºì
			line(line_pos.pos_1.x, line_pos.pos_1.y, line_pos.pos_2.x, line_pos.pos_2.y);
		}
	}
};
