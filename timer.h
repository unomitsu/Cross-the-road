#pragma once

class timer {
private:
	int time_start;		// �J�n����
	int time;			// �o�ߎ���

public:
	timer();			// �R���X�g���N�^
	void initialize();	// ������
	void update();		// �X�V
	void draw();		// �`��
};