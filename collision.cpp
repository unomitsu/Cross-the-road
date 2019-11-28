
#include "collision.h"
#include <cmath>

void collision_player_car(player *t_player, car *t_car) {
	float dir = 50.0f;	// 当たったことになる距離

	// 各座標を取得する
	VECTOR player_pos = t_player->get_position();
	VECTOR car_pos = t_car->get_position();

	// 距離の差の二乗
	double dir_x = pow(player_pos.x - car_pos.x, 2.0);
	double dir_y = pow(player_pos.y - car_pos.y, 2.0);
	double dir_r = pow(dir, 2.0);

	// 当たっていれば、プレイヤーに車の移動量をぶつける
	if (dir_x + dir_y <= dir_r) {
		t_player->add_vector(t_car->get_move_vector());
	}
}

