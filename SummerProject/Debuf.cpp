#include	"Debuf.h"
#include "ResourceServer.h"
#include "Game.h"
#include <DxLib.h>
#include "ModeGame.h"
#include "Player.h"


Debuf::Debuf(ObjectBase::OBJECTTYPE id, ModeGame& modegame)
	:_id(id),_modeGame(modegame)
{
	_grHandle = ResourceServer::GetHandles("Debuf");
	Init();
}

Debuf::~Debuf()
{
}

void Debuf::Init()
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
	
	_bright = 255;

}

void Debuf::Process(Game& g)
{


	if (_itemCnt >= 60 * 20)
	{
		Del(g);
	}

	auto modeGame =
		dynamic_cast<ModeGame*>(g._serverMode->Get("Game"));

	Vector2 _GetEffectPos{ static_cast<double>(_x), static_cast<double>(_y - 40.0) };

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

				if (ply->_specialMode == true)
				{

					// SEÄ¶
					PlaySoundMem(g._se["StarAttackDebuf"], DX_PLAYTYPE_BACK);

					break;
				}

				ply->_isDebuf = true;
				ply->_debufCoolTime = 60 * 5;


				/*_plyEffectPos.x = static_cast<double>(ply->_x);*/

				/*_plyEffectPos.y = static_cast<double>(ply->_y);*/

				modeGame->AddItemGetEffect(_GetEffectPos);

				
				// SEÄ¶
				PlaySoundMem(g._se["DebufGet"], DX_PLAYTYPE_BACK);
				
				/*modeGame->_isAddDebuf = true;*/
			}
			break;
		}
	}

	if (_bright <= 128)
	{
		_bright = 255;
	}

	_bright -= 2;

	_itemCnt++;
}

void Debuf::Draw(Game& g)
{
	auto	sx = _x - _w / 2;
	auto	sy = _y - _h;

	SetDrawBright(_bright, _bright, _bright);
	DrawGraph(sx, sy, _grHandle, TRUE);
	SetDrawBright(255, 255, 255);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	//DrawBox(_x + _hit_x, _y + _hit_y, _x + _hit_x + _hit_w, _y + _hit_y + _hit_h, GetColor(255, 0, 0), TRUE);	// ”¼“§–¾‚ÌÔ‚Å“–‚½‚è”»’è•`‰æ
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// •s“§–¾•`‰æŽw’è
}

void Debuf::Del(Game& g)
{
	g._objServer.Del(this);
}
