#include "SpecialMode.h"
#include "ResourceServer.h"
#include "ModeGame.h"
#include "Game.h"
#include <DxLib.h>
#include "Player.h"
#include "Math.h"

namespace SPECIALATTACK
{
	constexpr auto SPECIALMODEATTAKCOOLTIME = 60 * 10;
}


SpecialMode::SpecialMode(ObjectBase::OBJECTTYPE id, ModeGame& modegame)
	:_id(id), _modeGame(modegame)
{
	_grHandle = ResourceServer::GetHandles("specialAttack");

	Init();
}

SpecialMode::~SpecialMode()
{
}

void SpecialMode::Init()
{
	_itemCnt = 0;

	_w = 80;
	_h = 80;

	_x = rand() % _modeGame._newMapChips->MAPSIZE_W;
	_y = rand() % _modeGame._newMapChips->MAPSIZE_H;

	_hit_x = -40;
	_hit_y = -80;
	_hit_w = 80;
	_hit_h = 80;

	_x *= _modeGame._newMapChips->CHIPSIZE_W;
	_y *= _modeGame._newMapChips->CHIPSIZE_H;
	/*_x += _w / 2;
	_y += _h;*/

	while (_modeGame._newMapChips->IsHit(*this, static_cast<int>(_x), static_cast<int>(_y)) != 0)
	{
		_x = rand() % _modeGame._newMapChips->MAPSIZE_W;
		_y = rand() % _modeGame._newMapChips->MAPSIZE_H;

		_hit_x = -40;
		_hit_y = -80;
		_hit_w = 80;
		_hit_h = 80;

		_x *= _modeGame._newMapChips->CHIPSIZE_W;
		_y *= _modeGame._newMapChips->CHIPSIZE_H;
	}

	_degree = 0.0;

	_angle = Math::ToRadians(_degree);
}

void SpecialMode::Process(Game& g)
{
	auto modeGame =
		dynamic_cast<ModeGame*>(g._serverMode->Get("Game"));

	Vector2 _GetEffectPos{ static_cast<double>(_x), static_cast<double>(_y - 40.0) };

	if (_itemCnt >= 60 * 20)
	{
		Del(g);
	}

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	{
		switch ((*ite)->GetType()) {
		case ObjectBase::OBJECTTYPE::PLAYER1:
		case ObjectBase::OBJECTTYPE::PLAYER2:
		case ObjectBase::OBJECTTYPE::PLAYER3:
		case ObjectBase::OBJECTTYPE::PLAYER4:
			if (IsHit(*(*ite)) == true) {
				g._objServer.Del(this);
				auto ply = dynamic_cast<Player*>(*ite);

				ply->_specialAttack = true;
				ply->_specialAttackCoolTime = SPECIALATTACK::SPECIALMODEATTAKCOOLTIME;

				modeGame->AddItemGetEffect(_GetEffectPos);

				// SEçƒê∂
				PlaySoundMem(g._se["ItemGet"], DX_PLAYTYPE_BACK);


				/*modeGame->_isAddDebuf = true;*/
			}
			break;
		}
	}

	if (_degree == 360)
	{
		_degree = 0;
	}


	_degree += 1.3;
	

	_angle = Math::ToRadians(_degree);

	_itemCnt++;
}

void SpecialMode::Draw(Game& g)
{
	auto	sx = static_cast<int>(_x);
	auto	sy = static_cast<int>(_y) - _h / 2;

	DrawRotaGraph(sx, sy, 1.0, _angle, _grHandle, TRUE, FALSE);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	//DrawBox(_x + _hit_x, _y + _hit_y, _x + _hit_x + _hit_w, _y + _hit_y + _hit_h, GetColor(255, 0, 0), TRUE);	// îºìßñæÇÃê‘Ç≈ìñÇΩÇËîªíËï`âÊ
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// ïsìßñæï`âÊéwíË
}

void SpecialMode::Del(Game& g)
{
	g._objServer.Del(this);
}