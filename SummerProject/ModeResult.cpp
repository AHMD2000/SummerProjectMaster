#include "DxLib.h"
#include "ModeResult.h"
#include "ModeTitle.h"
#include "Game.h"
#include "ResourceServer.h"
#include <algorithm>
//#include <iostream>
#include <memory>
#include "PlayerUI.h"
#include "ResultCrown.h"


bool ModeResult::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }

	_cgResult = ResourceServer::GetHandles("result");

	_fadeOn = true;

	auto plyUI1 = std::make_unique<PlayerUI>(ObjectBase::OBJECTTYPE::PLAYER1, g);
	_plyUIs.emplace_back(std::move(plyUI1));
	auto plyUI2 = std::make_unique<PlayerUI>(ObjectBase::OBJECTTYPE::PLAYER2, g);
	_plyUIs.emplace_back(std::move(plyUI2));
	auto plyUI3 = std::make_unique<PlayerUI>(ObjectBase::OBJECTTYPE::PLAYER3, g);
	_plyUIs.emplace_back(std::move(plyUI3));
	auto plyUI4 = std::make_unique<PlayerUI>(ObjectBase::OBJECTTYPE::PLAYER4, g);
	_plyUIs.emplace_back(std::move(plyUI4));
	
	_resultCrown = std::make_unique<ResultCrown>(ObjectBase::OBJECTTYPE::CROWN);

	//BGM演奏開始
	_bgm = PlayMusic("res/bgm/GameResult.mp3", DX_PLAYTYPE_LOOP);

	return true;
}

bool ModeResult::Terminate(Game& g)
{
	base::Terminate(g);
	return true;
}

bool ModeResult::Process(Game& g)
{
	base::Process(g);

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	if (modeGame->_stopObjProcess == true && _fadeOn == true)
	{
		auto newFadeEffect = std::make_unique<FadeEffect>(_resultCnt, GetColor(0, 0, 0));
		_effects.emplace_back(std::move(newFadeEffect));

		_fadeOn = false;
	}

	// プレイヤーUIを更新する
	for (auto&& plyUIs : _plyUIs) {
		plyUIs->Process(g);
	}

	// エフェクトを更新する
	for (auto&& effect : _effects) {
		effect->Update(_resultCnt, g);
	}
	// 死んだエフェクトを削除する
	_effects.erase(
		std::remove_if(_effects.begin(), _effects.end(),
			[](auto&& eft) {return eft->isDead(); }),
		_effects.end());


	//リザルトの王冠の更新
	_resultCrown->Process(g);

	if (g._gTrg[0] & PAD_INPUT_A)
	{
		// このモードを削除
		g._serverMode->Del(this);

		// ゲームモードの削除
		g._serverMode->Del(g._serverMode->Get("Game"));

		g._serverMode->Del(g._serverMode->Get("UI"));

		// タイトルモードを追加
		ModeTitle* modeTitle = new ModeTitle();
		g._serverMode->Add(modeTitle, 0, "Title");

		//BGM演奏中止
		StopMusic();
	}


	/*std::sort(modeGame->_plyRanking.begin(), modeGame->_plyRanking.end());*/

	_resultCnt++;

	return true;
}

