#include "game_manager.h"
#include "collision.h"

game_manager::game_manager() {
	game_state = GAME_STATE_TITLE;

	game_span = 0;
	game_clear = false;
	game_miss = false;

	// 各種データを出力
	obj_player.draw_log();
	obj_player.draw();
	obj_douro.draw_log();
	obj_car.draw();
	obj_car.draw_log();

}

void game_manager::update() {
	switch (game_state) {
	case GAME_STATE_TITLE:
		obj_car.update();	// 車の移動

		// スペースキーが押されたら、ゲームへ移行
		if (game_span++ >= 30 && CheckHitKey(KEY_INPUT_SPACE) == 1) {
			// プレイヤー設定
			obj_player = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));

			// 移行処理
			clsDx();
			game_span = 0;
			game_state = GAME_STATE_PLAY;
		}
		break;
	case GAME_STATE_PLAY:
		obj_player.update();								// プレイヤーの操作
		obj_car.update();									// 車の移動
		obj_camera.update(obj_player.get_position());		// カメラの更新

		// クリアしている場合
		if (game_clear) {
			if (game_span++ >= 180) {
				// 当たったらリザルトへ移行
				game_state = GAME_STATE_RESULT;
			}
		}
		// 失敗している場合
		else if (game_miss) {
			if (game_span++ >= 180) {
				// 当たったらリザルトへ移行
				game_state = GAME_STATE_RESULT;
			}
		}
		// プレイ中の場合
		else {
			// プレイヤーとゴールのあたり判定

			// プレイヤーと車のあたり判定
			if (collision_player_car(&obj_player, &obj_car)) {
				game_miss = true;
			}
		}
		break;
	case GAME_STATE_RESULT:
		// スペースキーが押されたら、各種初期化してタイトルへ移行
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			// 各インスタンス
			obj_player = player();
			obj_car = car();
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
		DrawFormatString(250, 100, GetColor(255, 100, 100), "うどん屋へ行きたい\nスペースキーを押してはじめる.");
		break;
	case GAME_STATE_PLAY:
		break;
	case GAME_STATE_RESULT:
		if (game_clear) {}
		else if (game_miss) {
			DrawFormatString(250, 100, GetColor(255, 100, 100), "轢かれました。\nスペースキーでタイトルに戻る.");
		}
		break;
	}

	obj_player.draw();	// プレイヤークラス
	obj_car.draw();		// 車クラス
	obj_douro.draw();	// 道路クラス
	obj_camera.draw();	// カメラクラス
}

void game_manager::finalize() {
	// モデルハンドルの削除
	obj_player.finalize();
	obj_douro.finalize();
	obj_car.finalize();
}

/*
//player player1 = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));
player player1 = player("./resorces/bokoboko.pmd", 20.0f, VGet(200.0f, 0.0f, 0.0f));
//player player3 = player("./resorces/79吹雪型3.1/79磯波v3.1.pmx", 10.0f, VGet(-200.0f, 0.0f, 0.0f));
*/