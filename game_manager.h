#pragma

#include "player.h"
#include "car.h"
#include "douro.h"
#include "camera.h"
#include <vector>

#define GAME_STATE_TITLE	0
#define GAME_STATE_PLAY		1
#define GAME_STATE_RESULT	2

class game_manager {
private:
	int game_state;		// �Q�[���̉�ʏ��

	int game_span;		// �Q�[���I����̑ҋ@����
	bool game_clear;	// �Q�[���N���A�t���O
	bool game_miss;		// �Q�[�����s�t���O

	player obj_player;			// �v���C���[�C���X�^���X
	std::vector<car> obj_car;	// �ԃC���X�^���X
	douro obj_douro;			// ���H�C���X�^���X
	camera obj_camera;			// �J�����C���X�^���X

	int car_span;		// �ԍ쐬�̊Ԋu

public:
	game_manager();		// �R���X�g���N�^
	void update();		// �X�V
	void draw();		// �`��
	void finalize();	// ���f���f�[�^�̊J��
	void car_make();	// �Ԃ��쐬������폜�����肷����
};