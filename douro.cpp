#include "douro.h"

douro::douro() {
	model_name = "./resorces/Douro.mv1";				// 3D���f�����̊i�[
	model_extend = VGet(5.0f, 1.0f, 4.0f);				// 3D���f���̏k�ڗ��̊i�[
	model_handle = MV1LoadModel(model_name.c_str());	// 3D���f���̓ǂݍ���

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
	model_position = VGet(320.0f + 0.0f, -300.0f + -50.0f, 600.0f + -2000.0f);	// 3D���f���̍��W�̊i�[
	MV1SetPosition(model_handle, model_position);	// 3D���f����3D��Ԃւ̔z�u


	/* ���ǂ� */
	model_handle_udonbox = MV1LoadModel("./resorces/udon_box.mv1");		// 3D���f���̓ǂݍ���
	MV1SetScale(model_handle_udonbox, VGet(3.0f, 3.0f, 3.0f));			// 3D���f���̊g��k��
	MaterialNum = MV1GetMaterialNum(model_handle_udonbox);				// 3D���f���̗֊s���̏C��
	for (int i = 0; i < MaterialNum; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle_udonbox, i);	// �}�e���A���̗֊s���̑������擾  
		MV1SetMaterialOutLineDotWidth(model_handle_udonbox, i, dotwidth / 50.0f);	// �}�e���A���̗֊s���̑������g�債��������������  
	}
	MV1SetPosition(model_handle_udonbox, VGet(2000.0f, -50.0f, -4000.0f));			// 3D���f����3D��Ԃւ̔z�u
}

void douro::update() {
}

void douro::draw() {
	MV1DrawModel(model_handle);				// ���H
	MV1DrawModel(model_handle_udonbox);		// ���ǂ�

	/* �n�� */
	float pos_y = -350.0f;
	VECTOR pos1 = VGet(WORLD_LIMIT_LEFT, pos_y, WORLD_LIMIT_UP);
	VECTOR pos2 = VGet(WORLD_LIMIT_RIGHT, pos_y, WORLD_LIMIT_UP);
	VECTOR pos3 = VGet(WORLD_LIMIT_RIGHT, pos_y, WORLD_LIMIT_DOWN);
	VECTOR pos4 = VGet(WORLD_LIMIT_LEFT, pos_y, WORLD_LIMIT_DOWN);

	DrawTriangle3D(pos1, pos2, pos3, GetColor(100, 255, 100), TRUE);
	DrawTriangle3D(pos3, pos4, pos1, GetColor(100, 255, 100), TRUE);
}

void douro::draw_log() {
	printfDx("model_name[%s] _handle[%d]\n", model_name.c_str(), model_handle);
}

void douro::finalize() {
	// ���f���n���h���̍폜
	MV1DeleteModel(model_handle);
}