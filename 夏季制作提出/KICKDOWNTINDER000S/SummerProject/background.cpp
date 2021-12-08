#include "DxLib.h"
#include "BackGround.h"
#include "ResourceServer.h"

BackGround::BackGround()
{
	_cg = ResourceServer::GetHandles("bg");		// ”wŒi‰æ‘œ‚ğƒ[ƒh‚·‚é
}

BackGround::~BackGround()
{
}

void	BackGround::Draw()
{
	DrawGraph(0, 0, _cg, FALSE);
}