
#include "collision.h"
#include <cmath>

// �v���C���[�ƎԂ̊ȈՂ����蔻��
bool collision_player_car(player *t_player, car *t_car) {
	float dir = 200.0f;	// �����������ƂɂȂ鋗��

	// �e���W���擾����
	VECTOR player_pos = t_player->get_position();
	VECTOR car_pos = t_car->get_position();

	// �����̍��̓��
	double dir_x = pow(player_pos.x - car_pos.x, 2.0);
	double dir_y = pow(player_pos.z - car_pos.z, 2.0);
	double dir_r = pow(dir, 2.0);

	// �������Ă���΁A�v���C���[�ɎԂ̈ړ��ʂ��Ԃ���
	if (dir_x + dir_y <= dir_r) {
		VECTOR val = t_car->get_move_vector();
		t_player->add_vector(VGet(val.x, abs(val.x)/2.0f, val.z));
		return true;
	}

	return false;
}


// �v���C���[�ƃS�[���̂����蔻��
bool collision_player_udonbox(player *t_player) {
	// �S�[���̍��W�͈�
	float goal_right = 850.0f;
	float goal_down = -3400.0f;

	// �v���C���[��
	VECTOR pos = t_player->get_position();

	// �͈͓��Ȃ� true ��Ԃ�
	if (pos.x >= goal_right && pos.z <= goal_down) {
		return true;
	}

	// �͈͊O�Ȃ� false ��Ԃ�
	return false;
}