#pragma once

#include "scene.h"
#include "picture.h"


extern SceneManager* scene_manager;

extern bool is_open_sound_effect;

class SceneLoginRegistration : public Scene {
public:
	void on_enter() {
		account = get_remembered_accounts_accounts();
		password = get_remembered_accounts_password();

		is_open_eye = check_update_is_open_eye();
		is_remember_password = check_update_is_remember_password();

		timer_input_position_hint_blink.set_wait_time(500);
		timer_input_position_hint_blink.set_callback([&]() {
			is_display_input_position_hint = !is_display_input_position_hint;
			});
		timer_display_account_or_password_error_text.set_wait_time(2000);
		timer_display_account_or_password_error_text.set_callback([&]() {
			is_display_account_or_password_error_text = false;
			timer_display_account_or_password_error_text.reset();
			});
		timer_registration_sucess_or_falied_text.set_wait_time(2000);
		timer_registration_sucess_or_falied_text.set_callback([&]() {
			is_display_registration_sucess_or_failed = false;
			timer_registration_sucess_or_falied_text.reset();
			});

		animation_mysql_unconnected_text.set_atlas(&atlas_mysql_unconnected);
		animation_mysql_unconnected_text.set_interval(200);
		animation_mysql_unconnected_text.set_is_loop(false);

		if (current_is_input_account) account_insert_id = account.size();
		if (current_is_input_password) password_insert_id = password.size();

		// 登录注册场景中背景界面等位置
		const int login_or_registration_text_to_login_registration_interface_distance_x = 100;
		const int login_or_registration_text_to_login_registration_interface_distance_y = 70;
		const int account_text_to_login_registration_interface_distance_x = 50;
		const int account_text_to_login_registration_interface_distance_y = 121;
		const int password_text_to_account_text_distance = 22;
		const int box_to_box_distance = 23;
		const int eye_to_input_box_distance = 10;
		login_registration_interface_pos.x = (img_login_registration_background.getwidth() - img_login_registration_interface.getwidth()) / 2;
		login_registration_interface_pos.y = (img_login_registration_background.getheight() - img_login_registration_interface.getheight()) / 2;
		registration_text_pos.x = login_registration_interface_pos.x + img_login_registration_interface.getwidth() - login_or_registration_text_to_login_registration_interface_distance_x;
		registration_text_pos.y = login_registration_interface_pos.y + img_login_registration_interface.getheight() - login_or_registration_text_to_login_registration_interface_distance_y;
		login_registration_account_text_pos.x = login_registration_interface_pos.x + account_text_to_login_registration_interface_distance_x;
		login_registration_account_text_pos.y = login_registration_interface_pos.y + account_text_to_login_registration_interface_distance_y;
		login_registration_password_text_pos.x = login_registration_account_text_pos.x;
		login_registration_password_text_pos.y = login_registration_account_text_pos.y + img_login_registration_account_text.getheight() + password_text_to_account_text_distance;
		account_input_box_pos.x = login_registration_account_text_pos.x + img_login_registration_account_text.getwidth() + box_to_box_distance;
		account_input_box_pos.y = login_registration_account_text_pos.y;
		password_input_box_pos.x = account_input_box_pos.x;
		password_input_box_pos.y = login_registration_password_text_pos.y;
		login_or_registration_button_pos.x = login_registration_password_text_pos.x;
		login_or_registration_button_pos.y = login_registration_password_text_pos.y + img_login_registration_password_text.getheight() + box_to_box_distance;
		eye_pos.x = password_input_box_pos.x + img_login_registration_input_box.getwidth() - img_eye.getwidth() - eye_to_input_box_distance;
		eye_pos.y = password_input_box_pos.y + (img_login_registration_input_box.getheight() - img_eye.getheight()) / 2;

		// 文本提示的位置
		account_or_password_error_text_pos.x = login_registration_interface_pos.x + (img_login_registration_interface.getwidth() - img_account_or_password_error_text.getwidth()) / 2;
		account_or_password_error_text_pos.y = login_registration_interface_pos.y + account_text_to_login_registration_interface_distance_x;
		account_and_password_length_hint_text_pos.x = login_or_registration_button_pos.x + img_login_down_button.getwidth() - img_account_and_password_length_hint_text.getwidth();
		account_and_password_length_hint_text_pos.y = login_or_registration_button_pos.y - img_account_and_password_length_hint_text.getheight();
		is_remember_password_pos.x = login_or_registration_button_pos.x + img_login_down_button.getwidth() - img_remember_password.getwidth();
		is_remember_password_pos.y = login_or_registration_button_pos.y + img_login_down_button.getheight() + 
			password_input_box_pos.y - account_input_box_pos.y - img_login_registration_input_box.getheight() - img_remember_password.getheight();
		registration_sucess_text_pos.x = login_registration_interface_pos.x + (img_login_registration_interface.getwidth() - img_registration_sucess_text.getwidth()) / 2;
		registration_sucess_text_pos.y = login_registration_interface_pos.y + account_text_to_login_registration_interface_distance_x;
		registered_text_pos.x = login_registration_interface_pos.x + (img_login_registration_interface.getwidth() - img_registered_text.getwidth()) / 2;
		registered_text_pos.y = login_registration_interface_pos.y + account_text_to_login_registration_interface_distance_x;
	}

