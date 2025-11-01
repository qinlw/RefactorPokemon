#pragma once

#include "scene.h"
#include "mysql_fun.h"
#include "timer.h"


extern Scene* menu_scene;

extern bool is_first_game;
extern bool is_attribute_restrain;
extern bool is_open_music;
extern bool is_open_sound_effect;

class SceneSet : public Scene {
public:
	void on_enter() {
		set_background_pos.x = getwidth();
		set_background_pos.y = 0;

		mciSendString(_T("play wooden_cabinet_sound_slide_out from 0"), NULL, 0, NULL);
	}

	void on_update(int delta) {
		// 更新滑动的位置
		// 背景的位置
		// 滑出
		if (is_exit_set) {
			set_background_pos.x += set_background_slide_speed * delta * 2;
			if (set_background_pos.x > getwidth()) {
				is_exit_set = false;
				scene_manager->switch_scene(SceneManager::SceneType::Menu);
			}
		}
		// 滑入
		else if (set_background_pos.x > getwidth() - img_set_background.getwidth()) {
			set_background_pos.x -= set_background_slide_speed * delta;
			if (set_background_pos.x < getwidth() - img_set_background.getwidth()) set_background_pos.x = getwidth() - img_set_background.getwidth();
		}

		// 返回按钮的位置
		set_return_to_menu_button_pos.x = set_background_pos.x - img_set_return_to_menu_button.getwidth();
		set_return_to_menu_button_pos.y = 0;

		// 背景音乐选择后背景色的位置
		// 下滑
		if (is_choosing_background_music) {
			background_music_underpainting_pos.y += set_content_slide_speed * delta * 2;
			if (background_music_underpainting_pos.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight()) {
				background_music_underpainting_pos.y = background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight();
			}
		}
		// 上滑
		else {
			background_music_underpainting_pos.y -= set_content_slide_speed * delta;
			if (background_music_underpainting_pos.y <= background_music_set_bar_background_clolr_pos.y +
				img_set_bar_background_color.getheight() - img_background_music_underpainting.getheight()) {
				background_music_underpainting_pos.y = background_music_set_bar_background_clolr_pos.y +
					img_set_bar_background_color.getheight() - img_background_music_underpainting.getheight();
			}
		}

		// 背景音乐选择后背景色的位置
		// 下滑
		if (is_choosing_game_music) {
			game_music_underpainting_pos.y += set_content_slide_speed * delta * 2;
			if (game_music_underpainting_pos.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight()) {
				game_music_underpainting_pos.y = game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight();
			}
		}
		// 上滑
		else {
			game_music_underpainting_pos.y -= set_content_slide_speed * delta;
			if (game_music_underpainting_pos.y <= game_music_set_bar_background_clolr_pos.y +
				img_set_bar_background_color.getheight() - img_game_music_underpainting.getheight()) {
				game_music_underpainting_pos.y = game_music_set_bar_background_clolr_pos.y +
					img_set_bar_background_color.getheight() - img_game_music_underpainting.getheight();
			}
		}


		// 非滑动或者不需要处理及已处理的位置
		const int first_bar_to_top_distance = 73;
		const int up_bar_to_down_bar_distance = 60;
		const int left_to_bar_distance = 33;
		const int option_hight = 40;

		// 设置新手教程的位置		
		is_first_game_set_bar_background_clolr_pos.x = set_background_pos.x + left_to_bar_distance;
		is_first_game_set_bar_background_clolr_pos.y = set_background_pos.y + first_bar_to_top_distance;
		novice_teaching_text_pos.x = is_first_game_set_bar_background_clolr_pos.x;
		novice_teaching_text_pos.y = is_first_game_set_bar_background_clolr_pos.y;
		is_first_game_open_or_close_white_background_pos.x = is_first_game_set_bar_background_clolr_pos.x +
			img_set_bar_background_color.getwidth() - img_open_or_close_white_background.getwidth();
		is_first_game_open_or_close_white_background_pos.y = is_first_game_set_bar_background_clolr_pos.y;
		is_first_game_close_text_pos.x = is_first_game_set_bar_background_clolr_pos.x + img_set_bar_background_color.getwidth() - img_close_text.getwidth();
		is_first_game_close_text_pos.y = is_first_game_set_bar_background_clolr_pos.y;
		is_first_game_open_text_pos.x = is_first_game_close_text_pos.x - img_close_text.getwidth();
		is_first_game_open_text_pos.y = is_first_game_set_bar_background_clolr_pos.y;
		if (is_first_game) is_first_game_is_open_or_is_close_pos.x = is_first_game_open_text_pos.x;
		else is_first_game_is_open_or_is_close_pos.x = is_first_game_close_text_pos.x;
		is_first_game_is_open_or_is_close_pos.y = is_first_game_set_bar_background_clolr_pos.y;

		// 设置属性克制的位置
		attribute_restrain_switch_set_bar_background_clolr_pos.x = is_first_game_set_bar_background_clolr_pos.x;
		attribute_restrain_switch_set_bar_background_clolr_pos.y = is_first_game_set_bar_background_clolr_pos.y + up_bar_to_down_bar_distance;
		attribute_restrain_text_pos.x = attribute_restrain_switch_set_bar_background_clolr_pos.x;
		attribute_restrain_text_pos.y = attribute_restrain_switch_set_bar_background_clolr_pos.y;
		attribute_restrain_switch_close_text_pos.x = attribute_restrain_switch_set_bar_background_clolr_pos.x +
			img_set_bar_background_color.getwidth() - img_close_text.getwidth();
		attribute_restrain_switch_close_text_pos.y = attribute_restrain_switch_set_bar_background_clolr_pos.y;
		attribute_restrain_switch_open_text_pos.x = attribute_restrain_switch_close_text_pos.x - img_open_text.getwidth();
		attribute_restrain_switch_open_text_pos.y = attribute_restrain_switch_set_bar_background_clolr_pos.y;
		if (is_attribute_restrain) attribute_restrain_switch_is_open_or_is_close_pos.x = attribute_restrain_switch_open_text_pos.x;
		else attribute_restrain_switch_is_open_or_is_close_pos.x = attribute_restrain_switch_close_text_pos.x;
		attribute_restrain_switch_is_open_or_is_close_pos.y = attribute_restrain_switch_set_bar_background_clolr_pos.y;

		// 设置背景音乐的位置
		background_music_set_bar_background_clolr_pos.x = attribute_restrain_switch_set_bar_background_clolr_pos.x;
		background_music_set_bar_background_clolr_pos.y = attribute_restrain_switch_set_bar_background_clolr_pos.y + up_bar_to_down_bar_distance;
		background_music_text_pos.x = background_music_set_bar_background_clolr_pos.x;
		background_music_text_pos.y = background_music_set_bar_background_clolr_pos.y;
		background_music_choice_pos.x = background_music_set_bar_background_clolr_pos.x + img_set_bar_background_color.getwidth() - img_choice.getwidth();;
		background_music_choice_pos.y = background_music_set_bar_background_clolr_pos.y;
		background_music_current_set_music_pos.x = background_music_choice_pos.x - img_choice_background_color.getwidth();
		background_music_current_set_music_pos.y = background_music_choice_pos.y;
		background_music_underpainting_pos.x = background_music_current_set_music_pos.x;
		if (!is_updated_underpainting_pos) {
			background_music_underpainting_pos.y = background_music_current_set_music_pos.y - img_background_music_underpainting.getheight();
			is_updated_underpainting_pos = true;
		}
		background_music_rand_music_pos.x = background_music_underpainting_pos.x;
		background_music_rand_music_pos.y = background_music_underpainting_pos.y;
		background_music_1.x = background_music_rand_music_pos.x;
		background_music_1.y = background_music_rand_music_pos.y + option_hight;
		background_music_2.x = background_music_1.x;
		background_music_2.y = background_music_1.y + option_hight;
		background_music_3.x = background_music_2.x;
		background_music_3.y = background_music_2.y + option_hight;
		background_music_choice_background_color_pos.x = background_music_1.x;
		switch (background_music_id) {
		case 1:
			background_music_choice_background_color_pos.y = background_music_1.y;
			break;
		case 2:
			background_music_choice_background_color_pos.y = background_music_2.y;
			break;
		case 3:
			background_music_choice_background_color_pos.y = background_music_3.y;
			break;
		}

		// 设置战斗音乐的位置
		game_music_set_bar_background_clolr_pos.x = background_music_set_bar_background_clolr_pos.x;
		game_music_set_bar_background_clolr_pos.y = background_music_set_bar_background_clolr_pos.y + up_bar_to_down_bar_distance;
		game_music_text_pos.x = game_music_set_bar_background_clolr_pos.x;
		game_music_text_pos.y = game_music_set_bar_background_clolr_pos.y;
		game_music_choice_pos.x = game_music_set_bar_background_clolr_pos.x + img_set_bar_background_color.getwidth() - img_choice.getwidth();;
		game_music_choice_pos.y = game_music_set_bar_background_clolr_pos.y;
		game_music_current_set_music_pos.x = game_music_choice_pos.x - img_choice_background_color.getwidth();
		game_music_current_set_music_pos.y = game_music_choice_pos.y;
		game_music_underpainting_pos.x = game_music_current_set_music_pos.x;
		if (!is_updated_underpainting_pos) {
			game_music_underpainting_pos.y = game_music_current_set_music_pos.y - img_game_music_underpainting.getheight();
			is_updated_underpainting_pos = true;
		}
		game_music_rand_music_pos.x = game_music_underpainting_pos.x;
		game_music_rand_music_pos.y = game_music_underpainting_pos.y;
		game_music_1.x = game_music_rand_music_pos.x;
		game_music_1.y = game_music_rand_music_pos.y + option_hight;
		game_music_2.x = game_music_1.x;
		game_music_2.y = game_music_1.y + option_hight;
		game_music_3.x = game_music_2.x;
		game_music_3.y = game_music_2.y + option_hight;
		game_music_4.x = game_music_3.x;
		game_music_4.y = game_music_3.y + option_hight;
		game_music_5.x = game_music_4.x;
		game_music_5.y = game_music_4.y + option_hight;
		game_music_choice_background_color_pos.x = game_music_1.x;
		switch (game_music_id) {
		case 1:
			game_music_choice_background_color_pos.y = game_music_1.y;
			break;
		case 2:
			game_music_choice_background_color_pos.y = game_music_2.y;
			break;
		case 3:
			game_music_choice_background_color_pos.y = game_music_3.y;
			break;
		case 4:
			game_music_choice_background_color_pos.y = game_music_4.y;
			break;
		case 5:
			game_music_choice_background_color_pos.y = game_music_5.y;
			break;
		}


		// 设置音乐的位置
		is_open_music_set_bar_background_clolr_pos.x = game_music_set_bar_background_clolr_pos.x;
		is_open_music_set_bar_background_clolr_pos.y = game_music_set_bar_background_clolr_pos.y + up_bar_to_down_bar_distance;
		is_open_music_text_pos.x = is_open_music_set_bar_background_clolr_pos.x;
		is_open_music_text_pos.y = is_open_music_set_bar_background_clolr_pos.y;
		is_open_music_close_text_pos.x = is_open_music_set_bar_background_clolr_pos.x +
			img_set_bar_background_color.getwidth() - img_close_text.getwidth();
		is_open_music_close_text_pos.y = is_open_music_set_bar_background_clolr_pos.y;
		is_open_music_open_text_pos.x = is_open_music_close_text_pos.x - img_open_text.getwidth();
		is_open_music_open_text_pos.y = is_open_music_set_bar_background_clolr_pos.y;
		if (is_open_music) is_open_music_is_open_or_is_close_pos.x = is_open_music_open_text_pos.x;
		else is_open_music_is_open_or_is_close_pos.x = is_open_music_close_text_pos.x;
		is_open_music_is_open_or_is_close_pos.y = is_open_music_set_bar_background_clolr_pos.y;

		// 设置音效的位置
		is_open_sound_effect_set_bar_background_clolr_pos.x = is_open_music_set_bar_background_clolr_pos.x;
		is_open_sound_effect_set_bar_background_clolr_pos.y = is_open_music_set_bar_background_clolr_pos.y + up_bar_to_down_bar_distance;
		is_open_sound_effect_text_pos.x = is_open_sound_effect_set_bar_background_clolr_pos.x;
		is_open_sound_effect_text_pos.y = is_open_sound_effect_set_bar_background_clolr_pos.y;
		is_open_sound_effect_close_text_pos.x = is_open_sound_effect_set_bar_background_clolr_pos.x +
			img_set_bar_background_color.getwidth() - img_close_text.getwidth();
		is_open_sound_effect_close_text_pos.y = is_open_sound_effect_set_bar_background_clolr_pos.y;
		is_open_sound_effect_open_text_pos.x = is_open_sound_effect_close_text_pos.x - img_open_text.getwidth();
		is_open_sound_effect_open_text_pos.y = is_open_sound_effect_set_bar_background_clolr_pos.y;
		if (is_open_sound_effect) is_open_sound_effect_is_open_or_is_close_pos.x = is_open_sound_effect_open_text_pos.x;
		else is_open_sound_effect_is_open_or_is_close_pos.x = is_open_sound_effect_close_text_pos.x;
		is_open_sound_effect_is_open_or_is_close_pos.y = is_open_sound_effect_set_bar_background_clolr_pos.y;
	}

