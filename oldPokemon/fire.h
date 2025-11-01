#pragma once

#include "bullet.h"


extern bool is_open_sound_effect;

extern std::vector<Bullet*> bullet_list;

class Fire : public Bullet {
public:
	Fire() {
		animation_fireball.set_atlas(&atlas_fireball);
		animation_fireball.set_interval(100);
		animation_fire.set_atlas(&atlas_fire);
		animation_fire.set_interval(200);
		animation_fire.set_is_loop(false);
		animation_fire.set_callback([&]() {
			is_can_remove = true;
			});

		timer_is_inflict_one_harm.set_wait_time(200);
		timer_is_inflict_one_harm.set_one_shot(true);
		timer_is_inflict_one_harm.set_callback([&]() {
			is_inflict_one_harm = true;
			});

		bullet_ATK = 0;
		bullet_MATK = 10;
		use_mp = 20;

		bullet_size = { 32, 32 };
		bullet_velocity = { 0.5f, 0.0f };

		bullet_attribute = BulletAttribute::Fire;

		callback = [&]() {
			bullet_is_follow_pokemon = true;
			};
	}

	void on_update(int delta) {
		if (!is_harm) {
			bullet_pos.x += bullet_velocity.x * delta;
			bullet_pos.y += bullet_velocity.y * delta;
		}

		if (!is_harm) {
			animation_fireball.on_update(delta);
		}
		else {
			animation_fire.on_update(delta);
			if (is_permit_play_burn_sound_effect) {
				if (is_open_sound_effect) mciSendString(_T("play burn_sound_effect from 0"), NULL, 0, NULL);
				is_permit_play_burn_sound_effect = false;
			}
		}

		if (!is_inflict_one_harm) timer_is_inflict_one_harm.on_update(delta);

		if (check_is_exceed_screen()) is_can_remove = true;
	}

	void on_draw() {
		if (!is_harm) animation_fireball.on_draw(bullet_pos.x, bullet_pos.y);
		else animation_fire.on_draw(bullet_pos.x, bullet_pos.y);

		Bullet::on_draw();
	}

	int get_use_mp() {
		return use_mp;
	}

	POINTF get_bullet_velocity() {
		return bullet_velocity;
	}


private:
	Animation animation_fireball;								// 火球动画（火花未碰撞动画）
	Animation animation_fire;									// 火花动画

	bool is_permit_play_burn_sound_effect = true;				// 是否可以播放燃烧音效


};

void fire(int& mp, int ATK, int MATK, bool is_facing_right, POINT pokemon_pos, POINT pokemon_size, PokemonPlayer player_id) {
	Bullet* bullet = new Fire();

	const int fire_use_mp = bullet->get_use_mp();
	if (fire_use_mp > mp) return;
	mp -= fire_use_mp;

	bullet->set_ATK(bullet->get_ATK() * ATK);
	bullet->set_MATK(bullet->get_MATK() * MATK);

	const POINT& origin_bullet_size = bullet->get_bullet_size();
	const POINTF& origin_bullet_velocity = bullet->get_bullet_velocity();

	POINT current_bullet_position;
	POINTF current_bullet_velocity;
	current_bullet_position.x = is_facing_right ? pokemon_pos.x + pokemon_size.x - origin_bullet_size.x : pokemon_pos.x + origin_bullet_size.x;
	current_bullet_position.y = pokemon_pos.y + pokemon_size.y / 2;
	current_bullet_velocity.x = is_facing_right ? origin_bullet_velocity.x : -origin_bullet_velocity.x;
	current_bullet_velocity.y = origin_bullet_velocity.y;

	bullet->set_bullet_pos(current_bullet_position.x, current_bullet_position.y);
	bullet->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);

	bullet->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);

	bullet_list.push_back(bullet);

	if (is_open_sound_effect) mciSendString(_T("play fire_shoot_sound_effect from 0"), NULL, 0, NULL);
}