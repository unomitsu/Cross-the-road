#include "game_manager.h"
#include "collision.h"

game_manager::game_manager() {
	game_state = GAME_STATE_TITLE;

	game_span = 0;
	game_clear = false;
	game_miss = false;

	car_span = 0;
	key_span = 0;

	// 車一個挿入
	obj_car.push_back(car());

	// フォントデータ
	font_count_down = CreateFontToHandle(NULL, 100, 10, -1);



	/*
	// 各種データを出力
	obj_player.draw_log();
	obj_player.draw();
	obj_douro.draw_log();
	obj_car.at(0).draw();
	obj_car.at(0).draw_log();
	*/
}

void game_manager::update() {
	switch (game_state) {
	case GAME_STATE_TITLE:
		for (unsigned int i = 0; i < obj_car.size(); i++) {
			obj_car.at(i).update();							// 車の移動
		}

		// 難易度の選択
		if (key_span++ > 10) {
			if (CheckHitKey(KEY_INPUT_UP) == 1) {
				key_span = 0;
				if (--game_mode < 0) { game_mode = GAME_MODE_HARD; }
			}
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
				key_span = 0;
				if (++game_mode > GAME_MODE_HARD) { game_mode = GAME_MODE_EASY; }
			}
		}

		// スペースキーが押されたら、ゲームへ移行
		if (game_span++ >= 30 && CheckHitKey(KEY_INPUT_SPACE) == 1) {
			// プレイヤー設定
			obj_player = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));

			// 難易度による、車の数の設定
			switch (game_mode) {
			case GAME_MODE_EASY: car_interval = 30; break;
			case GAME_MODE_NORMAL: car_interval = 10; break;
			case GAME_MODE_HARD: car_interval = 2; break;
			}

			// 移行処理
			clsDx();
			key_span = 0;
			game_span = 0;
			game_state = GAME_STATE_PLAY;
		}
		break;
	case GAME_STATE_PLAY:
		if (key_span++ > 180) {
			obj_player.update();							// プレイヤーの操作
			obj_timer.update();								// タイマーの更新
		}
		else {
			obj_timer.initialize();							// タイマーの初期化
		}
		for (unsigned int i = 0; i < obj_car.size(); i++) {
			obj_car.at(i).update();							// 車の移動
		}
		obj_camera.update(obj_player.get_position());		// カメラの更新

		// クリアしている場合
		if (game_clear) {
			// 当たったらリザルトへ移行
			game_state = GAME_STATE_RESULT;
		}
		// 失敗している場合
		else if (game_miss) {
			// プレイヤーぐるぐる
			obj_player.rotation();

			// しばらく待ってからリザルトへ移行
			if (game_span++ >= 180) {
				game_state = GAME_STATE_RESULT;
			}
		}
		// プレイ中の場合
		else {
			// プレイヤーとゴールのあたり判定
			if (collision_player_udonbox(&obj_player)) {
				game_clear = true;
			}
			// プレイヤーと車たちのあたり判定
			for (unsigned int i = 0; i < obj_car.size(); i++) {
				if (collision_player_car(&obj_player, &obj_car.at(i))) {
					game_miss = true;
					obj_player.control_off();
					obj_camera.track_off();
				}
			}
		}
		
		// 車の追加
		car_make();

		break;
	case GAME_STATE_RESULT:
		// スペースキーが押されたら、各種初期化してタイトルへ移行
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			// 各インスタンス
			obj_player = player();
			obj_car.clear();
			obj_car.push_back(car());
			obj_douro = douro();
			obj_camera = camera();
			
			// ゲームクリアの判定変数
			game_span = 0;
			game_clear = false;
			game_miss = false;

			game_state = GAME_STATE_TITLE;
		}
		break;
	}

}

