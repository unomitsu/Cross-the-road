#pragma once
#include "DxLib.h"
#include <string>

class Player {
private:
	int model_handle;	// 3Dモデルのハンドル
	int attach_index;	// アタッチしたアニメーション番号

public:
	Player(char *filename, float extendf) {
		// 3Dモデルの読み込み
		model_handle = MV1LoadModel(filename);
		// モデルの拡大縮小
		MV1SetScale(model_handle, VGet(extendf, extendf, extendf));
		// 付属モーションのアタッチ
		attach_index = MV1AttachAnim(model_handle, 0, -1, FALSE);
		// 指定位置に移動
		MV1SetPosition(model_handle, VGet(320.0f, -300.0f, 600.0f));
	}
	void update() {

	}
	void draw() {

	}
};