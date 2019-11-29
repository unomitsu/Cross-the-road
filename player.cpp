#include "player.h"
#include "douro.h"

int player::model_handle_boko;		// �Ȃ񂩂��낢��̃n���h��
int player::model_handle_yukari;	// �䂩�肳��̃n���h��
int player::model_handle_printsu;	// �Ղ��������񂳂�̃n���h��

player::player() {
	// 3D���f���̓ǂݍ���
	model_handle_boko = MV1LoadModel("./resorces/bokoboko.pmd");
	model_handle_yukari = MV1LoadModel("./resorces/yukari/yukari.pmd");
	model_handle_printsu = MV1LoadModel("./resorces/�d���v�����c�E�I�C�Q��/�v�����c�E�I�C�Q��(�~���Ȃ�).pmx");

	// ����������
	initialize(GAME_CHARA_BOKO, 20.0f, VGet(0.0f, 0.0f, 0.0f), false);
}

player::player(int name, VECTOR pos) {
	switch (name) {
	case GAME_CHARA_BOKO: initialize(name, 20.0f, pos, true); break;
	case GAME_CHARA_YUKARI: initialize(name, 14.0f, pos, true); break;
	case GAME_CHARA_PRINTSU: initialize(name, 14.0f, pos, true); break;
	}
}

// �������� anim_load �ɂ��A�j���[�V�����̐ݒ�L����ύX
void player::initialize(int name, float extendf, VECTOR pos, bool anim_load) {
	// 3D���f���̓ǂݍ���(����)
	switch (name) {
	case GAME_CHARA_BOKO: model_handle = MV1DuplicateModel(model_handle_boko); break;
	case GAME_CHARA_YUKARI:	model_handle = MV1DuplicateModel(model_handle_yukari); break;
	case GAME_CHARA_PRINTSU:	model_handle = MV1DuplicateModel(model_handle_printsu); break;
	}
	model_extend = VGet(extendf, extendf, extendf);		// 3D���f���̏k�ڗ��̊i�[

	/* ----- 3D���f���̐ݒ�ύX ----- */

	// 3D���f���̊g��k��
	MV1SetScale(model_handle, model_extend);

	// 3D���f���̗֊s���̏C��
	int MaterialNum = MV1GetMaterialNum(model_handle);
	for (int i = 0; i < MaterialNum; i++) {
		float dotwidth = MV1GetMaterialOutLineDotWidth(model_handle, i);	// �}�e���A���̗֊s���̑������擾  
		MV1SetMaterialOutLineDotWidth(model_handle, i, dotwidth / 50.0f);	// �}�e���A���̗֊s���̑������g�債��������������  
	}

	/* ----- 3D���f���̔z�u ----- */											// ���_(320.0f, -300.0f, 600.0f)�Ƃ���
	model_position = VGet(320.0f + pos.x, -250.0f + pos.y, 600.0f + pos.z);		// 3D���f���̍��W�̊i�[
	model_rotation = VGet(0.0f, 0.0f, 0.0f);									// 3D���f���̉�]�l�̊i�[
	MV1SetPosition(model_handle, model_position);								// 3D���f����3D��Ԃւ̔z�u

	// �A�j���[�V�����Ƒ���֘A�̐ݒ������ꍇ
	if (anim_load) {
		/* ----- �A�j���[�V�����̐ݒ� ----- */
		attach_index = MV1AttachAnim(model_handle, 0, -1, FALSE);					// �t�����[�V�����̃A�^�b�`
		anim_total_time = MV1GetAttachAnimTotalTime(model_handle, attach_index);	// ���Đ����Ԃ̎擾
		anim_play_time = 0.0f;														// �Đ����Ԃ̏�����

		/* ----- �ړ��֘A�̐ݒ� ----- */
		model_move_state = PLAYER_STATE_STAND;	// ������Ԃ�ݒ肷��
		model_move_max = 20.0f;					// �ړ��ʂ̍ő�l���i�[
		model_move_value = 0.0f;				// �ړ��ʂ̌��ݒl���i�[
		model_move_external = VGet(0.0f, 0.0f, 0.0f);	// �O�͂�����������
		flag_control = true;

		// �A�j���[�V�����ɂ�郍�[�J���̍��W�ړ��𖳌��ɂ���
		MV1SetFrameUserLocalMatrix(model_handle, MV1SearchFrame(model_handle, "�Z���^�["), MGetIdent());
		//MV1SetFrameUserLocalMatrix(model_handle, MV1SearchFrame(model_handle, "�O���[�u"), MGetIdent());
	}
}

// �v���C���[�̍X�V
void player::update() {
	// �R���g���[���[�̍X�V
	update_control();

	// �A�j���[�V�����̍X�V
	update_anim();

	// 3D���f����3D��Ԃւ̍Ĕz�u
	MV1SetPosition(model_handle, model_position);
	MV1SetRotationXYZ(model_handle, model_rotation);
}

