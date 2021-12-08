#pragma once

#include	"ObjectBase.h"

class AttackCollision : public ObjectBase {
public:
	AttackCollision(ObjectBase::OBJECTTYPE id);
	~AttackCollision();

	virtual OBJECTTYPE	GetType() { return _id; };

	void Init();
	void Process(Game& g);
	void Damage(Game& g);

private:
	ObjectBase::OBJECTTYPE _id;
};