#include	"ModeUI.h"
#include    "ResourceServer.h"
#include	<DxLib.h>
#include    <algorithm>
#include	"ModeGame.h"


bool ModeUI::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }
	
	ResourceServer::GetHandles("UI", _grAllHandles);
	_grUIgaugeHandle = ResourceServer::GetHandles("UI_gauge");
	_UILimitTime = ResourceServer::GetHandles("UI_limitTime");

	_gaugeX = 125;
	_gaugeY = 1010;

	_maxCoin = 50.0;

	_fadeOn = true;

	_finalBGM = false;

	_BGMPerformance = false;

	_GameMusicPerformance = false;


	return false;
}

bool ModeUI::Terminate(Game& g)
{
	base::Terminate(g);

	return false;
}

bool ModeUI::Process(Game& g)
{
	base::Process(g);

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	if (modeGame->_stopObjProcess == true/* && _fadeOn == true*/)
	{
		auto newFadeEffect = std:: make_unique<FadeEffect>(_UIcnt, GetColor(0, 0, 0));
		_effects.emplace_back(std::move(newFadeEffect));

		/*_fadeOn = false;*/
	}

	// �G�t�F�N�g���X�V����
	for (auto&& effect : _effects) {
		effect->Update(_UIcnt, g);
	}
	// ���񂾃G�t�F�N�g���폜����
	_effects.erase(
		std::remove_if(_effects.begin(), _effects.end(),
			[](auto&& eft) {return eft->isDead(); }),
		_effects.end());
	

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	{
		switch ((*ite)->GetType()) {
		case ObjectBase::OBJECTTYPE::PLAYER1:
			(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER1);
			_plyRankingUI.emplace_back((*ite)->_plyCoin);
			_plyCoinRate[0] = (*ite)->_coin / _maxCoin;
			break;
		case ObjectBase::OBJECTTYPE::PLAYER2:
			(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER2);
			_plyRankingUI.emplace_back((*ite)->_plyCoin);
			_plyCoinRate[1] = (*ite)->_coin / _maxCoin;
			break;
		case ObjectBase::OBJECTTYPE::PLAYER3:
			(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER3);
			_plyRankingUI.emplace_back((*ite)->_plyCoin);
			_plyCoinRate[2] = (*ite)->_coin / _maxCoin;
			break;
		case ObjectBase::OBJECTTYPE::PLAYER4:
			(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER4);
			_plyRankingUI.emplace_back((*ite)->_plyCoin);
			_plyCoinRate[3] = (*ite)->_coin / _maxCoin;
			break;

		}
	}

	std::sort(_plyRankingUI.begin(), _plyRankingUI.end(), std::greater<std::pair<int, ObjectBase::OBJECTTYPE>>());

	_UIcnt++;

	if (_UIcnt >= 2)
	{
		if (_plyRankingUI.at(0).first >= _finalBGMCoin || _plyRankingUI.at(1).first >= _finalBGMCoin || _plyRankingUI.at(2).first >= _finalBGMCoin || _plyRankingUI.at(3).first >= _finalBGMCoin || modeGame->getGameCnt() <= 1200 && _BGMPerformance == false)
		{

			//// BGM�Đ��I��
			//StopMusic();

			//modeGame->_bgm = PlayMusic("res/bgm/GameFinal.mp3", DX_PLAYTYPE_LOOP);

			//_finalBGM = false;
			_finalBGM = true;

			_GameMusic = false;

			/*_GameMusicPerformance = false;*/
		}

		else if (_plyRankingUI.at(0).first <= 35 && _plyRankingUI.at(1).first <= 35 && _plyRankingUI.at(2).first <= 35 && _plyRankingUI.at(3).first <= 35 && modeGame->getGameCnt() >= 1201/* && _GameMusic == false*/&& _GameMusicPerformance == false)
		{
			//// BGM�Đ��I��
			//StopMusic();

			//modeGame->_bgm = PlayMusic("res/bgm/gameMusic.mp3", DX_PLAYTYPE_LOOP);

			_GameMusic = true;

			_finalBGM = false;
			/*_BGMPerformance = false;*/
			/*_finalBGM = false;*/
		}

		if (_finalBGM == true && _BGMPerformance == false)
		{
			// BGM�Đ��I��
			StopMusic();

			modeGame->_gameBGM = PlayMusic("res/bgm/GameFinal.mp3", DX_PLAYTYPE_LOOP);

			/*_finalBGM = false;*/

			_BGMPerformance = true;

			_GameMusicPerformance = false;
		}

		if (_GameMusicPerformance == false && _GameMusic == true)
		{
			// BGM�Đ��I��
			StopMusic();

			modeGame->_gameBGM = PlayMusic("res/bgm/gameMusic.mp3", DX_PLAYTYPE_LOOP);

			/*_GameMusic = false;*/

			_GameMusicPerformance = true;

			_BGMPerformance = false;
		}

	}
	

	return false;
}

