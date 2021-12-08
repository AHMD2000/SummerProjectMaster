#include "ResourceServer.h"
#include "DxLib.h"

// �ÓI�����o����
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
 *  �摜�̈ꊇ�ǂݍ���
 *  @param div_graph_map�@DivGraphMap�e�[�u��
 */
void ResourceServer::LoadTextures(const DivGraphMap& divGraphMap)
{
	for (auto&& dgm : divGraphMap) {
		auto& key = dgm.first;
		// �L�[����������
		auto it = _textures.find(key);
		if (it != _textures.end()) {
			continue;
		}
		// DivGraph���R�s�[����
		auto dg = dgm.second;
		auto allNum = dg._xNum * dg._yNum;
		dg._handles.resize(allNum);
		// �摜�̕����ǂݍ���
		LoadDivGraph(dg._filename.c_str(),
			allNum,
			dg._xNum, dg._yNum,
			dg._xSize, dg._ySize, dg._handles.data());
		// DivGraphMap�ɒǉ�����
		_textures.emplace(key.c_str(), dg);
	}
}
/*
 *  �摜�n���h���̎擾
 *  @param fileName �摜�t�@�C����
 *  @param no				�������̔ԍ�
 *	@return					�摜�n���h��
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
	// �L�[�̌���
	auto itr = _mapSound.find(FileName);
	if (itr != _mapSound.end())
	{
		// �L�[��������
		return itr->second;
	}
	// �L�[����������
	int snd = ::LoadSoundMem(FileName);     // DXLIB��API���ĂԂ̂ŁA::��擪�ɕt���A���̃N���X�̓������O�̊֐��Ƌ�ʂ���
	// �L�[�ƃf�[�^��map�ɓo�^
	_mapSound[FileName] = snd;

	return snd;
}