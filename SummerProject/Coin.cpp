#include "DxLib.h"
#include "Coin.h"
#include "Game.h"
#include "ResourceServer.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "ModeGame.h"
#include "mapchips.h"

Coin::Coin(ObjectBase::OBJECTTYPE id, ModeGame& modegame)
	:_id(id),_modeGame(modegame)
{
	ResourceServer::GetHandles("starcoin", _grAllHandles);
	Init();
}

Coin::~Coin()
{
}

void Coin::Init()
{
	_coinType = COINTYPE::FILDCOIN;

	_coinDir = 2;
	_standCoolTime = 0;
	_standEnd = false;
	_stand = false;
	_coinChange = true;
	_whoCoin = 4;
	_g = 1;
	_xJump = false;
	_jump = false;
	_w = 160;
	_h = 160;

	/*_x = 100;
	_y = 100;*/

	_x = rand() % _modeGame._newMapChips->MAPSIZE_W;
	_y = rand() % _modeGame._newMapChips->MAPSIZE_H;

	/*_x = rand() % _mapchip.MAPSIZE_W;
	_y = rand() % _mapchip.MAPSIZE_H;*/

	_hit_x = 55;
	_hit_y = 50;
	_hit_w = 50;
	_hit_h = 60;

	/*while (_mapchip.CheckHit(_x, _y) != 0)
	{
		_x = rand() % _mapchip.MAPSIZE_W;
		_y = rand() % _mapchip.MAPSIZE_H;
	}

	_x *= _mapchip.CHIPSIZE_W;
	_y *= _mapchip.CHIPSIZE_H;*/

	_x *= _modeGame._newMapChips->CHIPSIZE_W;
	_y *= _modeGame._newMapChips->CHIPSIZE_H;

	while (_modeGame._newMapChips->IsHit(*this, _x, _y) != 0)
	{
		_x = rand() % _modeGame._newMapChips->MAPSIZE_W;
		_y = rand() % _modeGame._newMapChips->MAPSIZE_H;

		_hit_x = 55;
		_hit_y = 50;
		_hit_w = 50;
		_hit_h = 60;

		_x *= _modeGame._newMapChips->CHIPSIZE_W;
		_y *= _modeGame._newMapChips->CHIPSIZE_H;

	}

	_animeNo = 0;
	_animeMax = 6;

	/*_x += _w / 2;
	_y += _h;*/
}