	void on_update(int delta) {
		timer_input_position_hint_blink.on_update(delta);
		if (is_display_mysql_unconnected_text) animation_mysql_unconnected_text.on_update(delta);
		if (is_display_account_or_password_error_text) timer_display_account_or_password_error_text.on_update(delta);
		if (is_display_registration_sucess_or_failed) timer_registration_sucess_or_falied_text.on_update(delta);

		const int input_box_letter_or_number_interval = 5;			// 输入框中的字母数字间隔
		const int hint_distance_to_letter_or_number = 2;			// 提示距离字母数字的距离
		// 账号输入框
		account_input_box_1_pos.x = account_input_box_pos.x + input_box_letter_or_number_interval;
		account_input_box_1_pos.y = account_input_box_pos.y;
		account_input_box_2_pos.x = account_input_box_1_pos.x + img_account_input_box_1.getwidth() + input_box_letter_or_number_interval;
		account_input_box_2_pos.y = account_input_box_1_pos.y;
		account_input_box_3_pos.x = account_input_box_2_pos.x + img_account_input_box_2.getwidth() + input_box_letter_or_number_interval;
		account_input_box_3_pos.y = account_input_box_1_pos.y;
		account_input_box_4_pos.x = account_input_box_3_pos.x + img_account_input_box_3.getwidth() + input_box_letter_or_number_interval;
		account_input_box_4_pos.y = account_input_box_1_pos.y;
		account_input_box_5_pos.x = account_input_box_4_pos.x + img_account_input_box_4.getwidth() + input_box_letter_or_number_interval;
		account_input_box_5_pos.y = account_input_box_1_pos.y;
		account_input_box_6_pos.x = account_input_box_5_pos.x + img_account_input_box_5.getwidth() + input_box_letter_or_number_interval;
		account_input_box_6_pos.y = account_input_box_1_pos.y;
		account_input_box_7_pos.x = account_input_box_6_pos.x + img_account_input_box_6.getwidth() + input_box_letter_or_number_interval;
		account_input_box_7_pos.y = account_input_box_1_pos.y;
		account_input_box_8_pos.x = account_input_box_7_pos.x + img_account_input_box_7.getwidth() + input_box_letter_or_number_interval;
		account_input_box_8_pos.y = account_input_box_1_pos.y;
		account_input_box_9_pos.x = account_input_box_8_pos.x + img_account_input_box_8.getwidth() + input_box_letter_or_number_interval;
		account_input_box_9_pos.y = account_input_box_1_pos.y;
		account_input_box_10_pos.x = account_input_box_9_pos.x + img_account_input_box_9.getwidth() + input_box_letter_or_number_interval;
		account_input_box_10_pos.y = account_input_box_1_pos.y;
		account_input_box_11_pos.x = account_input_box_10_pos.x + img_account_input_box_10.getwidth() + input_box_letter_or_number_interval;
		account_input_box_11_pos.y = account_input_box_1_pos.y;
		account_input_box_12_pos.x = account_input_box_11_pos.x + img_account_input_box_11.getwidth() + input_box_letter_or_number_interval;
		account_input_box_12_pos.y = account_input_box_1_pos.y;
		account_input_box_13_pos.x = account_input_box_12_pos.x + img_account_input_box_12.getwidth() + input_box_letter_or_number_interval;
		account_input_box_13_pos.y = account_input_box_1_pos.y;
		account_input_box_14_pos.x = account_input_box_13_pos.x + img_account_input_box_13.getwidth() + input_box_letter_or_number_interval;
		account_input_box_14_pos.y = account_input_box_1_pos.y;
		account_input_box_15_pos.x = account_input_box_14_pos.x + img_account_input_box_14.getwidth() + input_box_letter_or_number_interval;
		account_input_box_15_pos.y = account_input_box_1_pos.y;
		account_input_box_16_pos.x = account_input_box_15_pos.x + img_account_input_box_15.getwidth() + input_box_letter_or_number_interval;
		account_input_box_16_pos.y = account_input_box_1_pos.y;

		// 密码输入框
		password_input_box_1_pos.x = password_input_box_pos.x + input_box_letter_or_number_interval;
		password_input_box_1_pos.y = password_input_box_pos.y;
		password_input_box_2_pos.x = password_input_box_1_pos.x + img_password_input_box_1.getwidth() + input_box_letter_or_number_interval;
		password_input_box_2_pos.y = password_input_box_1_pos.y;
		password_input_box_3_pos.x = password_input_box_2_pos.x + img_password_input_box_2.getwidth() + input_box_letter_or_number_interval;
		password_input_box_3_pos.y = password_input_box_1_pos.y;
		password_input_box_4_pos.x = password_input_box_3_pos.x + img_password_input_box_3.getwidth() + input_box_letter_or_number_interval;
		password_input_box_4_pos.y = password_input_box_1_pos.y;
		password_input_box_5_pos.x = password_input_box_4_pos.x + img_password_input_box_4.getwidth() + input_box_letter_or_number_interval;
		password_input_box_5_pos.y = password_input_box_1_pos.y;
		password_input_box_6_pos.x = password_input_box_5_pos.x + img_password_input_box_5.getwidth() + input_box_letter_or_number_interval;
		password_input_box_6_pos.y = password_input_box_1_pos.y;
		password_input_box_7_pos.x = password_input_box_6_pos.x + img_password_input_box_6.getwidth() + input_box_letter_or_number_interval;
		password_input_box_7_pos.y = password_input_box_1_pos.y;
		password_input_box_8_pos.x = password_input_box_7_pos.x + img_password_input_box_7.getwidth() + input_box_letter_or_number_interval;
		password_input_box_8_pos.y = password_input_box_1_pos.y;
		password_input_box_9_pos.x = password_input_box_8_pos.x + img_password_input_box_8.getwidth() + input_box_letter_or_number_interval;
		password_input_box_9_pos.y = password_input_box_1_pos.y;
		password_input_box_10_pos.x = password_input_box_9_pos.x + img_password_input_box_9.getwidth() + input_box_letter_or_number_interval;
		password_input_box_10_pos.y = password_input_box_1_pos.y;
		password_input_box_11_pos.x = password_input_box_10_pos.x + img_password_input_box_10.getwidth() + input_box_letter_or_number_interval;
		password_input_box_11_pos.y = password_input_box_1_pos.y;
		password_input_box_12_pos.x = password_input_box_11_pos.x + img_password_input_box_11.getwidth() + input_box_letter_or_number_interval;
		password_input_box_12_pos.y = password_input_box_1_pos.y;
		password_input_box_13_pos.x = password_input_box_12_pos.x + img_password_input_box_12.getwidth() + input_box_letter_or_number_interval;
		password_input_box_13_pos.y = password_input_box_1_pos.y;
		password_input_box_14_pos.x = password_input_box_13_pos.x + img_password_input_box_13.getwidth() + input_box_letter_or_number_interval;
		password_input_box_14_pos.y = password_input_box_1_pos.y;
		password_input_box_15_pos.x = password_input_box_14_pos.x + img_password_input_box_14.getwidth() + input_box_letter_or_number_interval;
		password_input_box_15_pos.y = password_input_box_1_pos.y;
		password_input_box_16_pos.x = password_input_box_15_pos.x + img_password_input_box_15.getwidth() + input_box_letter_or_number_interval;
		password_input_box_16_pos.y = password_input_box_1_pos.y;
		switch (current_is_input_account ? account_insert_id : password_insert_id) {
		case 0:
			if(current_is_input_account) input_position_hint_pos.x = account_input_box_pos.x;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_pos.x;
			break;
		case 1:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_1_pos.x + img_account_input_box_1.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_1_pos.x + img_password_input_box_1.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 2:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_2_pos.x + img_account_input_box_2.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_2_pos.x + img_password_input_box_2.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 3:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_3_pos.x + img_account_input_box_3.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_3_pos.x + img_password_input_box_3.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 4:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_4_pos.x + img_account_input_box_4.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_4_pos.x + img_password_input_box_4.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 5:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_5_pos.x + img_account_input_box_5.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_5_pos.x + img_password_input_box_5.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 6:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_6_pos.x + img_account_input_box_6.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_6_pos.x + img_password_input_box_6.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 7:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_7_pos.x + img_account_input_box_7.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_7_pos.x + img_password_input_box_7.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 8:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_8_pos.x + img_account_input_box_8.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_8_pos.x + img_password_input_box_8.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 9:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_9_pos.x + img_account_input_box_9.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_9_pos.x + img_password_input_box_9.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 10:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_10_pos.x + img_account_input_box_10.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_10_pos.x + img_password_input_box_10.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 11:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_11_pos.x + img_account_input_box_11.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_11_pos.x + img_password_input_box_11.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 12:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_12_pos.x + img_account_input_box_12.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_12_pos.x + img_password_input_box_12.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 13:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_13_pos.x + img_account_input_box_13.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_13_pos.x + img_password_input_box_13.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 14:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_14_pos.x + img_account_input_box_14.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_14_pos.x + img_password_input_box_14.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 15:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_15_pos.x + img_account_input_box_15.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_15_pos.x + img_password_input_box_15.getwidth() - hint_distance_to_letter_or_number;
			break;
		case 16:
			if (current_is_input_account) input_position_hint_pos.x = account_input_box_16_pos.x + img_account_input_box_16.getwidth() - hint_distance_to_letter_or_number;
			if (current_is_input_password) input_position_hint_pos.x = password_input_box_16_pos.x + img_password_input_box_16.getwidth() - hint_distance_to_letter_or_number;
			break;
		}
		input_position_hint_pos.y = current_is_input_account ? account_input_box_pos.y : password_input_box_pos.y;

		/*if ((current_is_input_account && account.size()) || (current_is_input_password && password.size())) {
			switch (current_is_input_account ? account[account.size() - 1] : password[password.size() - 1]) {
			case 'A':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'A');
				break;
			case 'a':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'a');
				break;
			case 'B':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'B');
				break;
			case 'b':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'b');
				break;
			case 'C':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'C');
				break;
			case 'c':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'c');
				break;
			case 'D':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'D');
				break;
			case 'd':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'd');
				break;
			case 'E':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'E');
				break;
			case 'e':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'e');
				break;
			case 'F':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'F');
				break;
			case 'f':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'f');
				break;
			case 'G':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'G');
				break;
			case 'g':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'g');
				break;
			case 'H':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'H');
				break;
			case 'h':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'h');
				break;
			case 'I':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'I');
				break;
			case 'i':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'i');
				break;
			case 'J':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'J');
				break;
			case 'j':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'j');
				break;
			case 'K':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'K');
				break;
			case 'k':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'k');
				break;
			case 'L':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'L');
				break;
			case 'l':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'l');
				break;
			case 'M':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'M');
				break;
			case 'm':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'm');
				break;
			case 'N':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'N');
				break;
			case 'n':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'n');
				break;
			case 'O':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'O');
				break;
			case 'o':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'o');
				break;
			case 'P':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'P');
				break;
			case 'p':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'p');
				break;
			case 'Q':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'Q');
				break;
			case 'q':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'q');
				break;
			case 'R':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'R');
				break;
			case 'r':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'r');
				break;
			case 'S':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'S');
				break;
			case 's':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 's');
				break;
			case 'T':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'T');
				break;
			case 't':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 't');
				break;
			case 'U':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'U');
				break;
			case 'u':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'u');
				break;
			case 'V':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'V');
				break;
			case 'v':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'v');
				break;
			case 'W':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'W');
				break;
			case 'w':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'w');
				break;
			case 'X':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'X');
				break;
			case 'x':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'x');
				break;
			case 'Y':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'Y');
				break;
			case 'y':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'y');
				break;
			case 'Z':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'Z');
				break;
			case 'z':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), 'z');
				break;
			case '0':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '0');
				break;
			case '1':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '1');
				break;
			case '2':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '2');
				break;
			case '3':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '3');
				break;
			case '4':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '4');
				break;
			case '5':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '5');
				break;
			case '6':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '6');
				break;
			case '7':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '7');
				break;
			case '8':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '8');
				break;
			case '9':
				set_img_input_box(current_is_input_account ? account.size() : password.size(), '9');
				break;
			}
		}*/

		display_account_password();
	}

