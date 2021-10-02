#include "DxLib.h"
#include "ModeTitle.h"
#include "ModeGame.h"
#include "ModeUI.h"
#include "Game.h"
#include "ResourceServer.h"
#include "ModeRule.h"
#include "ModeCredit.h"


static int NowSelectTitle = static_cast<int>(TITLESTATE::Title_Gamestart); // 現在の選択状況

bool ModeTitle::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }

	// タイトル画像のロード
	_cgTitle = ResourceServer::GetHandles("title");
	_cgTitlename = ResourceServer::GetHandles("titlename");
	_cgGameStart = ResourceServer::GetHandles("GameStart");//ゲーム開始
	_cgRule = ResourceServer::GetHandles("Rule");//ゲーム説明
	_cgwaku = ResourceServer::GetHandles("waku");//選択枠

	//BGM演奏開始
	_bgm = PlayMusic("res/bgm/SUMMER_TRIANGLE.mp3", DX_PLAYTYPE_LOOP);

	return true;
}

bool ModeTitle::Terminate(Game& g)
{
	base::Terminate(g);
	return true;
}

bool ModeTitle::Process(Game& g)
{
	base::Process(g);

	//if (g._gTrg[0] & PAD_INPUT_B)
	//{
	//	// このモードを削除
	//	g._serverMode->Del(this);

	//	// ゲームモードを追加
	//	ModeGame* modeGame = new ModeGame();
	//	g._serverMode->Add(modeGame, 0, "Game");
	//}

	if (_TitleProcess == true)
	{
		if (g._gTrg[0] & PAD_INPUT_DOWN) {// 下を押されたら
			NowSelectTitle = (NowSelectTitle + 1) % static_cast<int>(TITLESTATE::Title_Num);// 選択状態を一つ下げる

			//SE入力
			PlaySoundMem(g._se["TitleMove"], DX_PLAYTYPE_BACK);
		}
		if (g._gTrg[0] & PAD_INPUT_UP) {// 上を押されたら
			NowSelectTitle = (NowSelectTitle + (static_cast<int>(TITLESTATE::Title_Num) - 1)) % static_cast<int>(TITLESTATE::Title_Num);// 選択状態を一つあげる

			 //SE入力
			PlaySoundMem(g._se["TitleMove"], DX_PLAYTYPE_BACK);
		}
		if (g._gTrg[0] & PAD_INPUT_B) {// Bボタンを押されたら
			switch (NowSelectTitle)//選択中の状態によって処理を分岐
			{
				case static_cast<int>(TITLESTATE::Title_Gamestart): // スタート選択中なら
			{
				// このモードを削除
				g._serverMode->Del(this);
				// ゲームモードを追加
				ModeGame* modegame = new ModeGame();
				ModeUI* modeUI = new ModeUI();

				g._serverMode->Add(modegame, 0, "Game");
				g._serverMode->Add(modeUI, 1, "UI");

				modegame->_stage = ModeGame::STAGE::NORMAL;

				//SE入力
				PlaySoundMem(g._se["TitleEnter"], DX_PLAYTYPE_BACK);

				// BGM再生終了
				StopMusic();
			}
			break;

			case static_cast<int>(TITLESTATE::Title_Rule): // ゲーム説明選択中なら
			{
				//// このモードを削除
				//g._serverMode->Del(this);
				//// タイトルモードを削除
				//g._serverMode->Del(g._serverMode->Get("Title"));
				// ゲーム説明を追加
				ModeRule* moderule = new ModeRule();
				g._serverMode->Add(moderule, 1, "RuleScreen");

				SetTitleProcess(false);

				//SE入力
				PlaySoundMem(g._se["TitleEnter"], DX_PLAYTYPE_BACK);


			}
			break;

			case static_cast<int>(TITLESTATE::Title_Credit): // クレジット選択中なら
			{
				//// このモードを削除
				//g._serverMode->Del(this);
				//// タイトルモードを削除
				//g._serverMode->Del(g._serverMode->Get("Title"));
				// クレジットを追加
				ModeCredit* modecredit = new ModeCredit();
				g._serverMode->Add(modecredit, 1, "Credit");

				SetTitleProcess(false);


				//SE入力
				PlaySoundMem(g._se["TitleEnter"], DX_PLAYTYPE_BACK);
			}
			break;

			}

		}
	}


	return true;
}

bool ModeTitle::Draw(Game& g)
{
	base::Draw(g);

	DrawGraph(0, 0, _cgTitle, FALSE);

	/*DrawGraph(360, 120, _cgTitlename, TRUE);*/

	/*DrawGraph(120, 560, _cgGameStart, TRUE);

	DrawGraph(120, 760, _cgRule, TRUE);*/

	int _wakuY = 0;
	switch (NowSelectTitle) // 選択状態によって処理を分岐
	{
	case static_cast<int>(TITLESTATE::Title_Gamestart): // スタート選択中なら
		_wakuY = 730;   // スタートの座標を格納
		break;
		case static_cast<int>(TITLESTATE::Title_Rule): // 説明選択中なら
		_wakuY = 810;   // 説明の座標を格納
		break;
	case static_cast<int>(TITLESTATE::Title_Credit): // クレジット選択中なら
		_wakuY = 890;   // クレジットの座標を格納
		break;
	}
	DrawGraph(165, _wakuY, _cgwaku, TRUE);

	return true;
}