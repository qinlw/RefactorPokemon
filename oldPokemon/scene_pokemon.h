#pragma once

#include "scene.h"
#include "scene_manager.h"
#include "pokemon_type.h"
#include "pokeman_charmander.h"
#include "pokemon_squirtle.h"
#include "pokemon_bulbasaur.h"
#include "animation.h"


extern SceneManager* scene_manager;

extern Pokemon* pokemon_player_1;
extern Pokemon* pokemon_player_2;

extern bool is_open_sound_effect;

class ScenePokemon : public Scene {
public:
	void on_enter() {
		animation_pokeball.set_atlas(&atlas_pokeball);
		animation_pokeball.set_interval(20);
		animation_pokeball.set_is_loop(false);
		animation_selector_charmander_left.set_atlas(&atlas_selector_charmander_left);
		animation_selector_charmander_left.set_interval(225);
		animation_selector_charmander_right.set_atlas(&atlas_selector_charmander_right);
		animation_selector_charmander_right.set_interval(225);
		animation_selector_squirtle_left.set_atlas(&atlas_selector_squirtle_left);
		animation_selector_squirtle_left.set_interval(225);
		animation_selector_squirtle_right.set_atlas(&atlas_selector_squirtle_right);
		animation_selector_squirtle_right.set_interval(225);
		animation_selector_bulbasaur_left.set_atlas(&atlas_selector_bulbasaur_left);
		animation_selector_bulbasaur_left.set_interval(225);
		animation_selector_bulbasaur_right.set_atlas(&atlas_selector_bulbasaur_right);
		animation_selector_bulbasaur_right.set_interval(225);

		return_btn_pos.x = getwidth() - img_return_button.getwidth() - 25;
		return_btn_pos.y = getheight() - img_return_button.getheight() - 20;

		pokeball_pos.x = (getwidth() - img_pokeball.getwidth()) / 2 - 11;
		pokeball_pos.y = (getheight() - img_pokeball.getheight()) / 2 + 44;

		pokeball_circle_center.x = pokeball_pos.x + img_pokeball.getwidth() / 2;
		pokeball_circle_center.y = pokeball_pos.y + img_pokeball.getheight() / 2;

		int flip_val_add = 75;
		pokemon_1P_pos.x = 120;
		pokemon_1P_pos.y = 120;
		pokemon_2P_pos.x = (getwidth() + pokemon_1P_pos.x) / 2 + pokemon_1P_pos.x + flip_val_add;		// 由于反转了，需要调整，所以要加一个75
		pokemon_2P_pos.y = pokemon_1P_pos.y;

		int add_x_1P = 60;
		int add_x_2P = 90;
		int reduce_y = -50;
		player_1P_pos.x = pokemon_1P_pos.x + add_x_1P;
		player_1P_pos.y = pokemon_1P_pos.y + reduce_y;
		player_2P_pos.x = pokemon_2P_pos.x + add_x_2P;
		player_2P_pos.y = pokemon_2P_pos.y + reduce_y;

		int left_btn_reduce_1P = -50;
		int right_btn_add_1P = 230;
		int left_btn_reduce_2P = -40;
		int right_btn_add_2P = 200;
		int height_btn = 160;
		btn_1P_left_pos.x = pokemon_1P_pos.x + left_btn_reduce_1P;
		btn_1P_left_pos.y = pokemon_1P_pos.y / 2 + height_btn;
		btn_1P_right_pos.x = pokemon_1P_pos.x + right_btn_add_1P;
		btn_1P_right_pos.y = btn_1P_left_pos.y;
		btn_2P_left_pos.x = pokemon_2P_pos.x + left_btn_reduce_2P;
		btn_2P_left_pos.y = pokemon_2P_pos.y / 2 + height_btn;
		btn_2P_right_pos.x = pokemon_2P_pos.x + right_btn_add_2P + flip_val_add;
		btn_2P_right_pos.y = btn_2P_left_pos.y;
	}

	void on_update(int delta) {
		if (is_enter_start) animation_pokeball.on_update(delta);
		animation_selector_charmander_left.on_update(delta);
		animation_selector_charmander_right.on_update(delta);
		animation_selector_squirtle_left.on_update(delta);
		animation_selector_squirtle_right.on_update(delta);
		animation_selector_bulbasaur_left.on_update(delta);
		animation_selector_bulbasaur_right.on_update(delta);

		if (animation_pokeball.get_idx_frame() == atlas_pokeball.get_size() - 1) {
			if (is_enter_game) {
				is_enter_game = false;
				is_enter_start = false;
				animation_pokeball.reset();
				scene_manager->switch_scene(SceneManager::SceneType::Game);
			}
			else {
				animation_pokeball.on_update(delta);
				is_enter_game = true;
			}
		}
	}

