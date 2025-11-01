#pragma once


#include <functional>

class Timer {
public:
	void reset() {
		pass_time = 0;
		shotted = false;
	}

	void set_wait_time(int val) {
		wait_time = val;
	}

	void puased() {
		puase = true;
	}

	void resume() {
		puase = false;
	}

	void set_one_shot(bool flag) {
		one_shot = flag;
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

	void on_update(int delta) {
		if (puase) return;

		pass_time += delta;
		if (pass_time >= wait_time) {
			if ((!one_shot || (one_shot && !shotted)) && callback) {
				callback();
			}
			pass_time = 0;
			shotted = true;
		}
	}


private:
	int pass_time = 0;					// 已经过时间
	int wait_time = 0;					// 等待时间
	bool puase = false;					// 是否暂停
	bool shotted = false;				// 是否已触发
	bool one_shot = false;				// 是否为单次触发
	std::function<void()> callback;		// 回调函数

};