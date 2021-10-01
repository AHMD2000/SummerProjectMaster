#pragma once

#include	"ModeBase.h"
#include    "StageGimmic.h"
#include	"BackGround.h"
#include	"Player.h"
#include    "Coin.h"
#include    "mapchips.h"
#include    "newMapchips.h"
#include	<memory>
#include	<vector>
#include	"Effect.h"
#include	"Crown.h"

//class Player;

class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	enum class STATE {
		COUNTDOWN,
		PLAYGAME,
	};

	enum class STAGE
	{
		NORMAL,
	};

	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

	void	AddCoin(Game& g);
	void	AddDebuf(Game& g);
	void	AddStar(Game& g);
	void	AddItem(Game& g);
	/*static	void ChangeisAddCoin();*/

	//フェードエフェクトの追加
	void AddFadeEffect(int color);

	// 爆炎エフェクトの追加
	void AddExplosionEffect(const Vector2& pos);

	// 残像エフェクトの追加
	void AddBlurEffect(const Vector2& pos, int grHandle, double angle);

	// 閃光エフェクトの追加
	void AddSparkEffect(const Vector2& pos);

	//アイテム１のエフェクト
	void AddItem1Effect(const Vector2& pos, int no);

	// アイテム１以外のヒットエフェクトの追加
	void AddHitEffect(const Vector2& pos);

	// コインゲットのエフェクトの追加
	void AddCoinGetEffect(const Vector2& pos);

	// スター状態のエフェクトの追加
	void AddStarStateEffect(const Vector2& pos, Player* ply);

	// アイテムゲットエフェクトの追加
	void AddItemGetEffect(const Vector2& pos);

	// 泥沼エフェクトの追加
	void AddFlarkEffect(const Vector2& pos, Player* ply);


	bool    _isAddCoin;
	bool    _isAddDebuf;
	bool	_stopObjProcess;
	int _bgm;

	std::vector<std::pair<int, ObjectBase::OBJECTTYPE>> _plyRanking;
	/*std::vector<std::unique_ptr<Player>> _plyRanking;*/

	// マップチップ
	NewMapChips* _newMapChips;

	int	getGameCnt() { return _gameCnt;}

	//エフェクトのカウント
	int	getEffectCnt() { return _effectCount; }

	STAGE GetStage() { return _stage; }

	STATE getState() { return _state; }

	STAGE _stage;

private:

	STATE	_state;

	int _effectCount; //エフェクトのカウント

	int	_circleHandle;

	int _debufWaitTime;
	int _starWaitTime;
	int _coinWaitTime;
	int _itemWaitTime;
	int _cnt;
	int _countDownCnt;
	int _gameCnt;//ゲームの制限時間

	// 背景
	BackGround	_bg;

	std::vector<int> _grAllCountDownHandles;// すべてのカウントダウンのグラフィックハンドル

	// マップチップ
	MapChips	_mapChips;

	//王冠
	std::unique_ptr<Crown> _crown;


	// エフェクトのユニークポインタの動的配列
	std::vector<std::unique_ptr<Effect>> _effects;
	//障害物のユニークポインタの動的配列
	std::vector<std::unique_ptr<StageGimmic>> _stageGimmics;

};