	void on_draw() {
		putimage(0, 0, &img_selector_background);

		putimage(pokeball_pos.x, pokeball_pos.y, &img_pokeball);

		if (is_enter_start) animation_pokeball.on_draw(pokeball_pos.x, pokeball_pos.y, false);

		switch (player_type_1P) {
		case PokemonType::Charmander:
			animation_selector_charmander_right.on_draw(pokemon_1P_pos.x, pokemon_1P_pos.y);
			break;
		case PokemonType::Squirtle:
			animation_selector_squirtle_right.on_draw(pokemon_1P_pos.x, pokemon_1P_pos.y);
			break;
		case PokemonType::Bulbasaur:
			animation_selector_bulbasaur_right.on_draw(pokemon_1P_pos.x, pokemon_1P_pos.y);
			break;
		}
		switch (player_type_2P) {
		case PokemonType::Charmander:
			animation_selector_charmander_left.on_draw(pokemon_2P_pos.x, pokemon_2P_pos.y);
			break;
		case PokemonType::Squirtle:
			animation_selector_squirtle_left.on_draw(pokemon_2P_pos.x, pokemon_2P_pos.y);
			break;
		case PokemonType::Bulbasaur:
			animation_selector_bulbasaur_left.on_draw(pokemon_2P_pos.x, pokemon_2P_pos.y);
			break;
		}

		putimage_alpha(return_btn_pos.x, return_btn_pos.y, &img_return_button);

		putimage_alpha(player_1P_pos.x, player_1P_pos.y, &img_1P);
		putimage_alpha(player_2P_pos.x, player_2P_pos.y, &img_2P);

		putimage_alpha(btn_1P_left_pos.x, btn_1P_left_pos.y, is_1P_left_btn ? &img_1P_selector_btn_down_left : &img_1P_selector_btn_idle_left);
		putimage_alpha(btn_1P_right_pos.x, btn_1P_right_pos.y, is_1P_right_btn ? &img_1P_selector_btn_down_right : &img_1P_selector_btn_idle_right);
		putimage_alpha(btn_2P_left_pos.x, btn_2P_left_pos.y, is_2P_left_btn ? &img_2P_selector_btn_down_left : &img_2P_selector_btn_idle_left);
		putimage_alpha(btn_2P_right_pos.x, btn_2P_right_pos.y,is_2P_right_btn ? &img_2P_selector_btn_down_right : &img_2P_selector_btn_idle_right);
	}

