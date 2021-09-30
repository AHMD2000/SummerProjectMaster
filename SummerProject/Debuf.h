#pragma once

#include	"ObjectBase.h"
#include	"mapchips.h"
#include	"ModeGame.h"



class Debuf : public ObjectBase
{
public:
	Debuf(ObjectBase::OBJECTTYPE id, ModeGame& modegame);
	~Debuf();

	virtual OBJECTTYPE	GetType() { return _id; }


	void	Draw(Game& g) override;

	void	Init();
	void	Process(Game& g);
	void	Del(Game& g);

private:

	int _bright;

	int _itemCnt;

	ObjectBase::OBJECTTYPE _id;

	ModeGame& _modeGame;

	MapChips	_mapchip;
};

