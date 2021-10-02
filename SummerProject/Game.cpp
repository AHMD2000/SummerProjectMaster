#include "DxLib.h"
#include "game.h"
#include <memory>
#include "ModeTitle.h"
#include "ResourceServer.h"
#include "ModeGame.h"
#include "ModeResult.h"
#include "AMGLogo.h"


const ResourceServer::DivGraphMap usedInGame{
  {"player_idle0",  {"res/player_idle0.png", 4, 4, 100, 100}},
  {"player_idle1",  {"res/player_idle1.png", 4, 4, 100, 100}},
  {"player_idle2",  {"res/player_idle2.png", 4, 4, 100, 100}},
  {"player_idle3",  {"res/player_idle3.png", 4, 4, 100, 100}},
  {"player_move0",  {"res/player_idle0.png", 4, 4, 100, 100}},
  {"player_move1",  {"res/player_idle1.png", 4, 4, 100, 100}},
  {"player_move2",  {"res/player_idle2.png", 4, 4, 100, 100}},
  {"player_move3",  {"res/player_idle3.png", 4, 4, 100, 100}},
  {"player_attack0",{"res/player_attack0.png",    5, 4, 400, 400}},
  {"player_attack1",{"res/player_attack1.png",    5, 4, 400, 400}},
  {"player_attack2",{"res/player_attack2.png",    5, 4, 400, 400}},
  {"player_attack3",{"res/player_attack3.png",    5, 4, 400, 400}},
  {"player_rush0",{"res/player_rush0.png",    16, 4, 100, 100}},
  {"player_rush1",{"res/player_rush1.png",    16, 4, 100, 100}},
  {"player_rush2",{"res/player_rush2.png",    16, 4, 100, 100}},
  {"player_rush3",{"res/player_rush3.png",    16, 4, 100, 100}},
  {"player_star",{"res/player_star.png",    4, 4, 100, 100}},
  {"starcoin",   {"res/spinCoin.png",  6, 1, 160, 160}},
  {"playercoin0",   {"res/playerCoin0.png",  1, 1, 50, 50}},
  {"playercoin1",   {"res/playerCoin1.png",  1, 1, 50, 50}},
  {"playercoin2",   {"res/playerCoin2.png",  1, 1, 50, 50}},
  {"playercoin3",   {"res/playerCoin3.png",  1, 1, 50, 50}},
  {"bg",     {"res/bg.jpg",    1, 1, 1920, 1080}},
  {"AMGlogo",     {"res/amg_rogo.png",    1, 1, 1280, 960}},
  {"RuleScreen",     {"res/asobikata.png",    1, 1, 1920, 1080}},
  {"RuleItem",     {"res/Item_gimmick.png",    1, 1, 1920, 1080}},
  {"RuleCoin",     {"res/asobikata_coin.png",    1, 1, 1920, 1080}},
  {"Credit",     {"res/staff_credit.png",    1, 1, 1920, 1080}},
  {"title",     {"res/title.png",    1, 1, 1920, 1080}},
  {"titlename",     {"res/titlename.png",    1, 1, 900, 120}},
  {"GameStart",     {"res/GameStart.png",    1, 1, 360, 120}},
  {"Rule",     {"res/Rule.png",    1, 1, 360, 120}},
  {"waku",     {"res/waku.png",    1, 1, 360, 120}},
  {"result",     {"res/GameResult.jpg",    1, 1, 1920, 1080}},
  {"player_attack0UI",{"res/ResultPlayer0.png",    4, 1, 400, 400}},
  {"player_attack1UI",{"res/ResultPlayer1.png",    4, 1, 400, 400}},
  {"player_attack2UI",{"res/ResultPlayer2.png",    4, 1, 400, 400}},
  {"player_attack3UI",{"res/ResultPlayer3.png",    4, 1, 400, 400}},
  {"banana0",     {"res/banana0.png",    1, 1, 80, 80}},
  {"banana1",     {"res/banana1.png",    1, 1, 80, 80}},
  {"banana2",     {"res/banana2.png",    1, 1, 80, 80}},
  {"banana3",     {"res/banana3.png",    1, 1, 80, 80}},
  {"UI_circle",     {"res/TestCircle.png",    1, 1, 256, 256}},
  {"Debuf",     {"res/debuf.png",    1, 1, 80,80}},
  {"star",	{"res/star.png",	3 ,1 ,80 ,80 }},
  {"specialAttack",	{"res/specialAttack.png",	1 ,1 ,80 ,80 }},
  {"mapchip",     {"res/platformer_simpleA_sheet.png",    8, 3, 40, 40}},
  {"UI",     {"res/playerUI.png",    2, 4, 420, 180}},
  {"UI_gauge",     {"res/UI_gauge.png",    1, 1, 260, 60}},
  {"UI_limitTime",     {"res/limitTimeUI.png",    1, 1, 265, 190}},
  {"Plexus_small",     {"res/Plexus_small.png",    1, 1, 120, 120}},
  {"Plexus_big",     {"res/Plexus_big.png",    1, 1, 240, 240}},
  {"Flark_big",     {"res/Flark_big.png",    1, 1, 540, 360}},
  {"Flark_small",     {"res/Flark_small.png",    1, 1, 270, 180}},
  {"Rake",     {"res/rake.png",    1, 1, 332, 212}},
  {"Rock",     {"res/rock.png",    1, 1, 225, 149}},
  {"FallenTree",     {"res/Fallen_tree_Nomal.png",    1, 1, 299, 120}},
  {"FallenTree2",     {"res/FallenTree2.png",    1, 1, 105, 267}},
  {"FallenTreeFlower",     {"res/Fallen_tree.png",    1, 1, 300, 139}},
  {"smoke",   {"res/smoke.png", 8, 8, 32, 32} },
  {"Item1",   {"res/item1_effect.png",  1, 1, 80, 80}},
  {"DebufEffect",   {"res/DebuEffect.png",  5, 2, 96, 96}},
  {"NomalHitEffect",   {"res/NomalHitEffect.png",  2, 4, 256, 256}},
  {"StarCoinGetEffect",   {"res/StarCoinGetEffect.png",  5, 4, 96, 96}},
  {"StarStateEffect",   {"res/RealStarStateEffect.png",  8, 6, 100, 100}},
  {"FlarkEffect",   {"res/FlarkEffect.png",  15, 4, 53, 53}},
  {"ItemGetEffect",   {"res/item_get_effect.png",  5, 2, 96, 96}},
  {"Crown",   {"res/crown.png",  4, 1, 80, 80}},
  {"ResultCoin",   {"res/resultCoin.png",  6, 1, 160, 90}},
  {"CountDown1",   {"res/countDown1.png",  1, 1, 515, 106}},
  {"CountDown2",   {"res/countDown2.png",  1, 1, 514, 106}},
  {"CountDown3",   {"res/countDown3.png",  1, 1, 515, 106}},
  {"CountDownStart",   {"res/countDownGameStart.png",  1, 1, 515, 106}},
  {"StandbyBanana0",   {"res/player_banana0.png",  1, 1, 40, 40}},
  {"StandbyBanana1",   {"res/player_banana1.png",  1, 1, 40, 40}},
  {"StandbyBanana2",   {"res/player_banana2.png",  1, 1, 40, 40}},
  {"StandbyBanana3",   {"res/player_banana3.png",  1, 1, 40, 40}},
};

