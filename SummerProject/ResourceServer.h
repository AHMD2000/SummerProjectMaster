#pragma once
#include	<unordered_map>
#include <string>
#include <tchar.h>
#include <memory>
#include <vector>

	// �����ǂݍ���LoadDivGraph�p
struct DivGraph
{
	std::string _filename;
	int _xNum;
	int _yNum;
	int _xSize;
	int _ySize;
	std::vector<int> _handles;
};

// ���\�[�X�Ǘ��T�[�o
// ���ׂĐÓI�����o�ō\������
class ResourceServer
{
public:
	// �C�ӂ̕�������L�[�ɂ���DivGraph���Ǘ�
	using DivGraphMap = std::unordered_map<std::string, DivGraph>;
	static void	Init();
	static void	Release();
	static void	ClearTextures();
	/*
	 *  �摜�̈ꊇ�ǂݍ���
	 *  @param div_graph_map�@DivGraphMap�e�[�u��
	 */
	static void LoadTextures(const DivGraphMap& div_graph_map);
	/*
	 *  �摜�n���h���̎擾
	 *  �S�Ẳ摜�𕪊��摜�ƂƂ��ēǂݍ���
	 *  @param fileName �摜�t�@�C����
	 *  @param no				�������̔ԍ�
	 *	@return					�摜�n���h��
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