#pragma once

#include	"ModeBase.h"


class ModeCredit : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);
protected:

	// ƒ^ƒCƒgƒ‹
	int		_cgCredit = 0;

};