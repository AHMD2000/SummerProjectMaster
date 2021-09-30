#pragma once

#include <vector>

class Game;
class ObjectBase;

// �}�b�v�`�b�v�N���X
class MapChips {
public:
	MapChips();
	~MapChips();

	void	Process(Game& g);
	void	Draw();

	int		CheckHit(int x, int y);
	int		IsHit(ObjectBase& o, int mx, int my);


public:

	// �}�b�v�̃T�C�Y�i�`�b�v���j
	// .tmx�̈ȉ����ݒ�
// <layer name="tile_base" width="64" height="18">
	static const int MAPSIZE_W = 32;	// width
	static const int MAPSIZE_H = 18;	// height

	// �`�b�v�摜�̌�
	// .tmx�̈ȉ����ݒ�
	// <tileset firstgid="1" name="platformer_simpleA_sheet" tilewidth="40" tileheight="40" tilecount="64" columns="8">

	// �`�b�v�̌�
	static const int CHIPCOUNT = 6;		// tilecount
	static const int CHIPCOUNT_W = 6;		// columns
	static const int CHIPCOUNT_H = (CHIPCOUNT / CHIPCOUNT_W);		// �v�Z�ŏo��

	// �`�b�v�̃T�C�Y�ipixel���j
	static const int CHIPSIZE_W = 60;
	static const int CHIPSIZE_H = 60;

	// ���C���[��
	static const int MAPSIZE_LAYER = 1;	// �u<layer �v �̐��𐔂���

	// �X�N���[��
	int		_scrX, _scrY;


private:
	/*std::vector<int> _grAllHandles;*/
	int		_cgChip[CHIPCOUNT];		// �}�b�v�`�b�v�摜

	// �}�b�v�f�[�^
	// .tmx �̈ȉ�����R�s�y
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
