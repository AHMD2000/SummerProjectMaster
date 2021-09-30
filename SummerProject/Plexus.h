#pragma once
#include	"ObjectBase.h"

class Plexus : public ObjectBase
{
public:

	enum class STATE
	{
		BIG,
		SMALL,
	};

	STATE _state;

	Plexus(ObjectBase::OBJECTTYPE id, STATE state);
	~Plexus();

	virtual OBJECTTYPE	GetType() { return _id; }
	STATE GetState() { return _state; }


	void	Draw(Game& g) override;

	void	Init();
	void	Process(Game& g);
private:

	ObjectBase::OBJECTTYPE _id;

};