#pragma once

#include "Math.h"
#include <string>
#include <vector>
#include "Vector.h"
#include "ObjectBase.h"
#include "game.h"

class Player;

// �G�t�F�N�g�p�N���X
class Effect : public ObjectBase
{
public:

    virtual OBJECTTYPE	GetType() { return ObjectBase::OBJECTTYPE::EFFECT; }

    Effect(const Vector2& pos, int startTime, const std::string& grKey = "");
    // �C�[�W���O����
    virtual void Easing(int elapsed) = 0;
    void Update(int freamCount, Game& g);
    virtual void Draw(Game& g);
    bool isDead()
    {
        return !_active;
    };
protected:
    //int _grHandle;  // ���݂̃O���t�B�b�N�n���h��
    //std::vector<int> _grAllHandles; // �S�ẴO���t�B�b�N�n���h��
    int _delayTime; // �x������
    int _startTime; // �J�n����
    int _lifeTime;  // ��������
    bool _active;   // �L������
    double _alpha;  // �A���t�@
    double _angle;  // ��]�p�x
    double _zoom;   // �g�嗦
    Vector2 _position;  // ���W
    int _blendMode; // DX�u�����h���[�h
};


//�t�F�[�h
class FadeEffect : public Effect
{
public:
    FadeEffect(int startTime, int color);
    //�C�[�W���O����
    virtual void Easing(int elapsed) override;
    //�`��
    virtual void Draw(Game& g) override;
private:
    int _color;
};

//�t�F�[�h
class FadeInEffect : public Effect
{
public:
    FadeInEffect(int startTime, int color);
    //�C�[�W���O����
    virtual void Easing(int elapsed) override;
    //�`��
    virtual void Draw(Game& g) override;
private:
    int _color;
};


// ����
class ExplosionEffect : public Effect
{
public:
    ExplosionEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};

// �c��
class BlurEffect : public Effect
{
public:
    BlurEffect(const Vector2& pos, int startTime, int grHandle, double angle);
    virtual void Easing(int elapsed) override;
};

// �M��
class FlashEffect : public Effect
{
public:
    FlashEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
};


// �A�C�e��1
class Item1Effect : public Effect
{
public:
    Item1Effect(const Vector2& pos, int startTime, int no);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};


//�A�C�e��1�ȊO�̃q�b�g�G�t�F�N�g
class HitEffect : public Effect
{
public:
    HitEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};

//�R�C���擾�G�t�F�N�g
class CoinGetEffect : public Effect
{
public:
    CoinGetEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};

//�X�^�[��ԃG�t�F�N�g
class StarStateEffect : public Effect
{
public:
    StarStateEffect(const Vector2& pos, int startTime, Player* ply);
    virtual void Easing(int elapsed) override;
    void Update(int freamCount, Game& g) override;
    virtual void Draw(Game& g) override;
private:
    Vector2 _start, _stop;

    Player* _ply;
};

//�A�C�e���Q�b�g�G�t�F�N�g
class ItemGetEffect : public Effect
{
public:
    ItemGetEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};


//�D���G�t�F�N�g
class FlarkEffect : public Effect
{
public:
    FlarkEffect(const Vector2& pos, int startTime, Player* ply);
    virtual void Easing(int elapsed) override;
    void Update(int freamCount, Game& g) override;
    virtual void Draw(Game& g) override;

private:
    Vector2 _start, _stop;

    Player* _ply;
};


// �ˌ��G�t�F�N�g
class RushEffect : public Effect
{
public:
    RushEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};