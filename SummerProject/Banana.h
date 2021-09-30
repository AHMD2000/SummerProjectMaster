#pragma once

#include	"ObjectBase.h"
#include	"mapchips.h"

class Banana : public ObjectBase{
public:

	/*enum class CHARACTER {
		kPLAYER1,
		kPLAYER2,
		kPLAYER3,
		kPLAYER4,
	};*/

	Banana(ObjectBase::OBJECTTYPE id, int ply/*,Banana::CHARACTER character*/);
	~Banana();

	


	virtual OBJECTTYPE	GetType() { return _id; };
	/*CHARACTER GetCharacter() { return _character; };*/


	void Init();
	void Process(Game& g);
	void Damage(Game& g);
	void	Draw(Game& g) override;

	int	_haveChara;

private:

	/*CHARACTER _character;*/

	MapChips	_mapchip;

	ObjectBase::OBJECTTYPE _id;
	int _item_cnt;
};