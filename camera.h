#pragma once
#include "DxLib.h"

class camera {
private:
	VECTOR position;	// �J�����̍��W
	bool track;			// �ǔ����邩�ǂ���

public:
	camera();					// �R���X�g���N�^
	void update(VECTOR pos);	// �J�����̍��W�̍X�V
	void draw();				// ���W���Ȃǂ̕`��
	void track_off();			// �ǔ�����߂�
};