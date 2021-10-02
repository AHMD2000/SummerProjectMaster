#include	"Plexus.h"
#include	"ResourceServer.h"
#include	"Game.h"
#include	<DxLib.h>


Plexus::Plexus(ObjectBase::OBJECTTYPE id, STATE state)
	:_id(id),_state(state)
{
	if (GetState() == STATE::BIG)
	{
		_grHandle = ResourceServer::GetHandles("Plexus_big");
	}
	else
	{
		_grHandle = ResourceServer::GetHandles("Plexus_small");
	}
	
	Init();
}

Plexus::~Plexus()
{
}

void Plexus::Init()
{
	if (GetState() == STATE::BIG)
	{
		_x = 960;
		_y = 640;

		_w = 240;
		_h = 240;
	}
	else
	{
		_w = 120;
		_h = 120;
		
		_x = 423 + _w / 2;
		_y = 375 + _h;
	}
	
}

void Plexus::Process(Game& g)
{
	ObjectBase::Process(g);
}

void Plexus::Draw(Game& g)
{
	int sx = static_cast<int>(_x) - _w / 2;
	int sy = static_cast<int>(_y) - _h;
		

	DrawGraph(sx, sy, _grHandle, TRUE);
}