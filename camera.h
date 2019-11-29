#pragma once
#include "DxLib.h"

class camera {
private:
	VECTOR position;	// カメラの座標
	bool track;			// 追尾するかどうか

public:
	camera();					// コンストラクタ
	void update(VECTOR pos);	// カメラの座標の更新
	void draw();				// 座標軸などの描画
	void track_off();			// 追尾をやめる
};