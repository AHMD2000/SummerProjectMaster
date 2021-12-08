#include "DxLib.h"
#include "ModeCredit.h"
#include "ModeGame.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeTitle.h"


bool ModeCredit::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }

	_cgCredit = ResourceServer::GetHandles("Credit");

	return true;
}

bool ModeCredit::Terminate(Game& g)
{
	base::Terminate(g);
	return true;
}

bool ModeCredit::Process(Game& g)
{
	base::Process(g);

	ModeTitle* modeTitle = (ModeTitle*)g._serverMode->Get("title");

	if (g._gTrg[0] & PAD_INPUT_C)
	{
		// このモードを削除
		g._serverMode->Del(this);

		modeTitle->SetTitleProcess(true);

		//// ゲームモードを追加
		//ModeTitle* modetitle = new ModeTitle();
		//g._serverMode->Add(modetitle, 0, "Title");

		//SE入力
		PlaySoundMem(g._se["TitleBack"], DX_PLAYTYPE_BACK);
	}


	return true;
}
bool ModeCredit::Draw(Game& g)
{
	base::Draw(g);

	DrawGraph(0, 0, _cgCredit, TRUE);
	return true;
}