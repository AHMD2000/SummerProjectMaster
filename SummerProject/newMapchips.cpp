/*
** マップチップ
*/

#define	_CRT_SECURE_NO_WARNINGS

#include "DxLib.h"
#include "NewMapChips.h"
#include "ResourceServer.h"
#include "Game.h"
#include "ObjectBase.h"

#include "res/json/picojson.h"


NewMapChips::NewMapChips(std::string filePath, std::string tiledFileName)
{
	// jsonデータからマップデータをロードする
	TiledJsonLoad(filePath, tiledFileName + ".json");

	// チップ画像をロード
	_cgChip = new int[CHIPCOUNT];		// マップチップ画像
	::LoadDivGraph((filePath + _strChipFile).c_str(), CHIPCOUNT, CHIPCOUNT_W, CHIPCOUNT_H, CHIPSIZE_W, CHIPSIZE_H, _cgChip);

	// スクロール値
	_scrX = 0;
	_scrY = 0;

}

NewMapChips::~NewMapChips()
{
	// 確保したメモリを解放する
	delete[]	_cgChip;
	delete[]	_mapData;
}

// 文字列のファイルをロードする
std::string NewMapChips::StringFileLoad(std::string strFileName)
{
	// ファイルを開く
	FILE* fp;
	fp = fopen(strFileName.c_str(), "rb");
	if (fp == NULL)
	{
		// ファイルが開けなかった（ファイル名が違うなど）
		return "";
	}
	// ファイルのサイズを取得
	fseek(fp, 0, SEEK_END); int size = ftell(fp); fseek(fp, 0, SEEK_SET);
	// メモリを確保する
	char* p;
	p = new char[size + 1];
	// メモリにデータを読み込む
	fread(p, 1, size, fp);
	// ファイルを閉じる
	fclose(fp);
	p[size] = '\0';

	// 読み込んだデータをstringにする
	std::string s = (char*)p;

	// メモリを解放する
	delete[] p;

	// stringを返す
	return s;
}

// Tiled-jsonデータロード
int		NewMapChips::TiledJsonLoad(std::string filePath, std::string strFileName)
{
	// ファイルを開いてstringを取得する
	std::string strJson = StringFileLoad(filePath + strFileName);
	if (strJson == "")
	{
		// ファイルが開けなかった
		return 0;
	}

	// 読み込んだstringをjsonオブジェクト化する
	picojson::value json;
	picojson::parse(json, strJson);
	picojson::object jsRoot = json.get<picojson::object>();

	// パラメータをjsonから取得
	MAPSIZE_W = (int)jsRoot["width"].get<double>();
	MAPSIZE_H = (int)jsRoot["height"].get<double>();

	// タイルセット取得(1つのみ対応)
	picojson::array aTileSets = jsRoot["tilesets"].get<picojson::array>();
	picojson::object jsTile = aTileSets[0].get<picojson::object>();
	CHIPCOUNT = (int)jsTile["tilecount"].get<double>();
	CHIPCOUNT_W = (int)jsTile["columns"].get<double>();
	CHIPCOUNT_H = (CHIPCOUNT / CHIPCOUNT_W);		// 計算で出す
	CHIPSIZE_W = (int)jsRoot["tilewidth"].get<double>();
	CHIPSIZE_H = (int)jsRoot["tileheight"].get<double>();
	_strChipFile = jsTile["image"].get<std::string>();

	// レイヤー情報の取得
	picojson::array aLayers = jsRoot["layers"].get<picojson::array>();
	// マップの"tilelayer"レイヤー数を数える
	int layer;
	layer = 0;
	for (int i = 0; i < aLayers.size(); i++)
	{
		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// レイヤーオブジェクト
		// レイヤー種類が「tilelayer」のものをカウントする
		if (jsLayer["type"].get<std::string>() == "tilelayer")
		{
			layer++;
		}
	}
	MAPSIZE_LAYER = layer;

	// レイヤー内データの取得
	_mapData = new int[(int)(MAPSIZE_LAYER * MAPSIZE_W * MAPSIZE_H)];
	layer = 0;
	for (int i = 0; i < aLayers.size(); i++)
	{
		picojson::object jsLayer = aLayers[i].get<picojson::object>();		// レイヤーオブジェクト
		// レイヤー種類が「tilelayer」のものをカウントする
		if (jsLayer["type"].get<std::string>() == "tilelayer")
		{
			picojson::array aData = jsLayer["data"].get<picojson::array>();			// マップ配列
			for (int y = 0; y < MAPSIZE_H; y++)
			{
				for (int x = 0; x < MAPSIZE_W; x++)
				{
					int layerstart = MAPSIZE_W * MAPSIZE_H * layer;
					int index = y * MAPSIZE_W + x;
					_mapData[layerstart + index] = (int)aData[index].get<double>();

				}
			}
			layer++;
		}
	}

	return 1;
}

void	NewMapChips::Process(Game& g)
{
	// カメラがマップデータを超えないようにする
	if (_scrX < 0) { _scrX = 0; }
	if (_scrX > MAPSIZE_W * CHIPSIZE_W - SCREEN_W) { _scrX = MAPSIZE_W * CHIPSIZE_W - SCREEN_W; }
	if (_scrY < 0) { _scrY = 0; }
	if (_scrY > MAPSIZE_H * CHIPSIZE_H - SCREEN_H) { _scrY = MAPSIZE_H * CHIPSIZE_H - SCREEN_H; }

}


