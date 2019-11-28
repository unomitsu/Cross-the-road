#pragma once
#include "DxLib.h"
#include <string>

// 3D���f���̈ړ����
#define PLAYER_STATE_STAND	0
#define PLAYER_STATE_START	1
#define PLAYER_STATE_RUN	2
#define PLAYER_STATE_STOP	3

// �A�j���[�V�����̊e�J�n�A�I������
#define ANIM_STAND_START	0.0f
#define ANIM_STAND_FINISH	0.0f
#define ANIM_START_START	10.0f
#define ANIM_START_FINISH	40.0f
#define ANIM_RUN_START		40.0f
#define ANIM_RUN_FINISH		220.0f
#define ANIM_STOP_START		220.0f
#define ANIM_STOP_FINISH	280.0f

class player {

private:
	std::string model_name;		// 3D���f���̃t�@�C����
	VECTOR model_extend;		// 3D���f���̏k�ڗ�
	VECTOR model_position;		// 3D���f���̍��W
	VECTOR model_rotation;		// 3D���f���̉�]�l

	int model_handle;			// 3D���f���̃n���h��
	int attach_index;			// �A�^�b�`�����A�j���[�V�����ԍ�
	int index_frame;			// �A�j���[�V�����̃t���[��
	
	float anim_total_time;		// �A�j���[�V�����̑��Đ�����
	float anim_play_time;		// �A�j���[�V�����̌��Đ�����

	int model_move_state;		// 3D���f���̏��
	float model_move_max;		// 3D���f���̈ړ��ʂ̍ő�l
	float model_move_value;		// 3D���f���̈ړ��ʂ̌��ݒl
	int model_move_direction;	// 3D���f���̐i�s����
	VECTOR model_move_external;	// 3D���f���ւ̊O��

public:
	player();	// �^�C�g���p�̃R���X�g���N�^
	player(std::string filename, float extendf, VECTOR pos);							// �w�肵�����f����ݒ�
	void initialize(std::string filename, float extendf, VECTOR pos, bool anim_load);	// �������� anim_load �ɂ��A�j���[�V�����̐ݒ�L����ύX
	void update();
	void update_anim();
	void update_control();
	void draw();
	void draw_log();
	void finalize();

	bool is_move();
	void add_vector(VECTOR vec);

	VECTOR get_position();
};

