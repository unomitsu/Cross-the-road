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

// �L�����N�^�[
#define GAME_CHARA_BOKO		0
#define GAME_CHARA_YUKARI	1
#define GAME_CHARA_PRINTSU	2

class player {

private:
	VECTOR model_extend;		// 3D���f���̏k�ڗ�
	VECTOR model_position;		// 3D���f���̍��W
	VECTOR model_rotation;		// 3D���f���̉�]�l

	static int model_handle_boko;		// �Ȃ񂩂��낢��̃n���h��
	static int model_handle_yukari;		// �䂩�肳��̃n���h��
	static int model_handle_printsu;	// �Ղ��������񂳂�̃n���h��

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
	bool flag_control;			// ����\���ǂ���

public:
	player();							// �R���X�g���N�^
	player(int name, VECTOR pos);		// �w�肵�����f����ݒ�
	void initialize(int name, float extendf, VECTOR pos, bool anim_load);	// �������� anim_load �ɂ��A�j���[�V�����̐ݒ�L����ύX
	void update();				// �X�V
	void update_anim();			// �A�j���[�V�����̍X�V
	void update_control();		// �R���g���[���[�̍X�V
	void draw();				// �`��
	void draw_log();			// �e�f�[�^�̏o��
	void finalize();			// �摜�f�[�^�̊J��

	bool is_move();					// �ړ��Ɏg���{�^���̂����ꂩ��������Ă���� true ��Ԃ�
	void add_vector(VECTOR vec);	// �O����̗͂��Ԃ�����
	void rotation();				// �Ԃ��������ɉ�]��������
	void control_off();				// ����ł��Ȃ�������

	VECTOR get_position();			// 3D���f���̍��W��Ԃ�
};

