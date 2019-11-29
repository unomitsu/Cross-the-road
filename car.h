#pragma once
#include "DxLib.h"
#include <string>

// 車が存在可能な道路の上限と下限
#define ROAD_LIMIT_LEFT		3000.0f		// 道路の左端
#define ROAD_LIMIT_RIGHT	-3000.0f	// 道路の右端

// 車の進行タイプ
#define CAR_MOVE_LEFT		0
#define CAR_MOVE_RIGHT		1

// 車のタイプ
#define CAR_TYPE_REGULAR	0
#define CAR_TYPE_RORA		1

class car {
private:
	std::string model_name;		// 3Dモデルのファイル名
	VECTOR model_extend;		// 3Dモデルの縮尺率
	VECTOR model_position;		// 3Dモデルの座標

	int model_handle;			// 3Dモデルのハンドル

	float speed;				// 車のスピード
	int move_type;				// 車の進行タイプ

public:
	float model_size;			// 車の大きさ
	bool flag;					// 有効フラグ

	car();									// タイトル用
	car(VECTOR pos, int move, int type);				// 座標を指定して作成
	void initialize(VECTOR pos, int move, int type);	// 初期設定
	void update();		// 更新
	void draw();		// 描画
	void draw_log();	// 各データの表示
	void finalize();	// モデルデータの開放

	VECTOR get_position();		// 座標を返す
	VECTOR get_move_vector();	// 移動量を返す プレイヤーにぶつけるときのやつ
};