#include "DxLib.h"
#include "player.h"
#include "douro.h"
#include "camera.h"
#include "car.h"
#include "collision.h"

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
	//player player1 = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));
	player player1 = player("./resorces/bokoboko.pmd", 20.0f, VGet(200.0f, 0.0f, 0.0f));
	//player player3 = player("./resorces/79����^3.1/79��gv3.1.pmx", 10.0f, VGet(-200.0f, 0.0f, 0.0f));
	
	/* ===== ���H�N���X�̐錾 ===== */
	douro big_douro = douro("./resorces/Douro.mv1", VGet(5.0f, 1.0f, 2.0f), VGet(680.0f, -50.0f, -1100.0f));
	
	/* ===== �J�����N���X�̐錾 ===== */
	camera main_camera = camera();

	// �ԃN���X
	car car_regular = car(VGet(2000.0f, 50.0f, -1350.0f));

	int handle = MV1LoadModel("./resorces/run.vmd");
	printfDx("Frame_num[%d]\n", MV1GetFrameNum(handle));
	 

	// �e��f�[�^���o��
	player1.draw_log();
	player1.draw();
	//player2.draw_log();
	//player2.draw();
	//player3.draw_log();
	//player3.draw();
	big_douro.draw_log();
	car_regular.draw();
	car_regular.draw_log();

	ScreenFlip();		// �\��ʂ֔��f
	WaitKey();			// �L�[���͑҂�������


	/* ===== ���C������ ===== */

	// �����L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0) {
		ClearDrawScreen();	// ��ʂ��N���A

		// �v���C���[�N���X
		player1.update();
		player1.draw();
		//player2.update();
		//player2.draw();
		//player3.update();
		//player3.draw();

		// ���H�N���X
		big_douro.draw();

		// �ԃN���X
		car_regular.draw();
		car_regular.update();

		// �J�����N���X
		main_camera.update();
		main_camera.draw();

		// �����蔻��
		collision_player_car(&player1, &car_regular);
		
		
		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// ���f���n���h���̍폜
	player1.finalize();
	//player2.finalize();
	//player3.finalize();
	big_douro.finalize();
	car_regular.finalize();

	DxLib_End();			// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}