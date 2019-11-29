#pragma once
#include "DxLib.h"
#include <string>

// 車が存在可能な道路の上限と下限
#define ROAD_LIMIT_LEFT		3000.0f		// 道路の左端
#define ROAD_LIMIT_RIGHT	-3000.0f	// 道路の右端

// 車のタイプ
#define CAR_TYPE_REGULAR	0
#define CAR_TYPE_RORA		1

class car {
private:
	std::string model_name;		// 3Dモデルのファイル名
	VECTOR model_extend;		// 3Dモデルの縮尺率
	VECTOR model_position;		// 3Dモデルの座標
	VECTOR model_rotation;		// 3Dモデルの回転値

	int car_type;				// 車の種類
	int model_handle;			// 3Dモデルハンドル
	static int model_regular;	// regular car
	static int model_rora;		// rora car

	float speed;				// 車のスピード

public:
	float model_size;			// 車の大きさ
	bool flag;					// 有効フラグ

	car();						// タイトル用
	car(int type, VECTOR pos, float v);									// 座標を指定して作成
	void initialize(int type, float extendf, VECTOR pos, float v);		// 初期設定
	void update();		// 更新
	void draw();		// 描画
	void draw_log();	// 各データの表示
	void finalize();	// モデルデータの開放

	VECTOR get_position();		// 座標を返す
	VECTOR get_move_vector();	// 移動量を返す プレイヤーにぶつけるときのやつ
};