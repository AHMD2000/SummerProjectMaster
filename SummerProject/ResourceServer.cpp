#include "ResourceServer.h"
#include "DxLib.h"

// 静的メンバ実体
ResourceServer::DivGraphMap ResourceServer::_textures;
std::unordered_map<std::string, int>	ResourceServer::_mapSound;

void ResourceServer::Init()
{
	_textures.clear();
}

void ResourceServer::Release()
{
	ClearTextures();
}

void ResourceServer::ClearTextures()
{
	for (auto&& dgm : _textures) {
		for (auto gh : dgm.second._handles) {
			DeleteGraph(gh);
		}
	}
	_textures.clear();
}
/*
 *  画像の一括読み込み
 *  @param div_graph_map　DivGraphMapテーブル
 */
void ResourceServer::LoadTextures(const DivGraphMap& divGraphMap)
{
	for (auto&& dgm : divGraphMap) {
		auto& key = dgm.first;
		// キーを検索する
		auto it = _textures.find(key);
		if (it != _textures.end()) {
			continue;
		}
		// DivGraphをコピーする
		auto dg = dgm.second;
		auto allNum = dg._xNum * dg._yNum;
		dg._handles.resize(allNum);
		// 画像の分割読み込み
		LoadDivGraph(dg._filename.c_str(),
			allNum,
			dg._xNum, dg._yNum,
			dg._xSize, dg._ySize, dg._handles.data());
		// DivGraphMapに追加する
		_textures.emplace(key.c_str(), dg);
	}
}
/*
 *  画像ハンドルの取得
 *  @param fileName 画像ファイル名
 *  @param no				分割時の番号
 *	@return					画像ハンドル
 */
int ResourceServer::GetHandles(const std::string& key, int no)
{
	auto it = _textures.find(key);
	if (it == _textures.end()) {
		return -1;
	}
	auto gh = it->second._handles.at(no);
	return gh;
}
bool ResourceServer::GetHandles(const std::string& key, std::vector<int>& handles)
{
	auto it = _textures.find(key);
	if (it == _textures.end()) {
		return false;
	}
	handles.resize(it->second._handles.size());

	handles = it->second._handles;
	return true;
}
int ResourceServer::GetAllNum(const std::string& key)
{
	auto it = _textures.find(key);
	if (it == _textures.end()) {
		return -1;
	}
	return it->second._xNum * it->second._yNum;
}

const DivGraph& ResourceServer::GetDivGraph(const std::string& key)
{
	auto it = _textures.find(key);
	//if (it == _textures.end()) {
	//	return nullptr;
	//}
	return it->second;
}


int		ResourceServer::LoadSoundMem(const TCHAR* FileName) {
	// キーの検索
	auto itr = _mapSound.find(FileName);
	if (itr != _mapSound.end())
	{
		// キーがあった
		return itr->second;
	}
	// キーが無かった
	int snd = ::LoadSoundMem(FileName);     // DXLIBのAPIを呼ぶので、::を先頭に付け、このクラスの同じ名前の関数と区別する
	// キーとデータをmapに登録
	_mapSound[FileName] = snd;

	return snd;
}