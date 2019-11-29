#pragma once
#include "player.h"
#include "car.h"

// プレイヤーと車の簡易あたり判定 当たるとtrueを返す
bool collision_player_car(player *t_player, car *t_car);

// プレイヤーとゴールのあたり判定
bool collision_player_udonbox(player *t_player);