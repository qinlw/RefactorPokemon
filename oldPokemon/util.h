#pragma once

#include "scene_manager.h"
#include "atlas.h"

#include <graphics.h>
#include <mysql.h>

#pragma comment(lib, "MSIMG32.LIB")


constexpr auto PI = 3.14159265359;;

extern SceneManager* scene_manager;

inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA }
	);
}

inline void button_sink_animatioin(int strength, int sink_time, POINT& pos, IMAGE* img) {
	cleardevice();
	pos.y += strength;
	scene_manager->on_draw();
	FlushBatchDraw();
	Sleep(sink_time);
}

inline void button_bulge_animatioin(int strength, int bulge_time, POINT& pos, IMAGE* img) {
	pos.y -= strength;
	scene_manager->on_draw();
	FlushBatchDraw();
	Sleep(bulge_time);
}

inline void flip_image(IMAGE* src, IMAGE* dst) {
	int w = src->getwidth();
	int h = src->getheight();
	Resize(dst, w, h);
	DWORD* src_buffer = GetImageBuffer(src);
	DWORD* dst_buffer = GetImageBuffer(dst);
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			int idx_src = y * w + x;
			int idx_dst = y * w + w - x - 1;
			dst_buffer[idx_dst] = src_buffer[idx_src];
		}
	}
}

inline void flip_atlas(Atlas& src, Atlas& dst) {
	dst.clear();
	for (int i = 0; i < src.get_size(); ++i) {
		IMAGE image_flipped;
		flip_image(src.get_image(i), &image_flipped);
		dst.add_image(image_flipped);
	}
}

inline void rotate_atlas(int time, IMAGE* img, Atlas& dst) {
	dst.clear();
	dst.add_image(*img);
	for (int i = 0; i < time; ++i) {
		IMAGE image_rotated;
		rotateimage(&image_rotated, img, (double)(-PI / time * i * 2));
		dst.add_image(image_rotated);
		// ²âÊÔ´úÂë
		//if (i & 1)
		//	putimage_alpha(i * 100, i * 100, dst.get_iamge(i));
		//else 
		//	putimage(i * 100, i * 100, dst.get_iamge(i));
		//FlushBatchDraw();
		//if (i == time - 1)
		//	int a = 0;
	}
}

inline bool is_regen(POINT pos_1, POINT pos_2, IMAGE& img_1, IMAGE img_2) {
	if ((pos_1.x >= pos_2.x - img_1.getwidth() && pos_1.x <= pos_2.x + img_2.getwidth()) || pos_1.x >= getwidth() - img_1.getwidth() || pos_1.x <= 0)
		return true;
	return false;
}

void load_music(LPCTSTR path_template, int n) {
	TCHAR path_file[256];
	for (int i = 0; i < n; ++i) {
		_stprintf_s(path_file, path_template, i + 1, i + 1);
		std::cout << "load_music:" << i + 1 << "->" << mciSendString(path_file, NULL, 0, NULL) << std::endl;	// ²âÊÔ´úÂë
	}
}