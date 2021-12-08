#pragma once

#include "Crown.h"

class Game;

class ResultCrown : public Crown
{
public:
	ResultCrown(ObjectBase::OBJECTTYPE id);
	~ResultCrown();

	void	Draw(Game& g) override;

	void	Init();
	void	Process(Game& g);

private:

	ObjectBase::OBJECTTYPE _id;
};
