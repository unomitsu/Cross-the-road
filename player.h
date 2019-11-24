#pragma once
#include "DxLib.h"
#include <string>

class Player {
private:
	int model_handle;	// 3D���f���̃n���h��
	int attach_index;	// �A�^�b�`�����A�j���[�V�����ԍ�

public:
	Player(char *filename, float extendf) {
		// 3D���f���̓ǂݍ���
		model_handle = MV1LoadModel(filename);
		// ���f���̊g��k��
		MV1SetScale(model_handle, VGet(extendf, extendf, extendf));
		// �t�����[�V�����̃A�^�b�`
		attach_index = MV1AttachAnim(model_handle, 0, -1, FALSE);
		// �w��ʒu�Ɉړ�
		MV1SetPosition(model_handle, VGet(320.0f, -300.0f, 600.0f));
	}
	void update() {

	}
	void draw() {

	}
};