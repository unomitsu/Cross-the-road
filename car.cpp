#include "car.h"

car::car(VECTOR pos) {
	model_name = "./resorces/boxcar.mv1";				// 3Dモデル名の格納
	model_extend = VGet(200.0f, 200.0f, 200.0f);		// 3Dモデルの縮尺率の格納
	model_handle = MV1LoadModel(model_name.c_str());	// 3Dモデルの読み込み

	move_type = CAR_MOVE_RIGHT;
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
	// 移動量の加算
	model_position.x += speed;

	// 車の進行タイプが右の時 x座標マイナス
	if (move_type == CAR_MOVE_RIGHT) {
		// 下限に到達したときの処理
		if (model_position.x <= ROAD_LIMIT_RIGHT) {
			model_position.x = ROAD_LIMIT_LEFT;
		}
	}
	// 車の進行タイプが左の時 x座標プラス
	else {
		// 上限に到達したときの処理
		if (ROAD_LIMIT_RIGHT <= model_position.x) {
			model_position.x = ROAD_LIMIT_RIGHT;
		}
	}

	// 移動後の座標で再配置
	MV1SetPosition(model_handle, model_position);
}

void car::draw() {
	// ３Ｄモデルを描画
	MV1DrawModel(model_handle);
}

void car::draw_log() {
	printfDx("car_type[REGULAR] _handle[%d]\n", model_handle);
}

void car::finalize() {
	// モデルハンドルの削除
	MV1DeleteModel(model_handle);
}