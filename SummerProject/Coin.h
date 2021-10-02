#pragma once

#include	"ObjectBase.h"
//#include	"ModeGame.h"

constexpr double E = 0.8;//íµÇÀï‘ÇËåWêî

class ModeGame;

class Coin : public ObjectBase {
public:

	enum class COINTYPE
	{
		PLAYERCOIN,
		FILDCOIN,
	};

	Coin(ObjectBase::OBJECTTYPE id, ModeGame& modegame);
	~Coin();
	virtual OBJECTTYPE	GetType() { return _id; }
	virtual	COINTYPE	GetCoinType() { return _coinType; }

	void	Jump(Game& g);

	void	Draw(Game& g) override;

	void	Init();
	void	Process(Game& g);
	/*void	GetCoin(Game& g);*/

	int	_g;
	bool _xJump;
	bool _jump;
	int _whoCoin;
	bool _stand;
	bool _standEnd;

	int _coinDir;

	COINTYPE _coinType;

private:
	ObjectBase::OBJECTTYPE _id;

	int	_standCoolTime;

	bool _coinChange;

	ModeGame& _modeGame;

	MapChips	_mapchip;

	
};