#include "DxLib.h"
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "ResourceServer.h"


// プログラムは WinMain から始まります
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetOutApplicationLogValidFlag(false);
	// 初期化 -------------------------------------------------------------------------
	// ＤＸライブラリ初期化処理
	SetGraphMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH);	// 画面の解像度を横1920×縦1080、1ドットあたり32ビットに指定する
	ChangeWindowMode(false);							// ウィンドウモードに指定する
	if (DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット

	// 乱数初期化
	srand((unsigned int)time(NULL));

	// リソースサーバ初期化
	ResourceServer::Init();

	// ゲームクラス
	Game* g = new Game();

	// 1フレームループを組む ----------------------------------------------------------
	while (ProcessMessage() == 0)		// プログラムが終了するまでループ
	{

		// ESCキーが押されてたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)) {
			break;
		}

		g->Input();		// 入力
		g->Process();	// 計算
		g->Draw();		// 描画
	}

	// 解放 ---------------------------------------------------------------------------
	ResourceServer::Release();	// リソースサーバ解放

	delete g;			// ゲームクラスの解放

	DxLib_End();		// ＤＸライブラリ使用の終了処理

	// 終了
	return 0;
}