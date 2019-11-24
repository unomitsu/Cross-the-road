#include "player.h"

player::player(std::string filename, float extendf, VECTOR pos) {
	model_name = filename;								// 3D���f�����̊i�[
	model_extend = extendf;								// 3D���f���̏k�ڗ��̊i�[
	model_handle = MV1LoadModel(model_name.c_str());	// 3D���f���̓ǂݍ���

	/* ----- 3D���f���̐ݒ�ύX ----- */

	// 3D���f���̊g��k��
	MV1SetScale(model_handle, VGet(extendf, extendf, extendf));
	
	// 3D���f���̗֊s���̏C��
	int MaterialNum = MV1GetMaterialNum(model_handle);
	for (int i = 0; i < MaterialNum; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle, i);	// �}�e���A���̗֊s���̑������擾  
		MV1SetMaterialOutLineDotWidth(model_handle, i, dotwidth / 50.0f);	// �}�e���A���̗֊s���̑������g�債��������������  
	}

	/* ----- 3D���f���̔z�u ���_(320.0f, -300.0f, 600.0f)�Ƃ��� ----- */
	model_position = VGet(320.0f + pos.x, -300.0f + pos.y, 600.0f + pos.z);		// 3D���f���̍��W�̊i�[
	MV1SetPosition(model_handle, model_position);								// 3D���f����3D��Ԃւ̔z�u

	/* ----- �A�j���[�V�����̐ݒ� ----- */
	attach_index = MV1AttachAnim(model_handle, 0, -1, FALSE);					// �t�����[�V�����̃A�^�b�`
	anim_total_time = MV1GetAttachAnimTotalTime(model_handle, attach_index);	// ���Đ����Ԃ̎擾
	anim_play_time = 0.0f;														// �Đ����Ԃ̏�����
}

void player::update() {

	// �Đ����Ԃ�i�߂�
	anim_play_time += 0.5f;

	// �Đ����Ԃ��A�j���[�V�����̑��Đ����ԂɒB������Đ����Ԃ��O�ɖ߂�
	if (anim_play_time >= anim_total_time) { anim_play_time = 0.0f; }
	
	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(model_handle, attach_index, anim_play_time);
}

void player::draw() {
	// �R�c���f����`��
	MV1DrawModel(model_handle);
}

void player::draw_log() {
	printfDx("model_name[%s] _handle[%d]\n", model_name.c_str(), model_handle);
	printfDx("model_anim_num[%d] _index[%d]\n", MV1GetAnimNum(model_handle), attach_index);
}

void player::finalize() {
	// ���f���n���h���̍폜
	MV1DeleteModel(model_handle);
}