	void on_draw() {
		// 主要背景界面等
		putimage_alpha(login_registration_background_pos_pos.x, login_registration_background_pos_pos.y, &img_login_registration_background);
		putimage_alpha(login_registration_interface_pos.x, login_registration_interface_pos.y, &img_login_registration_interface);
		putimage_alpha(registration_text_pos.x, registration_text_pos.y, is_down_login_registration_text_button ? (
			current_is_login ? &img_login_down_text : &img_registration_down_text) : (
			current_is_login ? &img_login_idle_text : &img_registration_idle_text));
		putimage_alpha(login_registration_account_text_pos.x, login_registration_account_text_pos.y, &img_login_registration_account_text);
		putimage_alpha(login_registration_password_text_pos.x, login_registration_password_text_pos.y, &img_login_registration_password_text);
		putimage_alpha(account_input_box_pos.x, account_input_box_pos.y, &img_login_registration_input_box);
		putimage_alpha(password_input_box_pos.x, password_input_box_pos.y, &img_login_registration_input_box);
		putimage_alpha(login_or_registration_button_pos.x, login_or_registration_button_pos.y, is_down_login_or_registration_button ? (
			current_is_login ? &img_login_down_button : &img_registration_down_button) : (
			current_is_login ? &img_login_idle_button : &img_registration_idle_button));
		putimage_alpha(eye_pos.x, eye_pos.y, &img_eye);
		if (!is_open_eye) {
			setlinecolor(RGB(0, 0, 0));	//黑
			line(eye_pos.x + img_eye.getwidth() / 4, eye_pos.y, eye_pos.x + img_eye.getwidth() - img_eye.getwidth() / 4, eye_pos.y + img_eye.getheight());
		}

		// 账号输入框中的字母数字
		putimage_alpha(account_input_box_1_pos.x, account_input_box_1_pos.y, &img_account_input_box_1);
		putimage_alpha(account_input_box_2_pos.x, account_input_box_2_pos.y, &img_account_input_box_2);
		putimage_alpha(account_input_box_3_pos.x, account_input_box_3_pos.y, &img_account_input_box_3);
		putimage_alpha(account_input_box_4_pos.x, account_input_box_4_pos.y, &img_account_input_box_4);
		putimage_alpha(account_input_box_5_pos.x, account_input_box_5_pos.y, &img_account_input_box_5);
		putimage_alpha(account_input_box_6_pos.x, account_input_box_6_pos.y, &img_account_input_box_6);
		putimage_alpha(account_input_box_7_pos.x, account_input_box_7_pos.y, &img_account_input_box_7);
		putimage_alpha(account_input_box_8_pos.x, account_input_box_8_pos.y, &img_account_input_box_8);
		putimage_alpha(account_input_box_9_pos.x, account_input_box_9_pos.y, &img_account_input_box_9);
		putimage_alpha(account_input_box_10_pos.x, account_input_box_10_pos.y, &img_account_input_box_10);
		putimage_alpha(account_input_box_11_pos.x, account_input_box_11_pos.y, &img_account_input_box_11);
		putimage_alpha(account_input_box_12_pos.x, account_input_box_12_pos.y, &img_account_input_box_12);
		putimage_alpha(account_input_box_13_pos.x, account_input_box_13_pos.y, &img_account_input_box_13);
		putimage_alpha(account_input_box_14_pos.x, account_input_box_14_pos.y, &img_account_input_box_14);
		putimage_alpha(account_input_box_15_pos.x, account_input_box_15_pos.y, &img_account_input_box_15);
		putimage_alpha(account_input_box_16_pos.x, account_input_box_16_pos.y, &img_account_input_box_16);

		// 密码输入框中的字母数字
		if (is_open_eye) {
			putimage_alpha(password_input_box_1_pos.x, password_input_box_1_pos.y, &img_password_input_box_1);
			putimage_alpha(password_input_box_2_pos.x, password_input_box_2_pos.y, &img_password_input_box_2);
			putimage_alpha(password_input_box_3_pos.x, password_input_box_3_pos.y, &img_password_input_box_3);
			putimage_alpha(password_input_box_4_pos.x, password_input_box_4_pos.y, &img_password_input_box_4);
			putimage_alpha(password_input_box_5_pos.x, password_input_box_5_pos.y, &img_password_input_box_5);
			putimage_alpha(password_input_box_6_pos.x, password_input_box_6_pos.y, &img_password_input_box_6);
			putimage_alpha(password_input_box_7_pos.x, password_input_box_7_pos.y, &img_password_input_box_7);
			putimage_alpha(password_input_box_8_pos.x, password_input_box_8_pos.y, &img_password_input_box_8);
			putimage_alpha(password_input_box_9_pos.x, password_input_box_9_pos.y, &img_password_input_box_9);
			putimage_alpha(password_input_box_10_pos.x, password_input_box_10_pos.y, &img_password_input_box_10);
			putimage_alpha(password_input_box_11_pos.x, password_input_box_11_pos.y, &img_password_input_box_11);
			putimage_alpha(password_input_box_12_pos.x, password_input_box_12_pos.y, &img_password_input_box_12);
			putimage_alpha(password_input_box_13_pos.x, password_input_box_13_pos.y, &img_password_input_box_13);
			putimage_alpha(password_input_box_14_pos.x, password_input_box_14_pos.y, &img_password_input_box_14);
			putimage_alpha(password_input_box_15_pos.x, password_input_box_15_pos.y, &img_password_input_box_15);
			putimage_alpha(password_input_box_16_pos.x, password_input_box_16_pos.y, &img_password_input_box_16);
		}

		// 输入位置提示图像的位置
		if (is_display_input_position_hint && (current_is_input_account || current_is_input_password)) putimage_alpha(input_position_hint_pos.x, input_position_hint_pos.y, &img_input_position_hint);

		// 文本提示
		if (is_display_account_or_password_error_text) putimage_alpha(account_or_password_error_text_pos.x, account_or_password_error_text_pos.y, &img_account_or_password_error_text);
		if (current_is_input_account ? account.size() < 6 : password.size() < 6 && (current_is_input_account || current_is_input_password))
			putimage_alpha(account_and_password_length_hint_text_pos.x, account_and_password_length_hint_text_pos.y, &img_account_and_password_length_hint_text);
		if (current_is_login) putimage_alpha(is_remember_password_pos.x, is_remember_password_pos.y, is_remember_password ? &img_remember_password : &img_do_not_remember_password);
		if (is_display_registration_sucess_or_failed) {
			if (is_registration_sucess) putimage_alpha(registration_sucess_text_pos.x, registration_sucess_text_pos.y, &img_registration_sucess_text);
			else putimage_alpha(registered_text_pos.x, registered_text_pos.y, &img_registered_text);
		}


		if (is_display_mysql_unconnected_text) animation_mysql_unconnected_text.on_draw(532, 200);
	}

