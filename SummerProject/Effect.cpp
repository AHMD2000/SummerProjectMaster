#include "Effect.h"
#include "Easing.h"
#include "ResourceServer.h"
#include "DxLib.h"
#include "Vector.h"
#include "Player.h"

// �R���X�g���N�^
Effect::Effect(const Vector2& pos, int startTime, const std::string& grKey)
	: _delayTime{ 0 }
	, _startTime{ startTime }
	, _lifeTime{ 0 }
	, _active{ true }
	, _alpha{ 255.0 }
	, _angle{ 0.0 }
	, _zoom{ 1.0 }
	, _position{ pos }
	, _blendMode{ DX_BLENDMODE_ADD }
	
{
	_grHandle = -1;

	// ���\�[�X�T�[�o�[����n���h�����擾����
	if (ResourceServer::GetHandles(grKey, _grAllHandles)) {
		_grHandle = _grAllHandles[0];
	}

}

// �X�V
void Effect::Update(int freamCount, Game& g)
{
	if (!_active) {
		g._objServer.Del(this);

		return;
	}
	// �o�ߎ��ԁ����ݎ����|(�J�n�����{�x������)
	auto elapsed = freamCount - (_startTime + _delayTime);
	if (elapsed < 0) {
		return; // �f�B���C(�x��)��
	}
	if (elapsed < _lifeTime) {
		Easing(elapsed);  // �C�[�W���O����
		return;
	}
	_active = false;
}

// �`��
void Effect::Draw(Game& g)
{
	SetDrawBlendMode(_blendMode, static_cast<int>(_alpha));
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	int x = static_cast<int>(_position.x);
	int y = static_cast<int>(_position.y);

	DrawRotaGraph(x, y, _zoom, _angle, _grHandle, true, false);

	SetDrawMode(DX_DRAWMODE_NEAREST);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// �t�F�[�h
FadeEffect::FadeEffect(int startTime, int color)
	:Effect{ {0, 0},  startTime }
	, _color{ color }
{
	_lifeTime = 60 * 1;
}
// (4-3)�C�[�W���O����
void FadeEffect::Easing(int elapsed) {
	auto linear = Easing::GetMode("Linear");
	_alpha = linear(elapsed, 255.0, 0.0, _lifeTime);
}
// (4-5.)�`��
void FadeEffect::Draw(Game& g) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
	DrawBoxAA(0, 0, 1920, 1080, _color, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

// ����
ExplosionEffect::ExplosionEffect(const Vector2& pos, int startTime)
	:Effect{ pos, startTime, "smoke" }
{
	_lifeTime = 60 * 4;
	_start = { pos.x + GetRand(24) - 12 , pos.y };
	_stop = { pos.x, pos.y - 300 };
	_blendMode = DX_BLENDMODE_ALPHA;
}

void ExplosionEffect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	_alpha = linear(elapsed, 255.0, 0.0, _lifeTime);
	_position.x = linear(elapsed, _start.x, _stop.x, _lifeTime);
	_position.y = linear(elapsed, _start.y, _stop.y, _lifeTime);
	_zoom = linear(elapsed, 1.0, 8.0, _lifeTime);
	auto no = linear(elapsed, 0, 64, _lifeTime);
	_grHandle = _grAllHandles[static_cast<int>(no)];
}

//�c��
BlurEffect::BlurEffect(const Vector2& pos, int startTime, int grHandle, double angle)
	:Effect{ pos, startTime }
{
	_lifeTime = 60 * 1;
	_grHandle = grHandle;
	_angle = angle;
}
void BlurEffect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	_alpha = linear(elapsed, 255.0, 0.0, _lifeTime);
}

// �M��
FlashEffect::FlashEffect(const Vector2& pos, int startTime)
	:Effect{ pos, startTime, "flash" }
{
	_lifeTime = 60;
}
// �C�[�W���O����
void FlashEffect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	_alpha = linear(elapsed, 255.0, 0.0, _lifeTime);
	_angle = linear(elapsed, 0.0, Math::ToRadians(360 * 4.0), _lifeTime);
	_zoom = linear(elapsed, 0.0, 8.0, _lifeTime);
}

// �A�C�e��1
Item1Effect::Item1Effect(const Vector2& pos, int startTime, int no)
	:Effect{ pos, startTime, "Item1" }
{
	_lifeTime = 1;
	/*_start = { pos.x + GetRand(24) - 12 , pos.y };
	_stop = { pos.x, pos.y - 300 };*/
	_grHandle = _grAllHandles[no];
	_blendMode = DX_BLENDMODE_ALPHA;
}

