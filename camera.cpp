#include "camera.h"

camera::camera() {
	// カメラの空間座標の初期化
	position = VGet(800.0f, 240.0f, 1500.0f);
}

void camera::update() {
	// 方向キーでカメラの座標を移動
	if (CheckHitKey(KEY_INPUT_LCONTROL) == 1) {
		if (CheckHitKey(KEY_INPUT_UP) == 1) { position.y += 50.0f; }
		if (CheckHitKey(KEY_INPUT_DOWN) == 1) { position.y -= 50.0f; }
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) { position.x -= 50.0f; }
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) { position.x += 50.0f; }
		if (CheckHitKey(KEY_INPUT_W) == 1) { position.z += 50.0f; }
		if (CheckHitKey(KEY_INPUT_S) == 1) { position.z -= 50.0f; }
	}

	// カメラの位置と注視点をセット、注視点は原点
	SetCameraPositionAndTarget_UpVecY(position, VGet(320.0f, 240.0f, 1.0f));
}

void camera::draw() {
	// 座標線の表示  GetColor(255, 255, 255)
	DrawLine3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1000.0f, 0.0f, 0.0f), GetColor(255, 0, 0));			// x 赤
	DrawLine3D(VGet(0.0f, -1000.0f, 0.0f), VGet(0.0f, 1000.0f, 0.0f), GetColor(0, 255, 0));			// y 青
	DrawLine3D(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 1000.0f), GetColor(255, 255, 255));		// z 緑


	DrawFormatString(100, 100, GetColor(255, 255, 255), "CAMERA(%f, %f, %f)", position.x, position.y, position.z);
}