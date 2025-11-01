#pragma once

#include "picture.h"
#include "pointf.h"
#include "pokemon_player.h"
#include "pokemon_attribute.h"
#include "bullet.h"
#include "animation.h"
#include "timer.h"
#include "collision_line.h"

#include <iostream>
#include <string>


extern bool is_open_sound_effect;

extern std::vector<CollisionLine> collision_thwartwise_line_list;
extern std::vector<CollisionLine> collision_vertical_line_list;
extern std::vector<Bullet*> bullet_list;

extern bool is_attribute_restrain;

class Pokemon {
public:
	Pokemon(bool flag = true) : is_facing_right(flag) {
		animation_current_pokemon = is_facing_right ? &animation_pokemon_right : &animation_pokemon_left;

		timer_recover_mp.set_wait_time(1000);
		timer_recover_mp.set_callback([&]() {
			mp += 5;
			if (mp > 100) mp = 100;
			});
		timer_move_sound.set_wait_time(100);
		timer_move_sound.set_callback([&]() {
			is_play_move_sound = true;
			});
	}

	virtual void skill_1() {}

	virtual void skill_2() {}

	virtual void skill_3() {}

	virtual void skill_4() {}

	virtual void on_update(int delta) {
		int direction = is_right_btn - is_left_btn;
		if (direction) {
			is_facing_right = direction > 0;
			animation_current_pokemon = is_facing_right ? &animation_pokemon_right : &animation_pokemon_left;
			float distance = direction * move_speed * delta;
			run_pos_change(distance);
		}
		else {
			animation_current_pokemon = is_facing_right ? &animation_pokemon_right : &animation_pokemon_left;
		}

		animation_current_pokemon->on_update(delta);

		if (hp > 0) timer_recover_mp.on_update(delta);
		if (hp < 0) hp = 0;
		if (!is_play_move_sound) timer_move_sound.on_update(delta);

		move_collision(delta);

		for (auto bullet : bullet_list) {
			if (bullet->get_target_player() != player_id) continue;
			if (bullet->get_bullet_is_follow_pokemon()) {
				bullet->set_bullet_pos(pokemon_left_top_dot.x + (pokemon_collision_size.x - bullet->get_bullet_size().x) / 2,
					pokemon_left_top_dot.y + (pokemon_collision_size.y - bullet->get_bullet_size().y) / 2);
			}
		}
	}

	virtual void on_draw() {
		// 血条及能量条测试代码		
		int status_bar_width = 400;
		int status_bar_height = 40;
		int status_bar_interval = 2;
		POINT status_bar_1P_pos = { 85, 0 };
		POINT status_bar_2P_pos = { getwidth() - status_bar_width - status_bar_1P_pos.x, 0 };

		//血条
		setcolor(RGB(111, 84, 13));
		rectangle(status_bar_1P_pos.x, status_bar_1P_pos.y, status_bar_1P_pos.x + status_bar_width, status_bar_height);
		rectangle(status_bar_1P_pos.x, status_bar_1P_pos.y + status_bar_height + status_bar_interval,
			status_bar_1P_pos.x + status_bar_width, status_bar_1P_pos.y + 2 * status_bar_height + status_bar_interval);
		rectangle(status_bar_2P_pos.x, status_bar_2P_pos.y, status_bar_2P_pos.x + status_bar_width, status_bar_height);
		rectangle(status_bar_2P_pos.x, status_bar_2P_pos.y + status_bar_height + status_bar_interval,
			status_bar_2P_pos.x + status_bar_width, status_bar_2P_pos.y + 2 * status_bar_height + status_bar_interval);
		if (player_id == PokemonPlayer::P1) {
			setfillcolor(RGB(255, 0, 0));
			fillroundrect(status_bar_1P_pos.x, status_bar_1P_pos.y, status_bar_1P_pos.x + hp * 4, status_bar_height, 8, 8);
			setfillcolor(RGB(0, 0, 255));
			fillroundrect(status_bar_1P_pos.x, status_bar_1P_pos.y + status_bar_height, status_bar_1P_pos.x + mp * 4, 2 * status_bar_height, 8, 8);
		}
		else {
			setfillcolor(RGB(255, 0, 0));
			fillroundrect(status_bar_2P_pos.x, status_bar_2P_pos.y, status_bar_2P_pos.x + hp * 4, status_bar_height, 8, 8);
			setfillcolor(RGB(0, 0, 255));
			fillroundrect(status_bar_2P_pos.x, status_bar_2P_pos.y + status_bar_height, status_bar_2P_pos.x + mp * 4, 2 * status_bar_height, 8, 8);
		}

		// 血条文字提示
		setbkmode(TRANSPARENT);
		TCHAR hp_s[20];
		TCHAR mp_s[20];
		_stprintf_s(hp_s, _T("hp: %d"), hp);
		_stprintf_s(mp_s, _T("mp: %d"), mp);
		if (player_id == PokemonPlayer::P1) {
			setcolor(RGB(0, 0, 0));
			outtextxy(10, status_bar_height * 2 + 5, hp_s);
			outtextxy(10, status_bar_height * 2 + 20, mp_s);
		}
		else {
			setcolor(RGB(0, 0, 0));
			outtextxy(getwidth() - 60, status_bar_height * 2 + 5, hp_s);
			outtextxy(getwidth() - 60, status_bar_height * 2 + 20, mp_s);
		}

		animation_current_pokemon->on_draw(pokemon_pos.x, pokemon_pos.y);
	}

