#pragma once
#include "ModeBase.h"

namespace AMG {
	constexpr auto FADEIN_FRAME = 60; // �t�F�[�h�C���t���[��
	constexpr auto WAIT_TIME = 120; //�\������
	constexpr auto FADEOUT_FRAME = 180; // �t�F�[�h�A�E�g�t���[��
	constexpr auto FADESPEED = 5; // �t�F�[�h�̃X�s�[�h
	constexpr auto TRANSPARENCY = 255; // �����x

}

class AMGLogo :public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);
protected:

	int _a;
	int _cnt;
	int _cgAMGlogo;
};