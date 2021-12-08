#pragma once
#include "ModeBase.h"

namespace AMG {
	constexpr auto FADEIN_FRAME = 60; // フェードインフレーム
	constexpr auto WAIT_TIME = 120; //表示時間
	constexpr auto FADEOUT_FRAME = 180; // フェードアウトフレーム
	constexpr auto FADESPEED = 5; // フェードのスピード
	constexpr auto TRANSPARENCY = 255; // 透明度

}

class AMGLogo :public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);
protected:

	int _a = 0;
	int _cnt = 0;
	int _cgAMGlogo = 0;
};