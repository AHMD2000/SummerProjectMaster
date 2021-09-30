#include	"Star.h"
#include "ResourceServer.h"
#include "ModeGame.h"
#include "Game.h"
#include <DxLib.h>
#include "Player.h"

namespace StarTime {

	constexpr auto _specialModeCoolTime = 60 * 8;
}


Star::Star(ObjectBase::OBJECTTYPE id, ModeGame& modegame)
	:_id(id),_modeGame(modegame)
{
	ResourceServer::GetHandles("star", _grAllHandles);
	Init();
}

Star::~Star()
{
}

void Star::Init()
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

	while (_modeGame._newMapChips->IsHit(*this, _x, _y) != 0)
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
	
	_animeNo = 0;
	_animeMax = 3;

}

void Star::Process(Game& g)
{

	ObjectBase::Process(g);

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

				ply->_specialMode = true;
				ply->_specialModeAttackCoolTime = StarTime::_specialModeCoolTime;

				modeGame->AddItemGetEffect(_GetEffectPos);

				// SEçƒê∂
				PlaySoundMem(g._se["ItemGet"], DX_PLAYTYPE_BACK);

				/*modeGame->_isAddDebuf = true;*/
			}
			break;
		}
	}

	_animeNo = (_cnt / 16) % _animeMax;
	_grHandle = _grAllHandles[_animeNo];

	_itemCnt++;
}

void Star::Draw(Game& g)
{
	auto	sx = _x - _w / 2;
	auto	sy = _y - _h;

	DrawGraph(sx, sy, _grHandle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(_x + _hit_x, _y + _hit_y, _x + _hit_x + _hit_w, _y + _hit_y + _hit_h, GetColor(255, 0, 0), TRUE);	// îºìßñæÇÃê‘Ç≈ìñÇΩÇËîªíËï`âÊ
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// ïsìßñæï`âÊéwíË
}

void Star::Del(Game& g)
{
	g._objServer.Del(this);
}