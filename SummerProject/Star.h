#pragma once

#include	"ObjectBase.h"
#include	"ModeGame.h"

class Star : public ObjectBase
{
public:
	Star(ObjectBase::OBJECTTYPE id, ModeGame& modegame);
	~Star();

	virtual OBJECTTYPE	GetType() { return _id; }


	void	Draw(Game& g) override;

	void	Init();
	void	Process(Game& g);
	void	Del(Game& g);

private:

	int _itemCnt;

	ObjectBase::OBJECTTYPE _id;

	ModeGame& _modeGame;

	MapChips	_mapchip;
};