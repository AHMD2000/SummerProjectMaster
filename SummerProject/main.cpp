#include "DxLib.h"
#include <stdio.h>
#include <time.h>
#include "game.h"
#include "ResourceServer.h"


// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ������ -------------------------------------------------------------------------
	// �c�w���C�u��������������
	SetGraphMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH);	// ��ʂ̉𑜓x����1280�~�c720�A1�h�b�g������32�r�b�g�Ɏw�肷��
	ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	if (DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g

	// ����������
	srand((unsigned int)time(NULL));

	// ���\�[�X�T�[�o������
	ResourceServer::Init();

	// �Q�[���N���X
	Game* g = new Game();

	// 1�t���[�����[�v��g�� ----------------------------------------------------------
	while (ProcessMessage() == 0)		// �v���O�������I������܂Ń��[�v
	{
		g->Input();		// ����
		g->Process();	// �v�Z
		g->Draw();		// �`��
	}

	// ��� ---------------------------------------------------------------------------
	ResourceServer::Release();	// ���\�[�X�T�[�o���

	delete g;			// �Q�[���N���X�̉��

	DxLib_End();		// �c�w���C�u�����g�p�̏I������

	// �I��
	return 0;
}