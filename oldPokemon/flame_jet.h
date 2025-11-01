#pragma once

#include "bullet.h"


extern bool is_open_sound_effect;

extern std::vector<Bullet*> bullet_list;

class FlameJet : public Bullet {
public:
	FlameJet() {
		animation_flame_jet_x_01.set_atlas(&atlas_flame_jet_x_01);
		animation_flame_jet_x_01.set_interval(100);
		animation_flame_jet_x_02.set_atlas(&atlas_flame_jet_x_02);
		animation_flame_jet_x_02.set_interval(100);
		animation_flame_jet_x_03.set_atlas(&atlas_flame_jet_x_03);
		animation_flame_jet_x_03.set_interval(100);
		animation_flame_jet_x_04.set_atlas(&atlas_flame_jet_x_04);
		animation_flame_jet_x_04.set_interval(100);
		animation_flame_jet_x_05.set_atlas(&atlas_flame_jet_x_05);
		animation_flame_jet_x_05.set_interval(100);
		animation_flame_jet_x_06.set_atlas(&atlas_flame_jet_x_06);
		animation_flame_jet_x_06.set_interval(100);
		animation_flame_jet_x_07.set_atlas(&atlas_flame_jet_x_07);
		animation_flame_jet_x_07.set_interval(100);
		animation_flame_jet_x_08.set_atlas(&atlas_flame_jet_x_08);
		animation_flame_jet_x_08.set_interval(100);
		animation_flame_jet_x_09.set_atlas(&atlas_flame_jet_x_09);
		animation_flame_jet_x_09.set_interval(100);
		animation_flame_jet_x_10.set_atlas(&atlas_flame_jet_x_10);
		animation_flame_jet_x_10.set_interval(100);
		animation_flame_jet_x_11.set_atlas(&atlas_flame_jet_x_11);
		animation_flame_jet_x_11.set_interval(100);
		animation_flame_jet_x_12.set_atlas(&atlas_flame_jet_x_12);
		animation_flame_jet_x_12.set_interval(100);
		animation_flame_jet_x_13.set_atlas(&atlas_flame_jet_x_13);
		animation_flame_jet_x_13.set_interval(100);
		animation_flame_jet_x_14.set_atlas(&atlas_flame_jet_x_14);
		animation_flame_jet_x_14.set_interval(100);
		animation_flame_jet_x_15.set_atlas(&atlas_flame_jet_x_15);
		animation_flame_jet_x_15.set_interval(100);
		animation_flame_jet_x_16.set_atlas(&atlas_flame_jet_x_16);
		animation_flame_jet_x_16.set_interval(100);

		bullet_ATK = 0;
		bullet_MATK = 20;
		use_mp = 40;

		bullet_size = { 10, 40 };
		bullet_velocity = { 0.6f, 0.0f };

		bullet_attribute = BulletAttribute::Fire;

		callback = [&]() {
			is_can_remove = true;
			if (!is_open_sound_effect) return;
			switch (rand() % 8 + 1) {
			case 1:
				mciSendString(_T("play short_burn_sound_effect_1 from 0"), NULL, 0, NULL);
				break;
			case 2:
				mciSendString(_T("play short_burn_sound_effect_2 from 0"), NULL, 0, NULL);
				break;
			case 3:
				mciSendString(_T("play short_burn_sound_effect_3 from 0"), NULL, 0, NULL);
				break;
			case 4:
				mciSendString(_T("play short_burn_sound_effect_4 from 0"), NULL, 0, NULL);
				break;
			case 5:
				mciSendString(_T("play short_burn_sound_effect_5 from 0"), NULL, 0, NULL);
				break;
			case 6:
				mciSendString(_T("play short_burn_sound_effect_6 from 0"), NULL, 0, NULL);
				break;
			case 7:
				mciSendString(_T("play short_burn_sound_effect_7 from 0"), NULL, 0, NULL);
				break;
			case 8:
				mciSendString(_T("play short_burn_sound_effect_8 from 0"), NULL, 0, NULL);
				break;
			}
			};
	}

