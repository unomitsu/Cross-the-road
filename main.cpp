#include "DxLib.h"
#include "player.h"
#include "douro.h"
#include "camera.h"
#include "car.h"
#include "collision.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);			// ウィンドウモードに設定
	SetWindowSizeExtendRate(1.5);	// 描画画面の倍率

	if (DxLib_Init() == -1) { return -1; }	// ＤＸライブラリ初期化処理、エラーが起きたら直ちに終了
	
	SetDrawScreen(DX_SCREEN_BACK);			// 描画先を裏画面に変更

	// Ｚバッファに対する描画を有効にする
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);
	
	SetBackgroundColor(100, 100, 100);		// 背景色設定


	/* ===== プレイヤークラスの宣言 ===== */
	//player player1 = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));
	player player1 = player("./resorces/bokoboko.pmd", 20.0f, VGet(200.0f, 0.0f, 0.0f));
	//player player3 = player("./resorces/79吹雪型3.1/79磯波v3.1.pmx", 10.0f, VGet(-200.0f, 0.0f, 0.0f));
	
	/* ===== 道路クラスの宣言 ===== */
	douro big_douro = douro("./resorces/Douro.mv1", VGet(5.0f, 1.0f, 2.0f), VGet(680.0f, -50.0f, -1100.0f));
	
	/* ===== カメラクラスの宣言 ===== */
	camera main_camera = camera();

	// 車クラス
	car car_regular = car(VGet(2000.0f, 50.0f, -1350.0f));

	int handle = MV1LoadModel("./resorces/run.vmd");
	printfDx("Frame_num[%d]\n", MV1GetFrameNum(handle));
	 

	// 各種データを出力
	player1.draw_log();
	player1.draw();
	//player2.draw_log();
	//player2.draw();
	//player3.draw_log();
	//player3.draw();
	big_douro.draw_log();
	car_regular.draw();
	car_regular.draw_log();

	ScreenFlip();		// 表画面へ反映
	WaitKey();			// キー入力待ちをする


	/* ===== メイン処理 ===== */

	// 何かキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0) {
		ClearDrawScreen();	// 画面をクリア

		// プレイヤークラス
		player1.update();
		player1.draw();
		//player2.update();
		//player2.draw();
		//player3.update();
		//player3.draw();

		// 道路クラス
		big_douro.draw();

		// 車クラス
		car_regular.draw();
		car_regular.update();

		// カメラクラス
		main_camera.update();
		main_camera.draw();

		// あたり判定
		collision_player_car(&player1, &car_regular);
		
		
		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// モデルハンドルの削除
	player1.finalize();
	//player2.finalize();
	//player3.finalize();
	big_douro.finalize();
	car_regular.finalize();

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}