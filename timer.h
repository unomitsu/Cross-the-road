#pragma once

class timer {
private:
	int time_start;		// 開始時間
	int time;			// 経過時間

public:
	timer();			// コンストラクタ
	void initialize();	// 初期化
	void update();		// 更新
	void draw();		// 描画
};