	void on_update(int delta) {
	//	if (!bullet_01_is_harm) bullet_01_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_02_is_harm) bullet_02_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_03_is_harm) bullet_03_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_04_is_harm) bullet_04_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_05_is_harm) bullet_05_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_06_is_harm) bullet_06_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_07_is_harm) bullet_07_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_08_is_harm) bullet_08_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_09_is_harm) bullet_09_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_10_is_harm) bullet_10_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_11_is_harm) bullet_11_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_12_is_harm) bullet_12_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_13_is_harm) bullet_13_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_14_is_harm) bullet_14_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_15_is_harm) bullet_15_pos.x += bullet_velocity.x * delta;
	//	if (!bullet_16_is_harm) bullet_16_pos.x += bullet_velocity.x * delta;
	//
	//	if (!bullet_01_is_harm) animation_flame_jet_x_01.on_update(delta);
	//	if (!bullet_02_is_harm) animation_flame_jet_x_02.on_update(delta);
	//	if (!bullet_03_is_harm) animation_flame_jet_x_03.on_update(delta);
	//	if (!bullet_04_is_harm) animation_flame_jet_x_04.on_update(delta);
	//	if (!bullet_05_is_harm) animation_flame_jet_x_05.on_update(delta);
	//	if (!bullet_06_is_harm) animation_flame_jet_x_06.on_update(delta);
	//	if (!bullet_07_is_harm) animation_flame_jet_x_07.on_update(delta);
	//	if (!bullet_08_is_harm) animation_flame_jet_x_08.on_update(delta);
	//	if (!bullet_09_is_harm) animation_flame_jet_x_09.on_update(delta);
	//	if (!bullet_10_is_harm) animation_flame_jet_x_10.on_update(delta);
	//	if (!bullet_11_is_harm) animation_flame_jet_x_11.on_update(delta);
	//	if (!bullet_12_is_harm) animation_flame_jet_x_12.on_update(delta);
	//	if (!bullet_13_is_harm) animation_flame_jet_x_13.on_update(delta);
	//	if (!bullet_14_is_harm) animation_flame_jet_x_14.on_update(delta);
	//	if (!bullet_15_is_harm) animation_flame_jet_x_15.on_update(delta);
	//	if (!bullet_16_is_harm) animation_flame_jet_x_16.on_update(delta);

		if (!is_harm) bullet_pos.x += bullet_velocity.x * delta;

		switch (animation_number) {
		case 1:
			if (!is_harm) animation_flame_jet_x_01.on_update(delta);
			break;
		case 2:
			if (!is_harm) animation_flame_jet_x_02.on_update(delta);
			break;
		case 3:
			if (!is_harm) animation_flame_jet_x_03.on_update(delta);
			break;
		case 4:
			if (!is_harm) animation_flame_jet_x_04.on_update(delta);
			break;
		case 5:
			if (!is_harm) animation_flame_jet_x_05.on_update(delta);
			break;
		case 6:
			if (!is_harm) animation_flame_jet_x_06.on_update(delta);
			break;
		case 7:
			if (!is_harm) animation_flame_jet_x_07.on_update(delta);
			break;
		case 8:
			if (!is_harm) animation_flame_jet_x_08.on_update(delta);
			break;
		case 9:
			if (!is_harm) animation_flame_jet_x_09.on_update(delta);
			break;
		case 10:
			if (!is_harm) animation_flame_jet_x_10.on_update(delta);
			break;
		case 11:
			if (!is_harm) animation_flame_jet_x_11.on_update(delta);
			break;
		case 12:
			if (!is_harm) animation_flame_jet_x_12.on_update(delta);
			break;
		case 13:
			if (!is_harm) animation_flame_jet_x_13.on_update(delta);
			break;
		case 14:
			if (!is_harm) animation_flame_jet_x_14.on_update(delta);
			break;
		case 15:
			if (!is_harm) animation_flame_jet_x_15.on_update(delta);
			break;
		case 16:
			if (!is_harm) animation_flame_jet_x_16.on_update(delta);
			break;
		}
	}