bool ModeResult::Draw(Game& g)
{
	base::Draw(g);

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");


	std::stringstream ss;

	DrawGraph(0, 0, _cgResult, TRUE);


	/*for (auto i = 0; i < modeGame->_plyRanking.size(); ++i) {
		ss << "(" << modeGame->_plyRanking.at(i).first << ")" << "; ";
	}
	DrawString(SCREEN_W / 2, SCREEN_H / 2, ss.str().c_str(), GetColor(255, 255, 255));*/

	/*for (auto i = 0; i < modeGame->_plyRanking.size(); ++i)
	{
		if (modeGame->_plyRanking.at(i).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));
		}
		if (modeGame->_plyRanking.at(i).second == ObjectBase::OBJECTTYPE::PLAYER2)
		{
			DrawString(0 + i * 300, 0, "Player2", GetColor(255, 255, 255));
		}
		if (modeGame->_plyRanking.at(i).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			DrawString(0 + i * 300, 0, "Player3", GetColor(255, 255, 255));
		}
		if (modeGame->_plyRanking.at(i).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			DrawString(0 + i * 300, 0, "Player4", GetColor(255, 255, 255));
		}
	}*/

	// 描画する文字列のサイズを設定
	SetFontSize(100);

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	{
		switch ((*ite)->GetType()) {
		case ObjectBase::OBJECTTYPE::PLAYER1:
		{
			auto ply0 = dynamic_cast<Player*>(*ite);
			if (ply0->GetAttackHit10() > 0)
			{
				DrawFormatString(250 + 480 * 0, 480, GetColor(255, 255, 255), "%d", ply0->GetAttackHit10());
			}
			DrawFormatString(320 + 480 * 0, 480, GetColor(255, 255, 255), "%d", ply0->GetAttackHit1());

			if (ply0->GetStarCoinNum10() > 0)
			{
				DrawFormatString(250 + 480 * 0, 690, GetColor(255, 255, 255), "%d", ply0->GetStarCoinNum10());
			}
			DrawFormatString(320 + 480 * 0, 690, GetColor(255, 255, 255), "%d", ply0->GetStarCoinNum1());

			if (ply0->GetBananaAttackHit10() > 0)
			{
				DrawFormatString(250 + 480 * 0, 900, GetColor(255, 255, 255), "%d", ply0->GetBananaAttackHit10());
			}
			DrawFormatString(320 + 480 * 0, 900, GetColor(255, 255, 255), "%d", ply0->GetBananaAttackHit1());

			break;
		}


		case ObjectBase::OBJECTTYPE::PLAYER2:
		{
			
			auto ply1 = dynamic_cast<Player*>(*ite);
			if (ply1->GetAttackHit10() > 0)
			{
				DrawFormatString(250 + 480 * 1, 480, GetColor(255, 255, 255), "%d", ply1->GetAttackHit10());
			}
			DrawFormatString(320 + 480 * 1, 480, GetColor(255, 255, 255), "%d", ply1->GetAttackHit1());

			if (ply1->GetStarCoinNum10() > 0)
			{
				DrawFormatString(250 + 480 * 1, 690, GetColor(255, 255, 255), "%d", ply1->GetStarCoinNum10());
			}
			DrawFormatString(320 + 480 * 1, 690, GetColor(255, 255, 255), "%d", ply1->GetStarCoinNum1());

			if (ply1->GetBananaAttackHit10() > 0)
			{
				DrawFormatString(250 + 480 * 1, 900, GetColor(255, 255, 255), "%d", ply1->GetBananaAttackHit10());
			}
			DrawFormatString(320 + 480 * 1, 900, GetColor(255, 255, 255), "%d", ply1->GetBananaAttackHit1());

			break;
		}


		case ObjectBase::OBJECTTYPE::PLAYER3:
		{
			auto ply2 = dynamic_cast<Player*>(*ite);

			if (ply2->GetAttackHit10() > 0)
			{
				DrawFormatString(250 + 480 * 2, 480, GetColor(255, 255, 255), "%d", ply2->GetAttackHit10());
			}
			DrawFormatString(320 + 480 * 2, 480, GetColor(255, 255, 255), "%d", ply2->GetAttackHit1());

			if (ply2->GetStarCoinNum10() > 0)
			{
				DrawFormatString(250 + 480 * 2, 690, GetColor(255, 255, 255), "%d", ply2->GetStarCoinNum10());
			}
			DrawFormatString(320 + 480 * 2, 690, GetColor(255, 255, 255), "%d", ply2->GetStarCoinNum1());

			if (ply2->GetBananaAttackHit10() > 0)
			{
				DrawFormatString(250 + 480 * 2, 900, GetColor(255, 255, 255), "%d", ply2->GetBananaAttackHit10());
			}
			DrawFormatString(320 + 480 * 2, 900, GetColor(255, 255, 255), "%d", ply2->GetBananaAttackHit1());

			break;
		}


		case ObjectBase::OBJECTTYPE::PLAYER4:
		{
			auto ply3 = dynamic_cast<Player*>(*ite);

			if (ply3->GetAttackHit10() > 0)
			{
				DrawFormatString(250 + 480 * 3, 480, GetColor(255, 255, 255), "%d", ply3->GetAttackHit10());
			}
			DrawFormatString(320 + 480 * 3, 480, GetColor(255, 255, 255), "%d", ply3->GetAttackHit1());

			if (ply3->GetStarCoinNum10() > 0)
			{
				DrawFormatString(250 + 480 * 3, 690, GetColor(255, 255, 255), "%d", ply3->GetStarCoinNum10());
			}
			DrawFormatString(320 + 480 * 3, 690, GetColor(255, 255, 255), "%d", ply3->GetStarCoinNum1());

			if (ply3->GetBananaAttackHit10() > 0)
			{
				DrawFormatString(250 + 480 * 3, 900, GetColor(255, 255, 255), "%d", ply3->GetBananaAttackHit10());
			}
			DrawFormatString(320 + 480 * 3, 900, GetColor(255, 255, 255), "%d", ply3->GetBananaAttackHit1());

			break;
		}

		}
	}

	SetFontSize(20);

	// プレイヤーUIを描画する
	for (auto&& plyUIs : _plyUIs) {
		plyUIs->Draw(g);
	}

	//リザルトの王冠の描画
	_resultCrown->Draw(g);

	// エフェクトを描画する
	for (auto&& effect : _effects) {
		effect->Draw(g);
	}


	return true;
}