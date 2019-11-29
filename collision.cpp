
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
		t_player->add_vector(VGet(val.x, abs(val.x)/2.0f, val.z));
		return true;
	}

	return false;
}


// プレイヤーとゴールのあたり判定
bool collision_player_udonbox(player *t_player) {
	// ゴールの座標範囲
	float goal_right = 850.0f;
	float goal_down = -3400.0f;

	// プレイヤーの
	VECTOR pos = t_player->get_position();

	// 範囲内なら true を返す
	if (pos.x >= goal_right && pos.z <= goal_down) {
		return true;
	}

	// 範囲外なら false を返す
	return false;
}