	void on_input(const ExMessage& msg) {
		// 鼠标事件
		switch (msg.message) {
		case WM_LBUTTONDOWN:
			// 账号输入框
			if (msg.x < account_input_box_pos.x + img_login_registration_input_box.getwidth() && msg.x > account_input_box_pos.x &&
				msg.y < account_input_box_pos.y + img_login_registration_input_box.getheight() && msg.y > account_input_box_pos.y) {
				current_is_input_password = false;
				current_is_input_account = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);		// 先将就用着，以后再换音效
			}

			// 密码输入框
			if (msg.x < password_input_box_pos.x + img_login_registration_input_box.getwidth() && msg.x > password_input_box_pos.x &&
				msg.y < password_input_box_pos.y + img_login_registration_input_box.getheight() && msg.y > password_input_box_pos.y) {
				current_is_input_password = true;
				current_is_input_account = false;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
			}

			// 转化注册或者登录按钮
			if (msg.x < registration_text_pos.x + img_registration_idle_text.getwidth() && msg.x > registration_text_pos.x &&
				msg.y < registration_text_pos.y + img_registration_idle_text.getheight() && msg.y > registration_text_pos.y) {
				is_down_login_registration_text_button = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
				break;
			}

			// 登录或注册按钮
			if (msg.x < login_or_registration_button_pos.x + img_login_idle_button.getwidth() && msg.x > login_or_registration_button_pos.x &&
				msg.y < login_or_registration_button_pos.y + img_login_idle_button.getheight() && msg.y > login_or_registration_button_pos.y) {
				is_down_login_or_registration_button = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
				break;
			}

			// 眼睛按钮
			if (msg.x < eye_pos.x + img_eye.getwidth() && msg.x > eye_pos.x && msg.y < eye_pos.y + img_eye.getheight() && msg.y > eye_pos.y) {
				is_open_eye = !is_open_eye;
				set_is_open_eye(is_open_eye);
				if (is_open_sound_effect) mciSendString(_T("play click_sound_1 from 0"), NULL, 0, NULL);
				break;
			}

			// 记住密码
			if (msg.x < is_remember_password_pos.x + img_remember_password.getwidth() && msg.x > is_remember_password_pos.x &&
				msg.y < is_remember_password_pos.y + img_remember_password.getheight() && msg.y > is_remember_password_pos.y && current_is_login) {
				is_down_remember_password = true;
				if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
			}

			break;
		case WM_LBUTTONUP:
			// 转化注册或登录按钮
			if (is_down_login_registration_text_button) {
				if (msg.x < registration_text_pos.x + img_registration_idle_text.getwidth() && msg.x > registration_text_pos.x &&
					msg.y < registration_text_pos.y + img_registration_idle_text.getheight() && msg.y > registration_text_pos.y) {
					current_is_input_password = false;
					current_is_input_account = false;
					account = "";
					password = "";
					account_insert_id = 0;
					password_insert_id = 0;
					clear_input_box();

					is_down_login_registration_text_button = false;
					current_is_login = !current_is_login;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					break;
				}
				else {
					is_down_login_registration_text_button = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					break;
				}
			}

			// 登录或注册按钮
			if (is_down_login_or_registration_button) {
				if (msg.x < login_or_registration_button_pos.x + img_login_idle_button.getwidth() && msg.x > login_or_registration_button_pos.x &&
					msg.y < login_or_registration_button_pos.y + img_login_idle_button.getheight() && msg.y > login_or_registration_button_pos.y) {
					current_is_input_password = false;
					current_is_input_account = false;
					is_down_login_or_registration_button = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					login_registration();
					break;
				}
				else {
					is_down_login_or_registration_button = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				}
			}

			// 记住密码
			if (is_down_remember_password) {
				if (msg.x < is_remember_password_pos.x + img_remember_password.getwidth() && msg.x > is_remember_password &&
					msg.y < is_remember_password_pos.y + img_remember_password.getheight() && msg.y > is_remember_password_pos.y) {
					is_remember_password = !is_remember_password;
					is_down_remember_password = true;
					set_is_remember_password(is_remember_password);
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				}
				else {
					is_down_remember_password = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
				}
			}

			break;
		}