void Item1Effect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	_alpha = linear(elapsed, 255.0, 0.0, _lifeTime);
	/*_position.x = linear(elapsed, _start.x, _stop.x, _lifeTime);
	_position.y = linear(elapsed, _start.y, _stop.y, _lifeTime);*/
	/*_zoom = linear(elapsed, 1.0, 8.0, _lifeTime);*/
	/*auto no = linear(elapsed, 0, 15, _lifeTime);
	_grHandle = _grAllHandles[static_cast<int>(no)];*/
}

// �A�C�e��1�ȊO�̃q�b�g�G�t�F�N�g
HitEffect::HitEffect(const Vector2& pos, int startTime)
	:Effect{ pos, startTime, "NomalHitEffect" }
{
	_lifeTime = 60 * 1;
	/*_start = { pos.x + GetRand(24) - 12 , pos.y };
	_stop = { pos.x, pos.y - 300 };*/
	/*_grHandle = _grAllHandles[no];*/
	_blendMode = DX_BLENDMODE_ALPHA;
}

void HitEffect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	_alpha = linear(elapsed, 255.0, 0.0, _lifeTime);
	/*_angle = linear(elapsed, 0.0, Math::ToRadians(360 * 4.0), _lifeTime);*/
	/*_position.x = linear(elapsed, _start.x, _stop.x, _lifeTime);
	_position.y = linear(elapsed, _start.y, _stop.y, _lifeTime);*/
	_zoom = linear(elapsed, 1.0, 2.0, _lifeTime);
	auto no = linear(elapsed, 0, 8, _lifeTime);
	_grHandle = _grAllHandles[static_cast<int>(no)];
}

//�R�C���̎擾�G�t�F�N�g
CoinGetEffect::CoinGetEffect(const Vector2& pos, int startTime)
	:Effect{ pos, startTime, "StarCoinGetEffect" }
{
	_lifeTime = 60 * 1;
	/*_start = { pos.x + GetRand(24) - 12 , pos.y };
	_stop = { pos.x, pos.y - 300 };*/
	/*_grHandle = _grAllHandles[no];*/
	_blendMode = DX_BLENDMODE_ALPHA;
}

void CoinGetEffect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	_alpha = linear(elapsed, 255.0, 0.0, _lifeTime);
	/*_angle = linear(elapsed, 0.0, Math::ToRadians(360 * 4.0), _lifeTime);*/
	/*_position.x = linear(elapsed, _start.x, _stop.x, _lifeTime);
	_position.y = linear(elapsed, _start.y, _stop.y, _lifeTime);*/
	_zoom = linear(elapsed, 1.0, 2.0, _lifeTime);
	auto no = linear(elapsed, 0, 20, _lifeTime);
	_grHandle = _grAllHandles[static_cast<int>(no)];
}

//�X�^�[��ԃG�t�F�N�g
StarStateEffect::StarStateEffect(const Vector2& pos, int startTime, Player* ply)
	:Effect{ pos, startTime, "StarStateEffect" },
	_ply(ply)
{
	/*_lifeTime = 60 * 1;*/
	/*_start = { pos.x + GetRand(24) - 12 , pos.y };
	_stop = { pos.x, pos.y - 300 };*/
	/*_grHandle = _grAllHandles[no];*/
	_blendMode = DX_BLENDMODE_ALPHA;


}

void StarStateEffect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	/*_alpha = linear(elapsed, 255.0, 0.0, _lifeTime);*/
	/*_angle = linear(elapsed, 0.0, Math::ToRadians(360 * 4.0), _lifeTime);*/
	/*_position.x = linear(elapsed, _start.x, _stop.x, _lifeTime);
	_position.y = linear(elapsed, _start.y, _stop.y, _lifeTime);*/
	/*_zoom = linear(elapsed, 1.0, 1.0, _lifeTime);*/
	/*auto no = linear(elapsed, 0, 48, _lifeTime);
	_grHandle = _grAllHandles[static_cast<int>(no)];*/
}

//�X�^�[��Ԃ̃G�t�F�N�g�̃A�b�v�f�[�g
void StarStateEffect::Update(int freamCount, Game& g)
{
	if (!_active) {
		g._objServer.Del(this);

		return;
	}

	auto no = /*linear(elapsed, 0, 48, _lifeTime);*/g._gFrameCount % 48;
	_grHandle = _grAllHandles[static_cast<int>(no)];

	if (_ply->_specialMode == false)
	{
		_active = false;
	}
}

