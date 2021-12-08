#pragma once
#include	<unordered_map>
#include <string>
#include <tchar.h>
#include <memory>
#include <vector>

	// 分割読み込みLoadDivGraph用
struct DivGraph
{
	std::string _filename;
	int _xNum;
	int _yNum;
	int _xSize;
	int _ySize;
	std::vector<int> _handles;
};

// リソース管理サーバ
// すべて静的メンバで構成する
class ResourceServer
{
public:
	// 任意の文字列をキーにしてDivGraphを管理
	using DivGraphMap = std::unordered_map<std::string, DivGraph>;
	static void	Init();
	static void	Release();
	static void	ClearTextures();
	/*
	 *  画像の一括読み込み
	 *  @param div_graph_map　DivGraphMapテーブル
	 */
	static void LoadTextures(const DivGraphMap& div_graph_map);
	/*
	 *  画像ハンドルの取得
	 *  全ての画像を分割画像ととして読み込む
	 *  @param fileName 画像ファイル名
	 *  @param no				分割時の番号
	 *	@return					画像ハンドル
	 */
	static int GetHandles(const std::string& key, int no = 0);
	static bool GetHandles(const std::string& key, std::vector<int>& handles);
	static int GetAllNum(const std::string& key);
	static const DivGraph& GetDivGraph(const std::string& key);


	

	static int		LoadSoundMem(const TCHAR* FileName);

private:
	static std::unordered_map<std::string, int>	_mapSound;
	static DivGraphMap _textures;
};