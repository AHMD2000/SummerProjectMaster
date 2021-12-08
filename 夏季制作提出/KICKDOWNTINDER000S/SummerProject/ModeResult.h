#pragma once

#include	"ModeBase.h"
#include	"ObjectBase.h"
#include	<vector>
#include	<iostream>
#include	<utility>
#include	"Player.h"
#include	<sstream>
#include	"ModeGame.h"
#include	<memory>
#include	"PlayerUI.h"
#include	"ResultCrown.h"

//class ResultCrown;

class ModeResult : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);


protected:

	/*Player	_ply;*/

	bool _fadeOn = true;

	int		_cgResult = 0;

	int _bgm = 0;

	//リザルト画面の王冠のユニークポインタ
	std::unique_ptr<ResultCrown> _resultCrown;

	// エフェクトのユニークポインタの動的配列
	std::vector<std::unique_ptr<Effect>> _effects;

	// プレイヤーUIのユニークポインタの動的配列
	std::vector<std::unique_ptr<PlayerUI>> _plyUIs;

	int _resultCnt = 0;


};