// �v���C���[�̃A�j���[�V�����̍X�V
void player::update_anim() {
	// �Đ����Ԃ�i�߂�.  �����ύX������΁A�ȉ���switch�����ŏ㏑������
	anim_play_time += 0.5f;

	switch (model_move_state) {
	// �u�ҋ@�v
	case PLAYER_STATE_STAND:
		// �L�[���Ȃ�A�u����o���v�Ɉڍs
		if (is_move()) {
			model_move_state = PLAYER_STATE_START;
			anim_play_time = ANIM_START_START;
		}
		// �L�[���Ȃ�A�u�ҋ@�v���p��
		else {
			anim_play_time = ANIM_STAND_START;
		}
		break;
	// �u����o���v
	case PLAYER_STATE_START:
		// �L�[���Ȃ�A�u����o���v��i�߂�
		if (is_move()) {

			// �u����o���v���I��������u����v�Ɉڍs
			if (ANIM_START_FINISH <= anim_play_time) {
				model_move_state = PLAYER_STATE_RUN;
				anim_play_time = ANIM_RUN_START;
			}
		}
		// �L�[���Ȃ�A�u��~�v�Ɉڍs
		else {
			model_move_state = PLAYER_STATE_STOP;
			anim_play_time = ANIM_STOP_START;
		}
		
		break;
	// �u����v
	case PLAYER_STATE_RUN:
		// �L�[���Ȃ�A�u����v��i�߂�
		if (is_move()) {
			// �u����v���I��������A�u����v�̏��߂ɖ߂�
			if (ANIM_RUN_FINISH <= anim_play_time) {
				model_move_state = PLAYER_STATE_RUN;
				anim_play_time = ANIM_RUN_START;
			}
		}
		// �L�[���Ȃ�A�u��~�v�Ɉڍs
		else {
			model_move_state = PLAYER_STATE_STOP;
			anim_play_time = ANIM_STOP_START;
		}
		break;
	// �u��~�v
	case PLAYER_STATE_STOP:
		// �L�[���Ȃ�A�u����o���v�Ɉڍs
		if (is_move()) {
			model_move_state = PLAYER_STATE_START;
			anim_play_time = ANIM_START_START;
		}
		// �L�[���Ȃ�A�u��~�v���p��
		else {
			// �u��~�v���I��������A�u�ҋ@�v�ɖ߂�
			if (ANIM_STOP_FINISH <= anim_play_time) {
				model_move_state = PLAYER_STATE_STAND;
				anim_play_time = ANIM_STAND_START;
			}
		}
		break;
	}
	// �Đ����Ԃ��Z�b�g����
	MV1SetAttachAnimTime(model_handle, attach_index, anim_play_time);
}

// �v���C���[�̈ړ�����̍X�V
void player::update_control() {
	// ���Z�p��VECTOR�ϐ���錾
	VECTOR move = VGet(0.0f, 0.0f, 0.0f);

	// �R���g���[���[
	if (flag_control) {
		// �ŋ߂̈ړ��������i�[
		if (CheckHitKey(KEY_INPUT_UP) == 1) { model_move_direction = 1; }		// �O 1
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) { model_move_direction = 2; }	// �E 2
		if (CheckHitKey(KEY_INPUT_DOWN) == 1) { model_move_direction = 3; }		// �� 3
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) { model_move_direction = 4; }		// �� 4


		// �ҋ@��Ԃ̎��A�ړ��ʂ�����������
		if (model_move_state == PLAYER_STATE_STAND) {
			model_move_value = 0.0f;
		}
		// ��~��Ԃ̎��A�ړ��ʂ����������Ă���
		else if (model_move_state == PLAYER_STATE_STOP) {
			model_move_value -= model_move_max / 20;

			// �ŏ��l�𒴂������̒���
			if (model_move_value < 0.0f) { model_move_value = 0.0f; }
		}
		// ���̑��̎��A�ړ��ʂ𑝉������Ă���
		else {
			model_move_value += model_move_max / 20;

			// �ő�l�𒴂������̒���
			if (model_move_max < model_move_value) { model_move_value = model_move_max; }
		}

		const float rotation_dif = 0.02f;
		const float rotation_max = 0.4f;

		// �ړ��ʂƉ�]�l�̍X�V���s��
		// -- �O�ւ̈ړ�
		if (CheckHitKey(KEY_INPUT_UP) == 1) {
			if (model_rotation.x > 0) { model_rotation.x *= -1.0f; }
			if ((model_rotation.x -= rotation_dif) < -rotation_max) { model_rotation.x = -rotation_max; }
			model_rotation.y = 0.0f;
			model_rotation.z = 0.0f;
			move.z -= model_move_value;
		}
		// -- �E�ւ̈ړ�
		if (CheckHitKey(KEY_INPUT_RIGHT) == 1) {
			model_rotation.x = 0.0f;
			model_rotation.y = DX_PI_F / 2;
			if (model_rotation.z < 0) { model_rotation.z *= -1.0f; }
			if ((model_rotation.z += rotation_dif) > rotation_max) { model_rotation.z = rotation_max; }
			move.x -= model_move_value;
		}
		// -- ��ւ̈ړ�
		if (CheckHitKey(KEY_INPUT_DOWN) == 1) {
			if (model_rotation.x > 0) { model_rotation.x *= -1.0f; }
			if ((model_rotation.x -= rotation_dif) < -rotation_max) { model_rotation.x = -rotation_max; }
			model_rotation.y = DX_PI_F;
			model_rotation.z = 0.0f;
			move.z += model_move_value;
		}
		// -- ���ւ̈ړ�
		if (CheckHitKey(KEY_INPUT_LEFT) == 1) {
			model_rotation.x = 0.0f;
			model_rotation.y = DX_PI_F * 3 / 2;
			if (model_rotation.z > 0) { model_rotation.z *= -1.0f; }
			if ((model_rotation.z -= rotation_dif) < -rotation_max) { model_rotation.z = -rotation_max; }
			move.x += model_move_value;
		}
		// �ړ����Ă��Ȃ��ꍇ
		if (!is_move()) {
			// ���Z������]�l�̌��Z
			if (model_rotation.z != 0.0f) {
				if (model_rotation.z < 0) { model_rotation.z += rotation_dif; }
				if (model_rotation.z > 0) { model_rotation.z -= rotation_dif; }
			}
			if (model_rotation.x != 0.0f) {
				if (model_rotation.x < 0) { model_rotation.x += rotation_dif; }
				if (model_rotation.x > 0) { model_rotation.x -= rotation_dif; }
			}

			// �u����o���v�u��~�v�̏ꍇ�̈ړ��ʂ̉��Z
			if (model_move_state == PLAYER_STATE_START || model_move_state == PLAYER_STATE_STOP) {
				switch (model_move_direction) {
				case 1:	move.z -= model_move_value;	break;
				case 2:	move.x -= model_move_value;	break;
				case 3:	move.z += model_move_value;	break;
				case 4:	move.x += model_move_value;	break;
				}
			}
		}
	}

	// �O�͂̉��Z
	move = VAdd(move, model_move_external);

	// �ړ��ʂ����Z���āA���W�̍X�V
	model_position = VAdd(model_position, move);

	// �͈͊O�̃`�F�b�N
	if (flag_control) {
		if (model_position.z < WORLD_LIMIT_UP) { model_position.z = WORLD_LIMIT_UP; }
		if (WORLD_LIMIT_DOWN < model_position.z) { model_position.z = WORLD_LIMIT_DOWN; }
		if (WORLD_LIMIT_LEFT < model_position.x) { model_position.x = WORLD_LIMIT_LEFT; }
		if (model_position.x < WORLD_LIMIT_RIGHT) { model_position.x = WORLD_LIMIT_RIGHT; }
	}
}

