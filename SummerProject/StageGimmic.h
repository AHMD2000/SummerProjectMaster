#pragma once

#include	"ObjectBase.h"

class StageGimmic : public ObjectBase
{
public:

	enum class STATE
	{
		FLARKBIG,
		FLARKSMALL,
		FALLENTREE,
		FALLENTREE2,
		FALLENTREEFLOWER,
		ROCK,
		RAKE,
	};

	STATE _state;

	StageGimmic(ObjectBase::OBJECTTYPE id, STATE state);
	~StageGimmic();

	virtual OBJECTTYPE	GetType() { return _id; }
	STATE GetState() { return _state; }


	void	Draw(Game& g) override;

	void	Init();
	void	Process(Game& g);

	double SetAngle( double angle) { return _angle = angle; }

private:

	ObjectBase::OBJECTTYPE _id;

	double _angle;
};