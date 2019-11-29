#include "car.h"

car::car() {
	initialize(VGet(2000.0f, 50.0f, -1350.0f), CAR_MOVE_RIGHT);
}

car::car(VECTOR pos, int move) {
	initialize(pos, move);
}
void car::initialize(VECTOR pos, int move) {
	model_name = "./resorces/boxcar.mv1";				// 3Dモデル名の格納
	model_extend = VGet(500.0f, 500.0f, 500.0f);		// 3Dモデルの縮尺率の格納
	model_handle = MV1LoadModel(model_name.c_str());	// 3Dモデルの読み込み
	flag = true;	// 有効にする

	move_type = move;
	speed = -20.0f;

	/* ----- 3Dモデルの設定変更 ----- */

	// 3Dモデルの拡大縮小
	MV1SetScale(model_handle, model_extend);

	// 3Dモデルの輪郭線の修正
	int MaterialNum = MV1GetMaterialNum(model_handle);
	for (int i = 0; i < MaterialNum; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle, i);	// マテリアルの輪郭線の太さを取得  
		MV1SetMaterialOutLineDotWidth(model_handle, i, dotwidth / 50.0f);	// マテリアルの輪郭線の太さを拡大した分小さくする  
	}

	/* ----- 3Dモデルの配置 原点(320.0f, -300.0f, 600.0f)とする ----- */
	model_position = VGet(320.0f + pos.x, -300.0f + pos.y, 600.0f + pos.z);		// 3Dモデルの座標の格納
	MV1SetPosition(model_handle, model_position);								// 3Dモデルの3D空間への配置
}

void car::update() {
	// 車の進行タイプが右の時 x座標マイナス
	if (move_type == CAR_MOVE_RIGHT) {
		// 移動量の加算
		model_position.x += speed;

		// 下限に到達したとき、有効フラグを落す
		if (model_position.x < ROAD_LIMIT_RIGHT) {
			flag = false;
		}
	}
	// 車の進行タイプが左の時 x座標プラス
	else {
		// 移動量の加算
		model_position.x -= speed;

		// 上限に到達したとき、有効フラグを落す
		if (ROAD_LIMIT_LEFT < model_position.x) {
			flag = false;
		}
	}

	// 移動後の座標で再配置
	MV1SetPosition(model_handle, model_position);
}

void car::draw() {
	// ３Ｄモデルを描画
	MV1DrawModel(model_handle);
	
	// DrawFormatString(10, 250, GetColor(255, 255, 255), "Pos(%.2f, %.2f, %.2f)\n", model_position.x, model_position.y, model_position.z);		// 3Dモデルの空間座標
	// DrawFormatString(10, 270, GetColor(255, 255, 255), "move_value[%.2f]\n", speed);
}

void car::draw_log() {
	printfDx("car_type[REGULAR] _handle[%d]\n", model_handle);
}

void car::finalize() {
	// モデルハンドルの削除
	MV1DeleteModel(model_handle);
}

// 車の座標を VECTOR 型で取得する
VECTOR car::get_position() {
	return model_position;
}

// 車の移動量を VECTOR 型で取得する
VECTOR car::get_move_vector() {
	if (move_type == CAR_MOVE_LEFT) {
		return VGet(speed, 0.0f, 0.0f);
	}
	return VGet(-speed, 0.0f, 0.0f);
}