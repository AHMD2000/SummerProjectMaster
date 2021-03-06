#pragma once

#include	"ModeBase.h"
#include	"Effect.h"
#include	<vector>



enum class TITLESTATE
{
	Title_Gamestart,  // ゲーム開始
	Title_Rule,   // ゲーム説明
	Title_Credit,  //クレジット
	Title_Num     // 本項目の数

};

//static int NowSelect = Title_Gamestart; // 現在の選択状況

class ModeTitle : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

	bool SetTitleProcess(bool no) {
		return _TitleProcess = no;
	}

protected:

	bool _TitleProcess = true;

	// タイトル
	int		_cgTitle = 0;

	int _a = 0;

	int		_waku = 0;
	int		_cgTitlename = 0;
	int		_cgGameStart = 0;
	int		_cgRule = 0;
	int		_cgwaku = 0;

	int		_titleCnt = 0;

	int		_fadInCnt = 0;

	bool	_fadeIn = false;

	// エフェクトのユニークポインタの動的配列
	std::vector<std::unique_ptr<Effect>> _effects;

	int _bgm = 0;
};
