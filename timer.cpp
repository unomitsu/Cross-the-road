#include "timer.h"
#include "DxLib.h"

timer::timer() {
	initialize();
}

void timer::initialize() {
	time_start = GetNowCount();		// ���݌o�ߎ��Ԃ𓾂�
	time = 0.0f;					// ���ݎ��Ԃ̏�����
}

void timer::update() {
	// �J�n�����ƌ��ݎ����̍����i�[����
	time = GetNowCount() - time_start;
}

void timer::draw() {
	// �o�ߎ��Ԃ�`��
	DrawFormatString(250, 10, GetColor(255, 100, 100), "%d", time);
}
