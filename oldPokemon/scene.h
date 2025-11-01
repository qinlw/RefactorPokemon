#pragma once

#include <graphics.h>
#include <iostream>
#include <cmath>

using std::string;


class Scene {
public:
	virtual void on_enter() {};
	virtual void on_update(int delta) {};
	virtual void on_draw() {};
	virtual void on_input(const ExMessage& msg) {};
	virtual void on_exit() {};

};
