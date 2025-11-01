#pragma once

#include "scene.h"
#include "picture.h"
#include "util.h"
#include "music_fun.h"
#include "animation.h"
#include "timer.h"


extern SceneManager* scene_manager;

extern bool is_open_music;
extern bool is_playing_background_music;
extern bool is_open_sound_effect;

class SceneProgressBar : public Scene{
public:
	void on_enter() {
		animation_charmander_right.set_atlas(&atlas_charmander_right);

		timer_int_nProgress.set_callback([&]() {
			++int_nProgress;
			int probability_value = rand() % probability_copies + 1;

			if (probability_value <= high_probability)
				probability_value = high_probability;
			else if (probability_value > high_probability && probability_value < high_probability + small_probability)
				probability_value = small_probability;
			else
				probability_value = minimal_probability;

			if (probability_value == high_probability) {
				int wait_time = rand() % (high_probability_range[1] - high_probability_range[0]) + high_probability_range[0];
				timer_int_nProgress.set_wait_time(wait_time);
				animation_charmander_right.set_interval(wait_time);
			}	
			else if (probability_value == small_probability) {
				int wait_time = rand() % (small_probability_range[1] - small_probability_range[0]) + small_probability_range[0];
				timer_int_nProgress.set_wait_time(wait_time);
				animation_charmander_right.set_interval(wait_time);
			}
			else {
				int wait_time = rand() % (minimal_probability_range[1] - minimal_probability_range[0]) + minimal_probability_range[0];
				timer_int_nProgress.set_wait_time(wait_time);
				animation_charmander_right.set_interval(wait_time);
			}
			if (int_nProgress > 99) int_nProgress = 99;
			});
		timer_switch_login_registration_scene.set_wait_time(1000);
		timer_switch_login_registration_scene.set_one_shot(true);
		timer_switch_login_registration_scene.set_callback([&]() {
			if (is_open_sound_effect) mciSendString(_T("play click_sound_3 from 50"), NULL, 0, NULL);
			scene_manager->switch_scene(SceneManager::SceneType::LoginRegistration);
			});

		progress_bar_percent_pos = { 1200, 400 };
		progress_bar_percentage_num_units_digit_pos.x = progress_bar_percent_pos.x - img_progress_bar_percentage_num_0.getwidth();
		progress_bar_percentage_num_units_digit_pos.y = progress_bar_percent_pos.y;
		progress_bar_percentage_num_tens_digit_pos.x = progress_bar_percentage_num_units_digit_pos.x - img_progress_bar_percentage_num_0.getwidth();
		progress_bar_percentage_num_tens_digit_pos.y = progress_bar_percentage_num_units_digit_pos.y;
		progress_bar_percentage_num_hundreds_digit_pos.x = progress_bar_percentage_num_tens_digit_pos.x - img_progress_bar_percentage_num_0.getwidth();
		progress_bar_percentage_num_hundreds_digit_pos.y = progress_bar_percentage_num_tens_digit_pos.y;

		if (is_open_music && !is_playing_background_music) play_background_music();
	}

	void on_update(int delta) {
		progress_bar_percentage_num_units_digit = (int_nProgress + 1) % 10;
		progress_bar_percentage_num_tens_digit = (int_nProgress + 1) / 10 % 10;
		progress_bar_percentage_num_hundreds_digit = (int_nProgress + 1) / 100 % 10;

		animation_charmander_right.on_update(delta);
		timer_int_nProgress.on_update(delta);
		if (progress_bar_percentage_num_hundreds_digit) timer_switch_login_registration_scene.on_update(delta);
	}

	void on_draw() {
		putimage_alpha(0, 0, &img_progress_bar_background);
		putimage_alpha(progress_bar_percent_pos.x, progress_bar_percent_pos.y, &img_progress_bar_percent);

		switch (progress_bar_percentage_num_units_digit) {
		case 0:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_0);
			break;
		case 1:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_1);
			break;
		case 2:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_2);
			break;
		case 3:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_3);
			break;
		case 4:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_4);
			break;
		case 5:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_5);
			break;
		case 6:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_6);
			break;
		case 7:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_7);
			break;
		case 8:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_8);
			break;
		case 9:
			putimage_alpha(progress_bar_percentage_num_units_digit_pos.x, progress_bar_percentage_num_units_digit_pos.y, &img_progress_bar_percentage_num_9);
			break;
		}

		switch (progress_bar_percentage_num_tens_digit) {
		case 0:
			if (int_nProgress + 1 < 10) break;
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_0);
			break;
		case 1:
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_1);
			break;
		case 2:
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_2);
			break;
		case 3:
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_3);
			break;
		case 4:
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_4);
			break;
		case 5:
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_5);
			break;
		case 6:
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_6);
			break;
		case 7:
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_7);
			break;
		case 8:
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_8);
			break;
		case 9:
			putimage_alpha(progress_bar_percentage_num_tens_digit_pos.x, progress_bar_percentage_num_tens_digit_pos.y, &img_progress_bar_percentage_num_9);
			break;
		}

		if (progress_bar_percentage_num_hundreds_digit == 1)
			putimage_alpha(progress_bar_percentage_num_hundreds_digit_pos.x, progress_bar_percentage_num_hundreds_digit_pos.y, &img_progress_bar_percentage_num_1);

		for (int i = 0; i < int_nProgress; ++i) {
			putimage_alpha(i * atlas_progress_bar_piece.get_image(i)->getwidth(), getheight() - atlas_progress_bar_piece.get_image(i)->getheight(),
				atlas_progress_bar_piece.get_image(i));
		}

		animation_charmander_right.on_draw(int_nProgress * atlas_progress_bar_piece.get_image(0)->getwidth() - 110,
			getheight() - atlas_progress_bar_piece.get_image(0)->getheight() - 95);
	}

	void on_input(const ExMessage& msg) {
	
	}

	void on_exit() {
	
	}


private:
	int int_nProgress = 0;																		// 进度条所显示的百分比 99即加载完成
	int progress_bar_percentage_num_units_digit;												// 进度条所显示百分比的个位数
	int progress_bar_percentage_num_tens_digit;													// 进度条所显示百分比的十位数
	int progress_bar_percentage_num_hundreds_digit;												// 进度条所显示百分比的百位数
	int high_probability = 9900;																// 大概率的份数占比
	int small_probability = 99;																	// 小概率的份数占比
	int minimal_probability = 1;																// 极小概率的份数占比
	int probability_copies = high_probability + small_probability + minimal_probability;		// 概率份数

	int high_probability_range[2] = { 0,10 };													// 大概率下的进度速度 数值越低，速度越快
	int small_probability_range[2] = { 100,200 };												// 小概率下的进度速度 数值越低，速度越快
	int minimal_probability_range[2] = { 1000,2000 };											// 极小概率下的进度速度 数值越低，速度越快


private:
	POINT progress_bar_percent_pos = { 0 };														// 进度条百分号的位置
	POINT progress_bar_percentage_num_units_digit_pos = { 0 };									// 进度条百分数中个位数的位置
	POINT progress_bar_percentage_num_tens_digit_pos = { 0 };									// 进度条百分数中十位数的位置
	POINT progress_bar_percentage_num_hundreds_digit_pos = { 0 };								// 进度条百分数中百位数的位置

	Animation animation_charmander_right;														// 朝向向左的小火龙动画

	Timer timer_int_nProgress;																	// 进度条计时器 回调函数即增加进度条百分比
	Timer timer_switch_login_registration_scene;												// 进入登录和注册场景的计时器

};