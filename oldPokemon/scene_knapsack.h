#pragma once

#include "scene.h"


extern bool is_selected_healing_potion_1P;										
extern bool is_selected_power_potion_1P;											
extern bool is_selected_invisibility_potion_1P;
extern bool is_selected_healing_potion_2P;
extern bool is_selected_power_potion_2P;
extern bool is_selected_invisibility_potion_2P;


const int lattice_num = 25;
const int lattice_heigh_num = 5;

class SceneKnapsack : public Scene {
public:
	void on_enter() {
		std::cout << "knapsack";

		// 初始化背包格子状态
		for (int i = 0; i < lattice_num; ++i) {
			knapsack_lattice_is_selected_1P[i] = false;
			knapsack_lattice_is_selected_2P[i] = false;
		}
		for (int i = 0; i < lattice_num; ++i) {
			knapsack_lattice_is_down_1P[i] = false;
			knapsack_lattice_is_down_2P[i] = false;
		}
		// 背景位置
		int knapsack_field_background_to_left_screen_distance = 25, knapsack_field_background_to_top_screen_distance = 125;
		int player_id_offset_x = 30, player_id_offset_y = 13;
		int knapsack_lattice_to_knapsack_field_background_distance = 20;
		knapsack_field_background_1P_pos.x = background_base_pos.x + knapsack_field_background_to_left_screen_distance;
		knapsack_field_background_1P_pos.y = background_base_pos.y + knapsack_field_background_to_top_screen_distance;
		knapsack_field_background_2P_pos.x = getwidth() / 2 + img_knapsack_field_background.getwidth() - knapsack_field_background_to_left_screen_distance;
		knapsack_field_background_2P_pos.y = knapsack_field_background_1P_pos.y;
		player_1P_pos.x = knapsack_field_background_1P_pos.x + player_id_offset_x;
		player_1P_pos.y = knapsack_field_background_1P_pos.y + player_id_offset_y;
		player_2P_pos.x = knapsack_field_background_2P_pos.x + player_id_offset_x;
		player_2P_pos.y = knapsack_field_background_2P_pos.y + player_id_offset_y;
		knapsack_1P_pos.x = player_1P_pos.x + img_player_1P.getwidth();
		knapsack_1P_pos.y = player_1P_pos.y;
		knapsack_2P_pos.x = player_2P_pos.x + img_player_2P.getwidth();
		knapsack_2P_pos.y = knapsack_1P_pos.y;
		// 背包格子位置集
		knapsack_lattice_1P_pos[0].x = player_1P_pos.x + img_player_1P.getwidth() / 2;
		knapsack_lattice_1P_pos[0].y = knapsack_field_background_1P_pos.y + img_knapsack_field_background.getheight()
			+ knapsack_lattice_to_knapsack_field_background_distance;
		knapsack_lattice_2P_pos[0].x = player_2P_pos.x + img_player_2P.getwidth() / 2;
		knapsack_lattice_2P_pos[0].y = knapsack_field_background_2P_pos.y + img_knapsack_field_background.getheight()
			+ knapsack_lattice_to_knapsack_field_background_distance;
		for (int i = 1; i < lattice_num; ++i) {
			knapsack_lattice_1P_pos[i].x = knapsack_lattice_1P_pos[i - 1].x + img_knapsack_lattice_unselected.getwidth();
			knapsack_lattice_1P_pos[i].y = knapsack_lattice_1P_pos[i - 1].y;
			knapsack_lattice_2P_pos[i].x = knapsack_lattice_2P_pos[i - 1].x + img_knapsack_lattice_unselected.getwidth();
			knapsack_lattice_2P_pos[i].y = knapsack_lattice_2P_pos[i - 1].y;
			if (i % 5 == 0) {
				knapsack_lattice_1P_pos[i].x = knapsack_lattice_1P_pos[0].x;
				knapsack_lattice_1P_pos[i].y += img_knapsack_lattice_unselected.getheight();
				knapsack_lattice_2P_pos[i].x = knapsack_lattice_2P_pos[0].x;
				knapsack_lattice_2P_pos[i].y += img_knapsack_lattice_unselected.getheight();
			}
		}
		selected_prop_frame_pos_1P[0].x = knapsack_field_background_1P_pos.x;
		selected_prop_frame_pos_1P[0].y = knapsack_lattice_1P_pos[0].y;
		selected_prop_frame_pos_2P[0].x = knapsack_field_background_2P_pos.x;
		selected_prop_frame_pos_2P[0].y = knapsack_lattice_2P_pos[0].y;
		// 已选择道具的方框位置集
		for (int i = 1; i < lattice_heigh_num; ++i) {
			selected_prop_frame_pos_1P[i].x = selected_prop_frame_pos_1P[i - 1].x;
			selected_prop_frame_pos_1P[i].y = selected_prop_frame_pos_1P[i - 1].y + img_selected_prop_frame.getheight();
			selected_prop_frame_pos_2P[i].x = selected_prop_frame_pos_2P[i - 1].x;
			selected_prop_frame_pos_2P[i].y = selected_prop_frame_pos_2P[i - 1].y + img_selected_prop_frame.getheight();
		}

		return_btn_pos.x = getwidth() - img_return_button.getwidth() - 25;
		return_btn_pos.y = getheight() - img_return_button.getheight() - 20;
	}

