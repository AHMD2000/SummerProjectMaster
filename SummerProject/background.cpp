#include "DxLib.h"
#include "BackGround.h"
#include "ResourceServer.h"

BackGround::BackGround()
{
	_cg = ResourceServer::GetHandles("bg");		// �w�i�摜�����[�h����
}

BackGround::~BackGround()
{
}

void	BackGround::Draw()
{
	DrawGraph(0, 0, _cg, FALSE);
}