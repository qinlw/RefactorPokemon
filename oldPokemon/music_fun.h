#pragma once


void play_background_music();
void stop_background_music();

extern bool is_playing_background_music;
extern bool is_playing_game_music;

extern int background_music_id;
extern int temp_background_music_id;

extern int game_music_id;
extern int temp_game_music_id;

// ≤•∑≈±≥æ∞“Ù¿÷
void play_background_music() {
	switch (background_music_id) {
	case 0:
		switch (rand() % 3 + 1) {
		case 1:
			if (temp_background_music_id != 1) stop_background_music();
			if (temp_background_music_id == 1 && is_playing_background_music) break;
			mciSendString(_T("play background_music_1 repeat from 0"), NULL, 0, NULL);
			is_playing_background_music = true;
			temp_background_music_id = 1;
			break;
		case 2:
			if (temp_background_music_id != 2) stop_background_music();
			if (temp_background_music_id == 2 && is_playing_background_music) break;
			mciSendString(_T("play background_music_2 repeat from 0"), NULL, 0, NULL);
			is_playing_background_music = true;
			temp_background_music_id = 2;
			break;
		case 3:
			if (temp_background_music_id != 3) stop_background_music();
			if (temp_background_music_id == 3 && is_playing_background_music) break;
			mciSendString(_T("play background_music_3 repeat from 0"), NULL, 0, NULL);
			is_playing_background_music = true;
			temp_background_music_id = 3;
			break;
		}
		break;
	case 1:
		if (temp_background_music_id != 1) stop_background_music();
		if (temp_background_music_id == 1 && is_playing_background_music) break;
		mciSendString(_T("play background_music_1 repeat from 0"), NULL, 0, NULL);
		is_playing_background_music = true;
		temp_background_music_id = 1;
		break;
	case 2:
		if (temp_background_music_id != 2) stop_background_music();
		if (temp_background_music_id == 2 && is_playing_background_music) break;
		mciSendString(_T("play background_music_2 repeat from 0"), NULL, 0, NULL);
		is_playing_background_music = true;
		temp_background_music_id = 2;
		break;
	case 3:
		if (temp_background_music_id != 3) stop_background_music();
		if (temp_background_music_id == 3 && is_playing_background_music) break;
		mciSendString(_T("play background_music_3 repeat from 0"), NULL, 0, NULL);
		is_playing_background_music = true;
		temp_background_music_id = 3;
		break;
	}
}

// Õ£÷π≤•∑≈±≥æ∞“Ù¿÷
void stop_background_music() {
	switch (temp_background_music_id) {
	case 1:
		mciSendString(_T("stop background_music_1"), NULL, 0, NULL);
		is_playing_background_music = false;
		break;
	case 2:
		mciSendString(_T("stop background_music_2"), NULL, 0, NULL);
		is_playing_background_music = false;
		break;
	case 3:
		mciSendString(_T("stop background_music_3"), NULL, 0, NULL);
		is_playing_background_music = false;
		break;
	}
}



// ≤•∑≈’Ω∂∑“Ù¿÷
void play_game_music() {
	switch (game_music_id) {
	case 0:
		switch (rand() % 3 + 1) {
		case 1:
			mciSendString(_T("play game_music_1 repeat from 0"), NULL, 0, NULL);
			is_playing_game_music = true;
			temp_game_music_id = 1;
			break;
		case 2:
			mciSendString(_T("play game_music_2 repeat from 0"), NULL, 0, NULL);
			is_playing_game_music = true;
			temp_game_music_id = 2;
			break;
		case 3:
			mciSendString(_T("play game_music_3 repeat from 0"), NULL, 0, NULL);
			is_playing_game_music = true;
			temp_game_music_id = 3;
			break;
		case 4:
			mciSendString(_T("play game_music_4 repeat from 0"), NULL, 0, NULL);
			is_playing_game_music = true;
			temp_game_music_id = 4;
			break;
		case 5:
			mciSendString(_T("play game_music_5 repeat from 0"), NULL, 0, NULL);
			is_playing_game_music = true;
			temp_game_music_id = 5;
			break;
		}
		break;
	case 1:
		mciSendString(_T("play game_music_1 repeat from 0"), NULL, 0, NULL);
		is_playing_game_music = true;
		temp_game_music_id = 1;
		break;
	case 2:
		mciSendString(_T("play game_music_2 repeat from 0"), NULL, 0, NULL);
		is_playing_game_music = true;
		temp_game_music_id = 2;
		break;
	case 3:
		mciSendString(_T("play game_music_3 repeat from 0"), NULL, 0, NULL);
		is_playing_game_music = true;
		temp_game_music_id = 3;
		break;
	case 4:
		mciSendString(_T("play game_music_4 repeat from 0"), NULL, 0, NULL);
		is_playing_game_music = true;
		temp_game_music_id = 4;
		break;
	case 5:
		mciSendString(_T("play game_music_5 repeat from 0"), NULL, 0, NULL);
		is_playing_game_music = true;
		temp_game_music_id = 5;
		break;
	}
}

// Õ£÷π≤•∑≈’Ω∂∑“Ù¿÷
void stop_game_music() {
	switch (temp_game_music_id) {
	case 1:
		mciSendString(_T("stop game_music_1"), NULL, 0, NULL);
		is_playing_game_music = false;
		break;
	case 2:
		mciSendString(_T("stop game_music_2"), NULL, 0, NULL);
		is_playing_game_music = false;
		break;
	case 3:
		mciSendString(_T("stop game_music_3"), NULL, 0, NULL);
		is_playing_game_music = false;
		break;
	case 4:
		mciSendString(_T("stop game_music_4"), NULL, 0, NULL);
		is_playing_game_music = false;
		break;
	case 5:
		mciSendString(_T("stop game_music_5"), NULL, 0, NULL);
		is_playing_game_music = false;
		break;
	}
}