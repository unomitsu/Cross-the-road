#pragma once
#include "DxLib.h"
#include <string>

// 車が存在可能な道路の上限と下限
#define ROAD_LIMIT_LEFT		3000.0f		// 道路の左端
#define ROAD_LIMIT_RIGHT	-3000.0f	// 道路の右端

// 車の進行タイプ
#define CAR_MOVE_LEFT		0
#define CAR_MOVE_RIGHT		1


class car {
private:
	std::string model_name;		// 3Dモデルのファイル名
	VECTOR model_extend;		// 3Dモデルの縮尺率
	VECTOR model_position;		// 3Dモデルの座標

	int model_handle;			// 3Dモデルのハンドル

	float speed;				// 車のスピード
	int move_type;				// 車の進行タイプ

public:
	bool flag;					// 有効フラグ

	car();									// タイトル用
	car(VECTOR pos, int move);				// 座標を指定して作成
	void initialize(VECTOR pos, int move);	// 初期設定
	void update();
	void draw();
	void draw_log();
	void finalize();

	VECTOR get_position();
	VECTOR get_move_vector();
};