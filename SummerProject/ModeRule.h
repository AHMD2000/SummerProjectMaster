#pragma once


#include	"ModeBase.h"
#include <DxLib.h>


class ModeRule : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

protected:

	/*int     _cgRuleScreen;
	int     _cgwaku2;
	int     _cgCoinatume;
	int     _cgItemGimmick;
	int     _cgToTitle;*/
	int NowSelect;

	int		_cgHandle = 0;
};