bool ModeUI::Draw(Game& g)
{
	base::Draw(g);

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	if (_UIcnt >= 2)
	{
		if (_plyRankingUI.at(0).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			DrawGraph(0 * 420, 900, _grAllHandles[0], TRUE);
		}

		else if (_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(1).first)
			{
				DrawGraph(0 * 420, 900, _grAllHandles[0], TRUE);
			}
			else
			{
				DrawGraph(0 * 420, 900, _grAllHandles[1], TRUE);
			}
		}

		else if (_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(2).first)
			{
				DrawGraph(0 * 420, 900, _grAllHandles[0], TRUE);
			}
			else
			{
				DrawGraph(0 * 420, 900, _grAllHandles[1], TRUE);
			}
		}

		else if (_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(3).first)
			{
				DrawGraph(0 * 420, 900, _grAllHandles[0], TRUE);
			}
			else
			{
				DrawGraph(0 * 420, 900, _grAllHandles[1], TRUE);
			}
		}

		if (_plyRankingUI.at(0).second == ObjectBase::OBJECTTYPE::PLAYER2)
		{
			DrawGraph(1 * 420, 900, _grAllHandles[2], TRUE);
		}

		else if (_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER2)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(1).first)
			{
				DrawGraph(1 * 420, 900, _grAllHandles[2], TRUE);
			}
			else
			{
				DrawGraph(1 * 420, 900, _grAllHandles[3], TRUE);
			}
		}

		else if (_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER2)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(2).first)
			{
				DrawGraph(1 * 420, 900, _grAllHandles[2], TRUE);
			}
			else
			{
				DrawGraph(1 * 420, 900, _grAllHandles[3], TRUE);
			}
		}

		else if (_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER2)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(3).first)
			{
				DrawGraph(1 * 420, 900, _grAllHandles[2], TRUE);
			}
			else
			{
				DrawGraph(1 * 420, 900, _grAllHandles[3], TRUE);
			}
		}

		if (_plyRankingUI.at(0).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			DrawGraph( 1080, 900, _grAllHandles[4], TRUE);
		}

		else if (_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(1).first)
			{
				DrawGraph(1080, 900, _grAllHandles[4], TRUE);
			}
			else
			{
				DrawGraph(1080, 900, _grAllHandles[5], TRUE);
			}
		}

		else if (_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(2).first)
			{
				DrawGraph(1080, 900, _grAllHandles[4], TRUE);
			}
			else
			{
				DrawGraph(1080, 900, _grAllHandles[5], TRUE);
			}
		}

		else if (_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(3).first)
			{
				DrawGraph(1080, 900, _grAllHandles[4], TRUE);
			}
			else
			{
				DrawGraph(1080, 900, _grAllHandles[5], TRUE);
			}
		}

		if (_plyRankingUI.at(0).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			DrawGraph(1080 + 420, 900, _grAllHandles[6], TRUE);
		}

		else if (_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(1).first)
			{
				DrawGraph(1080 + 420, 900, _grAllHandles[6], TRUE);
			}
			else
			{
				DrawGraph(1080 + 420, 900, _grAllHandles[7], TRUE);
			}
		}

		else if (_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(2).first)
			{
				DrawGraph(1080 + 420, 900, _grAllHandles[6], TRUE);
			}
			else
			{
				DrawGraph(1080 + 420, 900, _grAllHandles[7], TRUE);
			}
		}

		else if (_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(3).first)
			{
				DrawGraph(1080 + 420, 900, _grAllHandles[6], TRUE);
			}
			else
			{
				DrawGraph(1080 + 420, 900, _grAllHandles[7], TRUE);
			}
		}
	}

	else
	{
		DrawGraph(0 * 420, 900, _grAllHandles[0], TRUE);
		DrawGraph(1 * 420, 900, _grAllHandles[2], TRUE);
		DrawGraph(1080, 900, _grAllHandles[4], TRUE);
		DrawGraph(1080 + 420, 900, _grAllHandles[6], TRUE);
	}

	_plyRankingUI.clear();

	//if (modeGame->getGameCnt() > 60 * 60)
	//{
	//	DrawFormatString(60 + 4 * 420, 910, GetColor(0, 0, 255), "%d%d:%d", 0, modeGame->getGameCnt() / 3600, modeGame->getGameCnt() / 60 % 60);
	//}

	//else if (modeGame->getGameCnt() <= 60 * 60 && modeGame->getGameCnt() > 60 * 10)
	//{
	//	DrawFormatString(60 + 4 * 420, 910, GetColor(0, 0, 255), "%d%d:%d", 0, modeGame->getGameCnt() / 3600, modeGame->getGameCnt() / 60);
	//}

	//else
	//{
	//	DrawFormatString(60 + 4 * 420, 910, GetColor(0, 0, 255), "%d%d:%d%d", 0, modeGame->getGameCnt() / 3600, 0 , modeGame->getGameCnt() / 60);
	//}

	//SetFontSize(20);

#pragma warning(disable:4244)

	//�R�C���̃Q�[�W��\��
	for (auto i = 0; i < 2; ++i)
	{
		DrawRectGraph(_gaugeX + i * 420, _gaugeY, 0, 0, 260 * _plyCoinRate[i], 60, _grUIgaugeHandle, TRUE, FALSE);
	}

	DrawRectGraph(_gaugeX + 1080, _gaugeY, 0, 0, 260 * _plyCoinRate[2], 60, _grUIgaugeHandle, TRUE, FALSE);
	DrawRectGraph(_gaugeX + 1500, _gaugeY, 0, 0, 260 * _plyCoinRate[3], 60, _grUIgaugeHandle, TRUE, FALSE);
#pragma warning(default:4244)
	
	/*DrawGraph(_gaugeX + 0 * 390, _gaugeY, _grUIgaugeHandle, TRUE);*/

	DrawGraph(828, 890, _UILimitTime, TRUE);

	// �`�悷�镶����̃T�C�Y��ݒ�
	SetFontSize(64);
	if (modeGame->getGameCnt() >= 600)
	{
		DrawFormatString(2 * 420 + 90, 950, GetColor(0, 0, 255), "%d", modeGame->getGameCnt() / 60);
	}
	else
	{
		DrawFormatString(2 * 420 + 105, 950, GetColor(0, 0, 255), "%d", modeGame->getGameCnt() / 60);
	}
	
	SetFontSize(20);
	
	 // �G�t�F�N�g��`�悷��
	for (auto&& effect : _effects) {
		effect->Draw(g);
	}
	
	return false;
}