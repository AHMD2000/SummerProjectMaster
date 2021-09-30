#pragma once
#include <vector>
#include <iostream>
#include <utility>
#include <string>

class Game;

// オブジェクトクラス
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

	// // ModeGameクラスの参照を取得
	//ModeGame& GetModeGame() const { return _modeGame; }

	void	SetPosition(int x, int y) { _x = x; _y = y; }
	int		GetW() { return _w; }
	int		GetH() { return _h; }

	std::pair<int , OBJECTTYPE> _plyCoin;

public:
	double		_vx, _vy;
	int _charaDirSlide;
	int _charaDir;
	std::vector<int> _grAllHandles;// すべてのグラフィックハンドル
	int _grHandle;  // 現在のグラフィックハンドル
	int _animeNo;   // アニメ番号
	int _animeMax;        // アニメ最大数
	int		_x, _y;		// 座標
	int		_w, _h;		// 大きさ
	double		_spd;		// 移動速度
	int _grandY;

	/*ModeGame& _modeGame;*/

	// 当たり判定用（座標_x,_y位置からの差分）
	int		_hita_x, _hita_y;
	int		_hita_w, _hita_h;
	int		_hit_x, _hit_y;
	int		_hit_w, _hit_h;

	int		_coin;

	int		_cnt;		// 動作カウンタ

};
