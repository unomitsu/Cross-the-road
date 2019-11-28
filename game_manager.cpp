#include "game_manager.h"
#include "collision.h"

game_manager::game_manager() {
	game_state = GAME_STATE_TITLE;

	// �e��f�[�^���o��
	obj_player.draw_log();
	obj_player.draw();
	obj_douro.draw_log();
	obj_car.draw();
	obj_car.draw_log();

}

void game_manager::update() {
	switch (game_state) {
	case GAME_STATE_TITLE:
		obj_car.update();	// �Ԃ̈ړ�

			obj_camera.update();								// �J�����̑���
		// �X�y�[�X�L�[�������ꂽ��A�Q�[���ֈڍs
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			// �v���C���[�ݒ�
			obj_player = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));

			// �ڍs����
			clsDx();
			game_state = GAME_STATE_PLAY;
		}
		break;
	case GAME_STATE_PLAY:
		obj_player.update();								// �v���C���[�̑���
		obj_car.update();									// �Ԃ̈ړ�
		obj_camera.update();								// �J�����̑���

		// �v���C���[�ƎԂ́A�ȈՂ����蔻��
		if (collision_player_car(&obj_player, &obj_car)) {
			game_miss = true;
		}
		break;
	}

}

void game_manager::draw() {
	switch (game_state) {
	case GAME_STATE_TITLE:
		DrawFormatString(250, 100, GetColor(255, 255, 255), "���ǂ񉮂֍s������\n�X�y�[�X�L�[�������Ă͂��߂�.");
		break;
	case GAME_STATE_PLAY:
		break;
	case GAME_STATE_RESULT:
		break;
	}

	obj_player.draw();	// �v���C���[�N���X
	obj_car.draw();		// �ԃN���X
	obj_douro.draw();	// ���H�N���X
	obj_camera.draw();	// �J�����N���X
}

void game_manager::finalize() {
	// ���f���n���h���̍폜
	obj_player.finalize();
	obj_douro.finalize();
	obj_car.finalize();
}

/*
//player player1 = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));
player player1 = player("./resorces/bokoboko.pmd", 20.0f, VGet(200.0f, 0.0f, 0.0f));
//player player3 = player("./resorces/79����^3.1/79��gv3.1.pmx", 10.0f, VGet(-200.0f, 0.0f, 0.0f));
*/