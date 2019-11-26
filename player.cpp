#include "player.h"

player::player(std::string filename, float extendf, VECTOR pos) {
	model_name = filename;								// 3Dモデル名の格納
	model_extend = VGet(extendf, extendf, extendf);		// 3Dモデルの縮尺率の格納
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

	/* ----- 3Dモデルの配置 ----- */											// 原点(320.0f, -300.0f, 600.0f)とする
	model_position = VGet(320.0f + pos.x, -250.0f + pos.y, 600.0f + pos.z);		// 3Dモデルの座標の格納
	model_rotation = VGet(0.0f, 0.0f, 0.0f);									// 3Dモデルの回転値の格納
	MV1SetPosition(model_handle, model_position);								// 3Dモデルの3D空間への配置

	/* ----- アニメーションの設定 ----- */
	attach_index = MV1AttachAnim(model_handle, 0, -1, FALSE);					// 付属モーションのアタッチ
	anim_total_time = MV1GetAttachAnimTotalTime(model_handle, attach_index);	// 総再生時間の取得
	anim_play_time = 0.0f;														// 再生時間の初期化

	/* ----- 移動関連の設定 ----- */
	model_move_state = PLAYER_STATE_STAND;	// 初期状態を設定する
	model_move_max = 20.0f;					// 移動量の最大値を格納
	model_move_value = 0.0f;				// 移動量の現在値を格納

	// アニメーションによるローカルの座標移動を無効にする
	MV1SetFrameUserLocalMatrix(model_handle, MV1SearchFrame(model_handle, "センター"), MGetIdent());
	//MV1SetFrameUserLocalMatrix(model_handle, MV1SearchFrame(model_handle, "グルーブ"), MGetIdent());
}

// プレイヤーの更新
void player::update() {
	// コントローラーの更新
	update_control();

	// アニメーションの更新
	update_anim();

	// 3Dモデルの3D空間への再配置
	MV1SetPosition(model_handle, model_position);
	MV1SetRotationXYZ(model_handle, model_rotation);

	// 座標と向きの出力
	DrawFormatString(200, 150, GetColor(255, 255, 255), "Pos(%.2f, %.2f, %.2f)\n", model_position.x, model_position.y, model_position.z);
	DrawFormatString(200, 150, GetColor(255, 255, 255), "Rot(%.2f, %.2f, %.2f)\n", model_rotation.x, model_rotation.y, model_rotation.z);

}

// プレイヤーのアニメーションの更新
void player::update_anim() {
	// 再生時間を進める.  もし変更があれば、以下のswitch文内で上書きする
	anim_play_time += 0.5f;

	switch (model_move_state) {
	// 「待機」
	case PLAYER_STATE_STAND:
		// キー押なら、「走り出し」に移行
		if (is_move()) {
			model_move_state = PLAYER_STATE_START;
			anim_play_time = ANIM_START_START;
		}
		// キー離なら、「待機」を継続
		else {
			anim_play_time = ANIM_STAND_START;
		}
		break;
	// 「走り出し」
	case PLAYER_STATE_START:
		// キー押なら、「走り出し」を進める
		if (is_move()) {

			// 「走り出し」が終了したら「走る」に移行
			if (ANIM_START_FINISH <= anim_play_time) {
				model_move_state = PLAYER_STATE_RUN;
				anim_play_time = ANIM_RUN_START;
			}
		}
		// キー離なら、「停止」に移行
		else {
			model_move_state = PLAYER_STATE_STOP;
			anim_play_time = ANIM_STOP_START;
		}
		
		break;
	// 「走る」
	case PLAYER_STATE_RUN:
		// キー押なら、「走る」を進める
		if (is_move()) {
			// 「走る」が終了したら、「走る」の初めに戻る
			if (ANIM_RUN_FINISH <= anim_play_time) {
				model_move_state = PLAYER_STATE_RUN;
				anim_play_time = ANIM_RUN_START;
			}
		}
		// キー離なら、「停止」に移行
		else {
			model_move_state = PLAYER_STATE_STOP;
			anim_play_time = ANIM_STOP_START;
		}
		break;
	// 「停止」
	case PLAYER_STATE_STOP:
		// キー押なら、「走り出し」に移行
		if (is_move()) {
			model_move_state = PLAYER_STATE_START;
			anim_play_time = ANIM_START_START;
		}
		// キー離なら、「停止」を継続
		else {
			// 「停止」が終了したら、「待機」に戻る
			if (ANIM_STOP_FINISH <= anim_play_time) {
				model_move_state = PLAYER_STATE_STAND;
				anim_play_time = ANIM_STAND_START;
			}
		}
		break;
	}
	// 再生時間をセットする
	MV1SetAttachAnimTime(model_handle, attach_index, anim_play_time);
}