		// 账号密码输入框
		switch (msg.message) {
		case WM_KEYDOWN: {
			switch (msg.vkcode) {
				// 'enter'
			case 0x0D: {
				if (current_is_input_password) {
					// 模仿点击了登录注册
					is_down_login_or_registration_button = true;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_1 from 0"), NULL, 0, NULL);
					break;
				}
				break;
			}
					 // '⬆'
			case 0x26: {
				if (!current_is_input_account && !current_is_input_password) {
					current_is_input_password = true;
				}
				else if (current_is_input_password) {
					current_is_input_account = true;
					current_is_input_password = false;
				}
				if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_2 from 0"), NULL, 0, NULL);
				break;
			}
					 // '⬇'
			case 0x28: {
				if (!current_is_input_account && !current_is_input_password) {
					current_is_input_account = true;
				}
				else if (current_is_input_account) {
					current_is_input_account = false;
					current_is_input_password = true;
				}
				if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_2 from 0"), NULL, 0, NULL);
				break;
			}
					 // '←‘
			case VK_LEFT: {
				if (current_is_input_account && account_insert_id) {
					--account_insert_id;
				}
				if (current_is_input_password && password_insert_id) {
					--password_insert_id;
				}
				if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_2 from 0"), NULL, 0, NULL);
				break;
			}
						// '→' 
			case VK_RIGHT: {
				if (current_is_input_account && account_insert_id < account.size()) {
					++account_insert_id;
				}
				if (current_is_input_password && password_insert_id < password.size()) {
					++password_insert_id;
				}
				if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_2 from 0"), NULL, 0, NULL);
				break;
			}
			}

			// 删除
			if ((current_is_input_account || current_is_input_password) && msg.vkcode == 0x08) {
				if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_2 from 0"), NULL, 0, NULL);
				if (!(current_is_input_account ? account_insert_id : password_insert_id)) break;
				if (current_is_input_account) {
					clear_input_box_range(account_insert_id, account.size());
				}
				if (current_is_input_password) {
					clear_input_box_range(password_insert_id, password.size());
				}
				current_is_input_account ? --account_insert_id : --password_insert_id;
				current_is_input_account ? account.erase(account_insert_id, 1) : password.erase(password_insert_id, 1);
			}

			// 大写
			if ((((GetKeyState(VK_CAPITAL) & 0x0001) != 0) && (!(GetAsyncKeyState(VK_LSHIFT) & 0x8000) && !(GetAsyncKeyState(VK_RSHIFT) & 0x8000))) ||
				(((GetKeyState(VK_CAPITAL) & 0x0001) == 0) && ((GetAsyncKeyState(VK_LSHIFT) & 0x8000) || GetAsyncKeyState(VK_RSHIFT) & 0x8000))) {
				if ((!current_is_input_account && !current_is_input_password) || (current_is_input_account ? account.size() >= 16 : password.size() >= 16)) break;
				switch (msg.vkcode) {
					// 'A'
				case 0x41:
					current_is_input_account ? account.insert(account_insert_id, "A") : password.insert(password_insert_id, "A");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'B'
				case 0x42:
					current_is_input_account ? account.insert(account_insert_id, "B") : password.insert(password_insert_id, "B");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'C'
				case 0x43:
					current_is_input_account ? account.insert(account_insert_id, "C") : password.insert(password_insert_id, "C");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'D'
				case 0x44:
					current_is_input_account ? account.insert(account_insert_id, "D") : password.insert(password_insert_id, "D");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'E'
				case 0x45:
					current_is_input_account ? account.insert(account_insert_id, "E") : password.insert(password_insert_id, "E");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'F'
				case 0x46:
					current_is_input_account ? account.insert(account_insert_id, "F") : password.insert(password_insert_id, "F");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'G'
				case 0x47:
					current_is_input_account ? account.insert(account_insert_id, "G") : password.insert(password_insert_id, "G");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'H'
				case 0x48:
					current_is_input_account ? account.insert(account_insert_id, "H") : password.insert(password_insert_id, "H");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'I'
				case 0x49:
					current_is_input_account ? account.insert(account_insert_id, "I") : password.insert(password_insert_id, "I");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'J'
				case 0x4A:
					current_is_input_account ? account.insert(account_insert_id, "J") : password.insert(password_insert_id, "J");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'K'
				case 0x4B:
					current_is_input_account ? account.insert(account_insert_id, "K") : password.insert(password_insert_id, "K");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'L'
				case 0x4C:
					current_is_input_account ? account.insert(account_insert_id, "L") : password.insert(password_insert_id, "L");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'M'
				case 0x4D:
					current_is_input_account ? account.insert(account_insert_id, "M") : password.insert(password_insert_id, "M");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'N'
				case 0x4E:
					current_is_input_account ? account.insert(account_insert_id, "N") : password.insert(password_insert_id, "N");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'O'
				case 0x4F:
					current_is_input_account ? account.insert(account_insert_id, "O") : password.insert(password_insert_id, "O");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'P'
				case 0x50:
					current_is_input_account ? account.insert(account_insert_id, "P") : password.insert(password_insert_id, "P");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'Q'
				case 0x51:
					current_is_input_account ? account.insert(account_insert_id, "Q") : password.insert(password_insert_id, "Q");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'R'
				case 0x52:
					current_is_input_account ? account.insert(account_insert_id, "R") : password.insert(password_insert_id, "R");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'S'
				case 0x53:
					current_is_input_account ? account.insert(account_insert_id, "S") : password.insert(password_insert_id, "S");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'T'
				case 0x54:
					current_is_input_account ? account.insert(account_insert_id, "T") : password.insert(password_insert_id, "T");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'U'
				case 0x55:
					current_is_input_account ? account.insert(account_insert_id, "U") : password.insert(password_insert_id, "U");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'V'
				case 0x56:
					current_is_input_account ? account.insert(account_insert_id, "V") : password.insert(password_insert_id, "V");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'W'
				case 0x57:
					current_is_input_account ? account.insert(account_insert_id, "W") : password.insert(password_insert_id, "W");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'X'
				case 0x58:
					current_is_input_account ? account.insert(account_insert_id, "X") : password.insert(password_insert_id, "X");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'Y'
				case 0x59:
					current_is_input_account ? account.insert(account_insert_id, "Y") : password.insert(password_insert_id, "Y");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'Z'
				case 0x5A:
					current_is_input_account ? account.insert(account_insert_id, "Z") : password.insert(password_insert_id, "Z");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
				}
			}
			// 小写
			else {
				if ((!current_is_input_account && !current_is_input_password) || (current_is_input_account ? account.size() >= 16 : password.size() >= 16)) break;
				switch (msg.vkcode) {
					// 'a'
				case 0x41:
					current_is_input_account ? account.insert(account_insert_id, "a") : password.insert(password_insert_id, "a");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'b'
				case 0x42:
					current_is_input_account ? account.insert(account_insert_id, "b") : password.insert(password_insert_id, "b");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'c'
				case 0x43:
					current_is_input_account ? account.insert(account_insert_id, "c") : password.insert(password_insert_id, "c");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'd'
				case 0x44:
					current_is_input_account ? account.insert(account_insert_id, "d") : password.insert(password_insert_id, "d");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'e'
				case 0x45:
					current_is_input_account ? account.insert(account_insert_id, "e") : password.insert(password_insert_id, "e");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'f'
				case 0x46:
					current_is_input_account ? account.insert(account_insert_id, "f") : password.insert(password_insert_id, "f");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'g'
				case 0x47:
					current_is_input_account ? account.insert(account_insert_id, "g") : password.insert(password_insert_id, "g");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'h'
				case 0x48:
					current_is_input_account ? account.insert(account_insert_id, "h") : password.insert(password_insert_id, "h");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'i'
				case 0x49:
					current_is_input_account ? account.insert(account_insert_id, "i") : password.insert(password_insert_id, "i");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'j'
				case 0x4A:
					current_is_input_account ? account.insert(account_insert_id, "j") : password.insert(password_insert_id, "j");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'k'
				case 0x4B:
					current_is_input_account ? account.insert(account_insert_id, "k") : password.insert(password_insert_id, "k");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'l'
				case 0x4C:
					current_is_input_account ? account.insert(account_insert_id, "l") : password.insert(password_insert_id, "l");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'm'
				case 0x4D:
					current_is_input_account ? account.insert(account_insert_id, "m") : password.insert(password_insert_id, "m");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'n'
				case 0x4E:
					current_is_input_account ? account.insert(account_insert_id, "n") : password.insert(password_insert_id, "n");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'o'
				case 0x4F:
					current_is_input_account ? account.insert(account_insert_id, "o") : password.insert(password_insert_id, "o");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'p'
				case 0x50:
					current_is_input_account ? account.insert(account_insert_id, "p") : password.insert(password_insert_id, "p");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'q'
				case 0x51:
					current_is_input_account ? account.insert(account_insert_id, "q") : password.insert(password_insert_id, "q");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'r'
				case 0x52:
					current_is_input_account ? account.insert(account_insert_id, "r") : password.insert(password_insert_id, "r");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 's'
				case 0x53:
					current_is_input_account ? account.insert(account_insert_id, "s") : password.insert(password_insert_id, "s");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 't'
				case 0x54:
					current_is_input_account ? account.insert(account_insert_id, "t") : password.insert(password_insert_id, "t");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'u'
				case 0x55:
					current_is_input_account ? account.insert(account_insert_id, "u") : password.insert(password_insert_id, "u");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'v'
				case 0x56:
					current_is_input_account ? account.insert(account_insert_id, "v") : password.insert(password_insert_id, "v");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'w'
				case 0x57:
					current_is_input_account ? account.insert(account_insert_id, "w") : password.insert(password_insert_id, "w");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'x'
				case 0x58:
					current_is_input_account ? account.insert(account_insert_id, "x") : password.insert(password_insert_id, "x");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'y'
				case 0x59:
					current_is_input_account ? account.insert(account_insert_id, "y") : password.insert(password_insert_id, "y");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// 'z'
				case 0x5A:
					current_is_input_account ? account.insert(account_insert_id, "z") : password.insert(password_insert_id, "z");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
				}
			}
			// 数字
			if (!((!current_is_input_account && !current_is_input_password) || (current_is_input_account ? account.size() >= 16 : password.size() >= 16))) {
				switch (msg.vkcode) {
					// '0'
				case 0x30:
					current_is_input_account ? account.insert(account_insert_id, "0") : password.insert(password_insert_id, "0");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// '1'
				case 0x31:
					current_is_input_account ? account.insert(account_insert_id, "1") : password.insert(password_insert_id, "1");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// '2'
				case 0x32:
					current_is_input_account ? account.insert(account_insert_id, "2") : password.insert(password_insert_id, "2");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// '3'
				case 0x33:
					current_is_input_account ? account.insert(account_insert_id, "3") : password.insert(password_insert_id, "3");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// '4'
				case 0x34:
					current_is_input_account ? account.insert(account_insert_id, "4") : password.insert(password_insert_id, "4");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// '5'
				case 0x35:
					current_is_input_account ? account.insert(account_insert_id, "5") : password.insert(password_insert_id, "5");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// '6'
				case 0x36:
					current_is_input_account ? account.insert(account_insert_id, "6") : password.insert(password_insert_id, "6");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// '7'
				case 0x37:
					current_is_input_account ? account.insert(account_insert_id, "7") : password.insert(password_insert_id, "7");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// '8'
				case 0x38:
					current_is_input_account ? account.insert(account_insert_id, "8") : password.insert(password_insert_id, "8");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
					// '9'
				case 0x39:
					current_is_input_account ? account.insert(account_insert_id, "9") : password.insert(password_insert_id, "9");
					current_is_input_account ? ++account_insert_id : ++password_insert_id;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_1 from 0"), NULL, 0, NULL);
					break;
				}
			}
			break;
		}
		case WM_KEYUP: {
			switch (msg.vkcode) {
				// 'enter'
			case 0x0D: {
				if (!current_is_input_account && !current_is_input_password) {
					current_is_input_account = true;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_2 from 0"), NULL, 0, NULL);
				}
				else if (current_is_input_account) {
					current_is_input_account = false;
					current_is_input_password = true;
					if (is_open_sound_effect) mciSendString(_T("play keyboard_sound_2 from 0"), NULL, 0, NULL);
				}
				else if (current_is_input_password) {
					// 模仿点击了登录注册
					current_is_input_password = false;
					current_is_input_account = false;
					is_down_login_or_registration_button = false;
					if (is_open_sound_effect) mciSendString(_T("play click_sound_2_2 from 0"), NULL, 0, NULL);
					login_registration();
					break;
				}
				break;
			}
			}
		}
		}

	}

	void on_exit() {

	}

	void login_registration() {
		// 登录
		if (current_is_login) {
			putimage_alpha(login_or_registration_button_pos.x, login_or_registration_button_pos.y, &img_login_idle_button);
			if (check_is_can_login(account, password)) scene_manager->switch_scene(SceneManager::SceneType::Menu);
			else is_display_account_or_password_error_text = true;
			if (is_remember_password) set_update_remembered_accounts(account, password);
			else clear_remembered_accounts();
		}
		// 注册
		else {
			if (account.size() < 6 || password.size() < 6) {
				return;
			}
			is_registration_sucess = registration_account(account, password);
			is_display_registration_sucess_or_failed = true;
		}
	}

	void set_img_input_box(int input_box_id, char ch) {
		if (ch >= '0' && ch <= '9') {
			switch (input_box_id) {
			case 1: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_1 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_1 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 2: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_2 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_2 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 3: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_3 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_3 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 4: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_4 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_4 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 5: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_5 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_5 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 6: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_6 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_6 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 7: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_7 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_7 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 8: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_8 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_8 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 9: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_9 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_9 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 10: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_10 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_10 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 11: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_11 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_11 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 12: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_12 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_12 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 13: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_13 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_13 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 14: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_14 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_14 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 15: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_15 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_15 = img_login_registration_number_9;
					break;
				}
				break;
			}
			case 16: {
				switch (ch) {
				case '0':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_0;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_0;
					break;
				case '1':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_1;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_1;
					break;
				case '2':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_2;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_2;
					break;
				case '3':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_3;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_3;
					break;
				case '4':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_4;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_4;
					break;
				case '5':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_5;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_5;
					break;
				case '6':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_6;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_6;
					break;
				case '7':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_7;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_7;
					break;
				case '8':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_8;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_8;
					break;
				case '9':
					if (current_is_input_account) img_account_input_box_16 = img_login_registration_number_9;
					if (current_is_input_password) img_password_input_box_16 = img_login_registration_number_9;
					break;
				}
				break;
			}
			}
			return;
		}

		switch (input_box_id) {
		case 1: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_1 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_1 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 2: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_2 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_2 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 3: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_3 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_3 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 4: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_4 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_4 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 5: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_5 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_5 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 6: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_6 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_6 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 7: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_7 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_7 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 8: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_8 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_8 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 9: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_9 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_9 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 10: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_10 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_10 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 11: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_11 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_11 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 12: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_12 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_12 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 13: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_13 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_13 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 14: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_14 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_14 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 15: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_15 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_15 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		case 16: {
			switch (ch) {
			case 'A':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_A;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_A;
				break;
			case 'B':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_B;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_B;
				break;
			case 'C':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_C;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_C;
				break;
			case 'D':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_D;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_D;
				break;
			case 'E':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_E;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_E;
				break;
			case 'F':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_F;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_F;
				break;
			case 'G':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_G;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_G;
				break;
			case 'H':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_H;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_H;
				break;
			case 'I':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_I;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_I;
				break;
			case 'J':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_J;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_J;
				break;
			case 'K':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_K;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_K;
				break;
			case 'L':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_L;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_L;
				break;
			case 'M':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_M;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_M;
				break;
			case 'N':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_N;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_N;
				break;
			case 'O':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_O;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_O;
				break;
			case 'P':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_P;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_P;
				break;
			case 'Q':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_Q;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_Q;
				break;
			case 'R':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_R;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_R;
				break;
			case 'S':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_S;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_S;
				break;
			case 'T':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_T;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_T;
				break;
			case 'U':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_U;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_U;
				break;
			case 'V':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_V;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_V;
				break;
			case 'W':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_W;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_W;
				break;
			case 'X':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_X;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_X;
				break;
			case 'Y':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_Y;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_Y;
				break;
			case 'Z':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_capital_letters_Z;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_capital_letters_Z;
				break;
			case 'a':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_a;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_a;
				break;
			case 'b':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_b;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_b;
				break;
			case 'c':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_c;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_c;
				break;
			case 'd':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_d;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_d;
				break;
			case 'e':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_e;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_e;
				break;
			case 'f':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_f;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_f;
				break;
			case 'g':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_g;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_g;
				break;
			case 'h':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_h;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_h;
				break;
			case 'i':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_i;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_i;
				break;
			case 'j':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_j;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_j;
				break;
			case 'k':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_k;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_k;
				break;
			case 'l':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_l;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_l;
				break;
			case 'm':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_m;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_m;
				break;
			case 'n':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_n;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_n;
				break;
			case 'o':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_o;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_o;
				break;
			case 'p':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_p;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_p;
				break;
			case 'q':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_q;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_q;
				break;
			case 'r':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_r;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_r;
				break;
			case 's':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_s;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_s;
				break;
			case 't':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_t;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_t;
				break;
			case 'u':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_u;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_u;
				break;
			case 'v':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_v;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_v;
				break;
			case 'w':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_w;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_w;
				break;
			case 'x':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_x;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_x;
				break;
			case 'y':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_y;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_y;
				break;
			case 'z':
				if (current_is_input_account) img_account_input_box_16 = img_login_registration_small_letters_z;
				if (current_is_input_password) img_password_input_box_16 = img_login_registration_small_letters_z;
				break;
			}
			break;
		}
		}
	}

	void clear_input_box() {
		img_account_input_box_1 = img_nullptr;
		img_account_input_box_2 = img_nullptr;
		img_account_input_box_3 = img_nullptr;
		img_account_input_box_4 = img_nullptr;
		img_account_input_box_5 = img_nullptr;
		img_account_input_box_6 = img_nullptr;
		img_account_input_box_7 = img_nullptr;
		img_account_input_box_8 = img_nullptr;
		img_account_input_box_9 = img_nullptr;
		img_account_input_box_10 = img_nullptr;
		img_account_input_box_11 = img_nullptr;
		img_account_input_box_12 = img_nullptr;
		img_account_input_box_13 = img_nullptr;
		img_account_input_box_14 = img_nullptr;
		img_account_input_box_15 = img_nullptr;
		img_account_input_box_16 = img_nullptr;

		img_password_input_box_1 = img_nullptr;
		img_password_input_box_2 = img_nullptr;
		img_password_input_box_3 = img_nullptr;
		img_password_input_box_4 = img_nullptr;
		img_password_input_box_5 = img_nullptr;
		img_password_input_box_6 = img_nullptr;
		img_password_input_box_7 = img_nullptr;
		img_password_input_box_8 = img_nullptr;
		img_password_input_box_9 = img_nullptr;
		img_password_input_box_10 = img_nullptr;
		img_password_input_box_11 = img_nullptr;
		img_password_input_box_12 = img_nullptr;
		img_password_input_box_13 = img_nullptr;
		img_password_input_box_14 = img_nullptr;
		img_password_input_box_15 = img_nullptr;
		img_password_input_box_16 = img_nullptr;
	}

	void clear_input_box_id(int id) {
		switch (id) {
		case 1:
			current_is_input_account ? img_account_input_box_1 = img_nullptr : img_password_input_box_1 = img_nullptr;
			break;
		case 2:
			current_is_input_account ? img_account_input_box_2 = img_nullptr : img_password_input_box_2 = img_nullptr;
			break;
		case 3:
			current_is_input_account ? img_account_input_box_3 = img_nullptr : img_password_input_box_3 = img_nullptr;
			break;
		case 4:
			current_is_input_account ? img_account_input_box_4 = img_nullptr : img_password_input_box_4 = img_nullptr;
			break;
		case 5:
			current_is_input_account ? img_account_input_box_5 = img_nullptr : img_password_input_box_5 = img_nullptr;
			break;
		case 6:
			current_is_input_account ? img_account_input_box_6 = img_nullptr : img_password_input_box_6 = img_nullptr;
			break;
		case 7:
			current_is_input_account ? img_account_input_box_7 = img_nullptr : img_password_input_box_7 = img_nullptr;
			break;
		case 8:
			current_is_input_account ? img_account_input_box_8 = img_nullptr : img_password_input_box_8 = img_nullptr;
			break;
		case 9:
			current_is_input_account ? img_account_input_box_9 = img_nullptr : img_password_input_box_9 = img_nullptr;
			break;
		case 10:
			current_is_input_account ? img_account_input_box_10 = img_nullptr : img_password_input_box_10 = img_nullptr;
			break;
		case 11:
			current_is_input_account ? img_account_input_box_11 = img_nullptr : img_password_input_box_11 = img_nullptr;
			break;
		case 12:
			current_is_input_account ? img_account_input_box_12 = img_nullptr : img_password_input_box_12 = img_nullptr;
			break;
		case 13:
			current_is_input_account ? img_account_input_box_13 = img_nullptr : img_password_input_box_13 = img_nullptr;
			break;
		case 14:
			current_is_input_account ? img_account_input_box_14 = img_nullptr : img_password_input_box_14 = img_nullptr;
			break;
		case 15:
			current_is_input_account ? img_account_input_box_15 = img_nullptr : img_password_input_box_15 = img_nullptr;
			break;
		case 16:
			current_is_input_account ? img_account_input_box_16 = img_nullptr : img_password_input_box_16 = img_nullptr;
			break;
		}
	}

	void clear_input_box_range(int begin, int end) {
		for (int i = begin; i <= end; ++i) {
			clear_input_box_id(i);
		}
	}

	void display_account_password() {
		// 临时存储当前输入框的状态
		bool temp_current_is_input_account = current_is_input_account;
		bool temp_current_is_input_password = current_is_input_password;
		current_is_input_account = true;
		current_is_input_password = false;
		// 给每一位账号图像对象赋值
		for (int i = 0; i < account.size(); ++i) {
			if (i < account.size()) set_img_input_box(i + 1, account[i]);
		}
		current_is_input_account = false;
		current_is_input_password = true;
		// 给每一位密码图像对象赋值
		for (int i = 0; i < password.size(); ++i) {
			set_img_input_box(i + 1, password[i]);
		}
		// 恢复输入框的状态
		current_is_input_account = temp_current_is_input_account;
		current_is_input_password = temp_current_is_input_password;
	}


