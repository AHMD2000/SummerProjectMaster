#pragma once

#include	"ModeBase.h"




typedef enum
{
	Title_Gamestart,  // �Q�[���J�n
	Title_Rule,   // �Q�[������
	Title_Credit,  //�N���W�b�g
	Title_Num     // �{���ڂ̐�

};

//static int NowSelect = Title_Gamestart; // ���݂̑I����

class ModeTitle : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

	bool SetTitleProcess(bool no) {
		return _TitleProcess = no;
	}

protected:

	bool _TitleProcess = true;

	// �^�C�g��
	int		_cgTitle;

	int		_waku;
	int		_cgTitlename;
	int		_cgGameStart;
	int		_cgRule;
	int		_cgwaku;

	int _bgm;
};
