#include "game_manager.h"
#include "collision.h"

game_manager::game_manager() {
	game_state = GAME_STATE_TITLE;

	game_span = 0;
	game_clear = false;
	game_miss = false;

	// �Ԉ�}��
	obj_car.push_back(car());

	// �e��f�[�^���o��
	obj_player.draw_log();
	obj_player.draw();
	obj_douro.draw_log();
	obj_car.at(0).draw();
	obj_car.at(0).draw_log();

}

void game_manager::update() {
	switch (game_state) {
	case GAME_STATE_TITLE:
		for (unsigned int i = 0; i < obj_car.size(); i++) {
			obj_car.at(i).update();							// �Ԃ̈ړ�
		}

		// �X�y�[�X�L�[�������ꂽ��A�Q�[���ֈڍs
		if (game_span++ >= 30 && CheckHitKey(KEY_INPUT_SPACE) == 1) {
			// �v���C���[�ݒ�
			obj_player = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));

			// �ڍs����
			clsDx();
			game_span = 0;
			game_state = GAME_STATE_PLAY;
		}
		break;
	case GAME_STATE_PLAY:
		obj_player.update();								// �v���C���[�̑���
		for (unsigned int i = 0; i < obj_car.size(); i++) {
			obj_car.at(i).update();							// �Ԃ̈ړ�
		}
		obj_camera.update(obj_player.get_position());		// �J�����̍X�V

		// �N���A���Ă���ꍇ
		if (game_clear) {
			// ���������烊�U���g�ֈڍs
			game_state = GAME_STATE_RESULT;
		}
		// ���s���Ă���ꍇ
		else if (game_miss) {
			// �v���C���[���邮��
			obj_player.rotation();

			// ���΂炭�҂��Ă��烊�U���g�ֈڍs
			if (game_span++ >= 180) {
				game_state = GAME_STATE_RESULT;
			}
		}
		// �v���C���̏ꍇ
		else {
			// �v���C���[�ƃS�[���̂����蔻��
			if (collision_player_udonbox(&obj_player)) {
				game_clear = true;
			}
			// �v���C���[�ƎԂ����̂����蔻��
			for (unsigned int i = 0; i < obj_car.size(); i++) {
				if (collision_player_car(&obj_player, &obj_car.at(i))) {
					game_miss = true;
					obj_player.control_off();
					obj_camera.track_off();
				}
			}
		}
		
		// �Ԃ̒ǉ�
		car_make();

		break;
	case GAME_STATE_RESULT:
		// �X�y�[�X�L�[�������ꂽ��A�e�평�������ă^�C�g���ֈڍs
		if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
			// �e�C���X�^���X
			obj_player = player();
			obj_car.clear();
			obj_car.push_back(car());
			obj_douro = douro();
			obj_camera = camera();
			
			// �Q�[���N���A�̔���ϐ�
			game_span = 0;
			game_clear = false;
			game_miss = false;

			game_state = GAME_STATE_TITLE;
		}
		break;
	}

}

void game_manager::draw() {
	switch (game_state) {
	case GAME_STATE_TITLE:
		DrawFormatString(250, 100, GetColor(255, 100, 100), "���ǂ񉮂֍s������\n�X�y�[�X�L�[�������Ă͂��߂�.");
		break;
	case GAME_STATE_PLAY:
		break;
	case GAME_STATE_RESULT:
		if (game_clear) {
			DrawFormatString(250, 100, GetColor(255, 100, 100), "���ǂ񂨂������I\n�X�y�[�X�L�[�Ń^�C�g���ɖ߂�.");
		}
		else if (game_miss) {
			DrawFormatString(250, 100, GetColor(255, 100, 100), "瀂���܂����B\n�X�y�[�X�L�[�Ń^�C�g���ɖ߂�.");
		}
		break;
	}

	obj_player.draw();				// �v���C���[�N���X
	for (unsigned int i = 0; i < obj_car.size(); i++) {
		obj_car.at(i).draw();		// �ԃN���X
	}
	obj_douro.draw();				// ���H�N���X
	obj_camera.draw();				// �J�����N���X
}

void game_manager::finalize() {
	// ���f���n���h���̍폜
	obj_player.finalize();
	obj_douro.finalize();
	for (unsigned int i = 0; i < obj_car.size(); i++) {
		obj_car.at(i).finalize();
	}
}

/*
//player player1 = player("./resorces/yukari/yukari.pmd", 14.0f, VGet(0.0f, 0.0f, 0.0f));
player player1 = player("./resorces/bokoboko.pmd", 20.0f, VGet(200.0f, 0.0f, 0.0f));
//player player3 = player("./resorces/79����^3.1/79��gv3.1.pmx", 10.0f, VGet(-200.0f, 0.0f, 0.0f));
*/

void game_manager::car_make() {
	const float road_far_left = -3100.0f;		// �����̓��H�̍��Ԑ�
	const float road_far_right = -2500.0f;		// �����̓��H�̉E�Ԑ�
	const float road_this_left = -800.0f;		// ��O���̓��H�̍��Ԑ�
	const float road_this_right = -1300.0f;		// ��O���̓��H�̉E�Ԑ�

	// �w�肵���Ԋu���o�߂�����Ԃ�ǉ�����
	if (car_span++ >= 10) {
		switch (GetRand(3)) {
		case 0:		// �����̍�
			obj_car.push_back(car(VGet(ROAD_LIMIT_LEFT, 50.0f, road_far_left), CAR_MOVE_RIGHT));
			break;
		case 1:		// �����̉E
			obj_car.push_back(car(VGet(ROAD_LIMIT_LEFT, 50.0f, road_far_right), CAR_MOVE_RIGHT));
			break;
		case 2:		// ��O���̉E
			obj_car.push_back(car(VGet(ROAD_LIMIT_RIGHT, 50.0f, road_this_right), CAR_MOVE_LEFT));
			break;
		case 3:		// ��O���̍�
			obj_car.push_back(car(VGet(ROAD_LIMIT_RIGHT, 50.0f, road_this_left), CAR_MOVE_LEFT));
			break;
		}

		// �Ԋu�����ɖ߂�
		car_span = 0;
	}

	// �����ȎԂ��폜����
	for (auto itr = obj_car.begin(); itr != obj_car.end();) {
		if (itr->flag) { itr++; }
		else {
			itr->finalize();
			itr = obj_car.erase(itr);
		}
	}
}