// アプリの初期化
// 起動時に1回だけ実行される
Game::Game()
	: _gKey{ 0 },_gTrg { 0 }
{
	ResourceServer::LoadTextures(usedInGame);

	_se["Attack"] = ResourceServer::LoadSoundMem("res/se/new_attack_hit.wav");
	_se["BananaPut"] = ResourceServer::LoadSoundMem("res/se/BananaPut.mp3");
	_se["StarCoinAppearance"] = ResourceServer::LoadSoundMem("res/se/StarCoinAppearance.mp3");
	_se["CoinLost"] = ResourceServer::LoadSoundMem("res/se/coin_lost.wav");
	_se["CoinGet"] = ResourceServer::LoadSoundMem("res/se/StarCoinGet.mp3");
	_se["swingVainly"] = ResourceServer::LoadSoundMem("res/se/new_attack_karaburi.wav");
	_se["StarAttack"] = ResourceServer::LoadSoundMem("res/se/StarAttack.mp3");
	_se["ItemAppearance"] = ResourceServer::LoadSoundMem("res/se/ItemAppearance.mp3");
	_se["ItemGet"] = ResourceServer::LoadSoundMem("res/se/ItemGet.mp3");
	_se["PlayerCoinGet"] = ResourceServer::LoadSoundMem("res/se/coin_get_stage.wav");
	_se["DebufGet"] = ResourceServer::LoadSoundMem("res/se/debuf.mp3");
	_se["BananaAttack"] = ResourceServer::LoadSoundMem("res/se/BananaAttack.mp3");
	_se["CountDown"] = ResourceServer::LoadSoundMem("res/se/CountDown.mp3");
	_se["Start"] = ResourceServer::LoadSoundMem("res/se/Start.mp3");
	_se["TitleMove"] = ResourceServer::LoadSoundMem("res/se/title_move.wav");
	_se["TitleBack"] = ResourceServer::LoadSoundMem("res/se/title_back.wav");
	_se["TitleEnter"] = ResourceServer::LoadSoundMem("res/se/title_enter.wav");
	_se["SpecialAttack"] = ResourceServer::LoadSoundMem("res/se/SpecialAttack.mp3");
	_se["SpecialAttackLost"] = ResourceServer::LoadSoundMem("res/se/SpecialAttack.mp3");
	_se["StarAttackDebuf"] = ResourceServer::LoadSoundMem("res/se/StarInvalid.mp3");
	_se["StarAttackBanana"] = ResourceServer::LoadSoundMem("res/se/StarInvalid.mp3");
	_se["SpecialAttackStart"] = ResourceServer::LoadSoundMem("res/se/SpecialAttackStart.mp3");
	_se["TwoNockBack"] = ResourceServer::LoadSoundMem("res/se/TwoNockBack.mp3");
	_se["StarToStar"] = ResourceServer::LoadSoundMem("res/se/StarNockBack.mp3");

	_gFrameCount = 0;

	_serverMode = new ModeServer(*this);

	AMGLogo* amglogo = new AMGLogo();
	_serverMode->Add(amglogo, 0, "AMGlogo");
}

