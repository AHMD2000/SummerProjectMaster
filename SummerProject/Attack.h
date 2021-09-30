#pragma once

#include	"ObjectBase.h"
#include    "Player.h"

class Attack : public ObjectBase
{
public:
	Attack();
	~Attack();
	virtual OBJECTTYPE	GetType() { return ObjectBase::OBJECTTYPE::ATTACK; }

	void	Init();
	void	Process(Game& g);
	void	Attacking(Game& g);

private:
};