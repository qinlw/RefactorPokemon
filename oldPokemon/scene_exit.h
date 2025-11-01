#pragma once

#include "scene.h"
#include "util.h"
#include "picture.h"


class SceneExit : public Scene {
public:
	void on_enter() {
		exit_game_button_pos.x = (img_exit_background.getwidth() / 2 - img_exit_game_idle_button.getwidth() + interface_to_edge_distance) / 2;
		exit_game_button_pos.y = (img_exit_background.getheight() + pull_bar_length) / 2 - img_exit_game_idle_button.getheight();
		exit_login_button_pos.x = img_exit_background.getwidth() - exit_game_button_pos.x - img_exit_login_idle_button.getwidth();
		exit_login_button_pos.y = exit_game_button_pos.y;
	}

	void on_update(int delta) {

	}

	void on_draw() {
		putimage_alpha(exit_background_pos.x, exit_background_pos.y, &img_exit_background);
		putimage_alpha(exit_game_button_pos.x, exit_game_button_pos.y, is_down_exit_game_button ? &img_exit_game_down_button : &img_exit_game_idle_button);
		putimage_alpha(exit_login_button_pos.x, exit_login_button_pos.y, is_down_exit_login_button ? &img_exit_login_down_button : &img_exit_login_idle_button);
	}

	void on_input(const ExMessage& msg) {
		switch (msg.message) {
		case WM_LBUTTONDOWN:
			// 按下了退出游戏
			if (msg.x < exit_game_button_pos.x + img_exit_game_idle_button.getwidth() && msg.x > exit_game_button_pos.x &&
				msg.y < exit_game_button_pos.y + img_exit_game_idle_button.getheight() && msg.y > exit_game_button_pos.y) {
				is_down_exit_game_button = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
			}

			// 按下了退出登录
			if (msg.x < exit_login_button_pos.x + img_exit_login_idle_button.getwidth() && msg.x > exit_login_button_pos.x &&
				msg.y < exit_login_button_pos.y + img_exit_login_idle_button.getheight() && msg.y > exit_login_button_pos.y) {
				is_down_exit_login_button = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
			}
			break;
		case WM_LBUTTONUP:
			// 回到主菜单
			if (!(msg.x < img_exit_background.getwidth() - interface_to_edge_distance && msg.x > exit_background_pos.x + interface_to_edge_distance &&
				msg.y < img_exit_background.getheight() - interface_to_under_distance && msg.y > exit_background_pos.y + pull_bar_length)) {
				if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 0"), NULL, 0, NULL);
				scene_manager->switch_scene(SceneManager::SceneType::Menu);
			}

			// 按下了退出游戏
			if (is_down_exit_game_button) {
				if (msg.x < exit_game_button_pos.x + img_exit_game_idle_button.getwidth() && msg.x > exit_game_button_pos.x &&
					msg.y < exit_game_button_pos.y + img_exit_game_idle_button.getheight() && msg.y > exit_game_button_pos.y) {
					is_down_exit_game_button = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL); 
					putimage_alpha(exit_game_button_pos.x, exit_game_button_pos.y, is_down_exit_game_button ? &img_exit_game_down_button : &img_exit_game_idle_button);
					exit(0);
				}
				else {
					is_down_exit_game_button = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				}
			}

			// 按下了退出登录
			if (is_down_exit_login_button) {
				if (msg.x < exit_login_button_pos.x + img_exit_login_idle_button.getwidth() && msg.x > exit_login_button_pos.x &&
					msg.y < exit_login_button_pos.y + img_exit_login_idle_button.getheight() && msg.y > exit_login_button_pos.y) {
					is_down_exit_login_button = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL); 
					putimage_alpha(exit_login_button_pos.x, exit_login_button_pos.y, is_down_exit_login_button ? &img_exit_login_down_button : &img_exit_login_idle_button);
					scene_manager->switch_scene(SceneManager::SceneType::LoginRegistration);
				}
				else {
					is_down_exit_login_button = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				}
			}

			break;
		}
	}

	void on_exit() {

	}

private:
	const int pull_bar_length = 161;
	const int interface_to_edge_distance = 192;
	const int interface_to_under_distance = 80;

private:
	POINT exit_background_pos = { 0 };					// 退出背景的位置
	POINT exit_game_button_pos = { 0 };					// 退出游戏按钮的位置
	POINT exit_login_button_pos = { 0 };				// 退出登录按钮的位置

	bool is_down_exit_game_button = false;				// 是否按下了退出游戏按钮
	bool is_down_exit_login_button = false;				// 是否按下了退出登录按钮


};