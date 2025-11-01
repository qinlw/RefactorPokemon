#pragma once

#include "pokemon.h"
#include "fly_leaf.h"


class PokemonBulbasaur : public Pokemon {
public:
	PokemonBulbasaur(bool is_facing_right = true) : Pokemon(is_facing_right) {
		animation_pokemon_left.set_atlas(&atlas_bulbasaur_high_frame_left);
		animation_pokemon_left.set_interval(20);
		animation_pokemon_right.set_atlas(&atlas_bulbasaur_high_frame_right);
		animation_pokemon_right.set_interval(20);

		move_speed = 50.0f * base_speed;
		pokemon_base_ATK = 55;
		pokemon_base_MATK = 75;
		pokemon_base_DEF = 65;
		pokemon_base_MDEF = 65;

		pokemon_size = { 128, 115 };

		pokemon_attribute = PokemonAttribute::Wood;
		pokemon_type = PokemonType::Bulbasaur;
	}

	void skill_1() {
		fly_leaf(mp, pokemon_base_ATK, pokemon_base_MATK, is_facing_right, pokemon_pos, pokemon_size, player_id);
	}

	void skill_2() {
		std::cout << "bulbasaur skill_2" << std::endl;
	}

	void skill_3() {
		std::cout << "bulbasaur skill_3" << std::endl;
	}

	void skill_4() {
		std::cout << "bulbasaur skill_4" << std::endl;
	}

	void on_update(int delta) {
		Pokemon::on_update(delta);

		pokemon_left_top_dot = { is_facing_right ? pokemon_pos.x + 50 : pokemon_pos.x + 30, pokemon_pos.y + 50 };
		pokemon_left_low_dot = { is_facing_right ? pokemon_pos.x + 50 : pokemon_pos.x + 30, pokemon_pos.y + 115 };
		pokemon_right_top_dot = { is_facing_right ? pokemon_pos.x + 90 : pokemon_pos.x + 70 , pokemon_pos.y + 50 };
		pokemon_right_low_dot = { is_facing_right ? pokemon_pos.x + 90 : pokemon_pos.x + 70, pokemon_pos.y + 115 };

		pokemon_size = { 128, 115 };
	}

	void on_draw() {
		Pokemon::on_draw();

		if (is_debug) {
			setcolor(RGB(0, 0, 255));
			rectangle(pokemon_left_top_dot.x, pokemon_left_top_dot.y, pokemon_right_low_dot.x, pokemon_right_low_dot.y);
		}
	}


};