#include "DxLib.h"
#include "ObjectBase.h"
#include "Game.h"
#include <sstream>
#include "Vector.h"


ObjectBase::ObjectBase()
{
	Init();
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Init()
{
	_cnt = 0;
}

void ObjectBase::Update(int freamCount, Game& g)
{
}

void ObjectBase::Process(Game& g)
{
	_cnt++;
}

void ObjectBase::Draw(Game& g)
{
	/*int x, y;
	x = _x + _vx - g._mapChips._scrX;
	y = _y + _vy - g._mapChips._scrY;*/

	DrawGraph(_x, _y,_grHandle, TRUE);
	/*DrawGraph(x, y, _grHandle, TRUE);*/

	 /*開発用。当たり判定を表示する*/
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		// 半透明描画指定
	DrawBox(_x  + _hit_x, _y  + _hit_y, _x  + _hit_x + _hit_w,_y  + _hit_y + _hit_h, GetColor(255, 0, 0), TRUE);	// 半透明の赤で当たり判定描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定
	/*std::stringstream ss;
	ss << "_CoinFrameCount(" << _cnt << ")\n";
	DrawString(0, 48, ss.str().c_str(), GetColor(255, 255, 255));*/


}

bool ObjectBase::IsHit(ObjectBase& o)
{
	// このオブジェクトと、別オブジェクトoを、x,y,w,hで比較する
	if (_x + _hit_x < o._x + o._hit_x + o._hit_w && o._x + o._hit_x < _x + _hit_x + _hit_w		// x方向の判定
		&& _y + _hit_y < o._y + o._hit_y + o._hit_h && o._y + o._hit_y < _y + _hit_y + _hit_h		// y方向の判定
		)
	{
		// 2つのboxは当たっている
		return true;
	}

	// 2つのboxは当たっていない
	return false;
}
bool ObjectBase::IsHitA(ObjectBase& o)
{
	if (_x + _hita_x < o._x + o._hit_x + o._hit_w && o._x + o._hit_x < _x + _hita_x + _hita_w		// x方向の判定
		&& _y + _hita_y < o._y + o._hit_y + o._hit_h && o._y + o._hit_y < _y + _hita_y + _hita_h		// y方向の判定
		)
	{
		// 2つのboxは当たっている
		return true;
	}
	return false;
}

bool ObjectBase::IsHitAA(ObjectBase& o)
{
	if (_x + _hita_x < o._x + o._hita_x + o._hita_w && o._x + o._hita_x < _x + _hita_x + _hita_w		// x方向の判定
		&& _y + _hita_y < o._y + o._hita_y + o._hita_h && o._y + o._hita_y < _y + _hita_y + _hita_h		// y方向の判定
		)
	{
		// 2つのboxは当たっている
		return true;
	}

	return false;
}