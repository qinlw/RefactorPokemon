#pragma once

#include "picture.h"
#include "pointf.h"
#include "pokemon_player.h"
#include "bullet_attribute.h"
#include "animation.h"
#include "timer.h"


extern bool is_debug;

class Bullet {
public:
	void set_ATK(int val) {
		bullet_ATK = val;
	}

	int get_ATK() {
		return bullet_ATK;
	}

	void set_MATK(int val) {
		bullet_MATK = val;
	}

	int  get_MATK() {
		return bullet_MATK;
	}

	void set_use_mp(int val) {
		use_mp = val;
	}

	int get_use_mp() {
		return use_mp;
	}

	void set_animation_number(int val) {
		animation_number = val;
	}

	int get_animation_number() {
		return animation_number;
	}

	void set_bullet_velocity(float x, float y) {
		bullet_velocity.x = x;
		bullet_velocity.y = y;
	}

	POINTF get_bullet_velocity() {
		return bullet_velocity;
	}

	POINT get_bullet_size() {
		return bullet_size;
	}

	void set_pokemon_pos(int x, int y) {
		pokemon_pos.x = x;
		pokemon_pos.y = y;
	}

	POINT get_pokemon_pos() {
		return pokemon_pos;
	}

	void set_pokemon_size(int x, int y) {
		pokemon_size.x = x;
		pokemon_size.y = y;
	}

	POINT get_pokemon_size() {
		return pokemon_size;
	}

	virtual void set_bullet_pos(int x, int y) {
		bullet_pos.x = x;
		bullet_pos.y = y;
	}

	void set_target_player(PokemonPlayer pokemon_player) {
		target_player = pokemon_player;
	}

	PokemonPlayer get_target_player() {
		return target_player;
	}

	BulletAttribute get_bullet_attribute() {
		return bullet_attribute;
	}

	void reset_timer() {
		timer_is_inflict_one_harm.reset();
	}

	void set_bullet_is_facing_right(bool flag) {
		bullet_is_facing_right = flag;
	}

	void set_is_valid(bool flag) {
		is_valid = flag;
	}

	bool get_is_valid() {
		return is_valid;
	}

	void set_is_harm(bool flag) {
		is_harm = flag;
	}

	void set_is_inflict_one_harm(bool flag) {
		is_inflict_one_harm = flag;
	}

	bool get_is_inflict_one_harm() {
		return is_inflict_one_harm;
	}

	void set_is_can_remove(bool flag) {
		is_can_remove = flag;
	}

	bool check_is_can_remove() const {
		return is_can_remove;
	}

	void set_bullet_is_follow_pokemon(bool flag) {
		bullet_is_follow_pokemon = flag;
	}

	bool get_bullet_is_follow_pokemon() {
		return bullet_is_follow_pokemon;
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}

	void on_collision() {
		callback();
	}

	bool check_is_collision(POINT pos, POINT size) {
		return (max(bullet_pos.x + bullet_size.x, pos.x + size.x) - min(bullet_pos.x, pos.x)) < bullet_size.x + size.x
			&& (max(bullet_pos.y + bullet_size.y, pos.y + size.y) - min(bullet_pos.y, pos.y)) < bullet_size.y + size.y;
	}

	virtual void on_update(int delta) {}

	virtual void on_draw() {
		if (is_debug) {
			setcolor(RGB(255, 255, 255));
			rectangle(bullet_pos.x, bullet_pos.y, bullet_pos.x + bullet_size.x, bullet_pos.y + bullet_size.y);
			circle(bullet_pos.x + bullet_size.x / 2, bullet_pos.y + bullet_size.y / 2, bullet_size.x / 2);
		}
	}
	 

protected:
	int bullet_ATK;													// 子弹的基础物攻
	int bullet_MATK;												// 子弹的基础特攻
	int use_mp;														// 能量消耗

	float gravity;													// 子弹受到的重力

protected:
	int animation_number;											// 动画序号（连续性的技能播放动画时存在多个动画）

	POINTF bullet_skill_pre_action_pos_velocity;					// 子弹前摇期间的速度
	POINT bullet_skill_pre_action_pos_delta;						// 子弹前摇导致的位置变化

	bool bullet_is_follow_pokemon = false;							// 子弹是否跟随宝可梦
	bool is_skill_pre_action = false;								// 是否在技能前摇阶段

protected:
	POINTF bullet_velocity;											// 子弹速度
	POINT bullet_size;												// 子弹大小
	POINT bullet_pos;												// 子弹位置
	POINT pokemon_pos = { 0 };										// 发射时宝可梦的位置
	POINT pokemon_size = { 0 };										// 发射时宝可梦的尺寸

	PokemonPlayer target_player = PokemonPlayer::P1;				// 子弹目标玩家
	BulletAttribute bullet_attribute;								// 子弹属性

	Timer timer_is_inflict_one_harm;								// 是否造成一次伤害的定时器

	bool bullet_is_facing_right = true;								// 子弹是否面向右边
	bool is_inflict_one_harm = true;								// 是否造成一次伤害
	bool is_can_remove = false;										// 子弹是否能被移除
	bool is_valid = true;											// 子弹是否有效果
	bool is_harm = false;											// 子弹是否有伤害

	std::function<void()> callback;									// 子弹碰撞回调函数

protected:
	bool check_is_exceed_screen() {
		return (bullet_pos.x + bullet_size.x < 0) || (bullet_pos.x > getwidth())
			|| (bullet_pos.y + bullet_size.y < 0) || (bullet_pos.y > getheight());
	}

};