#include "ResultCrown.h"
#include "ResourceServer.h"
#include <DxLib.h>
#include "ModeGame.h"

ResultCrown::ResultCrown(ObjectBase::OBJECTTYPE id)
	:Crown(id),_id(id)
{
	Init();
}

ResultCrown::~ResultCrown()
{
}

void ResultCrown::Init()
{
	_w = 200;
	_h = 200;

	_animeNo = 0;
	_animeMax = 4;
}

void ResultCrown::Process(Game& g)
{
	ObjectBase::Process(g);

	_animeNo = (_cnt / 8) % _animeMax;
	_grHandle = _grAllHandles[_animeNo];
}

void ResultCrown::Draw(Game& g)
{
	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	if (modeGame->_plyRanking.at(0).second == ObjectBase::OBJECTTYPE::PLAYER1)
	{
		DrawRotaGraph(240 + 480 * 0, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(1).second == ObjectBase::OBJECTTYPE::PLAYER1)
	{
		if(modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(1).first)
		DrawRotaGraph(240 + 480 * 0, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(2).second == ObjectBase::OBJECTTYPE::PLAYER1)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(2).first)
			DrawRotaGraph(240 + 480 * 0, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(3).second == ObjectBase::OBJECTTYPE::PLAYER1)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(3).first)
			DrawRotaGraph(240 + 480 * 0, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	if (modeGame->_plyRanking.at(0).second == ObjectBase::OBJECTTYPE::PLAYER2)
	{
		DrawRotaGraph(240 + 480 * 1, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player2", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(1).second == ObjectBase::OBJECTTYPE::PLAYER2)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(1).first)
			DrawRotaGraph(240 + 480 * 1, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(2).second == ObjectBase::OBJECTTYPE::PLAYER2)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(2).first)
			DrawRotaGraph(240 + 480 * 1, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(3).second == ObjectBase::OBJECTTYPE::PLAYER2)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(3).first)
			DrawRotaGraph(240 + 480 * 1, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	if (modeGame->_plyRanking.at(0).second == ObjectBase::OBJECTTYPE::PLAYER3)
	{		
		DrawRotaGraph(240 + 480 * 2, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player3", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(1).second == ObjectBase::OBJECTTYPE::PLAYER3)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(1).first)
			DrawRotaGraph(240 + 480 * 2, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(2).second == ObjectBase::OBJECTTYPE::PLAYER3)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(2).first)
			DrawRotaGraph(240 + 480 * 2, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(3).second == ObjectBase::OBJECTTYPE::PLAYER3)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(3).first)
			DrawRotaGraph(240 + 480 * 2, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	if (modeGame->_plyRanking.at(0).second == ObjectBase::OBJECTTYPE::PLAYER4)
	{	
		DrawRotaGraph(240 + 480 * 3, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player4", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(1).second == ObjectBase::OBJECTTYPE::PLAYER4)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(1).first)
			DrawRotaGraph(240 + 480 * 3, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(2).second == ObjectBase::OBJECTTYPE::PLAYER4)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(2).first)
			DrawRotaGraph(240 + 480 * 3, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}
	else if (modeGame->_plyRanking.at(3).second == ObjectBase::OBJECTTYPE::PLAYER4)
	{
		if (modeGame->_plyRanking.at(0).first == modeGame->_plyRanking.at(3).first)
			DrawRotaGraph(240 + 480 * 3, 140, 2.5, 0.0, _grHandle, TRUE, FALSE);
		/*DrawString(0 + i * 300, 0, "Player1", GetColor(255, 255, 255));*/
	}

}