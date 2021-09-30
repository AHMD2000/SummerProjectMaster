#include "DxLib.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeUI.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeRule.h"
#include "ModeCredit.h"


static int NowSelectTitle = Title_Gamestart; // ���݂̑I����

bool ModeTitle::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }

	// �^�C�g���摜�̃��[�h
	_cgTitle = ResourceServer::GetHandles("title");
	_cgTitlename = ResourceServer::GetHandles("titlename");
	_cgGameStart = ResourceServer::GetHandles("GameStart");//�Q�[���J�n
	_cgRule = ResourceServer::GetHandles("Rule");//�Q�[������
	_cgwaku = ResourceServer::GetHandles("waku");//�I��g

	//BGM���t�J�n
	_bgm = PlayMusic("res/bgm/SUMMER_TRIANGLE.mp3", DX_PLAYTYPE_LOOP);

	return true;
}

bool ModeTitle::Terminate(Game& g)
{
	base::Terminate(g);
	return true;
}

bool ModeTitle::Process(Game& g)
{
	base::Process(g);

	//if (g._gTrg[0] & PAD_INPUT_B)
	//{
	//	// ���̃��[�h���폜
	//	g._serverMode->Del(this);

	//	// �Q�[�����[�h��ǉ�
	//	ModeGame* modeGame = new ModeGame();
	//	g._serverMode->Add(modeGame, 0, "Game");
	//}

	if (_TitleProcess == true)
	{
		if (g._gTrg[0] & PAD_INPUT_DOWN) {// ���������ꂽ��
			NowSelectTitle = (NowSelectTitle + 1) % Title_Num;// �I����Ԃ��������

			//SE����
			PlaySoundMem(g._se["TitleMove"], DX_PLAYTYPE_BACK);
		}
		if (g._gTrg[0] & PAD_INPUT_UP) {// ��������ꂽ��
			NowSelectTitle = (NowSelectTitle + (Title_Num - 1)) % Title_Num;// �I����Ԃ��������

			 //SE����
			PlaySoundMem(g._se["TitleMove"], DX_PLAYTYPE_BACK);
		}
		if (g._gTrg[0] & PAD_INPUT_B) {// B�{�^���������ꂽ��
			switch (NowSelectTitle)//�I�𒆂̏�Ԃɂ���ď����𕪊�
			{
			case Title_Gamestart: // �X�^�[�g�I�𒆂Ȃ�
			{
				// ���̃��[�h���폜
				g._serverMode->Del(this);
				// �Q�[�����[�h��ǉ�
				ModeGame* modegame = new ModeGame();
				ModeUI* modeUI = new ModeUI();

				g._serverMode->Add(modegame, 0, "Game");
				g._serverMode->Add(modeUI, 1, "UI");

				modegame->_stage = ModeGame::STAGE::NORMAL;

				//SE����
				PlaySoundMem(g._se["TitleEnter"], DX_PLAYTYPE_BACK);

				// BGM�Đ��I��
				StopMusic();
			}
			break;

			case Title_Rule: // �Q�[�������I�𒆂Ȃ�
			{
				//// ���̃��[�h���폜
				//g._serverMode->Del(this);
				//// �^�C�g�����[�h���폜
				//g._serverMode->Del(g._serverMode->Get("Title"));
				// �Q�[��������ǉ�
				ModeRule* moderule = new ModeRule();
				g._serverMode->Add(moderule, 1, "RuleScreen");

				SetTitleProcess(false);

				//SE����
				PlaySoundMem(g._se["TitleEnter"], DX_PLAYTYPE_BACK);


			}
			break;

			case Title_Credit: // �N���W�b�g�I�𒆂Ȃ�
			{
				//// ���̃��[�h���폜
				//g._serverMode->Del(this);
				//// �^�C�g�����[�h���폜
				//g._serverMode->Del(g._serverMode->Get("Title"));
				// �N���W�b�g��ǉ�
				ModeCredit* modecredit = new ModeCredit();
				g._serverMode->Add(modecredit, 1, "Credit");

				SetTitleProcess(false);


				//SE����
				PlaySoundMem(g._se["TitleEnter"], DX_PLAYTYPE_BACK);
			}
			break;

			}

		}
	}


	return true;
}

bool ModeTitle::Draw(Game& g)
{
	base::Draw(g);

	DrawGraph(0, 0, _cgTitle, FALSE);

	/*DrawGraph(360, 120, _cgTitlename, TRUE);*/

	/*DrawGraph(120, 560, _cgGameStart, TRUE);

	DrawGraph(120, 760, _cgRule, TRUE);*/

	int _wakuY = 0;
	switch (NowSelectTitle) // �I����Ԃɂ���ď����𕪊�
	{
	case Title_Gamestart: // �X�^�[�g�I�𒆂Ȃ�
		_wakuY = 660;   // �X�^�[�g�̍��W���i�[
		break;
	case Title_Rule: // �����I�𒆂Ȃ�
		_wakuY = 780;   // �����̍��W���i�[
		break;
	case Title_Credit: // �N���W�b�g�I�𒆂Ȃ�
		_wakuY = 900;   // �N���W�b�g�̍��W���i�[
		break;
	}
	DrawGraph(100, _wakuY, _cgwaku, TRUE);

	return true;
}