	void on_draw() {
		int pos = get_pokemon_pos().x;
		int size = get_pokemon_size().x;

		//if (bullet_is_facing_right) {
		//	if (bullet_01_pos.x > x) animation_flame_jet_x_01.on_draw(bullet_01_pos.x, bullet_01_pos.y);
		//	if (bullet_02_pos.x > x) animation_flame_jet_x_02.on_draw(bullet_02_pos.x, bullet_02_pos.y);
		//	if (bullet_03_pos.x > x) animation_flame_jet_x_03.on_draw(bullet_03_pos.x, bullet_03_pos.y);
		//	if (bullet_04_pos.x > x) animation_flame_jet_x_04.on_draw(bullet_04_pos.x, bullet_04_pos.y);
		//	if (bullet_05_pos.x > x) animation_flame_jet_x_05.on_draw(bullet_05_pos.x, bullet_05_pos.y);
		//	if (bullet_06_pos.x > x) animation_flame_jet_x_06.on_draw(bullet_06_pos.x, bullet_06_pos.y);
		//	if (bullet_07_pos.x > x) animation_flame_jet_x_07.on_draw(bullet_07_pos.x, bullet_07_pos.y);
		//	if (bullet_08_pos.x > x) animation_flame_jet_x_08.on_draw(bullet_08_pos.x, bullet_08_pos.y);
		//	if (bullet_09_pos.x > x) animation_flame_jet_x_09.on_draw(bullet_09_pos.x, bullet_09_pos.y);
		//	if (bullet_10_pos.x > x) animation_flame_jet_x_10.on_draw(bullet_10_pos.x, bullet_10_pos.y);
		//	if (bullet_11_pos.x > x) animation_flame_jet_x_11.on_draw(bullet_11_pos.x, bullet_11_pos.y);
		//	if (bullet_12_pos.x > x) animation_flame_jet_x_12.on_draw(bullet_12_pos.x, bullet_12_pos.y);
		//	if (bullet_13_pos.x > x) animation_flame_jet_x_13.on_draw(bullet_13_pos.x, bullet_13_pos.y);
		//	if (bullet_14_pos.x > x) animation_flame_jet_x_14.on_draw(bullet_14_pos.x, bullet_14_pos.y);
		//	if (bullet_15_pos.x > x) animation_flame_jet_x_15.on_draw(bullet_15_pos.x, bullet_15_pos.y);
		//	if (bullet_16_pos.x > x) animation_flame_jet_x_16.on_draw(bullet_16_pos.x, bullet_16_pos.y);
		//}
		//else {
		//	if (bullet_01_pos.x < x) animation_flame_jet_x_01.on_draw(bullet_01_pos.x, bullet_01_pos.y);
		//	if (bullet_02_pos.x < x) animation_flame_jet_x_02.on_draw(bullet_02_pos.x, bullet_02_pos.y);
		//	if (bullet_03_pos.x < x) animation_flame_jet_x_03.on_draw(bullet_03_pos.x, bullet_03_pos.y);
		//	if (bullet_04_pos.x < x) animation_flame_jet_x_04.on_draw(bullet_04_pos.x, bullet_04_pos.y);
		//	if (bullet_05_pos.x < x) animation_flame_jet_x_05.on_draw(bullet_05_pos.x, bullet_05_pos.y);
		//	if (bullet_06_pos.x < x) animation_flame_jet_x_06.on_draw(bullet_06_pos.x, bullet_06_pos.y);
		//	if (bullet_07_pos.x < x) animation_flame_jet_x_07.on_draw(bullet_07_pos.x, bullet_07_pos.y);
		//	if (bullet_08_pos.x < x) animation_flame_jet_x_08.on_draw(bullet_08_pos.x, bullet_08_pos.y);
		//	if (bullet_09_pos.x < x) animation_flame_jet_x_09.on_draw(bullet_09_pos.x, bullet_09_pos.y);
		//	if (bullet_10_pos.x < x) animation_flame_jet_x_10.on_draw(bullet_10_pos.x, bullet_10_pos.y);
		//	if (bullet_11_pos.x < x) animation_flame_jet_x_11.on_draw(bullet_11_pos.x, bullet_11_pos.y);
		//	if (bullet_12_pos.x < x) animation_flame_jet_x_12.on_draw(bullet_12_pos.x, bullet_12_pos.y);
		//	if (bullet_13_pos.x < x) animation_flame_jet_x_13.on_draw(bullet_13_pos.x, bullet_13_pos.y);
		//	if (bullet_14_pos.x < x) animation_flame_jet_x_14.on_draw(bullet_14_pos.x, bullet_14_pos.y);
		//	if (bullet_15_pos.x < x) animation_flame_jet_x_15.on_draw(bullet_15_pos.x, bullet_15_pos.y);
		//	if (bullet_16_pos.x < x) animation_flame_jet_x_16.on_draw(bullet_16_pos.x, bullet_16_pos.y);
		//}

		switch (animation_number) {
		case 1:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_01.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 2:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_02.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 3:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_03.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 4:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_04.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 5:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_05.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 6:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_06.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 7:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_07.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 8:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_08.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 9:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_09.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 10:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_10.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 11:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_11.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 12:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_12.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 13:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_13.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 14:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_14.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 15:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_15.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		case 16:
			if (bullet_is_facing_right ? bullet_pos.x > pos + size : bullet_pos.x < pos) animation_flame_jet_x_16.on_draw(bullet_pos.x, bullet_pos.y);
			break;
		}

		Bullet::on_draw();
	}


protected:
	//POINT bullet_01_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬01µÄÎ»ÖÃ
	//POINT bullet_02_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬02µÄÎ»ÖÃ
	//POINT bullet_03_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬03µÄÎ»ÖÃ
	//POINT bullet_04_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬04µÄÎ»ÖÃ
	//POINT bullet_05_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬05µÄÎ»ÖÃ
	//POINT bullet_06_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬06µÄÎ»ÖÃ
	//POINT bullet_07_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬07µÄÎ»ÖÃ
	//POINT bullet_08_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬08µÄÎ»ÖÃ
	//POINT bullet_09_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬09µÄÎ»ÖÃ
	//POINT bullet_10_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬10µÄÎ»ÖÃ
	//POINT bullet_11_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬11µÄÎ»ÖÃ
	//POINT bullet_12_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬12µÄÎ»ÖÃ
	//POINT bullet_13_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬13µÄÎ»ÖÃ
	//POINT bullet_14_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬14µÄÎ»ÖÃ
	//POINT bullet_15_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬15µÄÎ»ÖÃ
	//POINT bullet_16_pos = { 0 };					    // ×Óµ¯ÇÐÆ¬16µÄÎ»ÖÃ

