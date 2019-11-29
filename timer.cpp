#include "timer.h"
#include "DxLib.h"

timer::timer() {
	initialize();
}

void timer::initialize() {
	time_start = GetNowCount();		// 現在経過時間を得る
	time = 0.0f;					// 現在時間の初期化
}

void timer::update() {
	// 開始時刻と現在時刻の差を格納する
	time = GetNowCount() - time_start;
}

void timer::draw() {
	// 経過時間を描画
	DrawFormatString(250, 10, GetColor(255, 100, 100), "%d", time);
}
