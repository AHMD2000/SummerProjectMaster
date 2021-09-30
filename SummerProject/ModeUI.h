#pragma once

#include	"ModeBase.h"
#include	<vector>
#include	"ObjectBase.h"
#include	"Game.h"
#include	"Effect.h"

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

	int _UILimitTime;

	int _finalBGMCoin = 40;

	bool _fadeOn;

	bool _finalBGM;

	bool _GameMusic = false;

	bool _GameMusicPerformance = true;

	bool _BGMPerformance;

	std::vector<int> _grAllHandles;

	// エフェクトのユニークポインタの動的配列
	std::vector<std::unique_ptr<Effect>> _effects;


};