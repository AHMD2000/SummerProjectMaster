#pragma once

#include "Math.h"
#include <string>
#include <vector>
#include "Vector.h"
#include "ObjectBase.h"
#include "game.h"

class Player;

// エフェクト用クラス
class Effect : public ObjectBase
{
public:

    virtual OBJECTTYPE	GetType() { return ObjectBase::OBJECTTYPE::EFFECT; }

    Effect(const Vector2& pos, int startTime, const std::string& grKey = "");
    // イージング処理
    virtual void Easing(int elapsed) = 0;
    void Update(int freamCount, Game& g);
    virtual void Draw(Game& g);
    bool isDead()
    {
        return !_active;
    };
protected:
    //int _grHandle;  // 現在のグラフィックハンドル
    //std::vector<int> _grAllHandles; // 全てのグラフィックハンドル
    int _delayTime; // 遅延時間
    int _startTime; // 開始時間
    int _lifeTime;  // 生存時間
    bool _active;   // 有効無効
    double _alpha;  // アルファ
    double _angle;  // 回転角度
    double _zoom;   // 拡大率
    Vector2 _position;  // 座標
    int _blendMode; // DXブレンドモード
};


//フェード
class FadeEffect : public Effect
{
public:
    FadeEffect(int startTime, int color);
    //イージング処理
    virtual void Easing(int elapsed) override;
    //描画
    virtual void Draw(Game& g) override;
private:
    int _color;
};

//フェード
class FadeInEffect : public Effect
{
public:
    FadeInEffect(int startTime, int color);
    //イージング処理
    virtual void Easing(int elapsed) override;
    //描画
    virtual void Draw(Game& g) override;
private:
    int _color;
};


// 爆炎
class ExplosionEffect : public Effect
{
public:
    ExplosionEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};

// 残像
class BlurEffect : public Effect
{
public:
    BlurEffect(const Vector2& pos, int startTime, int grHandle, double angle);
    virtual void Easing(int elapsed) override;
};

// 閃光
class FlashEffect : public Effect
{
public:
    FlashEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
};


// アイテム1
class Item1Effect : public Effect
{
public:
    Item1Effect(const Vector2& pos, int startTime, int no);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};


//アイテム1以外のヒットエフェクト
class HitEffect : public Effect
{
public:
    HitEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};

//コイン取得エフェクト
class CoinGetEffect : public Effect
{
public:
    CoinGetEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};

//スター状態エフェクト
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

//アイテムゲットエフェクト
class ItemGetEffect : public Effect
{
public:
    ItemGetEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};


//泥沼エフェクト
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


// 突撃エフェクト
class RushEffect : public Effect
{
public:
    RushEffect(const Vector2& pos, int startTime);
    virtual void Easing(int elapsed) override;
private:
    Vector2 _start, _stop;
};