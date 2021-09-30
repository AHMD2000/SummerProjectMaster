#pragma once

#include "mapchips.h"
#include "ModeServer.h"
#include "ObjectServer.h"
#include "ResourceServer.h"
#include "Vector.h"
#include "Effect.h"

// 画面設定
constexpr auto SCREEN_W = 1920;		///< 画面の横解像度
constexpr auto SCREEN_H = 1080;		///< 画面の縦解像度
constexpr auto SCREEN_DEPTH = 32;   ///< １ドットあたりのビット数

class Effect;

// ゲームクラス
class Game
{
public:
	Game();				// アプリの初期化
	~Game();			// アプリの解放

	void Input();		// フレーム処理：入力
	void Process();		// フレーム処理：計算
	void Draw();		// フレーム処理：描画


// メンバ変数
	// ゲーム情報
	int _gKey[4];// キー入力の情報
	int _gTrg[4];/*トリガー入力*/
    int _gFrameCount;	// 毎フレーム+1するカウント

	ModeServer* _serverMode;

	ObjectServer _objServer;

	// マップチップ
	MapChips	_mapChips;

	// SEマップ
	std::unordered_map<std::string, int>	_se;

};
