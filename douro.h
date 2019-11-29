#pragma once
#include "DxLib.h"
#include <string>

// 存在可能な範囲
#define WORLD_LIMIT_UP		-4000.0f
#define WORLD_LIMIT_DOWN	1000.0f
#define WORLD_LIMIT_LEFT	3000.0f
#define WORLD_LIMIT_RIGHT	-1500.0f

class douro {
private:
	std::string model_name;		// 3Dモデルのファイル名
	VECTOR model_extend;		// 3Dモデルの縮尺率
	VECTOR model_position;		// 3Dモデルの座標

	int model_handle;			// 3Dモデルのハンドル

	int model_handle_udonbox;	// うどん屋の3Dモデルハンドル


public:
	douro();			// コンストラクタ
	void update();		// 更新
	void draw();		// 描画
	void draw_log();	// 各データの表示
	void finalize();	// モデルデータの開放
};