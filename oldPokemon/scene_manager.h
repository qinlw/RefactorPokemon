#pragma once

#include "scene.h"


extern int _main(int x, int y);

extern Scene* progress_bar_scene;
extern Scene* login_registration_scene;
extern Scene* menu_scene;
extern Scene* knapsack_scene;
extern Scene* set_scene;
extern Scene* exit_scene;
extern Scene* pokemon_scene;
extern Scene* game_scene;

extern HWND hwnd;

class SceneManager {
public:
	enum class SceneType {
		ProgressBar,
		LoginRegistration,
		Menu,
		Knapscack,
		Set,
		Exit,
		Pokemon,
		Game,
	};

	void scene_set(Scene* scene) {
		current_scene = scene;
		current_scene->on_enter();
	}

	void switch_scene(SceneType type) {
		current_scene->on_exit();
		switch (type) {
		case SceneType::ProgressBar:
			current_scene = progress_bar_scene;
			break;
		case SceneType::LoginRegistration:
			current_scene = login_registration_scene;
			break;
		case SceneType::Menu:
			current_scene = menu_scene;
			break;
		case SceneType::Knapscack:
			current_scene = knapsack_scene;
			break;
		case SceneType::Set:
			current_scene = set_scene;
			break;
		case SceneType::Exit:
			current_scene = exit_scene;
			break;
		case SceneType::Pokemon: {
			if (current_scene == menu_scene) {
				RECT rect;
				if (GetWindowRect(hwnd, &rect)) 
					_main(rect.left, rect.top);
			}
			current_scene = pokemon_scene;
			break;
		}
		case SceneType::Game:
			current_scene = game_scene;
			break;
		}
		current_scene->on_enter();
	}

	void on_enter() {
		current_scene->on_enter();
	}

	void on_update(int delta) {
		current_scene->on_update(delta);
	}

	void on_draw() {
		current_scene->on_draw();
	}

	void on_input(const ExMessage& msg) {
		current_scene->on_input(msg);
	}

	void on_exit() {
		current_scene->on_exit();
	}

private:
	Scene* current_scene = nullptr;

};