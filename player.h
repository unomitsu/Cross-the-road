#pragma once
#include "DxLib.h"
#include <string>

// 3Dモデルの移動状態
#define PLAYER_STATE_STAND	0
#define PLAYER_STATE_START	1
#define PLAYER_STATE_RUN	2
#define PLAYER_STATE_STOP	3

// アニメーションの各開始、終了時間
#define ANIM_STAND_START	0.0f
#define ANIM_STAND_FINISH	0.0f
#define ANIM_START_START	10.0f
#define ANIM_START_FINISH	40.0f
#define ANIM_RUN_START		40.0f
#define ANIM_RUN_FINISH		220.0f
#define ANIM_STOP_START		220.0f
#define ANIM_STOP_FINISH	280.0f

class player {

private:
	std::string model_name;		// 3Dモデルのファイル名
	VECTOR model_extend;		// 3Dモデルの縮尺率
	VECTOR model_position;		// 3Dモデルの座標
	VECTOR model_rotation;		// 3Dモデルの回転値

	int model_handle;			// 3Dモデルのハンドル
	int attach_index;			// アタッチしたアニメーション番号
	int index_frame;			// アニメーションのフレーム
	
	float anim_total_time;		// アニメーションの総再生時間
	float anim_play_time;		// アニメーションの現再生時間

	int model_move_state;		// 3Dモデルの状態
	float model_move_max;		// 3Dモデルの移動量の最大値
	float model_move_value;		// 3Dモデルの移動量の現在値
	int model_move_direction;	// 3Dモデルの進行方向

public:
	player(std::string filename, float extendf, VECTOR pos);
	void update();
	void update_anim();
	void update_control();
	void draw();
	void draw_log();
	void finalize();
	bool is_move();
};

