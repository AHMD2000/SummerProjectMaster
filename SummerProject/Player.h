#pragma once
#include	"ObjectBase.h"
#include "ModeServer.h"
#include "ModeGame.h"
#include "Vector.h"
#include	<iostream>
#include	<utility>
#include	"newMapchips.h"
#include	"Effect.h"

class Player : public ObjectBase
{
public:
	enum class STATE	{
		IDLE,
		MOVE,
		ATTACK,
		BANANA,
		NOCKBACK,
		RUSH,
	};

	Player(ObjectBase::OBJECTTYPE id,Game& g);
	~Player();
	virtual OBJECTTYPE	GetType() { return _id; };
	void	Init();
	void	Process(Game& g) override;
	void	Draw(Game& g) override;
	void	Collision(Game& g);
	void    GetCoin(Game& g);
	void	GetPlayerCoin(Game& g);
	void    DamageGetCoin(Game& g);
	void	Attack(Game& g);
	void	Damage(Game& g);
	void	StarDamage(Game& g);
	void	BananaDamage(Game& g);
	void	BananaPut(Game& g);
	void	NockBackMode(Game& g);
	void	NockBack(Game& g);
	void	Rush(Game& g);
	void	RushDamage(Game& g);

	void ChangeState(STATE state);

	int	GetId() { return static_cast<int>(_id); }
	int	GetState() { return static_cast<int>(_state); }

	void GetCoinEffect() { _getCoin = true; }

	int GetAttackHit1() { return _attackHit1; }
	int GetAttackHit10() { return _attackHit10; }

	int GetStarCoinNum1() { return _StarCoinGet1; }
	int GetStarCoinNum10() { return _StarCoinGet10; }

	int SetStarCoinNum1() { return _StarCoinGet1++; }
	int SetStarCoinNumReset() { return _StarCoinGet1 = 0; }
	int SetStarCoinNum10() { return _StarCoinGet10++; }

	int GetBananaAttackHit1() { return _bananaAttackHit1; }
	int GetBananaAttackHit10() { return _bananaAttackHit10; }

	int SetBananaAttackHit1() { return _bananaAttackHit1++; }
	int SetBananaAttackHitReset() { return _bananaAttackHit1 = 0; }
	int SetBananaAttackHit10() { return _bananaAttackHit10++; }

	bool SetOverCoin(bool over) {
		return _overCoin = over;
	}

	int SetOverCoinNum(int overcoin) {
		return _overCoinNum = overcoin;
	}

	bool	_bananaAttack;

	bool	_specialAttack;
	bool	_specialMode;
	bool	_specialModeEffect;

	int _specialModeAttackCoolTime;
	int _debufCoolTime;
	int _specialAttackCoolTime;
	bool _isDebuf;
	bool _fallCoin;

	Vector2	_nockBackpos{ 0,0 };




private:
	void Idle(Game& g);
	void Move(Game& g);

	ModeServer* _serverMode;

	NewMapChips* _newMapchip;

	ObjectBase::OBJECTTYPE _id;
	STATE _state;

	int _cooltime;

	int	_oldCoin;

	bool _overCoin = false;

	int _overCoinNum = 0;

	int _bananaAttackHit1;
	int _bananaAttackHit10;

	int _StarCoinGet1;
	int _StarCoinGet10;

	int _attackHit1;
	int _attackHit10;

	bool _finalBGM;

	bool _flarkEffect;

	bool _stateAttack;

	bool _getCoin;

	//int _gameTime = 60 * 90; //ÉQÅ[ÉÄÇÃêßå¿éûä‘

	int _stateCnt;
	int _xBack, _yBack;
	/*int _coin;*/
	static const int ATTACK_MAX = 1;

	int _bananaGage;
	int _bananaGageMax;

	int _specialModeCooltime;
	int _rushAttackCoolTime;
	
	bool _attackMissingSE = true;

	double _specialAttackEffectAngle;

	std::unique_ptr<StarStateEffect>	_starStatefect;
    
	std::unique_ptr<FlarkEffect>	_flarkefect;

	std::vector<int>  _grSpecialEffect;
	std::vector<int> _grDebufEffect;
	std::vector<int>  _grStarCoinGetEffect;

	int _grStandbyBanana;
};