#include "douro.h"

douro::douro(std::string filename, VECTOR extendf, VECTOR pos) {
	model_name = filename;								// 3Dモデル名の格納
	model_extend = extendf;								// 3Dモデルの縮尺率の格納
	model_handle = MV1LoadModel(model_name.c_str());	// 3Dモデルの読み込み

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

void douro::update() {
}

void douro::draw() {
	// ３Ｄモデルを描画
	MV1DrawModel(model_handle);
}

void douro::draw_log() {
	printfDx("model_name[%s] _handle[%d]\n", model_name.c_str(), model_handle);
}

void douro::finalize() {
	// モデルハンドルの削除
	MV1DeleteModel(model_handle);
}