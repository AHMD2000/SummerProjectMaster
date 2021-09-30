#pragma once

#include "mapchips.h"
#include "ModeServer.h"
#include "ObjectServer.h"
#include "ResourceServer.h"
#include "Vector.h"
#include "Effect.h"

// ��ʐݒ�
constexpr auto SCREEN_W = 1920;		///< ��ʂ̉��𑜓x
constexpr auto SCREEN_H = 1080;		///< ��ʂ̏c�𑜓x
constexpr auto SCREEN_DEPTH = 32;   ///< �P�h�b�g������̃r�b�g��

class Effect;

// �Q�[���N���X
class Game
{
public:
	Game();				// �A�v���̏�����
	~Game();			// �A�v���̉��

	void Input();		// �t���[�������F����
	void Process();		// �t���[�������F�v�Z
	void Draw();		// �t���[�������F�`��


// �����o�ϐ�
	// �Q�[�����
	int _gKey[4];// �L�[���͂̏��
	int _gTrg[4];/*�g���K�[����*/
    int _gFrameCount;	// ���t���[��+1����J�E���g

	ModeServer* _serverMode;

	ObjectServer _objServer;

	// �}�b�v�`�b�v
	MapChips	_mapChips;

	// SE�}�b�v
	std::unordered_map<std::string, int>	_se;

};