void	NewMapChips::Draw()
{
	int x, y, layer;
	for (layer = 0; layer < MAPSIZE_LAYER; layer++)
	{
		for (y = 0; y < MAPSIZE_H; y++)
		{
			for (x = 0; x < MAPSIZE_W; x++)
			{
				int layerstart = MAPSIZE_W * MAPSIZE_H * layer;
				int index = y * MAPSIZE_W + x;
				int pos_x = x * CHIPSIZE_W - _scrX;
				int pos_y = y * CHIPSIZE_H - _scrY;
				int chip_no = _mapData[layerstart + index];
				// .tmxのcsv形式は、透明を0とし、画像のチップは[1]から始まる。
				// そのため、全体的に数値を-1する。透明は-1となるので、if判定を追加
				chip_no--;
				if (chip_no >= 0)
				{
					DrawGraph(pos_x, pos_y, _cgChip[chip_no], TRUE);

					// 開発用：このチップは当たり判定を行うものか？
					if (CheckHit(x, y) != 0)
					{

						SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		// 半透明描画指定
						DrawBox(pos_x, pos_y, pos_x + CHIPSIZE_W, pos_y + CHIPSIZE_H, GetColor(255, 0, 0), TRUE);	// 半透明の赤で当たり判定描画
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定

					}
				}
			}
		}
	}
}





// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
int NewMapChips::CheckHit(int x, int y)
{
	// マップチップ位置はマップデータからはみ出ているか？
	if (0 <= x && x < MAPSIZE_W && 0 <= y && y < MAPSIZE_H)
	{	// はみでていない

		// マップチップIDが0以外は当たり判定を行う
		// 現在、レイヤーは考慮されていない
		int chip_no = _mapData[y * MAPSIZE_W + x];

		// 当たるIDかどうかをチェック
		int idtable[] =
		{
			4,
			-1		// 最後
		};
		int i = 0;
		while (idtable[i] != -1)
		{
			if (chip_no == idtable[i])
			{
				// 当たった
				return chip_no;
			}
			i++;
		}
	}

	// 当たっていない
	return 0;
}

int NewMapChips::CheckHitFlark(int x, int y)
{
	// マップチップ位置はマップデータからはみ出ているか？
	if (0 <= x && x < MAPSIZE_W && 0 <= y && y < MAPSIZE_H)
	{	// はみでていない

		// マップチップIDが0以外は当たり判定を行う
		// 現在、レイヤーは考慮されていない
		int chip_no = _mapData[y * MAPSIZE_W + x];

		// 当たるIDかどうかをチェック
		int idtable[] =
		{
			5,
			-1		// 最後
		};
		int i = 0;
		while (idtable[i] != -1)
		{
			if (chip_no == idtable[i])
			{
				// 当たった
				return chip_no;
			}
			i++;
		}
	}

	// 当たっていない
	return 0;
}


// オブジェクトとマップチップが当たったかの判定、および当たった場合の処理
// 引数：
//   o = オブジェクト
//   mx = Xの移動方向(マイナス:0:プラス)
//   my = Yの移動方向(マイナス:0:プラス)
// 戻値：
//   0 : 当たってない
//   1 : 当たった
int NewMapChips::IsHit(ObjectBase& o, int mx, int my)
{
	int x, y;

	// キャラ矩形を作成する
	int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
	l = o._x + o._hit_x;
	t = o._y + o._hit_y;
	r = o._x + o._hit_x + o._hit_w - 1;
	b = o._y + o._hit_y + o._hit_h - 1;

	// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
	for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++)
	{
		for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++)
		{
			// (x,y)は、マップチップの座標（チップ単位）
			// この位置のチップは当たるか？
			int chip_no = CheckHit(x, y);
			if (chip_no != 0)
			{	// このチップと当たった。
				// X,Yの移動方向を見て、その反対方向に補正する
				if (mx < 0)
				{	// 左に動いていたので、右に補正
					o._x = x * CHIPSIZE_W + CHIPSIZE_W - (o._hit_x);
				}
				if (mx > 0)
				{	// 右に動いていたので、左に補正
					o._x = x * CHIPSIZE_W - (o._hit_x + o._hit_w);
				}
				if (my > 0)
				{	// 下に動いていたので、上に補正
					o._y = y * CHIPSIZE_H - (o._hit_y + o._hit_h);
				}
				if (my < 0)
				{	// 上に動いていたので、下に補正
					o._y = y * CHIPSIZE_H + CHIPSIZE_H - (o._hit_y);
				}
				// 当たったので戻る
				return 1;
			}
		}
	}

	// 当たらなかった
	return 0;
}

int NewMapChips::IsHitFlark(ObjectBase& o, int mx, int my)
{
	int x, y;

	// キャラ矩形を作成する
	int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
	l = o._x + o._hit_x;
	t = o._y + o._hit_y;
	r = o._x + o._hit_x + o._hit_w - 1;
	b = o._y + o._hit_y + o._hit_h - 1;

	// キャラの左上座標～右下座標にあたるマップチップと、当たり判定を行う
	for (y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++)
	{
		for (x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++)
		{
			// (x,y)は、マップチップの座標（チップ単位）
			// この位置のチップは当たるか？
			int chip_no = CheckHitFlark(x, y);
			if (chip_no != 0)
			{	
				// このチップと当たった。
				// 当たったので戻る
				return 1;
			}
		}
	}

	// 当たらなかった
	return 0;
}