	void on_input(const ExMessage& msg) {
		if (hp <= 0) return;
		switch (msg.message) {
		case WM_KEYDOWN: {
			switch (player_id) {
			case PokemonPlayer::P1:
				switch (msg.vkcode) {
					// 'A'
				case 0x41:
					is_left_btn = true;
					break;
					// 'D'
				case 0x44:
					is_right_btn = true;
					break;
					// 'W'
				case 0x57:
					jump();
					break;
					// 'B'
				case 0x42:
					skill_1();
					break;
					// 'N'
				case 0x4E:
					skill_2();
					break;
					// 'M'
				case 0x4D:
					skill_3();
					break;
					// ','
				case 0xBC:
					skill_4();
					break;
				}
				break;
			case PokemonPlayer::P2:
				switch (msg.vkcode) {
					// '⬅'
				case VK_LEFT:
					is_left_btn = true;
					break;
					// '➡'
				case VK_RIGHT:
					is_right_btn = true;
					break;
					// '⬆'
				case VK_UP:
					jump();
					break;
					// 小键盘的'1'
				case 0x61:
					skill_1();
					break;
					// 小键盘的'2'
				case 0x62:
					skill_2();
					break;
					// 小键盘的'3'
				case 0x63:
					skill_3();
					break;
				case 0x64:
					// 小键盘的'4'
					skill_4();
					break;
				}
				break;
			}
		}
					   break;
		case WM_KEYUP: {
			switch (player_id) {
			case PokemonPlayer::P1:
				switch (msg.vkcode) {
					// 'A'
				case 0x41:
					is_left_btn = false;
					break;
					// 'D'
				case 0x44:
					is_right_btn = false;
					break;
				}
				break;
			case PokemonPlayer::P2:
				switch (msg.vkcode) {
					// '⬅'
				case VK_LEFT:
					is_left_btn = false;
					break;
					// '➡'
				case VK_RIGHT:
					is_right_btn = false;
					break;
				}
				break;
			}
		}
		}
	}

	int get_hp() {
		return hp;
	}

	void set_velocity(float x, float y) {
		pokemon_velocity.x = x;
		pokemon_velocity.y = y;
	}

	int get_pokemon_base_ATK() {
		return pokemon_base_ATK;
	}

	int get_pokemon_base_MATK() {
		return pokemon_base_MATK;
	}

	void set_pokemon_pos(int x, int y) {
		pokemon_pos.x = x;
		pokemon_pos.y = y;
	}

	POINT get_pokemon_pos() {
		return pokemon_pos;
	}

	POINT get_pokemon_size() {
		return pokemon_size;
	}

	void set_id(PokemonPlayer id) {
		player_id = id;
	}

	PokemonType get_pokemon_type() {
		return pokemon_type;
	}

