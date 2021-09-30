#include "DxLib.h"
#include "ModeRule.h"
#include "ModeGame.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeTitle.h"

typedef enum
{
	Rule_Coin,
	Rule_Item,
	Mode_Title,
	Rule_Num
};

static int NowSelect = Rule_Coin;
bool ModeRule::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }

	_cgHandle = ResourceServer::GetHandles("RuleScreen");
}

bool ModeRule::Terminate(Game& g)
{
	base::Terminate(g);
	return true;
}

bool ModeRule::Process(Game& g)
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

	if (g._gTrg[0] & PAD_INPUT_RIGHT) {
		NowSelect = (NowSelect + 1) % Rule_Num;

		//SE入力
		PlaySoundMem(g._se["TitleMove"], DX_PLAYTYPE_BACK);
	}
	if (g._gTrg[0] & PAD_INPUT_LEFT) {
		NowSelect = (NowSelect + (Rule_Num - 1)) % Rule_Num;

		//SE入力
		PlaySoundMem(g._se["TitleMove"], DX_PLAYTYPE_BACK);
	}
	switch (NowSelect)
	{
	case Rule_Coin:
	{
		_cgHandle = ResourceServer::GetHandles("RuleScreen");

		break;
	}
	

	case Rule_Item:
	{
		_cgHandle = ResourceServer::GetHandles("RuleCoin");

		break;

	}
	
	case Mode_Title:
	{
		_cgHandle = ResourceServer::GetHandles("RuleItem");

		break;
	}
	

	}
	return true;
}
bool ModeRule::Draw(Game& g)
{
	base::Draw(g);
	DrawGraph(0, 0, _cgHandle, FALSE);

	return true;
}