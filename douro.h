#pragma once
#include "DxLib.h"
#include <string>

class douro {
private:
	std::string model_name;		// 3Dモデルのファイル名
	VECTOR model_extend;		// 3Dモデルの縮尺率
	VECTOR model_position;		// 3Dモデルの座標

	int model_handle;			// 3Dモデルのハンドル

public:
	douro();
	void update();
	void draw();
	void draw_log();
	void finalize();
};