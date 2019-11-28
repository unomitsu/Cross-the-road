#pragma once
#include "DxLib.h"
#include <string>

class douro {
private:
	std::string model_name;		// 3D���f���̃t�@�C����
	VECTOR model_extend;		// 3D���f���̏k�ڗ�
	VECTOR model_position;		// 3D���f���̍��W

	int model_handle;			// 3D���f���̃n���h��

public:
	douro();
	void update();
	void draw();
	void draw_log();
	void finalize();
};