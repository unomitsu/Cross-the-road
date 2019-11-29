#pragma once
#include "DxLib.h"

class camera {
private:
	VECTOR position;

public:
	camera();
	void update(VECTOR pos);
	void draw();
};