	Animation animation_flame_jet_x_01;				    // »ðÑæÅçÉäÇÐÆ¬01µÄ¶¯»­
	Animation animation_flame_jet_x_02;				    // »ðÑæÅçÉäÇÐÆ¬02µÄ¶¯»­
	Animation animation_flame_jet_x_03;				    // »ðÑæÅçÉäÇÐÆ¬03µÄ¶¯»­
	Animation animation_flame_jet_x_04;				    // »ðÑæÅçÉäÇÐÆ¬04µÄ¶¯»­
	Animation animation_flame_jet_x_05;				    // »ðÑæÅçÉäÇÐÆ¬05µÄ¶¯»­
	Animation animation_flame_jet_x_06;				    // »ðÑæÅçÉäÇÐÆ¬06µÄ¶¯»­
	Animation animation_flame_jet_x_07;				    // »ðÑæÅçÉäÇÐÆ¬07µÄ¶¯»­
	Animation animation_flame_jet_x_08;				    // »ðÑæÅçÉäÇÐÆ¬08µÄ¶¯»­
	Animation animation_flame_jet_x_09;				    // »ðÑæÅçÉäÇÐÆ¬09µÄ¶¯»­
	Animation animation_flame_jet_x_10;				    // »ðÑæÅçÉäÇÐÆ¬10µÄ¶¯»­
	Animation animation_flame_jet_x_11;				    // »ðÑæÅçÉäÇÐÆ¬11µÄ¶¯»­
	Animation animation_flame_jet_x_12;				    // »ðÑæÅçÉäÇÐÆ¬12µÄ¶¯»­
	Animation animation_flame_jet_x_13;				    // »ðÑæÅçÉäÇÐÆ¬13µÄ¶¯»­
	Animation animation_flame_jet_x_14;				    // »ðÑæÅçÉäÇÐÆ¬14µÄ¶¯»­
	Animation animation_flame_jet_x_15;				    // »ðÑæÅçÉäÇÐÆ¬15µÄ¶¯»­
	Animation animation_flame_jet_x_16;				    // »ðÑæÅçÉäÇÐÆ¬16µÄ¶¯»­

	//bool bullet_01_is_harm = false;					// ×Óµ¯ÇÐÆ¬01ÊÇ·ñÓÐÉËº¦
	//bool bullet_02_is_harm = false;					// ×Óµ¯ÇÐÆ¬02ÊÇ·ñÓÐÉËº¦
	//bool bullet_03_is_harm = false;					// ×Óµ¯ÇÐÆ¬03ÊÇ·ñÓÐÉËº¦
	//bool bullet_04_is_harm = false;					// ×Óµ¯ÇÐÆ¬04ÊÇ·ñÓÐÉËº¦
	//bool bullet_05_is_harm = false;					// ×Óµ¯ÇÐÆ¬05ÊÇ·ñÓÐÉËº¦
	//bool bullet_06_is_harm = false;					// ×Óµ¯ÇÐÆ¬06ÊÇ·ñÓÐÉËº¦
	//bool bullet_07_is_harm = false;					// ×Óµ¯ÇÐÆ¬07ÊÇ·ñÓÐÉËº¦
	//bool bullet_08_is_harm = false;					// ×Óµ¯ÇÐÆ¬08ÊÇ·ñÓÐÉËº¦
	//bool bullet_09_is_harm = false;					// ×Óµ¯ÇÐÆ¬09ÊÇ·ñÓÐÉËº¦
	//bool bullet_10_is_harm = false;					// ×Óµ¯ÇÐÆ¬10ÊÇ·ñÓÐÉËº¦
	//bool bullet_11_is_harm = false;					// ×Óµ¯ÇÐÆ¬11ÊÇ·ñÓÐÉËº¦
	//bool bullet_12_is_harm = false;					// ×Óµ¯ÇÐÆ¬12ÊÇ·ñÓÐÉËº¦
	//bool bullet_13_is_harm = false;					// ×Óµ¯ÇÐÆ¬13ÊÇ·ñÓÐÉËº¦
	//bool bullet_14_is_harm = false;					// ×Óµ¯ÇÐÆ¬14ÊÇ·ñÓÐÉËº¦
	//bool bullet_15_is_harm = false;					// ×Óµ¯ÇÐÆ¬15ÊÇ·ñÓÐÉËº¦
	//bool bullet_16_is_harm = false;					// ×Óµ¯ÇÐÆ¬16ÊÇ·ñÓÐÉËº¦

};


