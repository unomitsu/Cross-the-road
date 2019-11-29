
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
		printfDx("VAL %.2f", val);
		t_player->add_vector(VGet(val.x, abs(val.x), val.z));
		return true;
	}

	return false;
}

