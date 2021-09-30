#pragma once

#include <vector>

class Game;
class ObjectBase;

// マップチップクラス
class MapChips {
public:
	MapChips();
	~MapChips();

	void	Process(Game& g);
	void	Draw();

	int		CheckHit(int x, int y);
	int		IsHit(ObjectBase& o, int mx, int my);


public:

	// マップのサイズ（チップ数）
	// .tmxの以下より設定
// <layer name="tile_base" width="64" height="18">
	static const int MAPSIZE_W = 32;	// width
	static const int MAPSIZE_H = 18;	// height

	// チップ画像の個数
	// .tmxの以下より設定
	// <tileset firstgid="1" name="platformer_simpleA_sheet" tilewidth="40" tileheight="40" tilecount="64" columns="8">

	// チップの個数
	static const int CHIPCOUNT = 6;		// tilecount
	static const int CHIPCOUNT_W = 6;		// columns
	static const int CHIPCOUNT_H = (CHIPCOUNT / CHIPCOUNT_W);		// 計算で出す

	// チップのサイズ（pixel数）
	static const int CHIPSIZE_W = 60;
	static const int CHIPSIZE_H = 60;

	// レイヤー数
	static const int MAPSIZE_LAYER = 1;	// 「<layer 」 の数を数える

	// スクロール
	int		_scrX, _scrY;


private:
	/*std::vector<int> _grAllHandles;*/
	int		_cgChip[CHIPCOUNT];		// マップチップ画像

	// マップデータ
	// .tmx の以下からコピペ
	//   <data encoding="csv">
	int		_mapData[MAPSIZE_LAYER * MAPSIZE_W * MAPSIZE_H] = {
		// <layer name="tile_base" width="64" height="18">
		//  <data encoding="csv">
		4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,4,
		4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,
		4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,
		4,0,0,0,4,4,4,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,4,0,0,0,0,0,4,
		4,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,4,
		4,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,4,
		4,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,
		4,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,
		4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,4,
		4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,4,
		4,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,
		4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,
		4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,
		4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
		4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
	};
};
