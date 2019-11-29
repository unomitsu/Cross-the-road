#pragma

#include "player.h"
#include "car.h"
#include "douro.h"
#include "camera.h"

#define GAME_STATE_TITLE	0
#define GAME_STATE_PLAY		1
#define GAME_STATE_RESULT	2

class game_manager {
private:
	int game_state;		// �Q�[���̉�ʏ��

	int game_span;		// �Q�[���I����̑ҋ@����
	bool game_clear;	// �Q�[���N���A�t���O
	bool game_miss;		// �Q�[�����s�t���O

	player obj_player;	// �v���C���[�C���X�^���X
	car obj_car;		// �ԃC���X�^���X
	douro obj_douro;	// ���H�C���X�^���X
	camera obj_camera;	// �J�����C���X�^���X

public:
	game_manager();
	void update();
	void draw();
	void finalize();
};