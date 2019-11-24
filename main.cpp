#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	ChangeWindowMode(TRUE);			// �E�B���h�E���[�h�ɐݒ�
	SetWindowSizeExtendRate(1.5);	// �`���ʂ̔{��

	if (DxLib_Init() == -1) { return -1; }	// �c�w���C�u���������������A�G���[���N�����璼���ɏI��
	
	SetDrawScreen(DX_SCREEN_BACK);	// �`���𗠉�ʂɕύX

	// �y�o�b�t�@�ɑ΂���`���L���ɂ���
	SetUseZBufferFlag(TRUE);
	SetWriteZBufferFlag(TRUE);
	
	// �w�i�F�ݒ�
	SetBackgroundColor(100, 100, 100);

	/* ===== �������� ===== */

	// 3D���f���̓ǂݍ���
	//int model_handle1 = MV1LoadModel("./resorces/eric.mv1");
	int model_handle1 = MV1LoadModel("./resorces/yukari/yukari.pmd");
	int model_handle2 = MV1LoadModel("./resorces/bokoboko.pmd");
	int model_handle3 = MV1LoadModel("./resorces/79����^3.1/79��gv3.1.pmx");
	int model_handle_douro = MV1LoadModel("./resorces/Douro.mv1");
	
	printfDx("HANDLE1 : %d\n", model_handle1);
	printfDx("HANDLE2 : %d\n", model_handle2);
	printfDx("HANDLE3 : %d\n", model_handle3);
	printfDx("HANDLE_DOURO : %d\n", model_handle_douro);
	//printfDx("HANDLE4 : %d\n", model_handle4);

	// �X�P�[���ύX
	MV1SetScale(model_handle1, VGet(14.0f, 14.0f, 14.0f));	// model_handle1 �S����10�{
	MV1SetScale(model_handle2, VGet(25.0f, 25.0f, 25.0f));	// model_handle2 �S����20�{
	MV1SetScale(model_handle3, VGet(10.0f, 10.0f, 10.0f));	// model_handle3 �S����10�{

	// �֊s���̏C��
	int MaterialNum1 = MV1GetMaterialNum(model_handle1);
	for (int i = 0; i < MaterialNum1; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle1, i);	// �}�e���A���̗֊s���̑������擾  
		MV1SetMaterialOutLineDotWidth(model_handle1, i, dotwidth / 50.0f);	// �}�e���A���̗֊s���̑������g�債��������������  
	}
	int MaterialNum2 = MV1GetMaterialNum(model_handle2);
	for (int i = 0; i < MaterialNum2; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle2, i);	// �}�e���A���̗֊s���̑������擾  
		MV1SetMaterialOutLineDotWidth(model_handle2, i, dotwidth / 20.0f);	// �}�e���A���̗֊s���̑������g�債��������������  
	}
	int MaterialNum3 = MV1GetMaterialNum(model_handle3);
	for (int i = 0; i < MaterialNum3; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle3, i);	// �}�e���A���̗֊s���̑������擾  
		MV1SetMaterialOutLineDotWidth(model_handle3, i, dotwidth / 50.0f);	// �}�e���A���̗֊s���̑������g�債��������������  
	}

	// �摜�̓ǂݍ��݁A���H���f���̃e�N�X�`���̕ύX
	int image_handle = LoadGraph("./resorces/douro.bmp");
	printfDx("HANDLE_IMAGE : %d\n", image_handle);
	printfDx("ROAD_TEXTURE_NUM : %d\n", MV1GetTextureNum(model_handle_douro));
	
	//MV1SetTextureGraphHandle(model_handle_douro, 0, image_handle, FALSE); // �R�c���f����Y���̉�]�l���X�O�x�ɃZ�b�g����
	MV1SetScale(model_handle_douro, VGet(5.0f, 1.0f, 2.0f));	// model_handle_douro  x 2�{, z 10�{
	//MV1SetRotationXYZ(model_handle_douro, VGet(0.0f, 90.0f * DX_PI_F / 180.0f, 0.0f));

	// �A�j���[�V�����̓ǂݍ���
	int anime_run = MV1LoadModel("./resorces/runrun.mv1");
	int anime_koi = MV1LoadModel("./resorces/koi.vmd");
	printfDx("ANIME_RUN : %d\n", anime_run);
	printfDx("ANIME_KOI : %d\n", anime_koi);

	// model_handle �� anim_run_handle �A�j���[�V�����̃A�^�b�`
	int attach_index1 = MV1AttachAnim(model_handle1, 0, -1, FALSE);
	int attach_index2 = MV1AttachAnim(model_handle2, 0, -1, FALSE);
	int attach_index3 = MV1AttachAnim(model_handle3, 0, anime_run, FALSE);
	//int attach_index4 = MV1AttachAnim(model2_handle, 0, anim_koi, FALSE);

	// ��ʂɉf��ʒu�ɂR�c���f�����ړ�
	MV1SetPosition(model_handle1, VGet(320.0f, -300.0f, 600.0f));
	MV1SetPosition(model_handle2, VGet(150.0f, -300.0f, 600.0f));
	MV1SetPosition(model_handle3, VGet(500.0f, -300.0f, 600.0f));
	MV1SetPosition(model_handle_douro, VGet(1000.0f, -350.0f, -500.0f));
	//MV1SetPosition(model_handle4, VGet(1000.0f, -300.0f, 600.0f));

	// �R�c���f����`��
	MV1DrawModel(model_handle1);
	MV1DrawModel(model_handle2);
	MV1DrawModel(model_handle3);
	MV1DrawModel(model_handle_douro);
	//MV1DrawModel(model_handle4);

	// attach ����Ă���A�j���[�V�����̐����o��
	printfDx("ANIM_model1  : %d\n", MV1GetAnimNum(model_handle1));
	printfDx("ANIM_model2  : %d\n", MV1GetAnimNum(model_handle2));
	printfDx("ANIM_model3  : %d\n", MV1GetAnimNum(model_handle3));
	printfDx("NUM_ANIME1   : %d\n", MV1GetAnimNum(anime_run));
	printfDx("NUM_ANIME2   : %d\n", MV1GetAnimNum(anime_koi));
	printfDx("ATTACH_INDEX1 : %d\n", attach_index1);
	printfDx("ATTACH_INDEX2 : %d\n", attach_index2);
	printfDx("ATTACH_INDEX3 : %d\n", attach_index3);
	//printfDx("ATTACH_INDEX4 : %d\n", attach_index4);
	printfDx("WAHO : %s\n", MV1GetAnimName(model_handle1, 0));
	printfDx("WAHO : %s\n", MV1GetAnimName(model_handle2, 0));
	printfDx("WAHO : %s\n", MV1GetAnimName(model_handle3, 0));

	//
	// �J�����̍��W��������
	VECTOR CameraPos;
	CameraPos.x = 800.0f;
	CameraPos.y = 0.0f;
	CameraPos.z = 1500.0f;

	// ���H�̍��W��������
	VECTOR DouroPos = VGet(100.0f, 0.0f, -1000.0f);

	/* ===== ���C������ ===== */
	
	// ���Đ����Ԃ̎擾
	float total_time1 = MV1GetAttachAnimTotalTime(model_handle1, attach_index1);
	float total_time2 = MV1GetAttachAnimTotalTime(model_handle2, attach_index2);
	float total_time3 = MV1GetAttachAnimTotalTime(model_handle3, 0);
	printfDx("ANIME_TIME1   : %f\n", total_time1);
	printfDx("ANIME_TIME2   : %f\n", total_time2);
	printfDx("ANIME_TIME3   : %f\n", total_time3);

	printfDx("LIGHT   : %d\n", GetEnableLightHandleNum());
	
	// �Đ����Ԃ̏�����
	float play_time1 = 0.0f;
	float play_time2 = 0.0f;
	float play_time3 = 0.0f;

	ScreenFlip();
	WaitKey();

	// �����L�[��������邩�E�C���h�E��������܂Ń��[�v
	while (ProcessMessage() == 0) {
		ClearDrawScreen();	// ��ʂ��N���A

		// �Đ����Ԃ�i�߂�
		play_time1 += 0.5f;
		play_time2 += 0.5f;
		play_time3 += 0.5f;

		// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
		if (play_time1 >= total_time1) { play_time1 = 0.0f; }
		if (play_time2 >= total_time2) { play_time2 = 0.0f; }
		if (play_time3 >= total_time3) { play_time3 = 0.0f; }

		// �Đ����Ԃ��Z�b�g����
		MV1SetAttachAnimTime(model_handle1, attach_index1, play_time1);
		MV1SetAttachAnimTime(model_handle2, attach_index2, play_time2);
		MV1SetAttachAnimTime(model_handle3, attach_index3, play_time3);

		// �R�c���f���̕`��
		MV1DrawModel(model_handle1);
		MV1DrawModel(model_handle2);
		MV1DrawModel(model_handle3);
		//MV1DrawModel(model_handle4);
		
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

		/*
		// �R�c��ԏ�ɓ��H�摜��`��
		//DrawBillboard3D(VGet(320.0f, 240.0f, 100.0f), 0.5f, 0.5f, 120.0f, 0.0f, image_handle, TRUE);
		//DrawBillboard3D(DouroPos, 0.0f, 0.0f, 1000.0f, 0.5f, image_handle, FALSE);
		//DrawFormatString(100, 200, GetColor(255, 255, 255), "DOURO(%f, %f, %f)", DouroPos.x, DouroPos.y, DouroPos.z);
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			if (CheckHitKey(KEY_INPUT_UP) == 1) { DouroPos.y += 5.0f; }
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) { DouroPos.y -= 5.0f; }
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) { DouroPos.x -= 5.0f; }
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) { DouroPos.x += 5.0f; }
			if (CheckHitKey(KEY_INPUT_W) == 1) { DouroPos.z += 5.0f; }
			if (CheckHitKey(KEY_INPUT_S) == 1) { DouroPos.z -= 5.0f; }
		}
		*/
		MV1DrawModel(model_handle_douro);

		// ����ʂ̓��e��\��ʂɔ��f
		ScreenFlip();
	}

	// ���f���n���h���̍폜
	MV1DeleteModel(model_handle1);
	MV1DeleteModel(model_handle2);
	MV1DeleteModel(model_handle3);
	//MV1DeleteModel(model_handle4);

	DxLib_End();			// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}