	void on_update(int delta) {
		// 更新双方玩家已选择的道具数
		int selected_num_1P = 0;
		int selected_num_2P = 0;
		for (int i = 0; i < lattice_num; ++i) {
			if (knapsack_lattice_is_selected_1P[i]) {
				++selected_num_1P;
				optional_prop_1P_is_can = selected_num_1P < optional_prop_limit_num;
			}
			if (knapsack_lattice_is_selected_2P[i]) {
				++selected_num_2P;
				optional_prop_2P_is_can = selected_num_2P < optional_prop_limit_num;
			}
		}
		optional_prop_num_1P = selected_num_1P;
		optional_prop_num_2P = selected_num_2P;
		selected_num_1P = 0;
		selected_num_2P = 0;

		// 更新双方玩家选择的道具
		is_selected_healing_potion_1P = knapsack_lattice_is_selected_1P[healing_potion_knapsack_lattice_id];
		is_selected_power_potion_1P = knapsack_lattice_is_selected_1P[power_potion_knapsack_lattice_id];
		is_selected_invisibility_potion_1P = knapsack_lattice_is_selected_1P[invisibility_potion_knapsack_lattice_id];
		is_selected_healing_potion_2P = knapsack_lattice_is_selected_2P[healing_potion_knapsack_lattice_id];
		is_selected_power_potion_2P = knapsack_lattice_is_selected_2P[power_potion_knapsack_lattice_id];
		is_selected_invisibility_potion_2P = knapsack_lattice_is_selected_2P[invisibility_potion_knapsack_lattice_id];
	}

