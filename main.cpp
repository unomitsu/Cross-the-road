#include "DxLib.h"
#include "game_manager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);			// ウィンドウモードに設定
	SetWindowSizeExtendRate(1.5);	// 描画画面の倍率

	if (DxLib_Init() == -1) { return -1; }	// ＤＸライブラリ初期化処理、エラーが起きたら直ちに終了
	
	SetDrawScreen(DX_SCREEN_BACK);			// 描画先を裏画面に変更

	// Ｚバッファに対する描画を有効にする
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);
	
	SetBackgroundColor(100, 100, 100);		// 背景色設定

	game_manager gm = game_manager();

	// 何かキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0) {
		ClearDrawScreen();	// 画面をクリア

		gm.update();
		gm.draw();

		ScreenFlip();		// 裏画面の内容を表画面に反映
	}

	gm.finalize();

	DxLib_End();			// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}