// プレイヤーの移動操作の更新
void player::update_control() {
	// 最近の移動方向を格納
	if (CheckHitKey(KEY_INPUT_UP) == 1) { model_move_direction = 1; }		// 前 1
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) { model_move_direction = 2; }	// 右 2
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) { model_move_direction = 3; }		// 後 3
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) { model_move_direction = 4; }		// 左 4


	// 待機状態の時、移動量を初期化する
	if (model_move_state == PLAYER_STATE_STAND) {
		model_move_value = 0.0f;
	}
	// 停止状態の時、移動量を減少させていく
	else if (model_move_state == PLAYER_STATE_STOP) {
		model_move_value -= 0.25f;

		// 最小値を超えた時の調整
		if (model_move_value < 0.0f) { model_move_value = 0.0f; }
	}
	// その他の時、移動量を増加させていく
	else {
		model_move_value += 0.25f;
		
		// 最大値を超えた時の調整
		if (model_move_max < model_move_value) { model_move_value = model_move_max; }
	}


	// 移動量と回転値の更新を行う
	// -- 前への移動
	if (CheckHitKey(KEY_INPUT_UP) == 1) {
		model_rotation.y = 0.0f;
		model_position.z -= model_move_value;
	}
	// -- 右への移動
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
		model_rotation.y = DX_PI_F / 2;
		model_position.x -= model_move_value;
	}
	// -- 後への移動
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
		model_rotation.y = DX_PI_F;
		model_position.z += model_move_value;
	}
	// -- 左への移動
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
		model_rotation.y = DX_PI_F * 3 / 2;
		model_position.x += model_move_value;
	}
	// 移動していない場合
	if (!is_move()) {
		// 「走り出し」「停止」の場合の移動量の加算
		if (model_move_state == PLAYER_STATE_START || model_move_state == PLAYER_STATE_STOP) {
			switch (model_move_direction) {
			case 1:	model_position.z -= model_move_value;	break;
			case 2:	model_position.x -= model_move_value;	break;
			case 3:	model_position.z += model_move_value;	break;
			case 4:	model_position.x += model_move_value;	break;
			}
		}
	}
	DrawFormatString(200, 180, GetColor(255, 255, 255), "move_value[%.2f]\n", model_move_value);
}

// 3Dモデルの描画
void player::draw() {
	// ３Ｄモデルを描画
	MV1DrawModel(model_handle);
	
	// 現座標に球を描画
	DrawSphere3D(model_position, 8.0f, 16, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

	std::string str;
	switch (model_move_state) {
	case PLAYER_STATE_STAND: str = "STATE_STAND"; break;
	case PLAYER_STATE_START: str = "STATE_START"; break;
	case PLAYER_STATE_RUN: str = "STATE_RUN"; break;
	case PLAYER_STATE_STOP:	str = "STATE_STOP"; break;
	}
	DrawFormatString(200, 200, GetColor(255, 255, 255), "%s _play_time[%f]\n", str.c_str(), anim_play_time);
}

// 3Dモデルの各データの出力
void player::draw_log() {
	printfDx("model_name[%s] _handle[%d]\n", model_name.c_str(), model_handle);
	printfDx("model_anim_num[%d] _index[%d]\n", MV1GetAnimNum(model_handle), attach_index);
}

// プレイヤークラスの終了処理
void player::finalize() {
	// モデルハンドルの削除
	MV1DeleteModel(model_handle);
}

// プレイヤーが動いているかの真偽を返す
bool player::is_move() {
	return (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1 || CheckHitKey(KEY_INPUT_LEFT) == 1);
}