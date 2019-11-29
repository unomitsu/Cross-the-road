
#include "collision.h"
#include <cmath>

// プレイヤーと車の簡易あたり判定
bool collision_player_car(player *t_player, car *t_car) {
	float dir = 200.0f;	// 当たったことになる距離

	// 各座標を取得する
	VECTOR player_pos = t_player->get_position();
	VECTOR car_pos = t_car->get_position();

	// 距離の差の二乗
	double dir_x = pow(player_pos.x - car_pos.x, 2.0);
	double dir_y = pow(player_pos.z - car_pos.z, 2.0);
	double dir_r = pow(dir, 2.0);

	// 当たっていれば、プレイヤーに車の移動量をぶつける
	if (dir_x + dir_y <= dir_r) {
		VECTOR val = t_car->get_move_vector();
		printfDx("VAL %.2f", val);
		t_player->add_vector(VGet(val.x, abs(val.x), val.z));
		return true;
	}

	return false;
}