void game_manager::draw() {
	switch (game_state) {
	case GAME_STATE_TITLE:
		DrawFormatString(200, 100, GetColor(0, 0, 0), "うどん屋へ行きたい\nスペースキーを押してはじめる.");
		DrawFormatString(200, 200, GetColor(0, 0, 0), "かんたん");
		DrawFormatString(200, 220, GetColor(0, 0, 0), "ふつう");
		DrawFormatString(200, 240, GetColor(0, 0, 0), "むずかしい");
		DrawFormatString(160, 200 + game_mode * 20, GetColor(0, 0, 0), "->");
		break;
	case GAME_STATE_PLAY:
		// カウントダウン
		if (key_span <= 60) { key_span++; }
		else if (key_span <= 120) { DrawStringToHandle(200, 100, "3", GetColor(255, 0, 0), font_count_down); key_span++; }
		else if (key_span <= 180) { DrawStringToHandle(200, 100, "2", GetColor(255, 0, 0), font_count_down); }
		else if (key_span <= 240) { DrawStringToHandle(200, 100, "1", GetColor(255, 0, 0), font_count_down); }

		// ゲームモード表示
		switch (game_mode) {
		case GAME_MODE_EASY: DrawFormatString(10, 10, GetColor(255, 255, 255), "MODE[ EASY ]"); break;
		case GAME_MODE_NORMAL: DrawFormatString(10, 10, GetColor(255, 255, 255), "MODE[ NORMAL ]"); break;
		case GAME_MODE_HARD: DrawFormatString(10, 10, GetColor(255, 255, 255), "MODE[ HARD ]"); break;
		}

		// タイマー表示
		obj_timer.draw();

		break;
	case GAME_STATE_RESULT:
		if (game_clear) {
			DrawFormatString(250, 100, GetColor(255, 100, 100), "うどんおいしい！\nスペースキーでタイトルに戻る.");
		}
		else if (game_miss) {
			DrawFormatString(250, 100, GetColor(255, 100, 100), "轢かれました。\nスペースキーでタイトルに戻る.");
		}
		break;
	}

	obj_player.draw();				// プレイヤークラス
	for (unsigned int i = 0; i < obj_car.size(); i++) {
		obj_car.at(i).draw();		// 車クラス
	}
	obj_douro.draw();				// 道路クラス
	obj_camera.draw();				// カメラクラス
}

void game_manager::finalize() {
	// モデルハンドルの削除
	obj_player.finalize();
	obj_douro.finalize();
	for (unsigned int i = 0; i < obj_car.size(); i++) {
		obj_car.at(i).finalize();
	}

	// フォントデータの削除
	DeleteFontToHandle(font_count_down);
}

/*
//player player1 = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));
player player1 = player("./resorces/bokoboko.pmd", 20.0f, VGet(200.0f, 0.0f, 0.0f));
//player player3 = player("./resorces/79吹雪型3.1/79磯波v3.1.pmx", 10.0f, VGet(-200.0f, 0.0f, 0.0f));
*/

void game_manager::car_make() {
	const float road_far_left = -3100.0f;		// 奥側の道路の左車線
	const float road_far_right = -2500.0f;		// 奥側の道路の右車線
	const float road_this_left = -800.0f;		// 手前側の道路の左車線
	const float road_this_right = -1300.0f;		// 手前側の道路の右車線

	// 指定した間隔が経過したら車を追加する
	if (car_span++ >= car_interval) {
		switch (GetRand(3)) {
		case 0:		// 奥側の左
			obj_car.push_back(car(VGet(ROAD_LIMIT_LEFT, 100.0f, road_far_left), CAR_MOVE_RIGHT));
			break;
		case 1:		// 奥側の右
			obj_car.push_back(car(VGet(ROAD_LIMIT_LEFT, 100.0f, road_far_right), CAR_MOVE_RIGHT));
			break;
		case 2:		// 手前側の右
			obj_car.push_back(car(VGet(ROAD_LIMIT_RIGHT, 100.0f, road_this_right), CAR_MOVE_LEFT));
			break;
		case 3:		// 手前側の左
			obj_car.push_back(car(VGet(ROAD_LIMIT_RIGHT, 100.0f, road_this_left), CAR_MOVE_LEFT));
			break;
		}

		// 間隔を元に戻す
		car_span = 0;
	}

	// 無効な車を削除する
	for (auto itr = obj_car.begin(); itr != obj_car.end();) {
		if (itr->flag) { itr++; }
		else {
			itr->finalize();
			itr = obj_car.erase(itr);
		}
	}
}