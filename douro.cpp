#include "douro.h"

douro::douro() {
	model_name = "./resorces/Douro.mv1";				// 3Dモデル名の格納
	model_extend = VGet(5.0f, 1.0f, 4.0f);				// 3Dモデルの縮尺率の格納
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
	model_position = VGet(320.0f + 0.0f, -300.0f + -50.0f, 600.0f + -2000.0f);	// 3Dモデルの座標の格納
	MV1SetPosition(model_handle, model_position);	// 3Dモデルの3D空間への配置


	/* うどん屋 */
	model_handle_udonbox = MV1LoadModel("./resorces/udon_box.mv1");		// 3Dモデルの読み込み
	MV1SetScale(model_handle_udonbox, VGet(3.0f, 3.0f, 3.0f));			// 3Dモデルの拡大縮小
	MaterialNum = MV1GetMaterialNum(model_handle_udonbox);				// 3Dモデルの輪郭線の修正
	for (int i = 0; i < MaterialNum; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle_udonbox, i);	// マテリアルの輪郭線の太さを取得  
		MV1SetMaterialOutLineDotWidth(model_handle_udonbox, i, dotwidth / 50.0f);	// マテリアルの輪郭線の太さを拡大した分小さくする  
	}
	MV1SetPosition(model_handle_udonbox, VGet(2000.0f, -50.0f, -4000.0f));			// 3Dモデルの3D空間への配置
}

void douro::update() {
}

void douro::draw() {
	MV1DrawModel(model_handle);				// 道路
	MV1DrawModel(model_handle_udonbox);		// うどん屋

	/* 地面 */
	float pos_y = -350.0f;
	VECTOR pos1 = VGet(WORLD_LIMIT_LEFT, pos_y, WORLD_LIMIT_UP);
	VECTOR pos2 = VGet(WORLD_LIMIT_RIGHT, pos_y, WORLD_LIMIT_UP);
	VECTOR pos3 = VGet(WORLD_LIMIT_RIGHT, pos_y, WORLD_LIMIT_DOWN);
	VECTOR pos4 = VGet(WORLD_LIMIT_LEFT, pos_y, WORLD_LIMIT_DOWN);

	DrawTriangle3D(pos1, pos2, pos3, GetColor(100, 255, 100), TRUE);
	DrawTriangle3D(pos3, pos4, pos1, GetColor(100, 255, 100), TRUE);
}

void douro::draw_log() {
	printfDx("model_name[%s] _handle[%d]\n", model_name.c_str(), model_handle);
}

void douro::finalize() {
	// モデルハンドルの削除
	MV1DeleteModel(model_handle);
}