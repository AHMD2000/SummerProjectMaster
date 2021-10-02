#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <string>

class Game;

// �I�u�W�F�N�g�N���X
class ObjectBase {
public:
	ObjectBase();
	~ObjectBase();

	enum class OBJECTTYPE {
		PLAYER1,
		PLAYER2,
		PLAYER3,
		PLAYER4,
		COIN,
		BANANA,
		DEBUF,
		STAR,
		SPECIALMODE,
		PLEXUS,
		GIMMIC,
		EFFECT,
		CROWN,
	};
	virtual OBJECTTYPE	GetType() = 0;

	virtual void	Init();
	virtual void	Process(Game& g);
	virtual void	Update(int freamCount, Game& g);
	virtual void	Draw(Game& g);

	bool	IsHit(ObjectBase& o);
	bool	IsHitA(ObjectBase& o);
	bool	IsHitAA(ObjectBase& o);
	virtual	void	Collision() {}
	virtual	void	Damage(Game& g) {}
	virtual	void	StarDamage(Game& g) {}
	virtual void	BananaDamage(Game& g) {}
	virtual void	RushDamage(Game& g) {}
	virtual	void	NockBackMode(Game& g) {}
	virtual	void	GetCoin(Game& g) {}
	virtual	void	GetPlayerCoin(Game& g) {}
	virtual	void	DamageGetCoin(Game& g) {}
	virtual	void	Attacking(Game& g) {}
	/*virtual	void	ChangeState() {}*/

	// // ModeGame�N���X�̎Q�Ƃ��擾
	//ModeGame& GetModeGame() const { return _modeGame; }

	void	SetPosition(int x, int y) { _x = x; _y = y; }
	int		GetW() { return _w; }
	int		GetH() { return _h; }

	std::pair<int , OBJECTTYPE> _plyCoin;

public:
	double		_vx, _vy;
	int _charaDirSlide;
	int _charaDir;
	std::vector<int> _grAllHandles;// ���ׂẴO���t�B�b�N�n���h��
	int _grHandle;  // ���݂̃O���t�B�b�N�n���h��
	int _animeNo;   // �A�j���ԍ�
	int _animeMax;        // �A�j���ő吔
	double		_x, _y;		// ���W
	int		_w, _h;		// �傫��
	double		_spd;		// �ړ����x
	int _grandY;

	/*ModeGame& _modeGame;*/

	// �����蔻��p�i���W_x,_y�ʒu����̍����j
	int		_hita_x, _hita_y;
	int		_hita_w, _hita_h;
	int		_hit_x, _hit_y;
	int		_hit_w, _hit_h;

	int		_coin;

	int		_cnt;		// ����J�E���^

};
