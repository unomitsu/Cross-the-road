#pragma once
#include "DxLib.h"
#include <string>

// �Ԃ����݉\�ȓ��H�̏���Ɖ���
#define ROAD_LIMIT_LEFT		3000.0f		// ���H�̍��[
#define ROAD_LIMIT_RIGHT	-3000.0f	// ���H�̉E�[

// �Ԃ̐i�s�^�C�v
#define CAR_MOVE_LEFT		0
#define CAR_MOVE_RIGHT		1

// �Ԃ̃^�C�v
#define CAR_TYPE_REGULAR	0
#define CAR_TYPE_RORA		1

class car {
private:
	std::string model_name;		// 3D���f���̃t�@�C����
	VECTOR model_extend;		// 3D���f���̏k�ڗ�
	VECTOR model_position;		// 3D���f���̍��W

	int model_handle;			// 3D���f���̃n���h��

	float speed;				// �Ԃ̃X�s�[�h
	int move_type;				// �Ԃ̐i�s�^�C�v

public:
	float model_size;			// �Ԃ̑傫��
	bool flag;					// �L���t���O

	car();									// �^�C�g���p
	car(VECTOR pos, int move, int type);				// ���W���w�肵�č쐬
	void initialize(VECTOR pos, int move, int type);	// �����ݒ�
	void update();		// �X�V
	void draw();		// �`��
	void draw_log();	// �e�f�[�^�̕\��
	void finalize();	// ���f���f�[�^�̊J��

	VECTOR get_position();		// ���W��Ԃ�
	VECTOR get_move_vector();	// �ړ��ʂ�Ԃ� �v���C���[�ɂԂ���Ƃ��̂��
};