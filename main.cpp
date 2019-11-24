#include "DxLib.h"
#include "player.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);			// �E�B���h�E���[�h�ɐݒ�
	SetWindowSizeExtendRate(1.5);	// �`���ʂ̔{��

	if (DxLib_Init() == -1) { return -1; }	// �c�w���C�u���������������A�G���[���N�����璼���ɏI��
	
	SetDrawScreen(DX_SCREEN_BACK);			// �`���𗠉�ʂɕύX

	// �y�o�b�t�@�ɑ΂���`���L���ɂ���
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);
	
	SetBackgroundColor(100, 100, 100);		// �w�i�F�ݒ�

	/* ===== �v���C���[�N���X�̐錾 ===== */
	player player1 = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));
	player player2 = player("./resorces/bokoboko.pmd", 20.0f, VGet(100.0f, 0.0f, 0.0f));
	player player3 = player("./resorces/79����^3.1/79��gv3.1.pmx", 10.0f, VGet(-100.0f, 0.0f, 0.0f));

	int model_handle_douro = MV1LoadModel("./resorces/Douro.mv1");			// 3D���f���̓ǂݍ���
	MV1SetScale(model_handle_douro, VGet(5.0f, 1.0f, 2.0f));				// 3D���f���̊g��  x 2�{, z 10�{
	MV1SetPosition(model_handle_douro, VGet(1000.0f, -350.0f, -500.0f));	// 3D���f���̈ʒu�ݒ�
	MV1DrawModel(model_handle_douro);		// 3D���f���̕`��

	printfDx("HANDLE_DOURO : %d\n", model_handle_douro);

	// �J�����̍��W��������
	VECTOR CameraPos;
	CameraPos.x = 800.0f;
	CameraPos.y = 240.0f;
	CameraPos.z = 1500.0f;

	// ���H�̍��W��������
	VECTOR DouroPos = VGet(100.0f, 0.0f, -1000.0f);

	/* ===== ���C������ ===== */
	player1.draw_log();
	player1.draw();
	player2.draw_log();
	player2.draw();
	player3.draw_log();
	player3.draw();


	ScreenFlip();
	WaitKey();

	// �����L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0) {
		ClearDrawScreen();	// ��ʂ��N���A

		player1.update();
		player1.draw();
		player2.update();
		player2.draw();
		player3.update();
		player3.draw();

		/* �J�����̂��ǂ� */
		// �����L�[�ŃJ�����̍��W���ړ�
		if (CheckHitKey(KEY_INPUT_SPACE) != 1) {
			if (CheckHitKey(KEY_INPUT_UP) == 1) { CameraPos.y += 5.0f; }
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) { CameraPos.y -= 5.0f; }
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) { CameraPos.x -= 5.0f; }
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) { CameraPos.x += 5.0f; }
			if (CheckHitKey(KEY_INPUT_W) == 1) { CameraPos.z += 5.0f; }
			if (CheckHitKey(KEY_INPUT_S) == 1) { CameraPos.z -= 5.0f; }
		}

		// �J�����̈ʒu�ƒ����_���Z�b�g�A�����_�͌��_
		SetCameraPositionAndTarget_UpVecY(CameraPos, VGet(320.0f, 240.0f, 1.0f));

		// ���W�����ۂ��̕\��GetColor(255, 255, 255)
		DrawLine3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1000.0f, 0.0f, 0.0f), GetColor(255, 0, 0));	// x?
		DrawLine3D(VGet(0.0f, -1000.0f, 0.0f), VGet(0.0f, 1000.0f, 0.0f), GetColor(0, 255, 0));	// y?
		DrawLine3D(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 1000.0f), GetColor(255, 255, 255));	// z?
		DrawFormatString(100, 100, GetColor(255, 255, 255), "CAMERA(%f, %f, %f)", CameraPos.x, CameraPos.y, CameraPos.z);

		// ���H�̕`��
		MV1DrawModel(model_handle_douro);

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// ���f���n���h���̍폜
	player1.finalize();
	player2.finalize();
	player3.finalize();

	DxLib_End();			// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}