#include "car.h"

car::car() {
	initialize(VGet(2000.0f, 50.0f, -1350.0f));
}

car::car(VECTOR pos) {
	initialize(pos);
}
void car::initialize(VECTOR pos) {
	model_name = "./resorces/boxcar.mv1";				// 3D���f�����̊i�[
	model_extend = VGet(200.0f, 200.0f, 200.0f);		// 3D���f���̏k�ڗ��̊i�[
	model_handle = MV1LoadModel(model_name.c_str());	// 3D���f���̓ǂݍ���

	move_type = CAR_MOVE_RIGHT;
	speed = -20.0f;

	/* ----- 3D���f���̐ݒ�ύX ----- */

	// 3D���f���̊g��k��
	MV1SetScale(model_handle, model_extend);

	// 3D���f���̗֊s���̏C��
	int MaterialNum = MV1GetMaterialNum(model_handle);
	for (int i = 0; i < MaterialNum; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle, i);	// �}�e���A���̗֊s���̑������擾  
		MV1SetMaterialOutLineDotWidth(model_handle, i, dotwidth / 50.0f);	// �}�e���A���̗֊s���̑������g�債��������������  
	}

	/* ----- 3D���f���̔z�u ���_(320.0f, -300.0f, 600.0f)�Ƃ��� ----- */
	model_position = VGet(320.0f + pos.x, -300.0f + pos.y, 600.0f + pos.z);		// 3D���f���̍��W�̊i�[
	MV1SetPosition(model_handle, model_position);								// 3D���f����3D��Ԃւ̔z�u
}

void car::update() {
	// �ړ��ʂ̉��Z
	model_position.x += speed;

	// �Ԃ̐i�s�^�C�v���E�̎� x���W�}�C�i�X
	if (move_type == CAR_MOVE_RIGHT) {
		// �����ɓ��B�����Ƃ��̏���
		if (model_position.x <= ROAD_LIMIT_RIGHT) {
			model_position.x = ROAD_LIMIT_LEFT;
		}
	}
	// �Ԃ̐i�s�^�C�v�����̎� x���W�v���X
	else {
		// ����ɓ��B�����Ƃ��̏���
		if (ROAD_LIMIT_RIGHT <= model_position.x) {
			model_position.x = ROAD_LIMIT_RIGHT;
		}
	}

	// �ړ���̍��W�ōĔz�u
	MV1SetPosition(model_handle, model_position);
}

void car::draw() {
	// �R�c���f����`��
	MV1DrawModel(model_handle);
	
	DrawFormatString(10, 250, GetColor(255, 255, 255), "Pos(%.2f, %.2f, %.2f)\n", model_position.x, model_position.y, model_position.z);		// 3D���f���̋�ԍ��W
	DrawFormatString(10, 270, GetColor(255, 255, 255), "move_value[%.2f]\n", speed);
}

void car::draw_log() {
	printfDx("car_type[REGULAR] _handle[%d]\n", model_handle);
}

void car::finalize() {
	// ���f���n���h���̍폜
	MV1DeleteModel(model_handle);
}

// �Ԃ̍��W�� VECTOR �^�Ŏ擾����
VECTOR car::get_position() {
	return model_position;
}

// �Ԃ̈ړ��ʂ� VECTOR �^�Ŏ擾����
VECTOR car::get_move_vector() {
	return VGet(speed, 0.0f, 0.0f);
}