	void run_pos_change(float distance) {
		pokemon_pos.x += distance;

		if (!is_play_move_sound || !check_land()) return;
		switch (rand() % 10) {
		case 1:
			mciSendString(_T("play move_sound_1 from 0"), NULL, 0, NULL);
			break;
		case 2:
			mciSendString(_T("play move_sound_2 from 0"), NULL, 0, NULL);
			break;
		case 3:
			mciSendString(_T("play move_sound_3 from 0"), NULL, 0, NULL);
			break;
		case 4:
			mciSendString(_T("play move_sound_4 from 0"), NULL, 0, NULL);
			break;
		case 5:
			mciSendString(_T("play move_sound_5 from 0"), NULL, 0, NULL);
			break;
		case 6:
			mciSendString(_T("play move_sound_6 from 0"), NULL, 0, NULL);
			break;
		case 7:
			mciSendString(_T("play move_sound_7 from 0"), NULL, 0, NULL);
			break;
		case 8:
			mciSendString(_T("play move_sound_8 from 0"), NULL, 0, NULL);
			break;
		case 9:
			mciSendString(_T("play move_sound_9 from 0"), NULL, 0, NULL);
			break;
		}
		is_play_move_sound = false;
	}

	void jump() {
		if (!is_platform) return;
		pokemon_velocity.y += jump_velocity;
		is_platform = false;
	}

	bool check_land() {
		return pokemon_velocity.y == 0;
	}
	

protected:
	int hp = 100;														// 生命值
	int mp = 100;														// 能量值
	float base_speed = 0.01f;											// 基础速度			
	float move_speed;													// 奔跑速度
	int pokemon_base_ATK;												// 宝可梦的基础物攻
	int pokemon_base_MATK;												// 宝可梦的基础特攻
	int pokemon_base_DEF;												// 宝可梦的基础物防
	int pokemon_base_MDEF;												// 宝可梦的基础特防

	const float gravity = 1.6e-3f;										// 重力加速度
	const float jump_velocity = -0.75f;									// 起跳速度

protected:
	POINTF pokemon_velocity;											// 宝可梦速度
	POINT pokemon_pos;													// 宝可梦的位置
	POINT pokemon_size;													// 宝可梦的大小
	POINT pokemon_collision_size = { 40, 65 };							// 宝可梦的碰撞区域大小
	POINT pokemon_left_top_dot;											// 宝可梦的左上检测点
	POINT pokemon_left_low_dot;											// 宝可梦的左下检测点
	POINT pokemon_right_top_dot;										// 宝可梦的右上检测点
	POINT pokemon_right_low_dot;										// 宝可梦的右下检测点

	Animation* animation_current_pokemon = nullptr;					 	// 当前宝可梦动画

	Animation animation_pokemon_left;									// 朝向向左的宝可梦动画
	Animation animation_pokemon_right;									// 朝向向右的宝可梦动画

	Timer timer_recover_mp;												// 恢复蓝条的定时器
	Timer timer_move_sound;												// 移动音效的定时器

	PokemonPlayer player_id;											// 玩家id
	PokemonAttribute pokemon_attribute;									// 宝可梦属性
	PokemonType pokemon_type;											// 宝可梦种类

