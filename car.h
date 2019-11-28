#pragma once
#include "DxLib.h"
#include <string>

// �Ԃ����݉\�ȓ��H�̏���Ɖ���
#define ROAD_LIMIT_LEFT		2000.0f
#define ROAD_LIMIT_RIGHT	-2000.0f

// �Ԃ̐i�s�^�C�v
#define CAR_MOVE_LEF		0
#define CAR_MOVE_RIGHT		1


class car {
private:
	std::string model_name;		// 3D���f���̃t�@�C����
	VECTOR model_extend;		// 3D���f���̏k�ڗ�
	VECTOR model_position;		// 3D���f���̍��W

	int model_handle;			// 3D���f���̃n���h��

	float speed;				// �Ԃ̃X�s�[�h
	int move_type;				// �Ԃ̐i�s�^�C�v

public:
	car(VECTOR pos);
	void update();
	void draw();
	void draw_log();
	void finalize();

	VECTOR get_position();
	VECTOR get_move_vector();
};