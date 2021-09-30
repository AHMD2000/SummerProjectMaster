#include	"StageGimmic.h"
#include	"ResourceServer.h"
#include	<DxLib.h>

StageGimmic::StageGimmic(ObjectBase::OBJECTTYPE id, STATE state)
	:_id(id), _state(state), _angle(0.0)
{
	if (GetState() == STATE::FLARKBIG)
	{
		_grHandle = ResourceServer::GetHandles("Flark_big");
	}
	else if(GetState() == STATE::FLARKSMALL)
	{
		_grHandle = ResourceServer::GetHandles("Flark_small");
	}
	else if (GetState() == STATE::RAKE)
	{
		_grHandle = ResourceServer::GetHandles("Rake");
	}
	else if (GetState() == STATE::FALLENTREE)
	{
		_grHandle = ResourceServer::GetHandles("FallenTree");
	}
	else if (GetState() == STATE::FALLENTREE2)
	{
		_grHandle = ResourceServer::GetHandles("FallenTree2");
	}
	else if (GetState() == STATE::FALLENTREEFLOWER)
	{
		_grHandle = ResourceServer::GetHandles("FallenTreeFlower");
	}
	else if (GetState() == STATE::ROCK)
	{
		_grHandle = ResourceServer::GetHandles("Rock");
	}

	Init();
}

StageGimmic::~StageGimmic()
{
}

void StageGimmic::Init()
{
	if (GetState() == STATE::FLARKBIG)
	{
		_w = 540;
		_h = 360;

		_x = 233 + _w / 2;
		_y = 469 + _h;

		
	}
	else if (GetState() == STATE::FLARKSMALL)
	{
		_w = 272;
		_h = 181;

		_x = 1045 + _w / 2;
		_y = 176 + _h;

		
	}
	else if (GetState() == STATE::RAKE)
	{
		_w = 332;
		_h = 212;

		_x = 219 + _w / 2;
		_y = 476 + _h;

		
	}
	else if (GetState() == STATE::FALLENTREE)
	{
		_w = 299;
		_h = 120;

		_x = 539 + _w / 2;
		_y = 375 + _h;

		
	}
	else if (GetState() == STATE::FALLENTREE2)
	{
		_w = 105;
		_h = 267;

		_x = 916 + _w / 2;
		_y = 474 + _h;


	}
	else if (GetState() == STATE::FALLENTREEFLOWER)
	{
		_w = 300;
		_h = 139;

		_x = 1257 + _w / 2;
		_y = 510 + _h;


	}
	else if (GetState() == STATE::ROCK)
	{
		_w = 225;
		_h = 149;

		_x = 925 + _w / 2;
		_y = -30 + _h;

		
	}
}

void StageGimmic::Process(Game& g)
{
	ObjectBase::Process(g);
}

void StageGimmic::Draw(Game& g)
{
	auto sx = _x;
	auto sy = _y - _h / 2;


	DrawRotaGraph(sx, sy,1.0, _angle, _grHandle, TRUE, FALSE);
}