private:
	int account_insert_id;
	int password_insert_id;

	string account;
	string password;


private:
	POINT login_registration_background_pos_pos = { 0 };						// 登录注册背景的位置
	POINT login_registration_interface_pos = { 0 };								// 登录注册界面的位置
	POINT registration_text_pos = { 0 };										// 注册文本的位置
	POINT login_registration_account_text_pos = { 0 };							// 登录注册的账号文本的位置
	POINT login_registration_password_text_pos = { 0 };							// 登录注册的密码文本的位置
	POINT account_input_box_pos = { 0 };										// 账号的输入框的位置
	POINT password_input_box_pos = { 0 };										// 密码的输入框的位置
	POINT login_or_registration_button_pos = { 0 };								// 登录或注册按钮的位置
	POINT eye_pos = { 0 };														// 眼睛的位置
	POINT account_input_box_1_pos = { 0 };										// 账号输入框里的第1个数或字母
	POINT account_input_box_2_pos = { 0 };										// 账号输入框里的第2个数或字母									
	POINT account_input_box_3_pos = { 0 };										// 账号输入框里的第3个数或字母									
	POINT account_input_box_4_pos = { 0 };										// 账号输入框里的第4个数或字母									
	POINT account_input_box_5_pos = { 0 };										// 账号输入框里的第5个数或字母									
	POINT account_input_box_6_pos = { 0 };										// 账号输入框里的第6个数或字母									
	POINT account_input_box_7_pos = { 0 };										// 账号输入框里的第7个数或字母									
	POINT account_input_box_8_pos = { 0 };										// 账号输入框里的第8个数或字母									
	POINT account_input_box_9_pos = { 0 };										// 账号输入框里的第9个数或字母									
	POINT account_input_box_10_pos = { 0 };										// 账号输入框里的第10个数或字母									
	POINT account_input_box_11_pos = { 0 };										// 账号输入框里的第11个数或字母									
	POINT account_input_box_12_pos = { 0 };										// 账号输入框里的第12个数或字母									
	POINT account_input_box_13_pos = { 0 };										// 账号输入框里的第13个数或字母									
	POINT account_input_box_14_pos = { 0 };										// 账号输入框里的第14个数或字母									
	POINT account_input_box_15_pos = { 0 };										// 账号输入框里的第15个数或字母									
	POINT account_input_box_16_pos = { 0 };										// 账号输入框里的第16个数或字母	
	POINT password_input_box_1_pos = { 0 };										// 密码输入框里的第1个数或字母
	POINT password_input_box_2_pos = { 0 };										// 密码输入框里的第2个数或字母									
	POINT password_input_box_3_pos = { 0 };										// 密码输入框里的第3个数或字母									
	POINT password_input_box_4_pos = { 0 };										// 密码输入框里的第4个数或字母									
	POINT password_input_box_5_pos = { 0 };										// 密码输入框里的第5个数或字母									
	POINT password_input_box_6_pos = { 0 };										// 密码输入框里的第6个数或字母									
	POINT password_input_box_7_pos = { 0 };										// 密码输入框里的第7个数或字母									
	POINT password_input_box_8_pos = { 0 };										// 密码输入框里的第8个数或字母									
	POINT password_input_box_9_pos = { 0 };										// 密码输入框里的第9个数或字母									
	POINT password_input_box_10_pos = { 0 };									// 密码输入框里的第10个数或字母									
	POINT password_input_box_11_pos = { 0 };									// 密码输入框里的第11个数或字母									
	POINT password_input_box_12_pos = { 0 };									// 密码输入框里的第12个数或字母									
	POINT password_input_box_13_pos = { 0 };									// 密码输入框里的第13个数或字母									
	POINT password_input_box_14_pos = { 0 };									// 密码输入框里的第14个数或字母									
	POINT password_input_box_15_pos = { 0 };									// 密码输入框里的第15个数或字母									
	POINT password_input_box_16_pos = { 0 };									// 密码输入框里的第16个数或字母	
	POINT input_position_hint_pos = { 0 };										// 输入位置提示图像的位置
	POINT account_or_password_error_text_pos = { 0 };							// 账号或密码错误的文本提示位置
	POINT account_and_password_length_hint_text_pos = { 0 };					// 账号和密码长度的提示文本
	POINT is_remember_password_pos = { 0 };										// 是否记住密码的位置
	POINT registration_sucess_text_pos = { 0 };									// 注册成功文本的位置
	POINT registered_text_pos = { 0 };											// 账号已被注册的文本位置

	Timer timer_input_position_hint_blink;										// 输入位置提示图像的闪烁定时器
	Timer timer_display_account_or_password_error_text;							// 显示账号或密码错误的提示文本定时器
	Timer timer_registration_sucess_or_falied_text;								// 显示注册成功或失败文本的定时器

	Animation animation_mysql_unconnected_text;									// 数据库未连接的文本

	bool is_down_login_registration_text_button = false;						// 是否按下了登录或者注册文本的按钮
	bool is_open_eye = false;													// 是否打开眼睛(是否显示密码)
	bool current_is_login = true;												// 现在是否是登录界面
	bool is_down_login_or_registration_button = false;							// 是否按下了登录或注册按钮 
	bool current_is_input_account = account.size() ? true : false;				// 当前是否正在输入账号
	bool current_is_input_password = false;										// 当前是否正在输入密码
	bool is_display_input_position_hint = true;									// 是否显示输入位置提示图像
	bool is_display_account_or_password_error_text = false;						// 是否显示账号或密码错误的提示文本
	bool is_display_account_and_password_length_hint_text = false;				// 是否显示账号和密码长度的提示文本
	bool is_down_remember_password = false;										// 是否按下了记住密码
	bool is_remember_password = false;											// 是否记住密码
	bool is_registration_sucess = true;											// 注册是否成功
	bool is_display_registration_sucess_or_failed = false;						// 是否显示注册成功或失败的文本
	bool is_display_mysql_unconnected_text = !is_mysql_connect;			   // 是否显示数据未连接的文本


};