// 3D���f���̕`��
void player::draw() {
	// �R�c���f����`��
	MV1DrawModel(model_handle);
	
	// �ړ���Ԃ̕\��
	std::string str;
	switch (model_move_state) {
	case PLAYER_STATE_STAND: str = "STATE_STAND"; break;
	case PLAYER_STATE_START: str = "STATE_START"; break;
	case PLAYER_STATE_RUN: str = "STATE_RUN"; break;
	case PLAYER_STATE_STOP:	str = "STATE_STOP"; break;
	}
	
	/*
	DrawFormatString(10, 100, GetColor(255, 255, 255), "%s _play_time[%f]\n", str.c_str(), anim_play_time);										// �ړ���ԂƃA�j���[�V�����̌��ݎ���
	DrawFormatString(10, 120, GetColor(255, 255, 255), "Pos(%.2f, %.2f, %.2f)\n", model_position.x, model_position.y, model_position.z);		// 3D���f���̋�ԍ��W
	DrawFormatString(10, 140, GetColor(255, 255, 255), "Rot(%.2f, %.2f, %.2f)\n", model_rotation.x, model_rotation.y, model_rotation.z);		// 3D���f���̉�]�l
	DrawFormatString(10, 160, GetColor(255, 255, 255), "Ext(%.2f, %.2f, %.2f)\n", model_move_external.x, model_move_external.y, model_move_external.z);	// 3D���f���ւ̊O��
	DrawFormatString(10, 180, GetColor(255, 255, 255), "move_value[%.2f]\n", model_move_value);
	*/
}

// 3D���f���̊e�f�[�^�̏o��
void player::draw_log() {
	printfDx("model_name[%s] _handle[%d]\n", "model_name", model_handle);
	printfDx("model_anim_num[%d] _index[%d]\n", MV1GetAnimNum(model_handle), attach_index);
}

// �v���C���[�N���X�̏I������
void player::finalize() {
	// ���f���n���h���̍폜
	MV1DeleteModel(model_handle);
}

// �v���C���[�������Ă��邩�̐^�U��Ԃ�
bool player::is_move() {
	return (CheckHitKey(KEY_INPUT_UP) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1 || CheckHitKey(KEY_INPUT_LEFT) == 1);
}

// �O����̗͂�ݒ肷��
void player::add_vector(VECTOR vec) {
	model_move_external = VAdd(model_move_external, vec);
}

void player::rotation() {
	model_rotation.y += 0.5f;
}
void player::control_off() {
	flag_control = false;
}


// �v���C���[�̍��W�� VECTOR �^�Ŏ擾����
VECTOR player::get_position() {
	return model_position;
}
