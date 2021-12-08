#pragma once

#include	"ObjectBase.h"
#include	<vector>
#include	<memory>


constexpr auto PLAYERMAX = 4;

class Player;

class Crown : public ObjectBase
{
public:

	Crown(ObjectBase::OBJECTTYPE id);
	~Crown();

	virtual OBJECTTYPE	GetType() { return _id; }

	void	Draw(Game& g) override;

	void	Init();
	void	Process(Game& g);

private:

	ObjectBase::OBJECTTYPE _id;

	bool _getPlyPtr;

	std::vector<Player*> _ply;
};