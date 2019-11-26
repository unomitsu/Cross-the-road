#include "camera.h"

camera::camera() {
	// �J�����̋�ԍ��W�̏�����
	position = VGet(800.0f, 240.0f, 1500.0f);
}

void camera::update() {
	// �����L�[�ŃJ�����̍��W���ړ�
	if (CheckHitKey(KEY_INPUT_LCONTROL) == 1) {
		if (CheckHitKey(KEY_INPUT_UP) == 1) { position.y += 50.0f; }
		if (CheckHitKey(KEY_INPUT_DOWN) == 1) { position.y -= 50.0f; }
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) { position.x -= 50.0f; }
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) { position.x += 50.0f; }
		if (CheckHitKey(KEY_INPUT_W) == 1) { position.z += 50.0f; }
		if (CheckHitKey(KEY_INPUT_S) == 1) { position.z -= 50.0f; }
	}

	// �J�����̈ʒu�ƒ����_���Z�b�g�A�����_�͌��_
	SetCameraPositionAndTarget_UpVecY(position, VGet(320.0f, 240.0f, 1.0f));
}

void camera::draw() {
	// ���W���̕\��  GetColor(255, 255, 255)
	DrawLine3D(VGet(-1000.0f, 0.0f, 0.0f), VGet(1000.0f, 0.0f, 0.0f), GetColor(255, 0, 0));			// x ��
	DrawLine3D(VGet(0.0f, -1000.0f, 0.0f), VGet(0.0f, 1000.0f, 0.0f), GetColor(0, 255, 0));			// y ��
	DrawLine3D(VGet(0.0f, 0.0f, -1000.0f), VGet(0.0f, 0.0f, 1000.0f), GetColor(255, 255, 255));		// z ��


	DrawFormatString(100, 100, GetColor(255, 255, 255), "CAMERA(%f, %f, %f)", position.x, position.y, position.z);
}