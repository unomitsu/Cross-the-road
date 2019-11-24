#include "DxLib.h"
#include "player.h"

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
	player player1 = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));
	player player2 = player("./resorces/bokoboko.pmd", 20.0f, VGet(100.0f, 0.0f, 0.0f));
	player player3 = player("./resorces/79吹雪型3.1/79磯波v3.1.pmx", 10.0f, VGet(-100.0f, 0.0f, 0.0f));

	int model_handle_douro = MV1LoadModel("./resorces/Douro.mv1");			// 3Dモデルの読み込み
	MV1SetScale(model_handle_douro, VGet(5.0f, 1.0f, 2.0f));				// 3Dモデルの拡大  x 2倍, z 10倍
	MV1SetPosition(model_handle_douro, VGet(1000.0f, -350.0f, -500.0f));	// 3Dモデルの位置設定
	MV1DrawModel(model_handle_douro);		// 3Dモデルの描画

	printfDx("HANDLE_DOURO : %d\n", model_handle_douro);

	// カメラの座標を初期化
	VECTOR CameraPos;
	CameraPos.x = 800.0f;
	CameraPos.y = 240.0f;
	CameraPos.z = 1500.0f;

	// 道路の座標を初期化
	VECTOR DouroPos = VGet(100.0f, 0.0f, -1000.0f);

	/* ===== メイン処理 ===== */
	player1.draw_log();
	player1.draw();
	player2.draw_log();
	player2.draw();
	player3.draw_log();
	player3.draw();


	ScreenFlip();
	WaitKey();

	// 何かキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0) {
		ClearDrawScreen();	// 画面をクリア

		player1.update();
		player1.draw();
		player2.update();
		player2.draw();
		player3.update();
		player3.draw();

		/* カメラのいどう */
		// 方向キーでカメラの座標を移動
		if (CheckHitKey(KEY_INPUT_SPACE) != 1) {
			if (CheckHitKey(KEY_INPUT_UP) == 1) { CameraPos.y += 5.0f; }
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) { CameraPos.y -= 5.0f; }
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) { CameraPos.x -= 5.0f; }
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) { CameraPos.x += 5.0f; }
			if (CheckHitKey(KEY_INPUT_W) == 1) { CameraPos.z += 5.0f; }
			if (CheckHitKey(KEY_INPUT_S) == 1) { CameraPos.z -= 5.0f; }
		}

		// カメラの位置と注視点をセット、注視点は原点
		SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(320.0f, 240.0f, 1.0f));

		// 座標線っぽいの表示GetColor(255, 255, 255)
		DrawLine3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1000.0f, 0.0f, 0.0f), GetColor(255, 0, 0));	// x?
		DrawLine3D(VGet(0.0f, -1000.0f, 0.0f), VGet(0.0f, 1000.0f, 0.0f), GetColor(0, 255, 0));	// y?
		DrawLine3D(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 1000.0f), GetColor(255, 255, 255));	// z?
		DrawFormatString(100, 100, GetColor(255, 255, 255), "CAMERA(%f, %f, %f)", CameraPos.x, CameraPos.y, CameraPos.z);

		// 道路の描画
		MV1DrawModel(model_handle_douro);

		// 裏画面の内容を表画面に反映
		ScreenFlip();
	}

	// モデルハンドルの削除
	player1.finalize();
	player2.finalize();
	player3.finalize();

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}