//class FlameJet_01 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_01_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_01_pos.x = x;
//		bullet_01_pos.y = y;
//	}
//
//};
//
//class FlameJet_02 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_02_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_02_pos.x = x;
//		bullet_02_pos.y = y;
//	}
//
//};
//
//class FlameJet_03 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_03_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_03_pos.x = x;
//		bullet_03_pos.y = y;
//	}
//
//};
//
//class FlameJet_04 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_04_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_04_pos.x = x;
//		bullet_04_pos.y = y;
//	}
//
//};
//
//class FlameJet_05 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_05_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_05_pos.x = x;
//		bullet_05_pos.y = y;
//	}
//
//};
//
//class FlameJet_06 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_06_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_06_pos.x = x;
//		bullet_06_pos.y = y;
//	}
//
//};
//
//class FlameJet_07 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_07_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_07_pos.x = x;
//		bullet_07_pos.y = y;
//	}
//
//};
//
//class FlameJet_08 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_08_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_08_pos.x = x;
//		bullet_08_pos.y = y;
//	}
//
//};
//
//class FlameJet_09 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_09_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_09_pos.x = x;
//		bullet_09_pos.y = y;
//	}
//
//};
//
//class FlameJet_10 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_10_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_10_pos.x = x;
//		bullet_10_pos.y = y;
//	}
//
//};
//
//class FlameJet_11 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_11_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_11_pos.x = x;
//		bullet_11_pos.y = y;
//	}
//
//};
//
//class FlameJet_12 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_12_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_12_pos.x = x;
//		bullet_12_pos.y = y;
//	}
//
//};
//
//class FlameJet_13 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_13_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_13_pos.x = x;
//		bullet_13_pos.y = y;
//	}
//
//};
//
//class FlameJet_14 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_14_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_14_pos.x = x;
//		bullet_14_pos.y = y;
//	}
//
//};
//
//class FlameJet_15 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_15_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_15_pos.x = x;
//		bullet_15_pos.y = y;
//	}
//
//};
//
//class FlameJet_16 : public FlameJet {
//public:
//	void set_is_harm(bool flag) {
//		bullet_16_is_harm = flag;
//	}
//
//	void set_bullet_pos(int x, int y) {
//		bullet_16_pos.x = x;
//		bullet_16_pos.y = y;
//	}
//
//};


