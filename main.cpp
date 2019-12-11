#include "DxLib.h"
#include "game_manager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);			// �E�B���h�E���[�h�ɐݒ�
	SetWindowSizeExtendRate(1.5);	// �`���ʂ̔{��

	if (DxLib_Init() == -1) { return -1; }	// �c�w���C�u���������������A�G���[���N�����璼���ɏI��
	
	SetDrawScreen(DX_SCREEN_BACK);			// �`���𗠉�ʂɕύX

	// �y�o�b�t�@�ɑ΂���`���L���ɂ���
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);
	
	SetBackgroundColor(100, 100, 100);		// �w�i�F�ݒ�

	game_manager gm = game_manager();

	// �����L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0) {
		ClearDrawScreen();	// ��ʂ��N���A

		gm.update();
		gm.draw();

		ScreenFlip();		// ����ʂ̓��e��\��ʂɔ��f
	}

	gm.finalize();

	DxLib_End();			// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}