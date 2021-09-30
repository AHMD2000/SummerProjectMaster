#include "DxLib.h"
#include "ModeGame.h"
#include "game.h"
#include "ResourceServer.h"
#include "AMGLogo.h"
#include "ModeTitle.h"
using namespace AMG;


bool AMGLogo::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }

	_cgAMGlogo = ResourceServer::GetHandles("AMGlogo");
	_a = 0;
	_cnt = 0;
	return true;
}

bool AMGLogo::Terminate(Game& g)
{
	base::Terminate(g);
	return true;
}

bool AMGLogo::Process(Game& g)
{
	base::Process(g);
	if (_cnt < FADEIN_FRAME) {
		_a += FADESPEED;
	}
	else if (_cnt < WAIT_TIME) {
		_a = TRANSPARENCY;
	}
	else if (_cnt < FADEOUT_FRAME) {
		_a -= FADESPEED;
	}
	else // このモードを削除
	{
		g._serverMode->Del(this);

		// ゲームモードを追加
		ModeTitle* modetitle = new ModeTitle();
		g._serverMode->Add(modetitle, 0, "title");
	}
	_cnt++;
	return true;
}



bool AMGLogo::Draw(Game& g)
{
	base::Draw(g);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _a);
	DrawGraph(180, 0, _cgAMGlogo, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	return true;
}