	void on_draw() {
		// 背景
		putimage_alpha(background_base_pos.x, background_base_pos.y, &img_background_base);
		putimage_alpha(knapsack_field_background_1P_pos.x, knapsack_field_background_1P_pos.y, &img_knapsack_field_background);
		putimage_alpha(knapsack_field_background_2P_pos.x, knapsack_field_background_2P_pos.y, &img_knapsack_field_background);
		putimage_alpha(player_1P_pos.x, player_1P_pos.y, &img_player_1P);
		putimage_alpha(player_2P_pos.x, player_2P_pos.y, &img_player_2P);
		putimage_alpha(knapsack_1P_pos.x, knapsack_1P_pos.y, &img_knapsack);
		putimage_alpha(knapsack_2P_pos.x, knapsack_2P_pos.y, &img_knapsack);
		// 背包格子
		for (int i = 0; i < lattice_num; ++i) {
			putimage_alpha(knapsack_lattice_1P_pos[i].x, knapsack_lattice_1P_pos[i].y, knapsack_lattice_is_selected_1P[i] ? &img_knapsack_lattice_selected : &img_knapsack_lattice_unselected);
			putimage_alpha(knapsack_lattice_2P_pos[i].x, knapsack_lattice_2P_pos[i].y, knapsack_lattice_is_selected_2P[i] ? &img_knapsack_lattice_selected : &img_knapsack_lattice_unselected);
		}
		// 已选择道具的方框
		for (int i = 0; i < lattice_heigh_num; ++i) {
			putimage_alpha(selected_prop_frame_pos_1P[i].x, selected_prop_frame_pos_1P[i].y, &img_selected_prop_frame);
			putimage_alpha(selected_prop_frame_pos_2P[i].x, selected_prop_frame_pos_2P[i].y, &img_selected_prop_frame);
		}
		// 道具
		putimage_alpha(knapsack_lattice_1P_pos[healing_potion_knapsack_lattice_id].x, knapsack_lattice_1P_pos[healing_potion_knapsack_lattice_id].y, &img_healing_potion);
		putimage_alpha(knapsack_lattice_1P_pos[power_potion_knapsack_lattice_id].x, knapsack_lattice_1P_pos[power_potion_knapsack_lattice_id].y, &img_power_potion);
		putimage_alpha(knapsack_lattice_1P_pos[invisibility_potion_knapsack_lattice_id].x, knapsack_lattice_1P_pos[invisibility_potion_knapsack_lattice_id].y, &img_invisibility_potion);
		putimage_alpha(knapsack_lattice_2P_pos[healing_potion_knapsack_lattice_id].x, knapsack_lattice_2P_pos[healing_potion_knapsack_lattice_id].y, &img_healing_potion);
		putimage_alpha(knapsack_lattice_2P_pos[power_potion_knapsack_lattice_id].x, knapsack_lattice_2P_pos[power_potion_knapsack_lattice_id].y, &img_power_potion);
		putimage_alpha(knapsack_lattice_2P_pos[invisibility_potion_knapsack_lattice_id].x, knapsack_lattice_2P_pos[invisibility_potion_knapsack_lattice_id].y, &img_invisibility_potion);
		putimage_alpha(return_btn_pos.x, return_btn_pos.y, &img_return_button);
	}

	void on_input(const ExMessage& msg) {
		switch (msg.message) {
			// 鼠标左键按下
		case WM_LBUTTONDOWN: {
			// 返回按钮
			if (msg.x >= return_btn_pos.x && msg.x <= return_btn_pos.x + img_return_button.getwidth() &&
				msg.y >= return_btn_pos.y && msg.y <= return_btn_pos.y + img_return_button.getheight()) {
				is_return_btn = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
				button_sink_animatioin(5, 50, return_btn_pos, &img_return_button);
				break;
			}
			// 背包格子
			for (int i = 0; i < lattice_num; ++i) {
				//1P
				if (msg.x >= knapsack_lattice_1P_pos[i].x && msg.x <= knapsack_lattice_1P_pos[i].x + img_knapsack_lattice_selected.getwidth() &&
					msg.y >= knapsack_lattice_1P_pos[i].y && msg.y <= knapsack_lattice_1P_pos[i].y + img_knapsack_lattice_selected.getheight()) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
					knapsack_lattice_is_down_1P[i] = true;
					break;
				}
				//2P
				if (msg.x >= knapsack_lattice_2P_pos[i].x && msg.x <= knapsack_lattice_2P_pos[i].x + img_knapsack_lattice_selected.getwidth() &&
					msg.y >= knapsack_lattice_2P_pos[i].y && msg.y <= knapsack_lattice_2P_pos[i].y + img_knapsack_lattice_selected.getheight()) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
					knapsack_lattice_is_down_2P[i] = true;
					break;
				}
			}
			break;
		}
			// 鼠标左键弹起
		case WM_LBUTTONUP: {
			// 返回按钮
			if (is_return_btn) {
				if (msg.x >= return_btn_pos.x && msg.x <= return_btn_pos.x + img_return_button.getwidth() &&
					msg.y >= return_btn_pos.y && msg.y <= return_btn_pos.y + img_return_button.getheight()) {
					is_return_btn = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					button_bulge_animatioin(5, 300, return_btn_pos, &img_return_button);
					scene_manager->switch_scene(SceneManager::SceneType::Menu);
				}
				else {
					if (is_return_btn) {
						is_return_btn = false;
						if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
						button_bulge_animatioin(5, 300, return_btn_pos, &img_return_button);
					}
				}
				break;
			}

			// 背包格子
			for (int i = 0; i < lattice_num; ++i) {
				//1P
				if (knapsack_lattice_is_down_1P[i]) {
					if (msg.x >= knapsack_lattice_1P_pos[i].x && msg.x <= knapsack_lattice_1P_pos[i].x + img_knapsack_lattice_selected.getwidth() &&
						msg.y >= knapsack_lattice_1P_pos[i].y && msg.y <= knapsack_lattice_1P_pos[i].y + img_knapsack_lattice_selected.getheight()) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
						if (optional_prop_1P_is_can) knapsack_lattice_is_selected_1P[i] = !knapsack_lattice_is_selected_1P[i];
						else knapsack_lattice_is_selected_1P[i] = knapsack_lattice_is_selected_1P[i] ? false : false;
						break;
					}
					knapsack_lattice_is_down_1P[i] = false;
				}

				//2P
				if (knapsack_lattice_is_down_2P[i]) {
					if (msg.x >= knapsack_lattice_2P_pos[i].x && msg.x <= knapsack_lattice_2P_pos[i].x + img_knapsack_lattice_selected.getwidth() &&
						msg.y >= knapsack_lattice_2P_pos[i].y && msg.y <= knapsack_lattice_2P_pos[i].y + img_knapsack_lattice_selected.getheight()) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
						if (optional_prop_2P_is_can) knapsack_lattice_is_selected_2P[i] = !knapsack_lattice_is_selected_2P[i];
						else knapsack_lattice_is_selected_2P[i] = knapsack_lattice_is_selected_2P[i] ? false : false;
						break;
					}
					knapsack_lattice_is_down_2P[i] = false;
				}
			}
		}
		}
	}

	void on_exit() {

	}