// アプリの解放
// 終了時に1回だけ実行される
Game::~Game()
{
	delete _serverMode;
}



//
// フレーム処理。1フレームに1回ずつ実行される
//

// フレーム処理：入力
void Game::Input()
{
	int keyold[4];
	 keyold[0] =  _gKey[0] ;
	 keyold[1] =  _gKey[1] ;
	 keyold[2] =  _gKey[2] ;
	 keyold[3] =  _gKey[3] ;

	_gKey[0] = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	_gKey[1] = GetJoypadInputState(DX_INPUT_PAD2);
	_gKey[2] = GetJoypadInputState(DX_INPUT_PAD3);
	_gKey[3] = GetJoypadInputState(DX_INPUT_PAD4);


	for (int i = 0; i < 4; i++) {
		_gTrg[i] = (_gKey[i] ^ keyold[i]) & _gKey[i];
	}
}

// フレーム処理：計算
void Game::Process()
{
	_serverMode->ProcessInit();
	_serverMode->Process();
	_serverMode->ProcessFinish();

	/*_mapChips.Process(*this);*/

	_gFrameCount++;
	
}

// フレーム処理：描画
void Game::Draw()
{
	_serverMode->DrawInit();
	_serverMode->Draw();
	_serverMode->DrawFinish();
}