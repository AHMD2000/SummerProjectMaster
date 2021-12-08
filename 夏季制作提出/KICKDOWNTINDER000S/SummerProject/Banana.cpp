#include "Banana.h"
#include "Game.h"
#include "Player.h"
#include "ResourceServer.h"
#include <Dxlib.h>

Banana::Banana(ObjectBase::OBJECTTYPE id,int ply/*,Banana::CHARACTER character*/)
	:_id(id),_haveChara(ply)/*,_character(character)*/
{
	Init();
}

Banana::~Banana()
{
}

void Banana::Init()
{
	_item_cnt = 0;
	_w = 80;
	_h = 80;
	_hit_x = -28;
	_hit_y = -62;
	_hit_w = 60;
	_hit_h = 50;

	if (_haveChara == 1)
	{
		_grHandle = ResourceServer::GetHandles("banana0");
	}
	else if (_haveChara == 2)
	{
		_grHandle = ResourceServer::GetHandles("banana1");
	}
	else if (_haveChara == 3)
	{
		_grHandle = ResourceServer::GetHandles("banana2");
	}
	else if (_haveChara == 4)
	{
		_grHandle = ResourceServer::GetHandles("banana3");
	}
}

void Banana::Process(Game& g)
{
	ObjectBase::Process(g);

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");
	
	if (_item_cnt > 60 * 10 )
	{
		g._objServer.Del(this);
	}

	if (_charaDir == 1)
	{
		modeGame->_newMapChips->IsHit(*this, 0, -1);
	}
	if (_charaDir == 0)
	{
		modeGame->_newMapChips->IsHit(*this, 0, 1);
	}
	if (_charaDir == 2)
	{
		modeGame->_newMapChips->IsHit(*this, -1, 0);
	}
	if (_charaDir == 3)
	{
		modeGame->_newMapChips->IsHit(*this, 1, 0);
	}

	/*if (_mapchip.CheckHit(_x / _mapchip.CHIPSIZE_W, _y / _mapchip.CHIPSIZE_H))
	{
		g._objServer.Del(this);
	}*/

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	{

		Vector2	bananaNock { 0,0 };
		Vector2	playerNock { 0,0 };

		if ((*ite)->GetType() == _id) {
			continue;
		}

		switch ((*ite)->GetType()) {
		case ObjectBase::OBJECTTYPE::PLAYER1:
		{
			auto ply = dynamic_cast<Player*>(*ite);

			if (IsHit(*(*ite)) == true) {
				if (_haveChara == 1)
				{
					break;
				}

				if (ply->_specialMode == true)
				{

					Damage(g);

					// SEçƒê∂
					PlaySoundMem(g._se["StarAttackBanana"], DX_PLAYTYPE_BACK);
					break;
				}

				/*if (GetCharacter() == _character)
				{
					break;
				}*/

				for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
				{
					switch ((*ite)->GetType()) {
					case ObjectBase::OBJECTTYPE::PLAYER2:
					{

						auto ply2 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 2)
						{
							ply2->SetBananaAttackHit1();
							if (ply2->GetBananaAttackHit1() == 10)
							{
								ply2->SetBananaAttackHitReset();
								ply2->SetBananaAttackHit10();
							}
						}

						break;
					}

					case ObjectBase::OBJECTTYPE::PLAYER3:
					{

						auto ply3 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 3)
						{
							ply3->SetBananaAttackHit1();
							if (ply3->GetBananaAttackHit1() == 10)
							{
								ply3->SetBananaAttackHitReset();
								ply3->SetBananaAttackHit10();
							}
						}

						break;
					}

					case ObjectBase::OBJECTTYPE::PLAYER4:
					{
						auto ply4 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 4)
						{
							ply4->SetBananaAttackHit1();
							if (ply4->GetBananaAttackHit1() == 10)
							{
								ply4->SetBananaAttackHitReset();
								ply4->SetBananaAttackHit10();
							}
						}

						break;
					}
					}

				}

				if (ply->_coin <= 10)
				{
					ply->SetOverCoin(true);
					ply->SetOverCoinNum(ply->_coin);
				}
				else
				{
					ply->_bananaAttack = true;
					ply->_fallCoin = true;
				}
				
				bananaNock.x = _x;
				bananaNock.y = _y;

				playerNock.x = ply->_x;
				playerNock.y = ply->_y;

				ply->_nockBackpos = playerNock - bananaNock;

				Damage(g);
				(*ite)->NockBackMode(g);
				(*ite)->BananaDamage(g);
				

				// SEçƒê∂
				PlaySoundMem(g._se["BananaAttack"], DX_PLAYTYPE_BACK);

				
			}
			break;
		}

		case ObjectBase::OBJECTTYPE::PLAYER2:
		{
			auto ply = dynamic_cast<Player*>(*ite);

			if (IsHit(*(*ite)) == true) {

				if (_haveChara == 2)
				{
					break;
				}

				if (ply->_specialMode == true)
				{
					Damage(g);

					// SEçƒê∂
					PlaySoundMem(g._se["StarAttackBanana"], DX_PLAYTYPE_BACK);
					break;
				}

				for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
				{
					switch ((*ite)->GetType()) {
					case ObjectBase::OBJECTTYPE::PLAYER1:
					{
						auto ply1 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 1)
						{
							ply1->SetBananaAttackHit1();
							if (ply1->GetBananaAttackHit1() == 10)
							{
								ply1->SetBananaAttackHitReset();
								ply1->SetBananaAttackHit10();
							}
						}

						break;
					}

					case ObjectBase::OBJECTTYPE::PLAYER3:
					{
						auto ply3 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 3)
						{
							ply3->SetBananaAttackHit1();
							if (ply3->GetBananaAttackHit1() == 10)
							{
								ply3->SetBananaAttackHitReset();
								ply3->SetBananaAttackHit10();
							}
						}

						break;
					}
					case ObjectBase::OBJECTTYPE::PLAYER4:
					{
						auto ply4 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 4)
						{
							ply4->SetBananaAttackHit1();
							if (ply4->GetBananaAttackHit1() == 10)
							{
								ply4->SetBananaAttackHitReset();
								ply4->SetBananaAttackHit10();
							}
						}

						break;
					}
					}
				}

				

				/*if (GetCharacter() == _character)
				{
					break;
				}*/
				if (ply->_coin <= 10)
				{
					ply->SetOverCoin(true);
					ply->SetOverCoinNum(ply->_coin);
				}
				else
				{
					ply->_bananaAttack = true;
					ply->_fallCoin = true;
				}

				bananaNock.x = _x;
				bananaNock.y = _y;

				playerNock.x = ply->_x;
				playerNock.y = ply->_y;

				ply->_nockBackpos = playerNock - bananaNock;

				Damage(g);
				(*ite)->NockBackMode(g);
				(*ite)->BananaDamage(g);


				// SEçƒê∂
				PlaySoundMem(g._se["BananaAttack"], DX_PLAYTYPE_BACK);
				
			}

			break;
		}

		case ObjectBase::OBJECTTYPE::PLAYER3:
		{

			auto ply = dynamic_cast<Player*>(*ite);

			if (IsHit(*(*ite)) == true) {

				if (_haveChara == 3)
				{
					break;
				}

				if (ply->_specialMode == true)
				{
					Damage(g);

					// SEçƒê∂
					PlaySoundMem(g._se["StarAttackBanana"], DX_PLAYTYPE_BACK);
					break;
				}

				for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
				{
					switch ((*ite)->GetType()) {
					case ObjectBase::OBJECTTYPE::PLAYER1:
					{
						auto ply1 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 1)
						{
							ply1->SetBananaAttackHit1();
							if (ply1->GetBananaAttackHit1() == 10)
							{
								ply1->SetBananaAttackHitReset();
								ply1->SetBananaAttackHit10();
							}
						}

						break;
					}
					case ObjectBase::OBJECTTYPE::PLAYER2:
					{
						auto ply2 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 2)
						{
							ply2->SetBananaAttackHit1();
							if (ply2->GetBananaAttackHit1() == 10)
							{
								ply2->SetBananaAttackHitReset();
								ply2->SetBananaAttackHit10();
							}
						}

						break;
					}
					case ObjectBase::OBJECTTYPE::PLAYER4:
					{
						auto ply4 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 4)
						{
							ply4->SetBananaAttackHit1();
							if (ply4->GetBananaAttackHit1() == 10)
							{
								ply4->SetBananaAttackHitReset();
								ply4->SetBananaAttackHit10();
							}
						}

						break;
					}
					}
				}

				/*if (GetCharacter() == _character)
				{
					break;
				}*/

				if (ply->_coin <= 10)
				{
					ply->SetOverCoin(true);
					ply->SetOverCoinNum(ply->_coin);
				}
				else
				{
					ply->_bananaAttack = true;
					ply->_fallCoin = true;
				}

				bananaNock.x = _x;
				bananaNock.y = _y;

				playerNock.x = ply->_x;
				playerNock.y = ply->_y;

				ply->_nockBackpos = playerNock - bananaNock;

				Damage(g);
				(*ite)->NockBackMode(g);
				(*ite)->BananaDamage(g);

				// SEçƒê∂
				PlaySoundMem(g._se["BananaAttack"], DX_PLAYTYPE_BACK);
				
			}
			break;

		}

		case ObjectBase::OBJECTTYPE::PLAYER4:

		{

			auto ply = dynamic_cast<Player*>(*ite);

			if (IsHit(*(*ite)) == true) {

				if (_haveChara == 4)
				{
					break;
				}


				if (ply->_specialMode == true)
				{
					Damage(g);

					// SEçƒê∂
					PlaySoundMem(g._se["StarAttackBanana"], DX_PLAYTYPE_BACK);
					break;
				}

				for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
				{
					switch ((*ite)->GetType()) {
					case ObjectBase::OBJECTTYPE::PLAYER1:
					{
						auto ply1 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 1)
						{
							ply1->SetBananaAttackHit1();
							if (ply1->GetBananaAttackHit1() == 10)
							{
								ply1->SetBananaAttackHitReset();
								ply1->SetBananaAttackHit10();
							}
						}

						break;
					}
					case ObjectBase::OBJECTTYPE::PLAYER3:
					{
						auto ply3 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 3)
						{
							ply3->SetBananaAttackHit1();
							if (ply3->GetBananaAttackHit1() == 10)
							{
								ply3->SetBananaAttackHitReset();
								ply3->SetBananaAttackHit10();
							}
						}

						break;
					}
					case ObjectBase::OBJECTTYPE::PLAYER2:
					{
						auto ply4 = dynamic_cast<Player*>(*ite);

						if (_haveChara == 2)
						{
							ply4->SetBananaAttackHit1();
							if (ply4->GetBananaAttackHit1() == 10)
							{
								ply4->SetBananaAttackHitReset();
								ply4->SetBananaAttackHit10();
							}
						}

						break;
					}
					}

				}

				/*if (GetCharacter() == _character)
				{
					break;
				}*/

				if (ply->_coin <= 10)
				{
					ply->SetOverCoin(true);
					ply->SetOverCoinNum(ply->_coin);
				}
				else
				{
					ply->_bananaAttack = true;
					ply->_fallCoin = true;
				}

				bananaNock.x = _x;
				bananaNock.y = _y;

				playerNock.x = ply->_x;
				playerNock.y = ply->_y;

				ply->_nockBackpos = playerNock - bananaNock;

				Damage(g);
				(*ite)->NockBackMode(g);
				(*ite)->BananaDamage(g);

				// SEçƒê∂
				PlaySoundMem(g._se["BananaAttack"], DX_PLAYTYPE_BACK);
				
			}
			/*ply->_bananaAttack = false;*/
			break;

		}

		}
		
	}
	
	_item_cnt++;
}

void Banana::Damage(Game& g)
{
	g._objServer.Del(this);
}

void Banana::Draw(Game& g)
{
	auto	sx = _x - _w / 2;
	auto	sy = _y - _h;

	DrawGraph(static_cast<int>(sx), static_cast<int>(sy), _grHandle, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	//DrawBox(static_cast<int>(_x) + _hit_x, static_cast<int>(_y) + _hit_y, static_cast<int>(_x) + _hit_x + _hit_w, static_cast<int>(_y) + _hit_y + _hit_h, GetColor(255, 0, 0), TRUE);	// îºìßñæÇÃê‘Ç≈ìñÇΩÇËîªíËï`âÊ
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// ïsìßñæï`âÊéwíË
}