private:
	int optional_prop_num_1P = 0;												// 1P已选择的道具数
	int optional_prop_num_2P = 0;												// 2P已选择的道具数

	const int optional_prop_limit_num = 3;										// 可选道具限制数

	const int healing_potion_knapsack_lattice_id = 0;							// 治疗药水在背包格子的位置
	const int power_potion_knapsack_lattice_id = 1;								// 能量药水在背包格子的位置
	const int invisibility_potion_knapsack_lattice_id = 2;						// 隐身药水在背包格子的位置


private:
	POINT background_base_pos = { 0 };											// 背景
	POINT knapsack_field_background_1P_pos = { 0 };								// 1P背包列表背景的位置
	POINT knapsack_field_background_2P_pos = { 0 };								// 2P背包列表背景的位置
	POINT player_1P_pos = { 0 };												// 1P玩家提示文本的位置
	POINT player_2P_pos = { 0 };												// 2P玩家提示文本的位置
	POINT knapsack_1P_pos = { 0 };												// 1P背包的位置
	POINT knapsack_2P_pos = { 0 };												// 2P背包的位置
	POINT knapsack_lattice_1P_pos[lattice_num] = { 0 };							// 1P背包格子的位置集
	POINT knapsack_lattice_2P_pos[lattice_num] = { 0 };							// 2P背包格子的位置集
	POINT selected_prop_frame_pos_1P[lattice_heigh_num] = { 0 };				// 1P已选择道具方框的位置集
	POINT selected_prop_frame_pos_2P[lattice_heigh_num] = { 0 };				// 2P已选择道具方框的位置集
	POINT return_btn_pos = { 0 };												// 返回按钮的位置

	bool is_return_btn = false;													// 返回按钮是否被按下
	bool knapsack_lattice_is_down_1P[lattice_num];								// 1P对应背包格子是否被按下
	bool knapsack_lattice_is_down_2P[lattice_num];								// 2P对应背包格子是否被按下
	bool knapsack_lattice_is_selected_1P[lattice_num];							// 1P对应背包格子是否被选择
	bool knapsack_lattice_is_selected_2P[lattice_num];							// 2P对应背包格子是否被选择
	bool optional_prop_1P_is_can = true;										// 1P是否还能选择道具
	bool optional_prop_2P_is_can = true;										// 2P是否还能选择道具

};