	void on_draw() {
		menu_scene->on_draw();
		putimage_alpha(set_background_pos.x, set_background_pos.y, &img_set_background);
		putimage_alpha(set_return_to_menu_button_pos.x, set_return_to_menu_button_pos.y, &img_set_return_to_menu_button);

		// 设置新手教程
		putimage_alpha(is_first_game_set_bar_background_clolr_pos.x, is_first_game_set_bar_background_clolr_pos.y, &img_set_bar_background_color);
		putimage_alpha(novice_teaching_text_pos.x, novice_teaching_text_pos.y, &img_novice_teaching_text);
		putimage_alpha(is_first_game_open_or_close_white_background_pos.x, is_first_game_open_or_close_white_background_pos.y, &img_open_or_close_white_background);
		putimage_alpha(is_first_game_is_open_or_is_close_pos.x, is_first_game_is_open_or_is_close_pos.y, &img_is_open_or_is_close);
		putimage_alpha(is_first_game_close_text_pos.x, is_first_game_close_text_pos.y, &img_close_text);
		putimage_alpha(is_first_game_open_text_pos.x, is_first_game_open_text_pos.y, &img_open_text);
		// 设置属性克制
		putimage_alpha(attribute_restrain_switch_set_bar_background_clolr_pos.x, attribute_restrain_switch_set_bar_background_clolr_pos.y, &img_set_bar_background_color);
		putimage_alpha(attribute_restrain_text_pos.x, attribute_restrain_text_pos.y, &img_attribute_restrain_switch);
		putimage_alpha(attribute_restrain_switch_is_open_or_is_close_pos.x, attribute_restrain_switch_is_open_or_is_close_pos.y, &img_is_open_or_is_close);
		putimage_alpha(attribute_restrain_switch_close_text_pos.x, attribute_restrain_switch_close_text_pos.y, &img_close_text);
		putimage_alpha(attribute_restrain_switch_open_text_pos.x, attribute_restrain_switch_open_text_pos.y, &img_open_text);
		// 设置背景音乐
		putimage_alpha(background_music_set_bar_background_clolr_pos.x, background_music_set_bar_background_clolr_pos.y, &img_set_bar_background_color);
		putimage_alpha(background_music_text_pos.x, background_music_text_pos.y, &img_background_music_text);
		putimage_alpha(background_music_choice_pos.x, background_music_choice_pos.y, &img_choice);
		putimage_alpha(background_music_current_set_music_pos.x, background_music_current_set_music_pos.y, &img_choice_background_color);
		switch (background_music_id) {
		case 0:
			putimage_alpha(background_music_current_set_music_pos.x, background_music_current_set_music_pos.y, &img_rand_music);
			break;
		case 1:
			putimage_alpha(background_music_current_set_music_pos.x, background_music_current_set_music_pos.y, &img_music_1);
			break;
		case 2:
			putimage_alpha(background_music_current_set_music_pos.x, background_music_current_set_music_pos.y, &img_music_2);
			break;
		case 3:
			putimage_alpha(background_music_current_set_music_pos.x, background_music_current_set_music_pos.y, &img_music_3);
			break;
		}
		// 设置战斗音乐
		putimage_alpha(game_music_set_bar_background_clolr_pos.x, game_music_set_bar_background_clolr_pos.y, &img_set_bar_background_color);
		putimage_alpha(game_music_text_pos.x, game_music_text_pos.y, &img_game_music_text);
		putimage_alpha(game_music_choice_pos.x, game_music_choice_pos.y, &img_choice);
		putimage_alpha(game_music_current_set_music_pos.x, game_music_current_set_music_pos.y, &img_choice_background_color);
		switch (game_music_id) {
		case 0:
			putimage_alpha(game_music_current_set_music_pos.x, game_music_current_set_music_pos.y, &img_rand_music);
			break;
		case 1:
			putimage_alpha(game_music_current_set_music_pos.x, game_music_current_set_music_pos.y, &img_music_1);
			break;
		case 2:
			putimage_alpha(game_music_current_set_music_pos.x, game_music_current_set_music_pos.y, &img_music_2);
			break;
		case 3:
			putimage_alpha(game_music_current_set_music_pos.x, game_music_current_set_music_pos.y, &img_music_3);
			break;
		case 4:
			putimage_alpha(game_music_current_set_music_pos.x, game_music_current_set_music_pos.y, &img_music_4);
			break;
		case 5:
			putimage_alpha(game_music_current_set_music_pos.x, game_music_current_set_music_pos.y, &img_music_5);
			break;
		}
		// 设置音乐
		putimage_alpha(is_open_music_set_bar_background_clolr_pos.x, is_open_music_set_bar_background_clolr_pos.y, &img_set_bar_background_color);
		putimage_alpha(is_open_music_text_pos.x, is_open_music_text_pos.y, &img_is_open_music_text);
		putimage_alpha(is_open_music_is_open_or_is_close_pos.x, is_open_music_is_open_or_is_close_pos.y, &img_is_open_or_is_close);
		putimage_alpha(is_open_music_close_text_pos.x, is_open_music_close_text_pos.y, &img_close_text);
		putimage_alpha(is_open_music_open_text_pos.x, is_open_music_open_text_pos.y, &img_open_text);
		// 设置音乐
		putimage_alpha(is_open_sound_effect_set_bar_background_clolr_pos.x, is_open_sound_effect_set_bar_background_clolr_pos.y, &img_set_bar_background_color);
		putimage_alpha(is_open_sound_effect_text_pos.x, is_open_sound_effect_text_pos.y, &img_is_open_sound_effect_text);
		putimage_alpha(is_open_sound_effect_is_open_or_is_close_pos.x, is_open_sound_effect_is_open_or_is_close_pos.y, &img_is_open_or_is_close);
		putimage_alpha(is_open_sound_effect_close_text_pos.x, is_open_sound_effect_close_text_pos.y, &img_close_text);
		putimage_alpha(is_open_sound_effect_open_text_pos.x, is_open_sound_effect_open_text_pos.y, &img_open_text);

		// 设置背景音乐中需要置顶的画面
		if (background_music_underpainting_pos.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(background_music_underpainting_pos.x, background_music_underpainting_pos.y, &img_background_music_underpainting);
		if (background_music_rand_music_pos.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(background_music_rand_music_pos.x, background_music_rand_music_pos.y, &img_underpainting_block);
		if (background_music_1.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(background_music_1.x, background_music_1.y, &img_underpainting_block);
		if (background_music_2.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(background_music_2.x, background_music_2.y, &img_underpainting_block);
		if (background_music_3.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(background_music_3.x, background_music_3.y, &img_underpainting_block);
		switch (background_music_id) {
		case 0:
			if (background_music_rand_music_pos.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(background_music_rand_music_pos.x, background_music_rand_music_pos.y, &img_choice_background_color);
			break;
		case 1:
			if (background_music_1.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(background_music_1.x, background_music_1.y, &img_choice_background_color);
			break;
		case 2:
			if (background_music_2.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(background_music_2.x, background_music_2.y, &img_choice_background_color);
			break;
		case 3:
			if (background_music_3.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(background_music_3.x, background_music_3.y, &img_choice_background_color);
			break;
		}
		if (background_music_rand_music_pos.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(background_music_rand_music_pos.x, background_music_rand_music_pos.y, &img_rand_music);
		if (background_music_1.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(background_music_1.x, background_music_1.y, &img_music_1);
		if (background_music_2.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(background_music_2.x, background_music_2.y, &img_music_2);
		if (background_music_3.y >= background_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(background_music_3.x, background_music_3.y, &img_music_3);

		// 设置战斗音乐中需要置顶的画面
		if (game_music_underpainting_pos.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_underpainting_pos.x, game_music_underpainting_pos.y, &img_game_music_underpainting);
		if (game_music_rand_music_pos.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_rand_music_pos.x, game_music_rand_music_pos.y, &img_underpainting_block);
		if (game_music_1.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_1.x, game_music_1.y, &img_underpainting_block);
		if (game_music_2.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_2.x, game_music_2.y, &img_underpainting_block);
		if (game_music_3.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_3.x, game_music_3.y, &img_underpainting_block);
		if (game_music_4.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_4.x, game_music_4.y, &img_underpainting_block);
		if (game_music_5.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_5.x, game_music_5.y, &img_underpainting_block);
		switch (game_music_id) {
		case 0:
			if (game_music_rand_music_pos.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(game_music_rand_music_pos.x, game_music_rand_music_pos.y, &img_choice_background_color);
			break;
		case 1:
			if (game_music_1.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(game_music_1.x, game_music_1.y, &img_choice_background_color);
			break;
		case 2:
			if (game_music_2.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(game_music_2.x, game_music_2.y, &img_choice_background_color);
			break;
		case 3:
			if (game_music_3.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(game_music_3.x, game_music_3.y, &img_choice_background_color);
			break;
		case 4:
			if (game_music_4.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(game_music_4.x, game_music_4.y, &img_choice_background_color);
			break;
		case 5:
			if (game_music_5.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
				putimage_alpha(game_music_5.x, game_music_5.y, &img_choice_background_color);
			break;
		}
		if (game_music_rand_music_pos.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_rand_music_pos.x, game_music_rand_music_pos.y, &img_rand_music);
		if (game_music_1.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_1.x, game_music_1.y, &img_music_1);
		if (game_music_2.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_2.x, game_music_2.y, &img_music_2);
		if (game_music_3.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_3.x, game_music_3.y, &img_music_3);
		if (game_music_4.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_4.x, game_music_4.y, &img_music_4);
		if (game_music_5.y >= game_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight())
			putimage_alpha(game_music_5.x, game_music_5.y, &img_music_5);
	}

	void on_input(const ExMessage& msg) {
		switch (msg.message) {
		case WM_LBUTTONUP:
			// 退出判断
			if (msg.x < set_background_pos.x) {
				is_exit_set = true;
				mciSendString(_T("play wooden_cabinet_sound_slide_in from 0"), NULL, 0, NULL);
				is_choosing_background_music = false;
				is_choosing_game_music = false;
				is_updated_underpainting_pos = false;
				break;
			}

			// 设置背景音乐的设置判断
			if (msg.x < background_music_choice_pos.x + img_choice.getwidth() && msg.x > background_music_current_set_music_pos.x &&
				msg.y < background_music_choice_pos.y + img_choice.getheight() && msg.y > background_music_choice_pos.y && 
				!is_choosing_game_music) {
				is_choosing_background_music = !is_choosing_background_music;
				if (is_open_sound_effect) mciSendString(_T("play tear_paper from 50"), NULL, 0, NULL);
				break;
			}

			// 设置战斗音乐的设置判断
			if (msg.x < game_music_choice_pos.x + img_choice.getwidth() && msg.x > game_music_current_set_music_pos.x &&
				msg.y < game_music_choice_pos.y + img_choice.getheight() && msg.y > game_music_choice_pos.y && !is_choosing_background_music) {
				is_choosing_game_music = !is_choosing_game_music;
				if (is_open_sound_effect) mciSendString(_T("play tear_paper from 50"), NULL, 0, NULL);
				break;
			}

			// 背景音乐的选择
			if (is_choosing_background_music) {
				if (msg.x < background_music_underpainting_pos.x + img_background_music_underpainting.getwidth()
					&& msg.x > background_music_underpainting_pos.x && msg.y < background_music_underpainting_pos.y +
					img_background_music_underpainting.getheight() && msg.y > background_music_underpainting_pos.y) {
					// 随机音乐
					if (msg.y < background_music_rand_music_pos.y + img_rand_music.getheight() && msg.y > background_music_rand_music_pos.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_background_music_id(0);
						if (is_open_music) play_background_music();
						is_choosing_background_music = false;
					}
					// 音乐1
					else if (msg.y < background_music_1.y + img_music_1.getheight() && msg.y > background_music_1.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_background_music_id(1);
						if (is_open_music) play_background_music();
						is_choosing_background_music = false;
					}
					// 音乐2
					else if (msg.y < background_music_2.y + img_music_2.getheight() && msg.y > background_music_2.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_background_music_id(2);
						if (is_open_music) play_background_music();
						is_choosing_background_music = false;
					}
					// 音乐3
					else if (msg.y < background_music_3.y + img_music_3.getheight() && msg.y > background_music_3.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_background_music_id(3);
						if (is_open_music) play_background_music();
						is_choosing_background_music = false;
					}
					return;
				}
				else {
					is_choosing_background_music = false;
					return;
				}
			}

			// 战斗音乐的选择
			if (is_choosing_game_music) {
				if (is_choosing_game_music && msg.x < game_music_underpainting_pos.x + img_game_music_underpainting.getwidth()
					&& msg.x > game_music_underpainting_pos.x && msg.y < game_music_underpainting_pos.y +
					img_game_music_underpainting.getheight() && msg.y > game_music_underpainting_pos.y) {
					// 随机音乐
					if (msg.y < game_music_rand_music_pos.y + img_rand_music.getheight() && msg.y > game_music_rand_music_pos.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_game_music_id(0);
						is_choosing_game_music = false;
					}
					// 音乐1
					else if (msg.y < game_music_1.y + img_music_1.getheight() && msg.y > game_music_1.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_game_music_id(1);
						is_choosing_game_music = false;
					}
					// 音乐2
					else if (msg.y < game_music_2.y + img_music_2.getheight() && msg.y > game_music_2.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_game_music_id(2);
						is_choosing_game_music = false;
					}
					// 音乐3
					else if (msg.y < game_music_3.y + img_music_3.getheight() && msg.y > game_music_3.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_game_music_id(3);
						is_choosing_game_music = false;
					}
					// 音乐4
					else if (msg.y < game_music_4.y + img_music_4.getheight() && msg.y > game_music_4.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_game_music_id(4);
						is_choosing_game_music = false;
					}
					// 音乐5
					else if (msg.y < game_music_5.y + img_music_5.getheight() && msg.y > game_music_5.y) {
						if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
						set_game_music_id(5);
						is_choosing_game_music = false;
					}
					return;
				}
				else {
					is_choosing_game_music = false;
					return;
				}
			}
		}

		if (is_choosing_background_music || is_choosing_game_music) return;

		switch (msg.message) {
		case WM_LBUTTONUP:
			// 退出判断
			if (msg.x < set_background_pos.x) {
				is_exit_set = true;
				mciSendString(_T("play wooden_cabinet_sound_slide_in from 0"), NULL, 0, NULL);
				break;
			}

			// 设置新手教程的设置判断
			if (msg.y < is_first_game_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight() && msg.y > is_first_game_set_bar_background_clolr_pos.y) {
				// 打开
				if (msg.x < is_first_game_open_text_pos.x + img_open_text.getwidth() && msg.x > is_first_game_open_text_pos.x) {
					set_is_first_game(true);
					if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
				}
				// 关闭
				else if (msg.x < is_first_game_close_text_pos.x + img_close_text.getwidth() && msg.x > is_first_game_close_text_pos.x) {
					set_is_first_game(false);
					if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
				}
				break;
			}

			// 设置属性克制的设置判断
			if (msg.y < attribute_restrain_switch_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight() && msg.y > attribute_restrain_switch_set_bar_background_clolr_pos.y) {
				// 打开
				if (msg.x < attribute_restrain_switch_open_text_pos.x + img_open_text.getwidth() && msg.x > attribute_restrain_switch_open_text_pos.x) {
					is_attribute_restrain = true;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
				}
				// 关闭
				else if (msg.x < attribute_restrain_switch_close_text_pos.x + img_close_text.getwidth() && msg.x > attribute_restrain_switch_close_text_pos.x) {
					is_attribute_restrain = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
				}
				break;
			}

			// 设置音乐开关的设置判断
			if (msg.y < is_open_music_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight() && msg.y > is_open_music_set_bar_background_clolr_pos.y) {
				// 打开
				if (msg.x < is_open_music_open_text_pos.x + img_open_text.getwidth() && msg.x > is_open_music_open_text_pos.x) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
					if (is_open_music) break;
					set_is_open_music(true);
					is_open_music = true;			
					play_background_music();
				}
				// 关闭
				else if (msg.x < is_open_music_close_text_pos.x + img_close_text.getwidth() && msg.x > is_open_music_close_text_pos.x) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
					is_open_music = false;
					set_is_open_music(false);
					stop_background_music();
				}
				break;
			}

			// 设置音效开关的设置判断
			if (msg.y < is_open_sound_effect_set_bar_background_clolr_pos.y + img_set_bar_background_color.getheight() && msg.y > is_open_sound_effect_set_bar_background_clolr_pos.y) {
				// 打开
				if (msg.x < is_open_sound_effect_open_text_pos.x + img_open_text.getwidth() && msg.x > is_open_sound_effect_open_text_pos.x) {
					mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
					is_open_sound_effect = true;
					set_is_open_sound_effect(true);
				}
				// 关闭
				else if (msg.x < is_open_sound_effect_close_text_pos.x + img_close_text.getwidth() && msg.x > is_open_sound_effect_close_text_pos.x) {
					if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 50"), NULL, 0, NULL);
					set_is_open_sound_effect(false);
					is_open_sound_effect = false;
				}
				break;
			}
		}
	}

	void on_exit() {

	}

private:
	const float set_background_slide_speed = 0.8f;									// 设置背景滑动速度
	const float set_content_slide_speed = 0.7f;										// 设置内容滑动速度

private:
	POINT set_background_pos = { 0 };												// 设置背景的位置
	POINT set_return_to_menu_button_pos = { 0 };									// 返回按钮的位置
	// 设置新手教程的位置
	POINT is_first_game_set_bar_background_clolr_pos = { 0 };						// 设置条背景色的位置
	POINT novice_teaching_text_pos = { 0 };											// 新手教程文本的位置
	POINT is_first_game_open_or_close_white_background_pos = { 0 };					// 白色背景位置的位置
	POINT is_first_game_close_text_pos = { 0 };										// 关闭文本的位置
	POINT is_first_game_open_text_pos = { 0 };										// 打开文本的位置
	POINT is_first_game_is_open_or_is_close_pos = { 0 };							// 是打开 or 是关闭  的位置
	// 设置属性克制的位置
	POINT attribute_restrain_switch_set_bar_background_clolr_pos = { 0 };			// 设置条背景色的位置
	POINT attribute_restrain_text_pos = { 0 };										// 属性克制文本的位置
	POINT attribute_restrain_switch_close_text_pos = { 0 };							// 关闭文本的位置
	POINT attribute_restrain_switch_open_text_pos = { 0 };							// 打开文本的位置
	POINT attribute_restrain_switch_is_open_or_is_close_pos = { 0 };				// 是打开 or 是关闭  的位置
	// 设置背景音乐的位置
	POINT background_music_set_bar_background_clolr_pos = { 0 };					// 设置条背景色的位置
	POINT background_music_text_pos = { 0 };										// 背景音乐文本的位置
	POINT background_music_choice_pos = { 0 };										// 背景音乐选择器的位置
	POINT background_music_current_set_music_pos = { 0 };							// 当前设置的音乐的位置
	POINT background_music_underpainting_pos = { 0 };								// 背景色的位置
	POINT background_music_choice_background_color_pos = { 0 };						// 选择的音乐的颜色
	POINT background_music_rand_music_pos = { 0 };									// 随机音乐的位置
	POINT background_music_1 = { 0 };												// 音乐1的位置
	POINT background_music_2 = { 0 };												// 音乐2的位置
	POINT background_music_3 = { 0 };												// 音乐3的位置
	// 设置战斗音乐的位置
	POINT game_music_set_bar_background_clolr_pos = { 0 };							// 设置条背景色的位置
	POINT game_music_text_pos = { 0 };												// 战斗音乐文本的位置
	POINT game_music_choice_pos = { 0 };											// 战斗音乐选择器的位置
	POINT game_music_current_set_music_pos = { 0 };									// 当前设置的音乐的位置
	POINT game_music_underpainting_pos = { 0 };										// 背景色的位置
	POINT game_music_choice_background_color_pos = { 0 };							// 选择的音乐的颜色
	POINT game_music_rand_music_pos = { 0 };										// 随机音乐的位置
	POINT game_music_1 = { 0 };														// 音乐1的位置
	POINT game_music_2 = { 0 };														// 音乐2的位置
	POINT game_music_3 = { 0 };														// 音乐3的位置
	POINT game_music_4 = { 0 };														// 音乐4的位置
	POINT game_music_5 = { 0 };														// 音乐5的位置
	// 设置音乐的位置			
	POINT is_open_music_set_bar_background_clolr_pos = { 0 };						// 设置条背景色的位置
	POINT is_open_music_text_pos = { 0 };											// 音乐文本的位置
	POINT is_open_music_close_text_pos = { 0 };										// 关闭文本的位置
	POINT is_open_music_open_text_pos = { 0 };										// 打开文本的位置
	POINT is_open_music_is_open_or_is_close_pos = { 0 };							// 是打开 or 是关闭  的位置
	// 设置音效的位置			
	POINT is_open_sound_effect_set_bar_background_clolr_pos = { 0 };				// 设置条背景色的位置
	POINT is_open_sound_effect_text_pos = { 0 };									// 音乐文本的位置
	POINT is_open_sound_effect_close_text_pos = { 0 };								// 关闭文本的位置
	POINT is_open_sound_effect_open_text_pos = { 0 };								// 打开文本的位置
	POINT is_open_sound_effect_is_open_or_is_close_pos = { 0 };						// 是打开 or 是关闭  的位置

	bool is_exit_set = false;														// 是否退出设置
	bool is_choosing_background_music = false;										// 是否正在选择背景音乐
	bool is_choosing_game_music = false;											// 是否正在选择战斗音乐
	bool is_updated_underpainting_pos = false;										// 是否更新过背景色的位置
};