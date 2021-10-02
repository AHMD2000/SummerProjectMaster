#include "DxLib.h"
#include "ModeRule.h"
#include "ModeGame.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeTitle.h"

enum class RULESTATE
{
	Rule_Coin,
	Rule_Item,
	Mode_Title,
	Rule_Num
};

static int NowSelect = static_cast<int>(RULESTATE::Rule_Coin);
bool ModeRule::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }

	_cgHandle = ResourceServer::GetHandles("RuleScreen");

	return true;
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
		NowSelect = (NowSelect + 1) % static_cast<int>(RULESTATE::Rule_Num);

		//SE入力
		PlaySoundMem(g._se["TitleMove"], DX_PLAYTYPE_BACK);
	}
	if (g._gTrg[0] & PAD_INPUT_LEFT) {
		NowSelect = (NowSelect + (static_cast<int>(RULESTATE::Rule_Num) - 1)) % static_cast<int>(RULESTATE::Rule_Num);

		//SE入力
		PlaySoundMem(g._se["TitleMove"], DX_PLAYTYPE_BACK);
	}
	switch (NowSelect)
	{
	case static_cast<int>(RULESTATE:: Rule_Coin) :
	{
		_cgHandle = ResourceServer::GetHandles("RuleScreen");

		break;
	}
	

	case static_cast<int>(RULESTATE::Rule_Item) :
	{
		_cgHandle = ResourceServer::GetHandles("RuleCoin");

		break;

	}
	
	case static_cast<int>(RULESTATE::Mode_Title):
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