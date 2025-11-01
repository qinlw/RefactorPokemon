#pragma once

#include "atlas.h"

#include <functional>


class Animation {
public:
	void reset() {
		time = 0;
		idx_frame = 0;
	}

	void set_interval(int ms) {
		interval = ms;
	}

	void set_is_loop(bool flag) {
		is_loop = flag;
	}

	void set_atlas(Atlas* new_atlas) {
		atlas = new_atlas;
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

	void set_peremptory_callback(std::function<void()> callback) {
		this->callback = callback;
		is_exist_peremptory_callback = true;
	}

	int get_interval() {
		return interval;
	}

	int get_idx_frame() {
		return idx_frame;
	}

	IMAGE* get_frame() {
		return atlas->get_image(idx_frame);
	}

	void on_update(int delta) {
		time += delta;
		if (time >= interval) {
			time = 0;
			++idx_frame;
			if (idx_frame >= atlas->get_size() - 1) {
				idx_frame = is_loop ? 0 : atlas->get_size() - 1;
				if (!is_loop && callback) callback();
				else if (is_exist_peremptory_callback && callback) callback();
			}
		}
	}

	void on_draw(int x, int y, bool is_exist_alpha = true) {
		if (is_exist_alpha) putimage_alpha(x, y, get_frame());
		else putimage(x, y, get_frame());
	}
	

private:
	int time = 0;									// 计时器
	int interval = 0;								// 帧间隔
	int idx_frame = 0;								// 帧下标
	bool is_loop = true;							// 是否循环播放
	bool is_exist_peremptory_callback = false;		// 是否存在强制回调
	Atlas* atlas = nullptr;					
	std::function<void()> callback;			

};