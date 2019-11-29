#pragma

#include "player.h"
#include "car.h"
#include "douro.h"
#include "camera.h"
#include <vector>

#define GAME_STATE_TITLE	0
#define GAME_STATE_PLAY		1
#define GAME_STATE_RESULT	2

class game_manager {
private:
	int game_state;		// ゲームの画面状態

	int game_span;		// ゲーム終了後の待機時間
	bool game_clear;	// ゲームクリアフラグ
	bool game_miss;		// ゲーム失敗フラグ

	player obj_player;			// プレイヤーインスタンス
	std::vector<car> obj_car;	// 車インスタンス
	douro obj_douro;			// 道路インスタンス
	camera obj_camera;			// カメラインスタンス

	int car_span;		// 車作成の間隔

public:
	game_manager();		// コンストラクタ
	void update();		// 更新
	void draw();		// 描画
	void finalize();	// モデルデータの開放
	void car_make();	// 車を作成したり削除したりするやつ
};