#pragma once

#include "bullet.h"


extern bool is_open_sound_effect;

extern std::vector<Bullet*> bullet_list;

class FlyLeaf : public Bullet {
public:
	FlyLeaf() {
		bullet_ATK = 15;
		bullet_MATK = 25;
		use_mp = 20;

		gravity = 0;

		bullet_skill_pre_action_pos_velocity = { 0.0f, -0.5f };
		bullet_skill_pre_action_pos_delta = { 0, 100 };

		is_skill_pre_action = true;

		bullet_size = { 44, 27 };
		bullet_velocity = { 1.0f, 0.15f };

		bullet_attribute = BulletAttribute::Wood;

		callback = [&]() {
			if (is_open_sound_effect) mciSendString(_T("play fly_leaf_hit from 0"), NULL, 0, NULL);
			};
	}

	void on_update(int delta) {
		if (is_skill_pre_action) {
			if (bullet_skill_pre_action_pos_delta.x > 0 || bullet_skill_pre_action_pos_delta.y > 0) {
				bullet_pos.x += bullet_skill_pre_action_pos_velocity.x * delta;
				bullet_pos.y += bullet_skill_pre_action_pos_velocity.y * delta;

				bullet_skill_pre_action_pos_delta.x += bullet_skill_pre_action_pos_velocity.x * delta;
				bullet_skill_pre_action_pos_delta.y += bullet_skill_pre_action_pos_velocity.y * delta;
			}
			else {
				is_skill_pre_action = false;
			}
		}
		else {
			bullet_pos.x += bullet_velocity.x * delta;
			bullet_pos.y += bullet_velocity.y * delta;
		}

		if (check_is_exceed_screen()) is_can_remove = true;
	}

	void on_draw() {
		putimage_alpha(bullet_pos.x, bullet_pos.y, atlas_fly_leaf_right.get_image(0));
		if (!is_skill_pre_action) {
			if (bullet_is_facing_right) putimage_alpha(bullet_pos.x, bullet_pos.y, atlas_fly_leaf_right.get_image(1));
			else putimage_alpha(bullet_pos.x, bullet_pos.y, atlas_fly_leaf_right.get_image(1));
		}

		Bullet::on_draw();
	}

};

void fly_leaf(int& mp, int ATK, int MATK, bool is_facing_right, POINT pokemon_pos, POINT pokemon_size, PokemonPlayer player_id) {
	Bullet* bullet = new FlyLeaf();

	const int water_gun_use_mp = bullet->get_use_mp();
	if (water_gun_use_mp > mp) return;
	mp -= water_gun_use_mp;

	bullet->set_ATK(bullet->get_ATK() * ATK);
	bullet->set_MATK(bullet->get_MATK() * MATK);
	bullet->set_bullet_is_facing_right(is_facing_right);

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

	if (is_open_sound_effect) mciSendString(_T("play fly_leaf_up from 0"), NULL, 0, NULL);
}