	void on_input(const ExMessage& msg) {
		switch (msg.message) {
		case WM_KEYDOWN:
			switch (msg.vkcode) {
			// 'A'
			case 0x41:
				is_1P_left_btn = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
				break;
			// 'D'
			case 0x44:
				is_1P_right_btn = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
				break;
			// '⬅'
			case VK_LEFT:
				is_2P_left_btn = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
				break;
			// '➡'
			case VK_RIGHT:
				is_2P_right_btn = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
				break;
			}
			break;
		case WM_KEYUP:
			switch (msg.vkcode) {
			// 'A'
			case 0x41:
				is_1P_left_btn = false;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				player_type_1P = (PokemonType)(((int)PokemonType::Invalid + (int)player_type_1P - 1) % (int)PokemonType::Invalid);
				break;
			// 'D'
			case 0x44:
				is_1P_right_btn = false;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				player_type_1P = (PokemonType)(((int)player_type_1P + 1) % (int)PokemonType::Invalid);
				break;
			// '⬅'
			case VK_LEFT:
				is_2P_left_btn = false;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				player_type_2P = (PokemonType)(((int)PokemonType::Invalid + (int)player_type_2P - 1) % (int)PokemonType::Invalid);
				break;
			// '➡'
			case VK_RIGHT:
				is_2P_right_btn = false;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				player_type_2P = (PokemonType)(((int)player_type_2P + 1) % (int)PokemonType::Invalid);
				break;
			// 'enter'
			case VK_RETURN:
				is_enter_start = true;
				if (is_open_sound_effect) mciSendString(_T("play mechanical_rotation_sound from 0"), NULL, 0, NULL);
				break;
			// 调式代码 'B'
			case 0x42:
				if (is_debug) scene_manager->switch_scene(SceneManager::SceneType::Game);
				break;
			}
			break;
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

			//setcolor(YELLOW);
			//cleardevice();
			//fillrectangle(btn_1P_left_pos.x, btn_1P_left_pos.y, btn_1P_left_pos.x + img_1P_selector_btn_idle_left.getwidth(), btn_1P_left_pos.y + img_1P_selector_btn_idle_left.getheight());
			//line(btn_1P_left_pos.x, btn_1P_left_pos.y + img_1P_selector_btn_idle_left.getheight() / 2 , 1280, btn_1P_left_pos.y + img_1P_selector_btn_idle_left.getheight() / 2);
			//FlushBatchDraw();

			// 切换宝可梦按钮
			if (msg.y >= btn_1P_left_pos.y && msg.y <= btn_1P_left_pos.y + img_1P_selector_btn_idle_left.getheight()) {
				if (msg.x >= btn_1P_left_pos.x && msg.x <= btn_1P_left_pos.x + img_1P_selector_btn_idle_left.getwidth()) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
					int centreL = btn_1P_left_pos.y + img_1P_selector_btn_idle_left.getheight() / 2;
					int yL = abs(msg.y - centreL);
					int innerL = abs(msg.x - btn_1P_left_pos.x);
					if (yL <= innerL) is_1P_left_btn = true;
					break;
				}
				else if (msg.x >= btn_1P_right_pos.x && msg.x <= btn_1P_right_pos.x + img_1P_selector_btn_idle_right.getwidth()) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
					int centreL = btn_1P_right_pos.y + img_1P_selector_btn_idle_right.getheight() / 2;
					int yL = abs(msg.y - centreL);
					int innerL = abs(img_1P_selector_btn_idle_right.getheight() / 2 - msg.x + btn_1P_right_pos.x);
					if (yL <= innerL) is_1P_right_btn = true;
					break;
				}
				else if (msg.x >= btn_2P_left_pos.x && msg.x <= btn_2P_left_pos.x + img_2P_selector_btn_idle_left.getwidth()) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
					int centreL = btn_2P_left_pos.y + img_2P_selector_btn_idle_left.getheight() / 2;
					int yL = abs(msg.y - centreL);
					int innerL = abs(msg.x - btn_2P_left_pos.x);
					if (yL <= innerL) is_2P_left_btn = true;
					break;
				}
				else if (msg.x >= btn_2P_right_pos.x && msg.x <= btn_2P_right_pos.x + img_2P_selector_btn_idle_right.getwidth()) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
					int centreL = btn_2P_right_pos.y + img_2P_selector_btn_idle_right.getheight() / 2;
					int yL = abs(msg.y - centreL);
					int innerL = abs(img_2P_selector_btn_idle_right.getheight() / 2 - msg.x + btn_2P_right_pos.x);
					if (yL <= innerL) is_2P_right_btn = true;
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
			}
			// 切换宝可梦按钮
			if (msg.y >= btn_1P_left_pos.y && msg.y <= btn_1P_left_pos.y + img_1P_selector_btn_idle_left.getheight()) {
				if (msg.x >= btn_1P_left_pos.x && msg.x <= btn_1P_left_pos.x + img_1P_selector_btn_idle_left.getwidth() && is_1P_left_btn) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					is_1P_left_btn = false;
					int centreL = btn_1P_left_pos.y + img_1P_selector_btn_idle_left.getheight() / 2;
					int yL = abs(msg.y - centreL);
					int innerL = abs(msg.x - btn_1P_left_pos.x);
					if (yL <= innerL) player_type_1P = (PokemonType)(((int)PokemonType::Invalid + (int)player_type_1P - 1) % (int)PokemonType::Invalid);
					break;
				}
				else if (msg.x >= btn_1P_right_pos.x && msg.x <= btn_1P_right_pos.x + img_1P_selector_btn_idle_right.getwidth() && is_1P_right_btn) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					is_1P_right_btn = false;
					int centreL = btn_1P_right_pos.y + img_1P_selector_btn_idle_right.getheight() / 2;
					int yL = abs(msg.y - centreL);
					int innerL = abs(img_1P_selector_btn_idle_right.getheight() / 2 - msg.x + btn_1P_right_pos.x);
					if (yL <= innerL) player_type_1P = (PokemonType)(((int)player_type_1P + 1) % (int)PokemonType::Invalid);
					break;
				}
				else if (msg.x >= btn_2P_left_pos.x && msg.x <= btn_2P_left_pos.x + img_2P_selector_btn_idle_left.getwidth() && is_2P_left_btn) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					is_2P_left_btn = false;
					int centreL = btn_2P_left_pos.y + img_2P_selector_btn_idle_left.getheight() / 2;
					int yL = abs(msg.y - centreL);
					int innerL = abs(msg.x - btn_2P_left_pos.x);
					if (yL <= innerL) player_type_2P = (PokemonType)(((int)PokemonType::Invalid + (int)player_type_2P - 1) % (int)PokemonType::Invalid);
					break;
				}
				else if (msg.x >= btn_2P_right_pos.x && msg.x <= btn_2P_right_pos.x + img_2P_selector_btn_idle_right.getwidth() && is_2P_right_btn) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					is_2P_right_btn = false;
					int centreL = btn_2P_right_pos.y + img_2P_selector_btn_idle_right.getheight() / 2;
					int yL = abs(msg.y - centreL);
					int innerL = abs(img_2P_selector_btn_idle_right.getheight() / 2 - msg.x + btn_2P_right_pos.x);
					if (yL <= innerL) player_type_2P = (PokemonType)(((int)player_type_2P + 1) % (int)PokemonType::Invalid);
					break;
				}
				else {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					is_1P_left_btn = false;					
					is_1P_right_btn = false;					
					is_2P_left_btn = false;					
					is_2P_right_btn = false;
					break;
				}
			}
			else if (is_1P_left_btn || is_1P_right_btn || is_2P_left_btn || is_2P_right_btn) {
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				is_1P_left_btn = false;
				is_1P_right_btn = false;
				is_2P_left_btn = false;
				is_2P_right_btn = false;
				break;
			}



			// 精灵球
			int xL = msg.x - pokeball_circle_center.x;
			int yL = msg.y - pokeball_circle_center.y;
			int L_square = xL * xL + yL * yL;
			int circleR_square = (img_pokeball.getwidth() / 2) * (img_pokeball.getwidth() / 2);
			if (L_square <= circleR_square) {
				is_enter_start = true;
				if (is_open_sound_effect) mciSendString(_T("play mechanical_rotation_sound from 0"), NULL, 0, NULL);
			}

			break;
		}
		}
	}

	void on_exit() {
		switch (player_type_1P) {
		case PokemonType::Charmander:
			pokemon_player_1 = new PokemonCharmander();
			break;
		case PokemonType::Squirtle:
			pokemon_player_1 = new PokemonSquirtle();
			break;
		case PokemonType::Bulbasaur:
			pokemon_player_1 = new PokemonBulbasaur();
			break;
		}
		pokemon_player_1->set_id(PokemonPlayer::P1);

		switch (player_type_2P) {
		case PokemonType::Charmander:
			pokemon_player_2 = new PokemonCharmander(false);
			break;
		case PokemonType::Squirtle:
			pokemon_player_2 = new PokemonSquirtle(false);
			break;
		case PokemonType::Bulbasaur:
			pokemon_player_2 = new PokemonBulbasaur(false);
			break;
		}
		pokemon_player_2->set_id(PokemonPlayer::P2);
	}


