#include "car.h"

// モデルハンドル
int car::model_regular;
int car::model_rora;

car::car() {
	// モデルハンドルの読み込み
	model_regular = MV1LoadModel("./resorces/boxcar.mv1");
	model_rora = MV1LoadModel("./resorces/rora.mv1");

	initialize(CAR_TYPE_REGULAR, 900.0f, VGet(2000.0f, 100.0f, -1350.0f), -50.0f);
}

car::car(int type, VECTOR pos, float v) {
	car_type = type;
	switch (type) {
	case CAR_TYPE_REGULAR:
		initialize(CAR_TYPE_REGULAR, 900.0f, pos, v);
		break;
	case CAR_TYPE_RORA:
		initialize(CAR_TYPE_RORA, 3.0f, pos, v);
		model_rotation = VGet(DX_PI_F / 2, 0.0f, 0.0f);
		break;
	}
}
void car::initialize(int type, float extendf, VECTOR pos, float v) {
	// 3Dモデルの読み込み(複製)
	switch (type) {
	case CAR_TYPE_REGULAR: model_handle = MV1DuplicateModel(model_regular); break;
	case CAR_TYPE_RORA:	model_handle = MV1DuplicateModel(model_rora); break;
	}
	model_extend = VGet(extendf, extendf, extendf);		// 3Dモデルの縮尺率の格納
	flag = true;	// 有効にする

	speed = v;		// 移動量の設定

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
	model_position = VGet(pos.x, -300.0f + pos.y, pos.z);		// 3Dモデルの座標の格納
	model_rotation = VGet(0.0f, 0.0f, 0.0f);					// 3Dモデルの回転値の初期化
	MV1SetPosition(model_handle, model_position);				// 3Dモデルの3D空間への配置
}

void car::update() {
	// 移動量計算用の変数
	VECTOR value = VGet(speed, 0.0f, 0.0f);

	// 移動量の加算
	model_position = VAdd(model_position, value);

	// 上限、下限に到達したとき有効フラグを落す
	if (model_position.x > ROAD_LIMIT_LEFT || ROAD_LIMIT_RIGHT > model_position.x) {
		flag = false;
	}

	// 各車タイプごとの処理
	switch (car_type) {
	case CAR_TYPE_RORA:	model_rotation.z -= speed / 1000.0f; break;
	}

	// 移動後の座標で再配置
	MV1SetPosition(model_handle, model_position);
	MV1SetRotationXYZ(model_handle, model_rotation);
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
	return VGet(speed, 0.0f, 0.0f);
}