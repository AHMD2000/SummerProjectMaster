#include "Crown.h"
#include "Game.h"
#include "Player.h"
#include "ResourceServer.h"
#include "ModeUI.h"
#include <DxLib.h>
#include <algorithm>
#include <vector>




Crown::Crown(ObjectBase::OBJECTTYPE id)
	:_id(id)
{
	ResourceServer::GetHandles("Crown", _grAllHandles);
	Init();
}

Crown::~Crown()
{
}

void Crown::Init()
{
	_w = 100;
	_h = 100;

	_animeNo = 0;
	_animeMax = 4;

	/*_ply.resize(PLAYERMAX);
	std::fill(_ply.begin(), _ply.end(), nullptr);*/

	_getPlyPtr = true;
}

void Crown::Process(Game& g)
{
	ObjectBase::Process(g);

	_animeNo = (_cnt / 8) % _animeMax;
	_grHandle = _grAllHandles[_animeNo];
	
}

void Crown::Draw(Game& g)
{
	ModeUI* modeUI = (ModeUI*)g._serverMode->Get("UI");

	if (_getPlyPtr == true)
	{
		for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
		{

			switch ((*ite)->GetType()) {
			case ObjectBase::OBJECTTYPE::PLAYER1:

				_ply.insert(_ply.begin(), dynamic_cast<Player*>(*ite));
				break;

			case ObjectBase::OBJECTTYPE::PLAYER2:

				_ply.insert(_ply.begin() + 1, dynamic_cast<Player*>(*ite));
				break;

			case ObjectBase::OBJECTTYPE::PLAYER3:

				_ply.insert(_ply.begin() + 2, dynamic_cast<Player*>(*ite));
				break;

			case ObjectBase::OBJECTTYPE::PLAYER4:

				_ply.insert(_ply.begin() + 3, dynamic_cast<Player*>(*ite));
				break;

			}

		}

		_getPlyPtr = false;
	}

	


	if (_cnt >= 2)
	{
		if (modeUI->_plyRankingUI.at(0).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			DrawRotaGraph(_ply[0]->_x, _ply[0]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
		}

		else if (modeUI->_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(1).first)
			{
				DrawRotaGraph(_ply[0]->_x, _ply[0]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}
			/*else
			{
				DrawRotaGraph(_ply[0]->_x, _ply[0]->_y - 100, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}*/
		}

		else if (modeUI->_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(2).first)
			{
				DrawRotaGraph(_ply[0]->_x, _ply[0]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		else if (modeUI->_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(3).first)
			{
				DrawRotaGraph(_ply[0]->_x, _ply[0]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		if (modeUI->_plyRankingUI.at(0).second == ObjectBase::OBJECTTYPE::PLAYER2)
		{
			DrawRotaGraph(_ply[1]->_x, _ply[1]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
		}

		else if (modeUI->_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER2)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(1).first)
			{
				DrawRotaGraph(_ply[1]->_x, _ply[1]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		else if (modeUI->_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER2)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(2).first)
			{
				DrawRotaGraph(_ply[1]->_x, _ply[1]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		else if (modeUI->_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER2)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(3).first)
			{
				DrawRotaGraph(_ply[1]->_x, _ply[1]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		if (modeUI->_plyRankingUI.at(0).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			DrawRotaGraph(_ply[2]->_x, _ply[2]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
		}

		else if (modeUI->_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(1).first)
			{
				DrawRotaGraph(_ply[2]->_x, _ply[2]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		else if (modeUI->_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(2).first)
			{
				DrawRotaGraph(_ply[2]->_x, _ply[2]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		else if (modeUI->_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER3)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(3).first)
			{
				DrawRotaGraph(_ply[2]->_x, _ply[2]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		if (modeUI->_plyRankingUI.at(0).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			DrawRotaGraph(_ply[3]->_x, _ply[3]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
		}

		else if (modeUI->_plyRankingUI.at(1).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(1).first)
			{
				DrawRotaGraph(_ply[3]->_x, _ply[3]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		else if (modeUI->_plyRankingUI.at(2).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(2).first)
			{
				DrawRotaGraph(_ply[3]->_x, _ply[3]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}

		else if (modeUI->_plyRankingUI.at(3).second == ObjectBase::OBJECTTYPE::PLAYER4)
		{
			if (modeUI->_plyRankingUI.at(0).first == modeUI->_plyRankingUI.at(3).first)
			{
				DrawRotaGraph(_ply[3]->_x, _ply[3]->_y - 95, 1.0, 0.0, _grHandle, TRUE, FALSE);
			}

		}
	}
	

}