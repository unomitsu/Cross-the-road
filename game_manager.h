#pragma

#include "player.h"
#include "car.h"
#include "douro.h"
#include "camera.h"
#include "timer.h"
#include <vector>

// ゲームの画面状態
#define GAME_STATE_TITLE	0
#define GAME_STATE_PLAY		1
#define GAME_STATE_RESULT	2

// ゲームの難易度
#define GAME_MODE_EASY		0
#define GAME_MODE_NORMAL	1
#define GAME_MODE_HARD		2

class game_manager {
private:
	int game_state;		// ゲームの画面状態
	int game_mode;		// ゲームの難易度

	int game_span;		// ゲーム終了後の待機時間
	bool game_clear;	// ゲームクリアフラグ
	bool game_miss;		// ゲーム失敗フラグ

	player obj_player;			// プレイヤーインスタンス
	std::vector<car> obj_car;	// 車インスタンス
	douro obj_douro;			// 道路インスタンス
	camera obj_camera;			// カメラインスタンス
	timer obj_timer;			// タイマー

	int car_span;		// 車作成の現間隔
	int car_interval;	// 車作成の制限間隔
	int key_span;		// キー入力の制限間隔

	int font_count_down;	// カウントダウン用のフォント

public:
	game_manager();		// コンストラクタ
	void update();		// 更新
	void draw();		// 描画
	void finalize();	// モデルデータの開放
	void car_make();	// 車を作成したり削除したりするやつ
};