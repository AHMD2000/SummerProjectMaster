#include "AttackCollision.h"
#include "Game.h"
#include "Player.h"

AttackCollision::AttackCollision(ObjectBase::OBJECTTYPE id)
	:_id(id)
{
	Init();
}

AttackCollision::~AttackCollision()
{
}

void AttackCollision::Init()
{
	_hit_x = 100;
	_hit_y = 100;
	_hit_w = 100;
	_hit_h = 100;
}

void AttackCollision::Process(Game& g)
{
	ObjectBase::Process(g);
	/*for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	{
		if ((*ite)->GetType() == _id) {
			continue;
		}
		switch ((*ite)->GetType()) {
			case ObjectBase::OBJECTTYPE::PLAYER1:
			case ObjectBase::OBJECTTYPE::PLAYER2:
			case ObjectBase::OBJECTTYPE::PLAYER3:
			case ObjectBase::OBJECTTYPE::PLAYER4:
				if (IsHit(*(*ite)) == true) {

					Damage(g);
					(*ite)->Damage(g);
				}

		}

	}*/
}

void AttackCollision::Damage(Game& g)
{

	g._objServer.Del(this);
}