void flame_jet(int& mp, int ATK, int MATK, bool is_facing_right, POINT pokemon_pos, POINT pokemon_size, PokemonPlayer player_id) {
	//Bullet* bullet_16 = new FlameJet_16();
	//Bullet* bullet_15 = new FlameJet_15();
	//Bullet* bullet_14 = new FlameJet_14();
	//Bullet* bullet_13 = new FlameJet_13();
	//Bullet* bullet_12 = new FlameJet_12();
	//Bullet* bullet_11 = new FlameJet_11();
	//Bullet* bullet_10 = new FlameJet_10();
	//Bullet* bullet_09 = new FlameJet_09();
	//Bullet* bullet_08 = new FlameJet_08();
	//Bullet* bullet_07 = new FlameJet_07();
	//Bullet* bullet_06 = new FlameJet_06();
	//Bullet* bullet_05 = new FlameJet_05();
	//Bullet* bullet_04 = new FlameJet_04();
	//Bullet* bullet_03 = new FlameJet_03();
	//Bullet* bullet_02 = new FlameJet_02();
	//Bullet* bullet_01 = new FlameJet_01();

	Bullet* bullet_16 = new FlameJet();
	Bullet* bullet_15 = new FlameJet();
	Bullet* bullet_14 = new FlameJet();
	Bullet* bullet_13 = new FlameJet();
	Bullet* bullet_12 = new FlameJet();
	Bullet* bullet_11 = new FlameJet();
	Bullet* bullet_10 = new FlameJet();
	Bullet* bullet_09 = new FlameJet();
	Bullet* bullet_08 = new FlameJet();
	Bullet* bullet_07 = new FlameJet();
	Bullet* bullet_06 = new FlameJet();
	Bullet* bullet_05 = new FlameJet();
	Bullet* bullet_04 = new FlameJet();
	Bullet* bullet_03 = new FlameJet();
	Bullet* bullet_02 = new FlameJet();
	Bullet* bullet_01 = new FlameJet();

	const int flame_jet_use_mp = bullet_16->get_use_mp();
	if (flame_jet_use_mp > mp) return;
	mp -= flame_jet_use_mp;

	bullet_16->set_animation_number(1);
	bullet_15->set_animation_number(2);
	bullet_14->set_animation_number(3);
	bullet_13->set_animation_number(4);
	bullet_12->set_animation_number(5);
	bullet_11->set_animation_number(6);
	bullet_10->set_animation_number(7);
	bullet_09->set_animation_number(8);
	bullet_08->set_animation_number(9);
	bullet_07->set_animation_number(10);
	bullet_06->set_animation_number(11);
	bullet_05->set_animation_number(12);
	bullet_04->set_animation_number(13);
	bullet_03->set_animation_number(14);
	bullet_02->set_animation_number(15);
	bullet_01->set_animation_number(16);

	bullet_16->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_15->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_14->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_13->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_12->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_11->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_10->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_09->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_08->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_07->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_06->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_05->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_04->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_03->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_02->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);
	bullet_01->set_pokemon_pos(pokemon_pos.x, pokemon_pos.y);

	bullet_16->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_15->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_14->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_13->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_12->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_11->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_10->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_09->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_08->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_07->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_06->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_05->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_04->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_03->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_02->set_pokemon_size(pokemon_size.x, pokemon_size.y);
	bullet_01->set_pokemon_size(pokemon_size.x, pokemon_size.y);

	bullet_16->set_ATK(bullet_16->get_ATK() * ATK);
	bullet_16->set_MATK(bullet_16->get_MATK() * MATK);
	bullet_15->set_ATK(bullet_15->get_ATK() * ATK);
	bullet_15->set_MATK(bullet_15->get_MATK() * MATK);
	bullet_14->set_ATK(bullet_14->get_ATK() * ATK);
	bullet_14->set_MATK(bullet_14->get_MATK() * MATK);
	bullet_13->set_ATK(bullet_13->get_ATK() * ATK);
	bullet_13->set_MATK(bullet_13->get_MATK() * MATK);
	bullet_12->set_ATK(bullet_12->get_ATK() * ATK);
	bullet_12->set_MATK(bullet_12->get_MATK() * MATK);
	bullet_11->set_ATK(bullet_11->get_ATK() * ATK);
	bullet_11->set_MATK(bullet_11->get_MATK() * MATK);
	bullet_10->set_ATK(bullet_10->get_ATK() * ATK);
	bullet_10->set_MATK(bullet_10->get_MATK() * MATK);
	bullet_09->set_ATK(bullet_09->get_ATK() * ATK);
	bullet_09->set_MATK(bullet_09->get_MATK() * MATK);
	bullet_08->set_ATK(bullet_08->get_ATK() * ATK);
	bullet_08->set_MATK(bullet_08->get_MATK() * MATK);
	bullet_07->set_ATK(bullet_07->get_ATK() * ATK);
	bullet_07->set_MATK(bullet_07->get_MATK() * MATK);
	bullet_06->set_ATK(bullet_06->get_ATK() * ATK);
	bullet_06->set_MATK(bullet_06->get_MATK() * MATK);
	bullet_05->set_ATK(bullet_05->get_ATK() * ATK);
	bullet_05->set_MATK(bullet_05->get_MATK() * MATK);
	bullet_04->set_ATK(bullet_04->get_ATK() * ATK);
	bullet_04->set_MATK(bullet_04->get_MATK() * MATK);
	bullet_03->set_ATK(bullet_03->get_ATK() * ATK);
	bullet_03->set_MATK(bullet_03->get_MATK() * MATK);
	bullet_02->set_ATK(bullet_02->get_ATK() * ATK);
	bullet_02->set_MATK(bullet_02->get_MATK() * MATK);
	bullet_01->set_ATK(bullet_01->get_ATK() * ATK);
	bullet_01->set_MATK(bullet_01->get_MATK() * MATK);

	bullet_16->set_bullet_is_facing_right(is_facing_right);
	bullet_15->set_bullet_is_facing_right(is_facing_right);
	bullet_14->set_bullet_is_facing_right(is_facing_right);
	bullet_13->set_bullet_is_facing_right(is_facing_right);
	bullet_12->set_bullet_is_facing_right(is_facing_right);
	bullet_11->set_bullet_is_facing_right(is_facing_right);
	bullet_10->set_bullet_is_facing_right(is_facing_right);
	bullet_09->set_bullet_is_facing_right(is_facing_right);
	bullet_08->set_bullet_is_facing_right(is_facing_right);
	bullet_07->set_bullet_is_facing_right(is_facing_right);
	bullet_06->set_bullet_is_facing_right(is_facing_right);
	bullet_05->set_bullet_is_facing_right(is_facing_right);
	bullet_04->set_bullet_is_facing_right(is_facing_right);
	bullet_03->set_bullet_is_facing_right(is_facing_right);
	bullet_02->set_bullet_is_facing_right(is_facing_right);
	bullet_01->set_bullet_is_facing_right(is_facing_right);

	const POINT& origin_bullet_size = bullet_16->get_bullet_size();
	const POINTF& origin_bullet_velocity = bullet_16->get_bullet_velocity();

	POINT current_bullet_16_position;
	POINT current_bullet_15_position;
	POINT current_bullet_14_position;
	POINT current_bullet_13_position;
	POINT current_bullet_12_position;
	POINT current_bullet_11_position;
	POINT current_bullet_10_position;
	POINT current_bullet_09_position;
	POINT current_bullet_08_position;
	POINT current_bullet_07_position;
	POINT current_bullet_06_position;
	POINT current_bullet_05_position;
	POINT current_bullet_04_position;
	POINT current_bullet_03_position;
	POINT current_bullet_02_position;
	POINT current_bullet_01_position;

	//current_bullet_16_position.x = is_facing_right ? pokemon_pos.x + pokemon_size.x - origin_bullet_size.x : pokemon_pos.x + origin_bullet_size.x;
	//current_bullet_16_position.y = pokemon_pos.y + pokemon_size.y / 2;
	//current_bullet_15_position.x = is_facing_right ? current_bullet_16_position.x - origin_bullet_size.x : current_bullet_16_position.x + origin_bullet_size.x;
	//current_bullet_15_position.y = current_bullet_16_position.y;
	//current_bullet_14_position.x = is_facing_right ? current_bullet_15_position.x - origin_bullet_size.x : current_bullet_15_position.x + origin_bullet_size.x;
	//current_bullet_14_position.y = current_bullet_15_position.y;
	//current_bullet_13_position.x = is_facing_right ? current_bullet_14_position.x - origin_bullet_size.x : current_bullet_14_position.x + origin_bullet_size.x;
	//current_bullet_13_position.y = current_bullet_14_position.y;
	//current_bullet_12_position.x = is_facing_right ? current_bullet_13_position.x - origin_bullet_size.x : current_bullet_13_position.x + origin_bullet_size.x;
	//current_bullet_12_position.y = current_bullet_13_position.y;
	//current_bullet_11_position.x = is_facing_right ? current_bullet_12_position.x - origin_bullet_size.x : current_bullet_12_position.x + origin_bullet_size.x;
	//current_bullet_11_position.y = current_bullet_12_position.y;
	//current_bullet_10_position.x = is_facing_right ? current_bullet_11_position.x - origin_bullet_size.x : current_bullet_11_position.x + origin_bullet_size.x;
	//current_bullet_10_position.y = current_bullet_11_position.y;
	//current_bullet_09_position.x = is_facing_right ? current_bullet_10_position.x - origin_bullet_size.x : current_bullet_10_position.x + origin_bullet_size.x;
	//current_bullet_09_position.y = current_bullet_10_position.y;
	//current_bullet_08_position.x = is_facing_right ? current_bullet_09_position.x - origin_bullet_size.x : current_bullet_09_position.x + origin_bullet_size.x;
	//current_bullet_08_position.y = current_bullet_09_position.y;
	//current_bullet_07_position.x = is_facing_right ? current_bullet_08_position.x - origin_bullet_size.x : current_bullet_08_position.x + origin_bullet_size.x;
	//current_bullet_07_position.y = current_bullet_08_position.y;
	//current_bullet_06_position.x = is_facing_right ? current_bullet_07_position.x - origin_bullet_size.x : current_bullet_07_position.x + origin_bullet_size.x;
	//current_bullet_06_position.y = current_bullet_07_position.y;
	//current_bullet_05_position.x = is_facing_right ? current_bullet_06_position.x - origin_bullet_size.x : current_bullet_06_position.x + origin_bullet_size.x;
	//current_bullet_05_position.y = current_bullet_06_position.y;
	//current_bullet_04_position.x = is_facing_right ? current_bullet_05_position.x - origin_bullet_size.x : current_bullet_05_position.x + origin_bullet_size.x;
	//current_bullet_04_position.y = current_bullet_05_position.y;
	//current_bullet_03_position.x = is_facing_right ? current_bullet_04_position.x - origin_bullet_size.x : current_bullet_04_position.x + origin_bullet_size.x;
	//current_bullet_03_position.y = current_bullet_04_position.y;
	//current_bullet_02_position.x = is_facing_right ? current_bullet_03_position.x - origin_bullet_size.x : current_bullet_03_position.x + origin_bullet_size.x;
	//current_bullet_02_position.y = current_bullet_03_position.y;
	//current_bullet_01_position.x = is_facing_right ? current_bullet_02_position.x - origin_bullet_size.x : current_bullet_02_position.x + origin_bullet_size.x;
	//current_bullet_01_position.y = current_bullet_02_position.y;

	current_bullet_16_position.x = is_facing_right ? pokemon_pos.x + pokemon_size.x - origin_bullet_size.x - 15 * bullet_16->get_bullet_size().x : pokemon_pos.x + origin_bullet_size.x;
	current_bullet_16_position.y = pokemon_pos.y + pokemon_size.y / 2;
	current_bullet_15_position.x = current_bullet_16_position.x + origin_bullet_size.x;
	current_bullet_15_position.y = current_bullet_16_position.y;
	current_bullet_14_position.x = current_bullet_15_position.x + origin_bullet_size.x;
	current_bullet_14_position.y = current_bullet_15_position.y;
	current_bullet_13_position.x = current_bullet_14_position.x + origin_bullet_size.x;
	current_bullet_13_position.y = current_bullet_14_position.y;
	current_bullet_12_position.x = current_bullet_13_position.x + origin_bullet_size.x;
	current_bullet_12_position.y = current_bullet_13_position.y;
	current_bullet_11_position.x = current_bullet_12_position.x + origin_bullet_size.x;
	current_bullet_11_position.y = current_bullet_12_position.y;
	current_bullet_10_position.x = current_bullet_11_position.x + origin_bullet_size.x;
	current_bullet_10_position.y = current_bullet_11_position.y;
	current_bullet_09_position.x = current_bullet_10_position.x + origin_bullet_size.x;
	current_bullet_09_position.y = current_bullet_10_position.y;
	current_bullet_08_position.x = current_bullet_09_position.x + origin_bullet_size.x;
	current_bullet_08_position.y = current_bullet_09_position.y;
	current_bullet_07_position.x = current_bullet_08_position.x + origin_bullet_size.x;
	current_bullet_07_position.y = current_bullet_08_position.y;
	current_bullet_06_position.x = current_bullet_07_position.x + origin_bullet_size.x;
	current_bullet_06_position.y = current_bullet_07_position.y;
	current_bullet_05_position.x = current_bullet_06_position.x + origin_bullet_size.x;
	current_bullet_05_position.y = current_bullet_06_position.y;
	current_bullet_04_position.x = current_bullet_05_position.x + origin_bullet_size.x;
	current_bullet_04_position.y = current_bullet_05_position.y;
	current_bullet_03_position.x = current_bullet_04_position.x + origin_bullet_size.x;
	current_bullet_03_position.y = current_bullet_04_position.y;
	current_bullet_02_position.x = current_bullet_03_position.x + origin_bullet_size.x;
	current_bullet_02_position.y = current_bullet_03_position.y;
	current_bullet_01_position.x = current_bullet_02_position.x + origin_bullet_size.x;
	current_bullet_01_position.y = current_bullet_02_position.y;

	POINTF current_bullet_velocity;
	current_bullet_velocity.x = is_facing_right ? origin_bullet_velocity.x : -origin_bullet_velocity.x;
	current_bullet_velocity.y = origin_bullet_velocity.y;

	bullet_16->set_bullet_pos(current_bullet_16_position.x, current_bullet_16_position.y);
	bullet_16->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_15->set_bullet_pos(current_bullet_15_position.x, current_bullet_15_position.y);
	bullet_15->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_14->set_bullet_pos(current_bullet_14_position.x, current_bullet_14_position.y);
	bullet_14->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_13->set_bullet_pos(current_bullet_13_position.x, current_bullet_13_position.y);
	bullet_13->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_12->set_bullet_pos(current_bullet_12_position.x, current_bullet_12_position.y);
	bullet_12->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_11->set_bullet_pos(current_bullet_11_position.x, current_bullet_11_position.y);
	bullet_11->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_10->set_bullet_pos(current_bullet_10_position.x, current_bullet_10_position.y);
	bullet_10->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_09->set_bullet_pos(current_bullet_09_position.x, current_bullet_09_position.y);
	bullet_09->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_08->set_bullet_pos(current_bullet_08_position.x, current_bullet_08_position.y);
	bullet_08->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_07->set_bullet_pos(current_bullet_07_position.x, current_bullet_07_position.y);
	bullet_07->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_06->set_bullet_pos(current_bullet_06_position.x, current_bullet_06_position.y);
	bullet_06->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_05->set_bullet_pos(current_bullet_05_position.x, current_bullet_05_position.y);
	bullet_05->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_04->set_bullet_pos(current_bullet_04_position.x, current_bullet_04_position.y);
	bullet_04->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_03->set_bullet_pos(current_bullet_03_position.x, current_bullet_03_position.y);
	bullet_03->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_02->set_bullet_pos(current_bullet_02_position.x, current_bullet_02_position.y);
	bullet_02->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);
	bullet_01->set_bullet_pos(current_bullet_01_position.x, current_bullet_01_position.y);
	bullet_01->set_bullet_velocity(current_bullet_velocity.x, current_bullet_velocity.y);

	bullet_16->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_15->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_14->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_13->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_12->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_11->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_10->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_09->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_08->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_07->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_06->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_05->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_04->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_03->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_02->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);
	bullet_01->set_target_player(player_id == PokemonPlayer::P1 ? PokemonPlayer::P2 : PokemonPlayer::P1);

	bullet_list.push_back(bullet_16);
	bullet_list.push_back(bullet_15);
	bullet_list.push_back(bullet_14);
	bullet_list.push_back(bullet_13);
	bullet_list.push_back(bullet_12);
	bullet_list.push_back(bullet_11);
	bullet_list.push_back(bullet_10);
	bullet_list.push_back(bullet_09);
	bullet_list.push_back(bullet_08);
	bullet_list.push_back(bullet_07);
	bullet_list.push_back(bullet_06);
	bullet_list.push_back(bullet_05);
	bullet_list.push_back(bullet_04);
	bullet_list.push_back(bullet_03);
	bullet_list.push_back(bullet_02);
	bullet_list.push_back(bullet_01);

	if (is_open_sound_effect) mciSendString(_T("play flame_jet_sound_effect from 0"), NULL, 0, NULL);
}