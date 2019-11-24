#include "player.h"

player::player(std::string filename, float extendf, VECTOR pos) {
	model_name = filename;								// 3Dモデル名の格納
	model_extend = extendf;								// 3Dモデルの縮尺率の格納
	model_handle = MV1LoadModel(model_name.c_str());	// 3Dモデルの読み込み

	/* ----- 3Dモデルの設定変更 ----- */

	// 3Dモデルの拡大縮小
	MV1SetScale(model_handle, VGet(extendf, extendf, extendf));
	
	// 3Dモデルの輪郭線の修正
	int MaterialNum = MV1GetMaterialNum(model_handle);
	for (int i = 0; i < MaterialNum; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle, i);	// マテリアルの輪郭線の太さを取得  
		MV1SetMaterialOutLineDotWidth(model_handle, i, dotwidth / 50.0f);	// マテリアルの輪郭線の太さを拡大した分小さくする  
	}

	/* ----- 3Dモデルの配置 原点(320.0f, -300.0f, 600.0f)とする ----- */
	model_position = VGet(320.0f + pos.x, -300.0f + pos.y, 600.0f + pos.z);		// 3Dモデルの座標の格納
	MV1SetPosition(model_handle, model_position);								// 3Dモデルの3D空間への配置

	/* ----- アニメーションの設定 ----- */
	attach_index = MV1AttachAnim(model_handle, 0, -1, FALSE);					// 付属モーションのアタッチ
	anim_total_time = MV1GetAttachAnimTotalTime(model_handle, attach_index);	// 総再生時間の取得
	anim_play_time = 0.0f;														// 再生時間の初期化
}

void player::update() {

	// 再生時間を進める
	anim_play_time += 0.5f;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (anim_play_time >= anim_total_time) { anim_play_time = 0.0f; }
	
	// 再生時間をセットする
	MV1SetAttachAnimTime(model_handle, attach_index, anim_play_time);
}

void player::draw() {
	// ３Ｄモデルを描画
	MV1DrawModel(model_handle);
}

void player::draw_log() {
	printfDx("model_name[%s] _handle[%d]\n", model_name.c_str(), model_handle);
	printfDx("model_anim_num[%d] _index[%d]\n", MV1GetAnimNum(model_handle), attach_index);
}

void player::finalize() {
	// モデルハンドルの削除
	MV1DeleteModel(model_handle);
}