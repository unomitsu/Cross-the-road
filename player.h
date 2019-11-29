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

// キャラクター
#define GAME_CHARA_BOKO		0
#define GAME_CHARA_YUKARI	1
#define GAME_CHARA_PRINTSU	2

class player {

private:
	VECTOR model_extend;		// 3Dモデルの縮尺率
	VECTOR model_position;		// 3Dモデルの座標
	VECTOR model_rotation;		// 3Dモデルの回転値

	static int model_handle_boko;		// なんかしろいやつのハンドル
	static int model_handle_yukari;		// ゆかりさんのハンドル
	static int model_handle_printsu;	// ぷりんつおいげんさんのハンドル

	int model_handle;			// 3Dモデルのハンドル
	int attach_index;			// アタッチしたアニメーション番号
	int index_frame;			// アニメーションのフレーム
	
	float anim_total_time;		// アニメーションの総再生時間
	float anim_play_time;		// アニメーションの現再生時間

	int model_move_state;		// 3Dモデルの状態
	float model_move_max;		// 3Dモデルの移動量の最大値
	float model_move_value;		// 3Dモデルの移動量の現在値
	int model_move_direction;	// 3Dモデルの進行方向
	VECTOR model_move_external;	// 3Dモデルへの外力
	bool flag_control;			// 操作可能かどうか

public:
	player();							// コンストラクタ
	player(int name, VECTOR pos);		// 指定したモデルを設定
	void initialize(int name, float extendf, VECTOR pos, bool anim_load);	// 初期処理 anim_load によりアニメーションの設定有無を変更
	void update();				// 更新
	void update_anim();			// アニメーションの更新
	void update_control();		// コントローラーの更新
	void draw();				// 描画
	void draw_log();			// 各データの出力
	void finalize();			// 画像データの開放

	bool is_move();					// 移動に使うボタンのいずれかが押されていれば true を返す
	void add_vector(VECTOR vec);	// 外からの力をぶつけるやつ
	void rotation();				// ぶつかった時に回転させるやつ
	void control_off();				// 操作できなくするやつ

	VECTOR get_position();			// 3Dモデルの座標を返す
};

