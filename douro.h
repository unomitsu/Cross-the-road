#pragma once
#include "DxLib.h"
#include <string>

// ���݉\�Ȕ͈�
#define WORLD_LIMIT_UP		-4000.0f
#define WORLD_LIMIT_DOWN	1000.0f
#define WORLD_LIMIT_LEFT	3000.0f
#define WORLD_LIMIT_RIGHT	-1500.0f

class douro {
private:
	std::string model_name;		// 3D���f���̃t�@�C����
	VECTOR model_extend;		// 3D���f���̏k�ڗ�
	VECTOR model_position;		// 3D���f���̍��W

	int model_handle;			// 3D���f���̃n���h��

	int model_handle_udonbox;	// ���ǂ񉮂�3D���f���n���h��


public:
	douro();			// �R���X�g���N�^
	void update();		// �X�V
	void draw();		// �`��
	void draw_log();	// �e�f�[�^�̕\��
	void finalize();	// ���f���f�[�^�̊J��
};