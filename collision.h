#pragma once
#include "player.h"
#include "car.h"

// �v���C���[�ƎԂ̊ȈՂ����蔻�� �������true��Ԃ�
bool collision_player_car(player *t_player, car *t_car);

// �v���C���[�ƃS�[���̂����蔻��
bool collision_player_udonbox(player *t_player);