void Coin::Process(Game& g)
{
	/*_mapchip->CheckHit();*/

	auto modeGame =
		dynamic_cast<ModeGame*>(g._serverMode->Get("Game"));

	Vector2 _StarCoinGetEffectPos{ static_cast<double>(_x) + static_cast<double>(_w / 2), static_cast<double>(_y) + static_cast<double>(_h / 2) };

	ObjectBase::Process(g);

	if (_coinType == COINTYPE::PLAYERCOIN && _coinChange == true)
	{
		if (_whoCoin == 0)
		{
			_grHandle = ResourceServer::GetHandles("playercoin0");
		}
		else if (_whoCoin == 1)
		{
			_grHandle = ResourceServer::GetHandles("playercoin1");
		}
		else if (_whoCoin == 2)
		{
			_grHandle = ResourceServer::GetHandles("playercoin2");
		}
		else if (_whoCoin == 3)
		{
			_grHandle = ResourceServer::GetHandles("playercoin3");
		}
		

		_w = 50;
		_h = 50;

		_hit_x = 13;
		_hit_y = 13;
		_hit_w = 24;
		_hit_h = 30;

		_coinChange = false;
	}

	if (_coinType == COINTYPE::FILDCOIN)
	{
		_animeNo = (_cnt / 8) % _animeMax;
		_grHandle = _grAllHandles[_animeNo];
	}

	if (_jump == true)
	{		_x += _vx;
			modeGame->_newMapChips->IsHit(*this, _vx, 0);
			_vy += _g;
			auto avy = std::abs(_vy);
			if (avy > 15) {
				avy = 15;
			}
			_vy = (_vy < 0) ? -avy : avy;
			_y += _vy;
			modeGame->_newMapChips->IsHit(*this, 0, _vy);

			if (_y >= (_grandY - 1))
			{
				_vy = -E * _vy;
				//_vx = -E * _vx;
				//_stand = true;
				/*if (std::abs(_vy)  < 1.0) {
					_vx = 0;
					_vy = 0;
					_jump = false;
				}*/

				if (_cnt >= 60 * 3) {
					_vx = 0;
					_vy = 0;
					_jump = false;
					/*_cnt = 0;*/
				}
			}
	}
	
	

	//if (_xJump == true)
	//{
	//	if (_coinDir == 0)
	//	{
	//		//_vx += _g;
	//		_x += _vx;
	//		if (_vx >= 10)
	//		{
	//			_vx = 0;
	//			_xJump = false;
	//		}
	//	}
	//	if (_coinDir == 1)
	//	{
	//		//_vx -= _g;
	//		_x += _vx;
	//		if (_vx <= -10)
	//		{
	//			_vx = 0;
	//			_xJump = false;
	//		}
	//	}
	//}
	
	

	//if (_stand == true)
	//{
	//	_vy = -E * _vy;
	//	_vy += _g;
	//	_y += _vy;

	//	_stand = false;
	//	_jump = true;

	//	/*_stand = false;*/
	//	if (_standCoolTime >= 10)
	//	{
	//		_standCoolTime = 0;
	//		_standEnd = true;
	//		_stand = false;
	//	}
	//	_standCoolTime++;
	//}

	//if (_standEnd == true)
	//{
	//	_vy = 0;

	//	_standEnd = false;

	//	
	//}

	

	/*if (_cnt == 1000)
	{
		_x = rand() % 1280;
		_y = rand() % 720;
		_cnt =0;
	}*/

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	{
		/*if ((*ite)->GetType() == _id) {
			continue;
		}*/
		switch ((*ite)->GetType()) {
		case ObjectBase::OBJECTTYPE::PLAYER1:
		{
			if (_whoCoin == 0)
			{
				break;
			}

			if (IsHit(*(*ite)) == true) {


				if (GetCoinType() == COINTYPE::FILDCOIN)
				{
					auto ply = dynamic_cast<Player*>(*ite);

					ply->SetStarCoinNum1();
					if (ply->GetStarCoinNum1() == 10)
					{
						ply->SetStarCoinNumReset();
						ply->SetStarCoinNum10();
					}

					g._objServer.Del(this);

					(*ite)->GetCoin(g);
					modeGame->_isAddCoin = true;


					//コインをゲットした時のエフェクト
					/*ply->GetCoinEffect();*/
					modeGame->AddCoinGetEffect(_StarCoinGetEffectPos);

					
					// SE再生
					PlaySoundMem(g._se["CoinGet"], DX_PLAYTYPE_BACK);
				}

				if (GetCoinType() == COINTYPE::PLAYERCOIN)
				{
					g._objServer.Del(this);

					(*ite)->GetPlayerCoin(g);

					// SE再生
					PlaySoundMem(g._se["PlayerCoinGet"], DX_PLAYTYPE_BACK);
				}

			}
		}

			
			break;

		case ObjectBase::OBJECTTYPE::PLAYER2:

			if (_whoCoin == 1)
			{
				break;
			}

			if (IsHit(*(*ite)) == true) {

				if (GetCoinType() == COINTYPE::FILDCOIN)
				{
					auto ply = dynamic_cast<Player*>(*ite);

					ply->SetStarCoinNum1();
					if (ply->GetStarCoinNum1() == 10)
					{
						ply->SetStarCoinNumReset();
						ply->SetStarCoinNum10();
					}

					g._objServer.Del(this);

					(*ite)->GetCoin(g);
					modeGame->_isAddCoin = true;

					//コインをゲットした時のエフェクト
					/*ply->GetCoinEffect();*/
					modeGame->AddCoinGetEffect(_StarCoinGetEffectPos);


					// SE再生
					PlaySoundMem(g._se["CoinGet"], DX_PLAYTYPE_BACK);
				}

				if (GetCoinType() == COINTYPE::PLAYERCOIN)
				{
					g._objServer.Del(this);

					(*ite)->GetPlayerCoin(g);

					// SE再生
					PlaySoundMem(g._se["PlayerCoinGet"], DX_PLAYTYPE_BACK);
				}

			}
			break;

		case ObjectBase::OBJECTTYPE::PLAYER3:

			if (_whoCoin == 2)
			{
				break;
			}


			if (IsHit(*(*ite)) == true) {

				if (GetCoinType() == COINTYPE::FILDCOIN)
				{
					auto ply = dynamic_cast<Player*>(*ite);

					ply->SetStarCoinNum1();
					if (ply->GetStarCoinNum1() == 10)
					{
						ply->SetStarCoinNumReset();
						ply->SetStarCoinNum10();
					}

					g._objServer.Del(this);

					(*ite)->GetCoin(g);
					modeGame->_isAddCoin = true;

					//コインをゲットした時のエフェクト
					/*ply->GetCoinEffect();*/
					modeGame->AddCoinGetEffect(_StarCoinGetEffectPos);

					// SE再生
					PlaySoundMem(g._se["CoinGet"], DX_PLAYTYPE_BACK);
				}

				if (GetCoinType() == COINTYPE::PLAYERCOIN)
				{
					g._objServer.Del(this);

					(*ite)->GetPlayerCoin(g);

					// SE再生
					PlaySoundMem(g._se["PlayerCoinGet"], DX_PLAYTYPE_BACK);
				}

			}
			break;

		case ObjectBase::OBJECTTYPE::PLAYER4:

			if (_whoCoin == 3)
			{
				break;
			}

			if (IsHit(*(*ite)) == true) {

				if (GetCoinType() == COINTYPE::FILDCOIN)
				{
					auto ply = dynamic_cast<Player*>(*ite);

					ply->SetStarCoinNum1();
					if (ply->GetStarCoinNum1() == 10)
					{
						ply->SetStarCoinNumReset();
						ply->SetStarCoinNum10();
					}

					g._objServer.Del(this);

					(*ite)->GetCoin(g);
					modeGame->_isAddCoin = true;

					//コインをゲットした時のエフェクト
					/*ply->GetCoinEffect();*/
					modeGame->AddCoinGetEffect(_StarCoinGetEffectPos);

					// SE再生
					PlaySoundMem(g._se["CoinGet"], DX_PLAYTYPE_BACK);
				}

				if (GetCoinType() == COINTYPE::PLAYERCOIN)
				{
					g._objServer.Del(this);

					(*ite)->GetPlayerCoin(g);

					// SE再生
					PlaySoundMem(g._se["PlayerCoinGet"], DX_PLAYTYPE_BACK);
				}
			
			}
			break;

		default:
			break;
		}
	}

}

//void Coin::Jump(Game& g)
//{
//	for (int i = 0; i < 10; ++i)
//	{
//		_g += 1;
//		_y += _g;
//	}
//	
//}

//void Coin::GetCoin(Game& g)
//{
//	g._objServer.Del(this);
//	/*Sleep(300);*/
//
//	g._objServer.Add(new Coin());
//
//}

void Coin::Draw(Game& g)
{
	auto	sx = _x + _w / 2;
	auto	sy = _y + _h / 2;

	DrawRotaGraph(sx, sy, 1.0, 0.0, _grHandle, TRUE, FALSE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(_x + _hit_x, _y + _hit_y, _x + _hit_x + _hit_w, _y + _hit_y + _hit_h, GetColor(255, 0, 0), TRUE);	// 半透明の赤で当たり判定描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定
}