private:


private:
	POINT return_btn_pos = { 0 };					// 返回按钮的位置
	POINT pokeball_pos = { 0 };						// 精灵球的位置
	POINT pokeball_circle_center = { 0 };			// 精灵球的圆心
	POINT pokemon_1P_pos = { 0 };					// 玩家1P的位置
	POINT pokemon_2P_pos = { 0 };					// 玩家2P的位置
	POINT player_1P_pos = { 0 };					// 1P图标的位置
	POINT player_2P_pos = { 0 };					// 2P图标的位置
	POINT btn_1P_left_pos = { 0 };					// 1P向左切换角色的按钮的位置
	POINT btn_1P_right_pos = { 0 };					// 1P向右切换角色的按钮的位置
	POINT btn_2P_left_pos = { 0 };					// 2P向左切换角色的按钮的位置 
	POINT btn_2P_right_pos = { 0 };					// 2P向右切换角色的按钮的位置

	PokemonType player_type_1P = PokemonType::Charmander;	// 玩家1的角色类型
	PokemonType player_type_2P = PokemonType::Charmander;	// 玩家2的角色类型

	Animation animation_pokeball;					// 旋转精灵球动画
	Animation animation_selector_charmander_left;	// 小火龙朝向为左的角色选择动画
	Animation animation_selector_charmander_right;	// 小火龙朝向为右的角色选择动画
	Animation animation_selector_squirtle_left;		// 杰尼龟朝向为左的角色选择动画
	Animation animation_selector_squirtle_right;	// 杰尼龟朝向为右的角色选择动画
	Animation animation_selector_bulbasaur_left;	// 妙蛙种子朝向为左的角色选择动画
	Animation animation_selector_bulbasaur_right;	// 妙蛙种子朝向为右的角色选择动画

	bool is_enter_game = false;						// 是否进入游戏场景
	bool is_return_btn = false;						// 返回按钮是否被按下
	bool is_1P_left_btn = false;					// 玩家1向左切换角色的按钮是否按下
	bool is_1P_right_btn = false;					// 玩家1向右切换角色的按钮是否按下
	bool is_2P_left_btn = false;					// 玩家2向左切换角色的按钮是否按下
	bool is_2P_right_btn = false;					// 玩家2向右切换角色的按钮是否按下
	bool is_enter_start = false;					// 是否按下enter或者开始

};