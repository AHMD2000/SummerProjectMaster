#pragma once

#include	"ModeBase.h"
#include	<vector>
#include	"ObjectBase.h"
#include	"Game.h"
#include	"Effect.h"
#include	"Player.h"

class ModeUI : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);


	std::vector<std::pair<int, ObjectBase::OBJECTTYPE>> _plyRankingUI;

protected:

	int _UIcnt;

	int _gaugeX, _gaugeY;

	double _maxCoin;
	double _plyCoinRate[4];

	int _grUIgaugeHandle;

	int _UILimitTime = 0;

	int _finalBGMCoin = 40;

	bool _fadeOn = true;

	bool _finalBGM;

	bool _GameMusic = false;

	bool _GameMusicPerformance = true;

	bool _BGMPerformance = false;

	int _fadeCnt;

	bool _SetModeResult;

	std::vector<int> _grAllHandles;

	//バナナ
	std::vector<int> _grAllBananaHandles;

	// エフェクトのユニークポインタの動的配列
	std::vector<std::unique_ptr<Effect>> _effects;

	// プレイヤーの動的配列
	std::vector<Player*> _plys;

	bool _inPlayer = true;


};