	bool is_play_move_sound = true;										// 是否播放移动音效
	bool is_platform = false;											// 是否在平台上
	bool is_facing_right = false;										// 当前是否朝向右边
	bool is_left_btn = false;											// 是否按下了左移按钮
	bool is_right_btn = false;											// 是否按下了右移按钮

private:
	void move_collision(int delta) {
		const float last_tick_velocity = pokemon_velocity.y;
		const float last_tick_low = pokemon_pos.y + 115;

		pokemon_pos.y += pokemon_velocity.y * (float)delta;
		pokemon_velocity.y += gravity * (float)delta;
		pokemon_pos.x += pokemon_velocity.x * delta;

		if (hp <= 0) return;

		// 屏幕周围
		if (pokemon_pos.x < -30) pokemon_pos.x = -30;
		if (pokemon_pos.x > collision_thwartwise_line_list[0].line_pos.pos_2.x - 97)
			pokemon_pos.x = collision_thwartwise_line_list[0].line_pos.pos_2.x - 97;

		// 横线
		if (pokemon_velocity.y > 0) {
			for (auto line : collision_thwartwise_line_list) {
				const bool is_collision_x = pokemon_left_low_dot.x <= line.line_pos.pos_2.x && pokemon_right_low_dot.x >= line.line_pos.pos_1.x;
				const bool is_collision_y = pokemon_left_top_dot.y <= line.line_pos.pos_1.y && pokemon_left_low_dot.y >= line.line_pos.pos_1.y;

				if (is_collision_x && is_collision_y && last_tick_velocity > 0) {
					pokemon_pos.y = line.line_pos.pos_1.y - pokemon_size.y;
					pokemon_velocity.y = 0;
					is_platform = true;
					break;
				}
			}
		}
		else if (pokemon_velocity.y <= 0) {
			for (auto line : collision_thwartwise_line_list) {
				bool is_collision_x = pokemon_left_low_dot.x < line.line_pos.pos_2.x && pokemon_right_low_dot.x > line.line_pos.pos_1.x;
				const bool is_collision_y = pokemon_left_top_dot.y < line.line_pos.pos_1.y && pokemon_left_low_dot.y > line.line_pos.pos_1.y;

				if (is_collision_x && is_collision_y) {
					pokemon_pos.y = line.line_pos.pos_1.y - 20;
					pokemon_velocity.y = 0;
					break;
				}
			}
		}

		// 竖线
		for (auto line : collision_vertical_line_list) {
			const bool is_collision_x = pokemon_left_low_dot.x < line.line_pos.pos_1.x && pokemon_right_low_dot.x > line.line_pos.pos_1.x;
			const bool is_collision_y = pokemon_left_low_dot.y > line.line_pos.pos_1.y && pokemon_left_top_dot.y < line.line_pos.pos_2.y;

			if (!is_collision_x || !is_collision_y) continue;

			if (is_facing_right) {
				if (pokemon_pos.x > line.line_pos.pos_1.x - 97)
					pokemon_pos.x = line.line_pos.pos_1.x - 97;
			}
			else {
				if (pokemon_pos.x < line.line_pos.pos_1.x - 30)
					pokemon_pos.x = line.line_pos.pos_1.x - 30;
			}
		}

		// 子弹与宝可梦的碰撞
		for (auto bullet : bullet_list) {
			if (!bullet->get_is_valid() || bullet->get_target_player() != player_id) continue;
			if (bullet->check_is_collision(pokemon_left_top_dot, pokemon_collision_size)) {
				bullet->on_collision();
				bullet->set_is_harm(true);
				if (bullet->get_is_inflict_one_harm()) {
					bullet->set_is_inflict_one_harm(false);
					bullet->reset_timer();
				}
				else {
					continue;
				}

				BulletAttribute current_bullet_attribute = bullet->get_bullet_attribute();
				float physics_k = 1.538462f;	// 物理攻击系数
				float magic_k = 3.692308f;		// 属性攻击系数
				int is_restrain = check_is_restrain(current_bullet_attribute, pokemon_attribute);	// 属性是否克制
				float attribute_k = is_restrain > 0 ? 1.5 : is_restrain < 0 ? 0.8 : 1;
				if (!is_attribute_restrain) attribute_k = 1;
				int damage = (float)bullet->get_ATK() / (float)(pokemon_base_DEF * physics_k)
					+ (float)bullet->get_MATK() / (float)(pokemon_base_MDEF * magic_k) * attribute_k;
				hp -= damage;
			}
		}
	}

	// 克制返回1 被克制返回-1 无克制关系返回0
	int check_is_restrain(BulletAttribute bullet_attribute, PokemonAttribute pokemon_attribute) {
		if ((int)bullet_attribute == (int)pokemon_attribute) return 0;
		if ((int)bullet_attribute == 0) {
			if ((int)pokemon_attribute == 1) return -1;
			else if ((int)pokemon_attribute == 2) return 1;
		}
		else if ((int)bullet_attribute == 1) {
			if ((int)pokemon_attribute == 2) return -1;
			else if ((int)pokemon_attribute == 0) return 1;
		}
		else if ((int)bullet_attribute == 2) {
			if ((int)pokemon_attribute == 0) return -1;
			else if ((int)pokemon_attribute == 1) return 1;
		}
	}


};