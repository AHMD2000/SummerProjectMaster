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

	_gaugeX = 130;
	_gaugeY = 1010;

	_maxCoin = 50.0;

	_fadeOn = true;

	_finalBGM = false;

	_BGMPerformance = false;


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

	// エフェクトを更新する
	for (auto&& effect : _effects) {
		effect->Update(_UIcnt, g);
	}
	// 死んだエフェクトを削除する
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
		if (_plyRankingUI.at(0).first >= _finalBGMCoin || _plyRankingUI.at(1).first >= _finalBGMCoin || _plyRankingUI.at(2).first >= _finalBGMCoin || _plyRankingUI.at(3).first >= _finalBGMCoin || modeGame->getGameCnt() <= 600)
		{

			//// BGM再生終了
			//StopMusic();

			//modeGame->_bgm = PlayMusic("res/bgm/GameFinal.mp3", DX_PLAYTYPE_LOOP);

			//_finalBGM = false;
			_finalBGM = true;
		}

		else if (_plyRankingUI.at(0).first <= 35 && _plyRankingUI.at(1).first <= 35 && _plyRankingUI.at(2).first <= 35 && _plyRankingUI.at(3).first <= 35/* && _GameMusic == false*/&& _GameMusicPerformance == true || _BGMPerformance == true)
		{
			//// BGM再生終了
			//StopMusic();

			//modeGame->_bgm = PlayMusic("res/bgm/gameMusic.mp3", DX_PLAYTYPE_LOOP);

			_GameMusic = true;
			/*_finalBGM = false;*/
		}

		if (_finalBGM == true && _BGMPerformance == false)
		{
			// BGM再生終了
			StopMusic();

			modeGame->_bgm = PlayMusic("res/bgm/GameFinal.mp3", DX_PLAYTYPE_LOOP);

			_BGMPerformance = true;
		}

		if (/*_finalBGM == false &&*/ _GameMusic == true)
		{
			// BGM再生終了
			StopMusic();

			modeGame->_bgm = PlayMusic("res/bgm/gameMusic.mp3", DX_PLAYTYPE_LOOP);

			_GameMusic = false;

			_GameMusicPerformance = false;
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
			DrawGraph(0 * 390, 900, _grAllHandles[0], TRUE);
		}

		else if (_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(1).first)
			{
				DrawGraph(0 * 390, 900, _grAllHandles[0], TRUE);
			}
			else
			{
				DrawGraph(0 * 390, 900, _grAllHandles[1], TRUE);
			}
		}

		else if (_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(2).first)
			{
				DrawGraph(0 * 390, 900, _grAllHandles[0], TRUE);
			}
			else
			{
				DrawGraph(0 * 390, 900, _grAllHandles[1], TRUE);
			}
		}

		else if (_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(3).first)
			{
				DrawGraph(0 * 390, 900, _grAllHandles[0], TRUE);
			}
			else
			{
				DrawGraph(0 * 390, 900, _grAllHandles[1], TRUE);
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
			DrawGraph(2 * 420 + 265, 900, _grAllHandles[4], TRUE);
		}

		else if (_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(1).first)
			{
				DrawGraph(2 * 420 + 265, 900, _grAllHandles[4], TRUE);
			}
			else
			{
				DrawGraph(2 * 420 + 265, 900, _grAllHandles[5], TRUE);
			}
		}

		else if (_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(2).first)
			{
				DrawGraph(2 * 420 + 265, 900, _grAllHandles[4], TRUE);
			}
			else
			{
				DrawGraph(2 * 420 + 265, 900, _grAllHandles[5], TRUE);
			}
		}

		else if (_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(3).first)
			{
				DrawGraph(2 * 420 + 265, 900, _grAllHandles[4], TRUE);
			}
			else
			{
				DrawGraph(2 * 420 + 265, 900, _grAllHandles[5], TRUE);
			}
		}

		if (_plyRankingUI.at(0).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			DrawGraph(2 * 420 + 265 + 420, 900, _grAllHandles[6], TRUE);
		}

		else if (_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(1).first)
			{
				DrawGraph(2 * 420 + 265 + 420, 900, _grAllHandles[6], TRUE);
			}
			else
			{
				DrawGraph(2 * 420 + 265 + 420, 900, _grAllHandles[7], TRUE);
			}
		}

		else if (_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(2).first)
			{
				DrawGraph(2 * 420 + 265 + 420, 900, _grAllHandles[6], TRUE);
			}
			else
			{
				DrawGraph(2 * 420 + 265 + 420, 900, _grAllHandles[7], TRUE);
			}
		}

		else if (_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			if (_plyRankingUI.at(0).first == _plyRankingUI.at(3).first)
			{
				DrawGraph(2 * 420 + 265 + 420, 900, _grAllHandles[6], TRUE);
			}
			else
			{
				DrawGraph(2 * 420 + 265 + 420, 900, _grAllHandles[7], TRUE);
			}
		}
	}

	else
	{
		DrawGraph(60 + 0 * 390, 900, _grAllHandles[0], TRUE);
		DrawGraph(60 + 1 * 390, 900, _grAllHandles[2], TRUE);
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

	//コインのゲージを表示
	for (auto i = 0; i < 2; ++i)
	{
		DrawRectGraph(_gaugeX + i * 420, _gaugeY, 0, 0, 260 * _plyCoinRate[i], 60, _grUIgaugeHandle, TRUE, FALSE);
	}

	DrawRectGraph(_gaugeX + 2 * 420 + 265, _gaugeY, 0, 0, 260 * _plyCoinRate[2], 60, _grUIgaugeHandle, TRUE, FALSE);
	DrawRectGraph(_gaugeX + 2 * 420 + 265 + 420, _gaugeY, 0, 0, 260 * _plyCoinRate[3], 60, _grUIgaugeHandle, TRUE, FALSE);
	
	/*DrawGraph(_gaugeX + 0 * 390, _gaugeY, _grUIgaugeHandle, TRUE);*/

	DrawGraph(2 * 420, 900, _UILimitTime, TRUE);

	// 描画する文字列のサイズを設定
	SetFontSize(64);
	if (modeGame->getGameCnt() >= 600)
	{
		DrawFormatString(2 * 420 + 100, 950, GetColor(0, 0, 255), "%d", modeGame->getGameCnt() / 60);
	}
	else
	{
		DrawFormatString(2 * 420 + 120, 950, GetColor(0, 0, 255), "%d", modeGame->getGameCnt() / 60);
	}
	
	SetFontSize(20);
	
	 // エフェクトを描画する
	for (auto&& effect : _effects) {
		effect->Draw(g);
	}
	
	return false;
}