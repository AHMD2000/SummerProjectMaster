#pragma once

#include	"ModeBase.h"
#include	"ObjectBase.h"
#include	<vector>
#include	<iostream>
#include	<utility>
#include	"Player.h"
#include	<sstream>
#include	"ModeGame.h"
#include	<memory>
#include	"PlayerUI.h"
#include	"ResultCrown.h"

//class ResultCrown;

class ModeResult : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);


protected:

	/*Player	_ply;*/

	bool _fadeOn;

	int		_cgResult;

	int _bgm;

	//���U���g��ʂ̉����̃��j�[�N�|�C���^
	std::unique_ptr<ResultCrown> _resultCrown;

	// �G�t�F�N�g�̃��j�[�N�|�C���^�̓��I�z��
	std::vector<std::unique_ptr<Effect>> _effects;

	// �v���C���[UI�̃��j�[�N�|�C���^�̓��I�z��
	std::vector<std::unique_ptr<PlayerUI>> _plyUIs;

	int _resultCnt;


};