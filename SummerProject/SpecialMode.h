#pragma once

#include "Objectbase.h"
#include "mapchips.h"
#include "ModeGame.h"

class SpecialMode : public  ObjectBase
{
public:
	SpecialMode(ObjectBase::OBJECTTYPE id, ModeGame& modegame);
	~SpecialMode();

	virtual OBJECTTYPE	GetType() { return _id; }

	void	Draw(Game& g) override;

	void	Init();
	void	Process(Game& g);
	void	Del(Game& g);


private:

	float _angle;

	double _degree;

	int _itemCnt;

	ObjectBase::OBJECTTYPE _id;

	ModeGame& _modeGame;

	MapChips	_mapchip;

};