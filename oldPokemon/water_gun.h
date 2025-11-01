#pragma once

#include "bullet.h"


extern bool is_open_sound_effect;

extern std::vector<Bullet*> bullet_list;

class WaterGun : public Bullet {
public:
	WaterGun() {
		animation_water_droplet_right.set_atlas(&atlas_water_droplet_right);
		animation_water_droplet_right.set_interval(100);
		animation_water_droplet_left.set_atlas(&atlas_water_droplet_left);
		animation_water_droplet_left.set_interval(100);
		animation_splashes.set_atlas(&atlas_splashes);
		animation_splashes.set_interval(200);
		animation_splashes.set_is_loop(false);
		animation_splashes.set_callback([&]() {
			is_can_remove = true;
			});

		bullet_ATK = 0;
		bullet_MATK = 70;
		use_mp = 20;

		gravity = 1.6e-3f;


		bullet_size = { 48, 48 };
		bullet_velocity = { 0.5f, -0.5f };

		bullet_attribute = BulletAttribute::Water;

		callback = [&]() {
			bullet_is_follow_pokemon = true;
			};
	}

	void on_update(int delta) {
		if (!is_harm) {
			bullet_velocity.y += gravity * delta;
			bullet_pos.x += bullet_velocity.x * delta;
			bullet_pos.y += bullet_velocity.y * delta;
		}

		if (!is_harm) {
			if (bullet_is_facing_right) animation_water_droplet_right.on_update(delta);
			else animation_water_droplet_left.on_update(delta);
		}
		else {
			animation_splashes.on_update(delta); 			
			if (is_permit_play_splash_sound_effect) {
				if (is_open_sound_effect) mciSendString(_T("play splash from 0"), NULL, 0, NULL);
				is_permit_play_splash_sound_effect = false;
			}
		}

		if (check_is_exceed_screen()) is_can_remove = true;
	}

	void on_draw() {
		if (!is_harm) {
			if (bullet_is_facing_right) animation_water_droplet_right.on_draw(bullet_pos.x, bullet_pos.y);
			else animation_water_droplet_left.on_draw(bullet_pos.x, bullet_pos.y);
		}
		else {
			animation_splashes.on_draw(bullet_pos.x, bullet_pos.y);
		}

		Bullet::on_draw();
	}

	int get_use_mp() {
		return use_mp;
	}

	POINTF get_bullet_velocity() {
		return bullet_velocity;
	}


private:
	Animation animation_water_droplet_right;						// 水枪发射向右的动画
	Animation animation_water_droplet_left;							// 水枪发射向左的动画
	Animation animation_splashes;									// 水枪命中后的动画

	bool is_permit_play_splash_sound_effect = true;					// 是否允许播放溅水音效

};


void water_gun(int& mp, int ATK, int MATK, bool is_facing_right, POINT pokemon_pos, POINT pokemon_size, PokemonPlayer player_id) {
	Bullet* bullet = new WaterGun();

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

	if (is_open_sound_effect) mciSendString(_T("play water_gun_sound_effect from 0"), NULL, 0, NULL);
}