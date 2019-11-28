
#include "collision.h"
#include <cmath>

void collision_player_car(player *t_player, car *t_car) {
	float dir = 50.0f;	// �����������ƂɂȂ鋗��

	// �e���W���擾����
	VECTOR player_pos = t_player->get_position();
	VECTOR car_pos = t_car->get_position();

	// �����̍��̓��
	double dir_x = pow(player_pos.x - car_pos.x, 2.0);
	double dir_y = pow(player_pos.y - car_pos.y, 2.0);
	double dir_r = pow(dir, 2.0);

	// �������Ă���΁A�v���C���[�ɎԂ̈ړ��ʂ��Ԃ���
	if (dir_x + dir_y <= dir_r) {
		t_player->add_vector(t_car->get_move_vector());
	}
}

