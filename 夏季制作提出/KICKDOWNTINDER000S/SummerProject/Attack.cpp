#include "DxLib.h"
#include "Attack.h"
#include "Game.h"
#include "ResourceServer.h"

Attack::Attack()
{
	Init();
}

Attack::~Attack()
{
}

void Attack::Init()
{
	_w = 32;
	_h = 32;

	_hit_x = 0;
	_hit_y = 0;
	_hit_w = 32;
	_hit_h = 32;
}

void Attack::Process(Game& g)
{
	ObjectBase::Process(g);

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	{
		
		if ((*ite)->GetType() == ObjectBase::OBJECTTYPE::PLAYER1)
		{
			
			if (IsHit(*(*ite)) == true)
			{
				
				Attacking(g);				// this はこのオブジェクト（攻撃）
				(*ite)->Attacking(g);		// (*ite) はプレイヤーオブジェクト
			}
		}
	}


}

void Attack::Attacking(Game& g)
{
	g._objServer.Del(this);

}