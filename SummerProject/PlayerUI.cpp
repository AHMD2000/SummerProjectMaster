#include "PlayerUI.h"
#include "Player.h"
#include "ObjectBase.h"
#include <DxLib.h>

PlayerUI::PlayerUI(ObjectBase::OBJECTTYPE id, Game& g)
	:Player(id,g),_id(id)
{
	switch (id) {
	case ObjectBase::OBJECTTYPE::PLAYER1:
		ResourceServer::GetHandles("player_attack0UI", _grAllAttackUIHandles);
		/*_plyCoin = std::make_pair(ObjectBase::OBJECTTYPE::PLAYER1, _coin);
		modeGame->_plyRanking.emplace_back(_plyCoin);*/
		break;
	case ObjectBase::OBJECTTYPE::PLAYER2:
		ResourceServer::GetHandles("player_attack1UI", _grAllAttackUIHandles);
		/*_plyCoin = std::make_pair(ObjectBase::OBJECTTYPE::PLAYER2, _coin);
		modeGame->_plyRanking.emplace_back(_plyCoin);*/
		break;
	case ObjectBase::OBJECTTYPE::PLAYER3:
		ResourceServer::GetHandles("player_attack2UI", _grAllAttackUIHandles);
		/*_plyCoin = std::make_pair(ObjectBase::OBJECTTYPE::PLAYER3, _coin);
		modeGame->_plyRanking.emplace_back(_plyCoin);*/
		break;
	case ObjectBase::OBJECTTYPE::PLAYER4:
		ResourceServer::GetHandles("player_attack3UI", _grAllAttackUIHandles);
		/*_plyCoin = std::make_pair(ObjectBase::OBJECTTYPE::PLAYER4, _coin);
		modeGame->_plyRanking.emplace_back(_plyCoin);*/
		break;
	}

	ResourceServer::GetHandles("ResultCoin", _grAllResultCoinHandles);

	Init();
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init()
{
	// ƒvƒŒƒCƒ„[î•ñ‚Ì‰Šú‰»
	_w = 100;
	_h = 100;

	_animeMax = 4;
	_animeNo = 0;

}

void PlayerUI::Process(Game& g)
{

	ObjectBase::Process(g);

	_animeNo = (_cnt / 20) % _animeMax;
	_grHandle = _grAllHandles[_animeNo];

	_grAttackUIHandle = _grAllAttackUIHandles[_animeNo];

	_CoinAnimeNum = (_cnt / 10) % _CoinanimeMax;
	_grResultCoinHandle = _grAllResultCoinHandles[_CoinAnimeNum];
}

void PlayerUI::Draw(Game& g)
{
	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	if (GetType() == ObjectBase::OBJECTTYPE::PLAYER1)
	{
		DrawRotaGraph(240 + 480 * 0, 290, 2.0, 0.0, _grHandle, TRUE, FALSE);
		DrawRotaGraph(165 + 480 * 0, 500, 1.0, 0.0, _grAttackUIHandle, TRUE, FALSE);
		DrawRotaGraph(205 + 480 * 0, 715, 1.0, 0.0, _grResultCoinHandle, TRUE, FALSE);
	}

	if (GetType() == ObjectBase::OBJECTTYPE::PLAYER2)
	{
		DrawRotaGraph(240 + 480 * 1, 290, 2.0, 0.0, _grHandle, TRUE, FALSE);
		DrawRotaGraph(165 + 480 * 1, 500, 1.0, 0.0, _grAttackUIHandle, TRUE, FALSE);
	}

	if (GetType() == ObjectBase::OBJECTTYPE::PLAYER3)
	{
		DrawRotaGraph(240 + 480 * 2, 290, 2.0, 0.0, _grHandle, TRUE, FALSE);
		DrawRotaGraph(165 + 480 * 2, 500, 1.0, 0.0, _grAttackUIHandle, TRUE, FALSE);
	}

	if (GetType() == ObjectBase::OBJECTTYPE::PLAYER4)
	{
		DrawRotaGraph(240 + 480 * 3, 290, 2.0, 0.0, _grHandle, TRUE, FALSE);
		DrawRotaGraph(165 + 480 * 3, 500, 1.0, 0.0, _grAttackUIHandle, TRUE, FALSE);
	}
	
}