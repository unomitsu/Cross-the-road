#pragma once
#include "DxLib.h"

class camera {
private:
	VECTOR position;

public:
	camera();
	void update();
	void draw();
};