//�X�^�[��Ԃ̃G�t�F�N�g��Draw�֐�
void StarStateEffect::Draw(Game& g)
{
	SetDrawBlendMode(_blendMode, static_cast<int>(_alpha));
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	int x = static_cast<int>(_ply->_x);
	int y = static_cast<int>(_ply->_y) - 50;

	DrawRotaGraph(x, y, _zoom, _angle, _grHandle, true, false);

	SetDrawMode(DX_DRAWMODE_NEAREST);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


//�A�C�e���Q�b�g�G�t�F�N�g
ItemGetEffect::ItemGetEffect(const Vector2& pos, int startTime)
	:Effect{ pos, startTime, "ItemGetEffect" }
{
	_lifeTime = 60 * 1;
	/*_start = { pos.x + GetRand(24) - 12 , pos.y };
	_stop = { pos.x, pos.y - 300 };*/
	/*_grHandle = _grAllHandles[no];*/
	_blendMode = DX_BLENDMODE_ALPHA;
}

void ItemGetEffect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	_alpha = linear(elapsed, 255.0, 0.0, _lifeTime);
	/*_angle = linear(elapsed, 0.0, Math::ToRadians(360 * 4.0), _lifeTime);*/
	/*_position.x = linear(elapsed, _start.x, _stop.x, _lifeTime);
	_position.y = linear(elapsed, _start.y, _stop.y, _lifeTime);*/
	_zoom = linear(elapsed, 1.0, 2.0, _lifeTime);
	auto no = linear(elapsed, 0, 10, _lifeTime);
	_grHandle = _grAllHandles[static_cast<int>(no)];
}


//�D���̃G�t�F�N�g
FlarkEffect::FlarkEffect(const Vector2& pos, int startTime, Player* ply)
	:Effect{ pos, startTime, "FlarkEffect" },
	_ply(ply)
{
	_zoom = 1.0;
	/*_lifeTime = 60 * 1;*/
	/*_start = { pos.x + GetRand(24) - 12 , pos.y };
	_stop = { pos.x, pos.y - 300 };*/
	_blendMode = DX_BLENDMODE_ALPHA;
}

void FlarkEffect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	_alpha = 255.0;/*linear(elapsed, 255.0, 0.0, _lifeTime);*/
	/*_angle = linear(elapsed, 0.0, Math::ToRadians(360 * 4.0), _lifeTime);*/
	/*_position.x = linear(elapsed, _start.x, _stop.x, _lifeTime);
	_position.y = linear(elapsed, _start.y, _stop.y, _lifeTime);*/
	/*_zoom = linear(elapsed, 3.0, 1.0, _lifeTime);
	auto no = linear(elapsed, 0, 60, _lifeTime);
	_grHandle = _grAllHandles[static_cast<int>(no)];*/
}

void FlarkEffect::Draw(Game& g)
{
	SetDrawBlendMode(_blendMode, static_cast<int>(_alpha));
	SetDrawMode(DX_DRAWMODE_BILINEAR);
	int x = static_cast<int>(_ply->_x);
	int y = static_cast<int>(_ply->_y) - 50;

	DrawRotaGraph(x, y, _zoom, _angle, _grHandle, true, false);

	SetDrawMode(DX_DRAWMODE_NEAREST);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


void FlarkEffect::Update(int freamCount, Game& g)
{
	if (!_active) {
		g._objServer.Del(this);

		return;
	}

	auto no = /*linear(elapsed, 0, 48, _lifeTime);*/g._gFrameCount % 60;
	_grHandle = _grAllHandles[static_cast<int>(no)];

	/*if ( == false)
	{
		_active = false;
	}*/
}


//�ˌ��G�t�F�N�g
RushEffect::RushEffect(const Vector2& pos, int startTime)
	:Effect{ pos, startTime, "smoke" }
{
	
}

void RushEffect::Easing(int elapsed)
{

}

//�t�F�[�h�C���G�t�F�N�g
FadeInEffect::FadeInEffect(int startTime, int color)
	:Effect{ {0, 0},  startTime }
	, _color{ color }
{
	_lifeTime = 60 * 1;
}

void FadeInEffect::Easing(int elapsed)
{
	auto linear = Easing::GetMode("Linear");
	_alpha = linear(elapsed, 0.0, 255.0, _lifeTime);
}

void FadeInEffect::Draw(Game& g)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(_alpha));
	DrawBoxAA(0, 0, 1920, 1080, _color, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}