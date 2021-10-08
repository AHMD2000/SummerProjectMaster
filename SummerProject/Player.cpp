#include "DxLib.h"
#include "Player.h"
#include "Game.h"
#include "ResourceServer.h"
#include "Coin.h"
#include <memory>
#include <sstream>
#include "Vector.h"
#include "AttackCollision.h"
#include "Banana.h"
#include "ModeGame.h"
#include "ModeResult.h"
#include "Effect.h"
#include <algorithm>





Player::Player(ObjectBase::OBJECTTYPE id,Game& g)
	:_id(id), _state(STATE::IDLE)
{
	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	switch (id)	{
	case ObjectBase::OBJECTTYPE::PLAYER1:
		ResourceServer::GetHandles("player_idle0", _grAllHandles);
		/*_plyCoin = std::make_pair(ObjectBase::OBJECTTYPE::PLAYER1, _coin);
		modeGame->_plyRanking.emplace_back(_plyCoin);*/
		break;
	case ObjectBase::OBJECTTYPE::PLAYER2:
		ResourceServer::GetHandles("player_idle1", _grAllHandles);
		/*_plyCoin = std::make_pair(ObjectBase::OBJECTTYPE::PLAYER2, _coin);
		modeGame->_plyRanking.emplace_back(_plyCoin);*/
		break;
	case ObjectBase::OBJECTTYPE::PLAYER3:
		ResourceServer::GetHandles("player_idle2", _grAllHandles);
		/*_plyCoin = std::make_pair(ObjectBase::OBJECTTYPE::PLAYER3, _coin);
		modeGame->_plyRanking.emplace_back(_plyCoin);*/
		break;
	case ObjectBase::OBJECTTYPE::PLAYER4:
		ResourceServer::GetHandles("player_idle3", _grAllHandles);
		/*_plyCoin = std::make_pair(ObjectBase::OBJECTTYPE::PLAYER4, _coin);
		modeGame->_plyRanking.emplace_back(_plyCoin);*/
		break;
	}

	ResourceServer::GetHandles("Item1", _grSpecialEffect);
	ResourceServer::GetHandles("DebufEffect", _grDebufEffect);
	ResourceServer::GetHandles("StarCoinGetEffect", _grStarCoinGetEffect);

	_easing = Easing::GetMode("OutCirc");

	_grStandbyBanana = ResourceServer::GetHandles("StandbyBanana" + std::to_string(GetId()));

	Init();
}


Player::~Player()
{
}

void Player::Init()
{
	_specialAttackEffectAngle = 0.0;
	_attackHit1 = 0;
	_attackHit10 = 0;
	_StarCoinGet1 = 0;
	_StarCoinGet10 = 0;
	_bananaAttackHit1 = 0;
	_bananaAttackHit10 = 0;
	_debufCoolTime = 0;
	_isDebuf = false;
	_specialModeCooltime = 0;
	_oldCoin = 0;
	_specialAttack = false;
	_specialMode = false;
	_specialModeEffect = true;
	_finalBGM = true;
	_bananaAttack = false;
	_flarkEffect = false;
	//バナナのクールタイム
	_cooltime = 0;
	_bananaGage = 60 * 5;
	_bananaGageMax = 60 * 5;
	_stateAttack = true;
	_fallCoin = false;
	/*_vx = -_w / 2;
	_vy = -_h + 1;*/
	_charaDirSlide = 4;
	_charaDir = 0;
	_animeMax = 4;
	_grHandle = -1;
	_animeNo = 0;
	// プレイヤー情報の初期化
	_w = 100;
	_h = 100;
	/*SetPosition({ 0,0 });*/
	_x = 0;
	_y = 0;
	_spd = 4.0;
	_hit_x = -30;
	_hit_y = -60;
	_hit_w = 60;
	_hit_h = 50;
	_hita_x = -2000;
	_hita_y = -2000;
	_hita_w = -2000;
	_hita_h = -2000;
	_coin = 10;
}


std::vector<std::string> playerGraph = {
	"player_idle",
	"player_move",
	"player_attack",
	"player_idle",
	"player_idle",
	"player_rush",
	"player_idle",
};


void Player::ChangeState(STATE state) {
	_state = state;
	_stateCnt = _cnt;

	_stateAttack = true;
	_attackMissingSE = true;

	if (_charaDir == 1 || _charaDir == 0)
	{
		_rushStart = _y;
	}
	else if (_charaDir == 2 || _charaDir == 3)
	{
		_rushStart = _x;
	}
	if (_charaDir == 0)
	{
		_rushStop = _y + 200.0;
	}
	else if (_charaDir == 1)
	{
		_rushStop = _y - 200.0;
	}
	else if (_charaDir == 2)
	{
		_rushStop = _x - 200.0;
	}
	else if (_charaDir == 3)
	{
		_rushStop = _x + 200.0;
	}

	

	_hita_x = -2000;
	_hita_y = -2000;
	_hita_w = -2000;
	_hita_h = -2000;

	_grAllHandles.clear();
	ResourceServer::GetHandles(playerGraph[GetState()] + std::to_string(GetId()), _grAllHandles);


	//switch (_id) {
	//case ObjectBase::OBJECTTYPE::PLAYER1:
	//	ResourceServer::GetHandles("player1", _grAllHandles);

	//	break;
	//case ObjectBase::OBJECTTYPE::PLAYER2:
	//	ResourceServer::GetHandles("player1", _grAllHandles);
	//	break;
	//case ObjectBase::OBJECTTYPE::PLAYER3:
	//	ResourceServer::GetHandles("player1", _grAllHandles);
	//	break;
	//case ObjectBase::OBJECTTYPE::PLAYER4:
	//	ResourceServer::GetHandles("player1", _grAllHandles);
	//	break;
	//}

}

void Player::Process(Game& g)
{
	ObjectBase::Process(g);

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");


	Vector2	_nockattack{ 0,0 };

	Vector2	_nock{ 0,0 };

	Vector2	_HitEffectPos{ 0,0 };

	Vector2 _PlyPos{ static_cast<double>(_x), static_cast<double>(_y - 40.0) };

	/*auto modeGame =
		dynamic_cast<ModeGame*>(g._serverMode->Get("Game"));*/


	switch (_state)
	{
	case Player::STATE::IDLE:
		Idle(g);
		break;
	case Player::STATE::MOVE:
		Move(g);
		break;
	case Player::STATE::ATTACK:
		Attack(g);
		break;
	case Player::STATE::BANANA:
		BananaPut(g);
		break;
	case Player::STATE::NOCKBACK:
		NockBack(g);
		break;
	case Player::STATE::RUSH:
		Rush(g);
		break;
	case Player::STATE::DIAGONALRUSH:
		DiagonalRush(g);
		break;
	default:
		break;
	}

	//g._mapChips._scrX = _x - (SCREEN_W / 2);		// 画面の横中央にキャラを置く
	//g._mapChips._scrY = _y - (SCREEN_H * 7 / 10);	// 画面の縦70%にキャラを置く


	if (_coin <= 0)
	{
		_coin = 0;
	}
	if (_coin >= 50)
	{
		_coin = 50;
	}

	/*if (modeGame->_newMapChips->IsHitFlark(*this, _x, _y != 0))
	{
		_spd = 2.0;
	}
	else
	{
		_spd = 4.0;
	}*/

	////BGM演奏開始

	//if (_coin >= 40 && _finalBGM == true)
	//{
	//	// BGM再生終了
	//	StopMusic();

	//	modeGame->_bgm = PlayMusic("res/bgm/GameFinal.mp3", DX_PLAYTYPE_LOOP);

	//	_finalBGM = false;
	//}

	//else if(_finalBGM == false && _coin <= 35)
	//{
	//	// BGM再生終了
	//	StopMusic();

	//	modeGame->_bgm = PlayMusic("res/bgm/gameMusic.mp3", DX_PLAYTYPE_LOOP);

	//	_finalBGM = true;
	//}
	
	if (_flarkEffectIn == true)
	{
		_flarkefect = std::make_unique<FlarkEffect>(_PlyPos, modeGame->getEffectCnt(), this);

		_flarkEffectIn = false;
	}
	

	if (_specialModeAttackCoolTime <= 0)
	{
		_specialMode = false;

	}

	if (_specialAttackCoolTime <= 0)
	{
		_specialAttack = false;
	}

	if (_specialMode == true)
	{
		_spd = 4.0 * 1.7;
	}
	else if(modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y) != 0))
	{
		_spd = 2.0;
	}
	else
	{
		_spd = 4.0;
	}

	if (_specialAttack == true)
	{
		/*modeGame->AddItem1Effect(_PlyPos, (_cnt - _stateCnt) % 15);*/
		/*auto SpecialAttackEffect = new Item1Effect(_PlyPos, modeGame->getEffectCnt(), (_cnt - _stateCnt) % 15);
		g._objServer.Add(SpecialAttackEffect);*/
	}

	if (_specialMode == true && _specialModeEffect == true)
	{
		/*modeGame->AddStarStateEffect(_PlyPos, this);*/
		/*auto _stareffect = new StarStateEffect(_PlyPos, modeGame->getEffectCnt(), this);
		g._objServer.Add(_stareffect);*/
		
		_starStatefect = std::make_unique<StarStateEffect>(_PlyPos, modeGame->getEffectCnt(), this);

		_specialModeEffect = false;
	}

	else if (_specialMode == false && _specialModeEffect == false)
	{
		_specialModeEffect = true;
	}

	if (_specialMode == true && _specialModeEffect == false)
	{
		_starStatefect->Update(modeGame->getEffectCnt(),g);
	}

	if (_flarkEffect == true)
	{
		_flarkefect->Update(modeGame->getEffectCnt(), g);
	}

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	{
		if ((*ite)->GetType() == _id) {
			continue;
		}
		switch ((*ite)->GetType()) {
		case ObjectBase::OBJECTTYPE::PLAYER1:
		case ObjectBase::OBJECTTYPE::PLAYER2:
		case ObjectBase::OBJECTTYPE::PLAYER3:
		case ObjectBase::OBJECTTYPE::PLAYER4:
			if (IsHit(*(*ite)) == true) {

				if (_specialMode == true && _specialModeCooltime <= 0)
				{
					auto plynock = dynamic_cast<Player*>(*ite);

					if (_charaDir == 1)
					{
						(*ite)->_charaDir = 0;
					}
					else if (_charaDir == 0)
					{
						(*ite)->_charaDir = 1;
					}
					else if (_charaDir == 2)
					{
						(*ite)->_charaDir = 3;
					}
					else if (_charaDir == 3)
					{
						(*ite)->_charaDir = 2;
					}

					/*_hita_x = 0;
					_hita_y = 0;
					_hita_w = 0;
					_hita_h = 0;*/
					/*GetCoin(g);*/
					
					/*(*ite)->BananaDamage(g);*/

					if (plynock->_coin <= 4)
					{
						plynock->SetOverCoin(true);
						plynock->_overCoinNum = plynock->_coin;
					}

					(*ite)->StarDamage(g);

					if ((*ite)->_coin <= 0)
					{

						_fallCoin = false;
					}

					else
					{
						plynock->_fallCoin = true;
					}

					/*_stateAttack = false;*/

					_nock.x = plynock->_x;
					_nock.y = plynock->_y;

					_nockattack.x = _x;
					_nockattack.y = _y;

					plynock->_nockBackpos = _nock - _nockattack;

					_HitEffectPos = _nock;

					_HitEffectPos.y = _HitEffectPos.y - 40.0;

					modeGame->AddHitEffect(_HitEffectPos);


					(*ite)->NockBackMode(g);
					/*DamageGetCoin(g);*/
					Collision(g);
					(*ite)->Collision();
					_specialModeCooltime = 60 * 1;

					// SE再生
					PlaySoundMem(g._se["StarAttack"], DX_PLAYTYPE_BACK);


				}

				else
				{
					Collision(g);
					(*ite)->Collision();
				}

				
			}
			break;
			//case ObjectBase::OBJECTTYPE::COIN:
			//	if (IsHit(*(*ite)) == true) {

			//		g._objServer.Del(this);

			//		GetCoin(g);
			//		modeGame->_isAddCoin = true;

			//		// SE再生
			//		PlaySoundMem(g._se["ShotPlayer"], DX_PLAYTYPE_BACK);
			//	}
			//	break;
			//	if (IsHit(*(*ite)) == true)
			//	{
			//		GetCoin(g);
			//		ModeGame::_isAddCoin = true;

			//		// SE再生
			//		PlaySoundMem(g._se["ShotPlayer"], DX_PLAYTYPE_BACK);
			//	}
			//	break;
			/*case ObjectBase::OBJECTTYPE::ATTACKCOLLISION:
				if (IsHit(*(*ite)) == true) {

					Damage(g);
					(*ite)->Damage(g);
				}
				break;*/
				/*case ObjectBase::OBJECTTYPE::BANANA:
					if (IsHit(*(*ite)) == true) {

						Damage(g);
						(*ite)->Damage(g);
					}
					break;*/
		default:
			break;
		}
	}

	if (_coin >= 50)
	{
		_coin = 50;

		for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
		{
			switch ((*ite)->GetType()) {
			case ObjectBase::OBJECTTYPE::PLAYER1:
				(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER1);
				modeGame->_plyRanking.emplace_back((*ite)->_plyCoin);
				break;
			case ObjectBase::OBJECTTYPE::PLAYER2:
				(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER2);
				modeGame->_plyRanking.emplace_back((*ite)->_plyCoin);
				break;
			case ObjectBase::OBJECTTYPE::PLAYER3:
				(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER3);
				modeGame->_plyRanking.emplace_back((*ite)->_plyCoin);
				break;
			case ObjectBase::OBJECTTYPE::PLAYER4:
				(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER4);
				modeGame->_plyRanking.emplace_back((*ite)->_plyCoin);
				break;

			}
		}

		std::sort(modeGame->_plyRanking.begin(), modeGame->_plyRanking.end(),std::greater<std::pair<int,ObjectBase::OBJECTTYPE>>());


		// ゲームモードのオブジェクト処理をストップ
		modeGame->_stopObjProcess = true;


		// BGM再生終了
		StopMusic();

		// SE再生
		PlaySoundMem(g._se["Finish"], DX_PLAYTYPE_BACK);

		//// UIモードを削除
		//g._serverMode->Del(g._serverMode->Get("UI"));

		//// ゲームモードを削除
		//g._serverMode->Del(modeGame);

		/*ModeResult* modeResult = new ModeResult();
		g._serverMode->Add(modeResult, 3, "Result");*/

	}

	if (_isDebuf == true)
	{
		_spd = 2.0;
		_debufCoolTime--;

		if (_debufCoolTime <= 0)
		{
			_spd = 4.0;
			_isDebuf = false;
		}
	}

	if (_bananaGage >= 60 * 5)
	{
		_bananaGage = 60 * 5;
	}

	//// 残像エフェクトを描画する
	//for (auto&& effect : _blurEffects) {
	//	effect->Update(modeGame->getEffectCnt(), g);
	//}

	//// 死んだ残像エフェクトを削除する
	//_blurEffects.erase(
	//	std::remove_if(_blurEffects.begin(), _blurEffects.end(),
	//		[](auto&& eft) {return eft->isDead(); }),
	//	_blurEffects.end());

	_bananaGage++;

	_xBack = static_cast<int>(_x);
	_yBack = static_cast<int>(_y);

	_oldCoin = _coin;

	_specialModeCooltime--;
	_specialModeAttackCoolTime--;
	_specialAttackCoolTime--;
}

void Player::Idle(Game& g)
{

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	_animeMax = 4;

	auto cnt = _cnt - _stateCnt;
	int key = 0;
	int keyTrg = 0;

	key = g._gKey[GetId()];

	keyTrg = g._gTrg[GetId()];


	// キー入力を判定して、主人公を移動させる
	if (key & PAD_INPUT_LEFT) {
		ChangeState(STATE::MOVE);

	}
	else if (key & PAD_INPUT_RIGHT) {
		ChangeState(STATE::MOVE);
	}
	if (key & PAD_INPUT_UP) {
		ChangeState(STATE::MOVE);
	}
	else if (key & PAD_INPUT_DOWN) {
		ChangeState(STATE::MOVE);
	}

	if (keyTrg & PAD_INPUT_4) {
		if (modeGame->getState() == ModeGame::STATE::COUNTDOWN || modeGame->getState() == ModeGame::STATE::FADEOUT)
		{
			return;
		}
		if (_specialMode == false)
		{
			ChangeState(STATE::ATTACK);

			if (_specialAttack == true)
			{
				// SE再生
				PlaySoundMem(g._se["SpecialAttackStart"], DX_PLAYTYPE_BACK);
			}

			else
			{
				// SE再生
				PlaySoundMem(g._se["swingVainly"], DX_PLAYTYPE_BACK);
			}
			
		}

	}


	if (keyTrg & PAD_INPUT_C) {
		if (modeGame->getState() == ModeGame::STATE::FADEOUT)
		{

			return;
		}
		if (_cooltime < 0)
		{
			_bananaGage = 0;
			ChangeState(STATE::BANANA);

			// SE再生
			PlaySoundMem(g._se["BananaPut"], DX_PLAYTYPE_BACK);
		}
		
	}

	if (keyTrg & PAD_INPUT_B) {
		if (modeGame->getState() == ModeGame::STATE::FADEOUT)
		{
			
			return;
		}

		if (_specialMode == false)
		{
			ChangeState(STATE::RUSH);

			// SE再生
			PlaySoundMem(g._se["swingVainly"], DX_PLAYTYPE_BACK);
		}
		
	}

	_cooltime--;

	_animeNo = (cnt / 20) % _animeMax + _charaDir * _charaDirSlide;
	_grHandle = _grAllHandles[_animeNo];

}

void Player::Move(Game& g)
{

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	if (modeGame->getState() == ModeGame::STATE::FADEOUT)
	{
		ChangeState(STATE::IDLE);

		return;
	}

	Vector2 _FlarkEffectPos{ static_cast<double>(_x - 30.0), static_cast<double>(_y - 70.0) };

	int keyTrg = 0;
	keyTrg = g._gTrg[GetId()];

	_animeMax = 4;

	Vector2 _velocityDir{ 0,0 };
	auto cnt = _cnt - _stateCnt;
	int key = 0;
	key = g._gKey[GetId()];
	bool isMove = false;

	
	if (key & PAD_INPUT_DOWN) {
		_velocityDir.y = 1.0;
		//_y += _spd;
		_charaDir = 0;
		//g._mapChips.IsHit(*this, 0, 1);
		isMove = true;

		if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y)) != 0)
		{
			/*modeGame->AddFlarkEffect(_FlarkEffectPos);*/

			_flarkEffect = true;
		}
	}
	if (key & PAD_INPUT_UP) {
		_velocityDir.y = -1.0;
		//_y -= _spd;
		_charaDir = 1;
		//g._mapChips.IsHit(*this, 0, -1);
		isMove = true;

		if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y)) != 0)
		{
			/*modeGame->AddFlarkEffect(_FlarkEffectPos);*/
			/*_flarkefect->Update(_cnt, g);*/
			/*_flarkefect->Draw(g);*/

			_flarkEffect = true;
		}
	}

	// キー入力を判定して、主人公を移動させる
	if (key & PAD_INPUT_LEFT) {
		_velocityDir.x = -1.0;
		//_x -= _spd;
		_charaDir = 2;
		//g._mapChips.IsHit(*this, -1, 0);
		isMove = true;

		if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y) != 0))
		{
			/*modeGame->AddFlarkEffect(_FlarkEffectPos);*/
			/*_flarkefect->Update(_cnt, g);*/
			/*_flarkefect->Draw(g);*/

			_flarkEffect = true;
		}
	}
	if (key & PAD_INPUT_RIGHT) {
		_velocityDir.x = 1.0;
		//_x += _spd;
		_charaDir = 3;
		//g._mapChips.IsHit(*this, 1, 0);
		isMove = true;

		if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y)) != 0)
		{
			/*modeGame->AddFlarkEffect(_FlarkEffectPos);*/
			/*_flarkefect->Update(_cnt, g);*/
			/*_flarkefect->Draw(g);*/

			_flarkEffect = true;
		}
	}

	if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y)) == 0)
	{
		_flarkEffect = false;
	}

	if(!isMove) {
		_flarkEffect = false;
		ChangeState(STATE::IDLE);
	}

	if (keyTrg & PAD_INPUT_4) {
		if (modeGame->getState() == ModeGame::STATE::COUNTDOWN)
		{
			return;
		}
		if (_specialMode == false)
		{
			ChangeState(STATE::ATTACK);

			if (_specialAttack == true)
			{
				// SE再生
				PlaySoundMem(g._se["SpecialAttackStart"], DX_PLAYTYPE_BACK);
			}

			else
			{
				// SE再生
				PlaySoundMem(g._se["swingVainly"], DX_PLAYTYPE_BACK);
			}
		}
		
	}

	if (keyTrg & PAD_INPUT_C) {
		if (_cooltime < 0)
		{
			_bananaGage = 0;

			ChangeState(STATE::BANANA);

			// SE再生
			PlaySoundMem(g._se["BananaPut"], DX_PLAYTYPE_BACK);
		}
	}

	if (keyTrg & PAD_INPUT_B) {
		
		if (_specialMode == false)
		{
			ChangeState(STATE::RUSH);

			// SE再生
			PlaySoundMem(g._se["swingVainly"], DX_PLAYTYPE_BACK);
		}

	}

	_velocityDir.Normalize();
	_velocityDir *= _spd;

	_x += _velocityDir.x;
	modeGame->_newMapChips->IsHit(*this, static_cast<int>(_velocityDir.x), 0);
	_y += _velocityDir.y;
	modeGame->_newMapChips->IsHit(*this, 0, static_cast<int>(_velocityDir.y));

	
	/*if (key & PAD_INPUT_A) {
		ChangeState(STATE::ATTACK);
	}*/

	_cooltime--;

	_animeNo = (cnt / 10) % _animeMax + _charaDir * _charaDirSlide;
	_grHandle = _grAllHandles[_animeNo];
}

void Player::Draw(Game& g) {

	/*ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");*/

	/*if (_specialMode == true)
	{
		ResourceServer::GetHandles("player_star", _grAllHandles);
	}

	else
	{
		ResourceServer::GetHandles(playerGraph[GetState()] + std::to_string(GetId()), _grAllHandles);
	}*/

	auto cnt = _cnt - _stateCnt;

	int sx = static_cast<int>(_x);
	int sy = static_cast<int>(_y) - _h / 2;


	std::stringstream ss;

	switch (_state)
	{
	case Player::STATE::IDLE:
		DrawRotaGraph(sx, sy, 1.0, 0.0, _grHandle, TRUE, FALSE);
		
		break;
	case Player::STATE::MOVE:
		DrawRotaGraph(sx, sy, 1.0, 0.0, _grHandle, TRUE, FALSE);
		
		break;
	case Player::STATE::ATTACK:
		DrawRotaGraph(sx, sy, 1.0, 0.0, _grHandle, TRUE, FALSE);
		/*DrawGraph(sx, sy, _grHandle, TRUE);
		if (cnt % 5 == 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawGraph(sx, sy, _grHandle, TRUE);
		}*/
		break;
	case Player::STATE::NOCKBACK:

		//DrawRotaGraph(sx, sy, 1.0, 0.0, _grHandle, TRUE, FALSE);

		DrawRotaGraph(sx, sy, 1.0, 0.0, _grHandle, TRUE, FALSE);
		if (cnt % 5 == 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
			DrawRotaGraph(sx, sy, 1.0, 0.0, _grHandle, TRUE, FALSE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}

		break;

	case Player::STATE::RUSH:
		DrawRotaGraph(sx, sy, 1.0, 0.0, _grHandle, TRUE, FALSE);
		
		break;
	}

	switch (_id)
	{
	case ObjectBase::OBJECTTYPE::PLAYER1:

		/*ss << "制限時間(" << _gameTime / 60 << ")\n";*/
		ss << "_Coin1(" << _coin << ")\n";
		/*ss << "バナナ(" << _cooltime / 60 << ")\n";*/
		
		/*DrawBox(sx, sy - 10, sx + _w, sy, GetColor(255, 255, 255),FALSE);*/
		/*if (_bananaGage >= 60 * 5)
		{
			DrawBox(sx, sy - 10, sx + _w * _bananaGage / _bananaGageMax, sy, GetColor(0, 255, 0), TRUE);
		}
		else {
			DrawBox(sx, sy - 10, sx + _w * _bananaGage / _bananaGageMax, sy, GetColor(255, 0, 0), TRUE);
		}*/
		
		/*DrawString(static_cast<int>(_x) - _w / 2, static_cast<int>(_y) - _h * 2, ss.str().c_str(), GetColor(255, 255, 255));*/
		break;
	case ObjectBase::OBJECTTYPE::PLAYER2:
		ss << "_Coin2(" << _coin << ")\n";
		
		
		/*DrawBox(sx, sy - 10, sx + _w, sy, GetColor(255, 255, 255), FALSE);*/
		/*DrawBox(sx, sy - 10, sx + _w * _bananaGage / _bananaGageMax, sy, GetColor(0, 255, 0), TRUE);*/
		/*DrawString(static_cast<int>(_x) - _w / 2, static_cast<int>(_y) - _h - 30, ss.str().c_str(), GetColor(255, 255, 255));*/
		break;
	case ObjectBase::OBJECTTYPE::PLAYER3:
		ss << "_Coin3(" << _coin << ")\n";

		/*DrawBox(sx, sy - 10, sx + _w, sy, GetColor(255, 255, 255), FALSE);*/
		/*DrawBox(sx, sy - 10, sx + _w * _bananaGage / _bananaGageMax, sy, GetColor(0, 255, 0), TRUE);*/
		/*DrawString(static_cast<int>(_x) - _w / 2, static_cast<int>(_y) - _h - 30, ss.str().c_str(), GetColor(255, 255, 255));*/
		break;
	case ObjectBase::OBJECTTYPE::PLAYER4:
		ss << "_Coin4(" << _coin << ")\n";

		/*DrawBox(sx, sy - 10, sx + _w, sy, GetColor(255, 255, 255), FALSE);*/
		/*DrawBox(sx, sy - 10, sx + _w * _bananaGage / _bananaGageMax, sy, GetColor(0, 255, 0), TRUE);*/
		/*DrawString(static_cast<int>(_x) - _w / 2, static_cast<int>(_y) - _h - 30, ss.str().c_str(), GetColor(255, 255, 255));*/
		break;
	}


	/*if (_cooltime <= 0)
	{
		DrawRotaGraph(static_cast<int>(_x), static_cast<int>(_y) - 60, 1.0, 0.0, _grStandbyBanana, TRUE, FALSE);
	}*/

	/*DrawGraph(sx, sy, _grHandle, TRUE);*/


	if (_specialAttack == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		_specialAttackEffectAngle += 0.03;
		if (_specialAttackEffectAngle >= 3.14)
		{
			_specialAttackEffectAngle = 0.0;
		}
		DrawRotaGraph(sx, sy + 10, 1.0, _specialAttackEffectAngle, _grSpecialEffect[0], true, false);

		SetDrawMode(DX_DRAWMODE_NEAREST);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (_specialMode == true && _specialModeEffect == false)
	{
		/*SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155.0);
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		DrawRotaGraph(sx, sy + 10, 1.0, 0.0, _grSpecialEffect[cnt % 15], true, false);

		SetDrawMode(DX_DRAWMODE_NEAREST);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/

		_starStatefect->Draw(g);
	}
	
	if (_isDebuf == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		DrawRotaGraph(sx, sy - 10, 2.0, 0.0, _grDebufEffect[cnt % 10], true, false);

		SetDrawMode(DX_DRAWMODE_NEAREST);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (_flarkEffect == true)
	{
		_flarkefect->Draw(g);
	}

	//// 残像エフェクトを描画する
	//for (auto&& effect : _blurEffects) {
	//	effect->Draw(g);
	//}

	/*if (_getCoin == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155.0);
		SetDrawMode(DX_DRAWMODE_BILINEAR);

		DrawRotaGraph(sx, sy, 1.0, 0.0, _grStarCoinGetEffect[cnt % 20], true, false);

		SetDrawMode(DX_DRAWMODE_NEAREST);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		if (cnt % 20 == 19)
		{
			_getCoin = false;
		}
	}*/

	//// 開発用。当たり判定を表示する
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);		// 半透明描画指定
	//DrawBox(_x + _hit_x, _y + _hit_y, _x + _hit_x + _hit_w, _y + _hit_y + _hit_h, GetColor(255, 0, 0), TRUE);	// 半透明の赤で当たり判定描画
 //   DrawBox(_x + _hita_x, _y + _hita_y, _x + _hita_x + _hita_w, _y + _hita_y + _hita_h, GetColor(0, 255, 0), TRUE);	// 半透明の緑で当たり判定描画
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// 不透明描画指定


	
	
}

void Player::Attack(Game& g)
{

	Vector2	_nockattack{ 0.0,0.0 };

	Vector2	_nock{ 0.0,0.0 };

	Vector2	_PlyEffect{ 0.0,0.0 };

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");
	
	

	auto cnt = _cnt - _stateCnt;
	_animeMax = 5;
	_animeNo = (cnt / 10) % _animeMax + _charaDir * 5;
	_grHandle = _grAllHandles[_animeNo];


	if (cnt > 60 * 0.2 && (_cnt - (_stateCnt + 60 * 0.2)) < 60 * 0.2)
	{
		if (_stateAttack == true)
		{
			if (_charaDir == 1)
			{
				_hita_x = -15;
				_hita_y = -180;
				_hita_w = 30;
				_hita_h = 120;
			}

			if (_charaDir == 0)
			{
				_hita_x = -15;
				_hita_y = -10;
				_hita_w = 30;
				_hita_h = 140;
			}

			if (_charaDir == 2)
			{
				_hita_x = -180;
				_hita_y = -45;
				_hita_w = 150;
				_hita_h = 30;
			}

			if (_charaDir == 3)
			{
				_hita_x = 30;
				_hita_y = -45;
				_hita_w = 150;
				_hita_h = 30;
			}
		}

	}

	for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	{
		if ((*ite)->GetType() == _id) {
			continue;
		}

		int hitx = static_cast<int>(_x) + _hita_x;
		int hity = static_cast<int>(_y) + _hita_y;

		/*if (_newMapchip->CheckHit(hitx, hity) != 0)
		{
			_hita_x = 0;
			_hita_y = 0;
			_hita_w = 0;
			_hita_h = 0;
		}*/
		switch ((*ite)->GetType()) {
		case ObjectBase::OBJECTTYPE::PLAYER1:
		case ObjectBase::OBJECTTYPE::PLAYER2:
		case ObjectBase::OBJECTTYPE::PLAYER3:
		case ObjectBase::OBJECTTYPE::PLAYER4:
			if (IsHitA(*(*ite)) == true && _stateAttack == true) {

				

				auto plynock = dynamic_cast<Player*>(*ite);

				if (plynock->_specialMode == true)
				{
					break;
				}

				_attackMissingSE = false;

				_attackHit1++;
				if (_attackHit1 == 10)
				{
					_attackHit10++;
					_attackHit1 = 0;
				}

				_hita_x = -2000;
				_hita_y = -2000;
				_hita_w = -2000;
				_hita_h = -2000;

				if (_charaDir == 1)
				{
					(*ite)->_charaDir = 0;
				}
				else if (_charaDir == 0)
				{
					(*ite)->_charaDir = 1;
				}
				else if (_charaDir == 2)
				{
					(*ite)->_charaDir = 3;
				}
				else if (_charaDir == 3)
				{
					(*ite)->_charaDir = 2;
				}

				
				
				_stateAttack = false;

				_nock.x = plynock->_x;
				_nock.y = plynock->_y;
				
				_nockattack.x = _x;
				_nockattack.y = _y;

				plynock->_nockBackpos = _nock - _nockattack;

				_PlyEffect = _nock;

				_PlyEffect.y = _PlyEffect.y - 40.0;

				
				(*ite)->NockBackMode(g);

				if (_specialAttack == true)
				{
					_coin = (*ite)->_coin;
					(*ite)->_coin = _oldCoin;

					_specialAttack = false;

					modeGame->AddHitEffect(_PlyEffect);


					// SE再生
					PlaySoundMem(g._se["SpecialAttack"], DX_PLAYTYPE_BACK);

					break;
				}

				modeGame->AddHitEffect(_PlyEffect);

				// SE再生
				PlaySoundMem(g._se["Attack"], DX_PLAYTYPE_BACK);

				if ((*ite)->_coin <= 0)
				{
					break;
				}

				if (plynock->_coin <= 5)
				{
					_coin += plynock->_coin;
					plynock->_coin = 0;
					break;
				}

				/*GetCoin(g);*/
				DamageGetCoin(g);
				(*ite)->Damage(g);
				

				

			}

			else if (IsHitAA(*(*ite)) == true && _stateAttack == true) {

				auto plynock = dynamic_cast<Player*>(*ite);

				_hita_x = -2000;
				_hita_y = -2000;
				_hita_w = -2000;
				_hita_h = -2000;
				/*GetCoin(g);*/
				/*(*ite)->Damage(g);*/

				_stateAttack = false;

				_nock.x = plynock->_x;
				_nock.y = plynock->_y;

				_nockattack.x = _x;
				_nockattack.y = _y;

				plynock->_nockBackpos = _nock - _nockattack;

				_nockBackpos = _nockattack - _nock;


				NockBackMode(g);

				(*ite)->NockBackMode(g);

				// SE再生
				PlaySoundMem(g._se["TwoNockBack"], DX_PLAYTYPE_BACK);

			}


			if (cnt > 60 * 0.4 && (_cnt - (_stateCnt + 60 * 0.4)) < 60 * 0.4)
			{
				_hita_x = -2000;
				_hita_y = -2000;
				_hita_w = -2000;
				_hita_h = -2000;

				_stateAttack = false;
			}
			
			break;
		}
	}

	if (cnt > 60 * 0.7 && (_cnt - (_stateCnt + 60 * 0.7)) < 60 * 0.7)
	{
		//if (_attackMissingSE == true)
		//{
		//	// SE再生
		//	PlaySoundMem(g._se["swingVainly"], DX_PLAYTYPE_BACK);
		//}

		//if (_specialAttack == true)
		//{
		//	// SE再生
		//	PlaySoundMem(g._se["SpecialAttackLost"], DX_PLAYTYPE_BACK);
		//}
		ChangeState(STATE::IDLE);
	}
		

	_cooltime--;

}

void Player::BananaPut(Game& g)
{

	_cooltime = 60 * 5;

	switch (GetType()) {
		case ObjectBase::OBJECTTYPE::PLAYER1:
		{
			if (_charaDir == 1)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 1/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x), static_cast<int>(_y) - _h + 45);
				banana->_charaDir = 1;
				g._objServer.Add(banana);
			}

			if (_charaDir == 0)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 1/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x), static_cast<int>(_y) + banana->GetH() - 20);
				banana->_charaDir = 0;
				g._objServer.Add(banana);
			}

			if (_charaDir == 2)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 1/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x) - _w / 2 - banana->GetH() / 2 + 20, static_cast<int>(_y));
				banana->_charaDir = 2;
				g._objServer.Add(banana);
			}

			if (_charaDir == 3)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 1/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x) + _w / 2 + banana->GetH() / 2 - 24, static_cast<int>(_y));
				banana->_charaDir = 3;
				g._objServer.Add(banana);
			}

			break;
		}
		case ObjectBase::OBJECTTYPE::PLAYER2:
		{
			if (_charaDir == 1)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 2/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x), static_cast<int>(_y) - _h + 45);
				banana->_charaDir = 6;
				g._objServer.Add(banana);
			}

			if (_charaDir == 0)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 2/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x), static_cast<int>(_y) + banana->GetH() - 20);
				banana->_charaDir = 0;
				g._objServer.Add(banana);
			}

			if (_charaDir == 2)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 2/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x) - _w / 2 - banana->GetH() / 2 + 20, static_cast<int>(_y));
				banana->_charaDir = 2;
				g._objServer.Add(banana);
			}

			if (_charaDir == 3)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 2/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x) + _w / 2 + banana->GetH() / 2 - 24, static_cast<int>(_y));
				banana->_charaDir = 4;
				g._objServer.Add(banana);
			}

			break;
		
		}
		case ObjectBase::OBJECTTYPE::PLAYER3:
		{
			if (_charaDir == 1)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 3/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x), static_cast<int>(_y) - _h + 45);
				banana->_charaDir = 6;
				g._objServer.Add(banana);
			}

			if (_charaDir == 0)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 3/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x), static_cast<int>(_y) + banana->GetH() - 20);
				banana->_charaDir = 0;
				g._objServer.Add(banana);
			}

			if (_charaDir == 2)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 3/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x) - _w / 2 - banana->GetH() / 2 + 20, static_cast<int>(_y));
				banana->_charaDir = 2;
				g._objServer.Add(banana);
			}

			if (_charaDir == 3)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 3/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x) + _w / 2 + banana->GetH() / 2 - 24, static_cast<int>(_y));
				banana->_charaDir = 4;
				g._objServer.Add(banana);
			}

			break;
		
		}
		case ObjectBase::OBJECTTYPE::PLAYER4:
		{
			if (_charaDir == 1)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 4/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x), static_cast<int>(_y) - _h + 45);
				banana->_charaDir = 6;
				g._objServer.Add(banana);
			}

			if (_charaDir == 0)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 4/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x), static_cast<int>(_y) + banana->GetH() - 20);
				banana->_charaDir = 0;
				g._objServer.Add(banana);
			}

			if (_charaDir == 2)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 4/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x) - _w / 2 - banana->GetH() / 2 + 20, static_cast<int>(_y));
				banana->_charaDir = 2;
				g._objServer.Add(banana);
			}

			if (_charaDir == 3)
			{
				auto banana = new Banana(ObjectBase::OBJECTTYPE::BANANA, 4/*,Banana::CHARACTER::kPLAYER1*/);
				banana->SetPosition(static_cast<int>(_x) + _w / 2 + banana->GetH() / 2 - 24, static_cast<int>(_y));
				banana->_charaDir = 4;
				g._objServer.Add(banana);
			}

			break;
		
		}
	}

	_cooltime--;

	ChangeState(STATE::IDLE);
}

void Player::NockBackMode(Game& g)
{
	ChangeState(STATE::NOCKBACK);
}

void Player::NockBack(Game& g)
{
	auto cnt = _cnt - _stateCnt;

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	//Coin* coin[10];

	if (_bananaAttack == true)
	{
		if (_fallCoin == true)
		{
			for (int i = 0; i < 10; ++i)
			{
				auto coin = new Coin(ObjectBase::OBJECTTYPE::COIN, *modeGame);

				coin->_coinDir = rand() % 2;

				auto x = static_cast<int>(_x);/*(coin->_coinDir) ? _x + _w: _x - _w;*/
				auto y = static_cast<int>(_y);
				coin->_grandY = static_cast<int>(_y);

				coin->SetPosition(x, y);

				g._objServer.Add(coin);
				coin->_whoCoin = GetId();
				/*coin->Jump(g);*/
				if (coin->_coinDir == 0)
				{
					coin->_vx = rand() % 5 * -1.0;
					coin->_vx = -1;
				}
				if (coin->_coinDir == 1)
				{
					//coin->_vx = rand() % 5;
					coin->_vx = 1;
				}
				coin->_vy = (15.0 + rand() % 10) * -1.0;
				coin->_jump = true;
				coin->_xJump = true;
				coin->_coinType = Coin::COINTYPE::PLAYERCOIN;

				
			}
			_fallCoin = false;
			_bananaAttack = false;
		}

	
		
		
	}

	if (_fallCoin == true)
	{
		for (int i = 0; i < 4; ++i)
		{
			auto coin = new Coin(ObjectBase::OBJECTTYPE::COIN,  *modeGame);

			coin->_coinDir = rand() % 2;

			auto x = static_cast<int>(_x);/*(coin->_coinDir) ? _x + _w : _x - _w;*/
			auto y = static_cast<int>(_y) - 10;
			coin->_grandY = static_cast<int>(_y);

			coin->SetPosition(x, y);

			g._objServer.Add(coin);
			coin->_whoCoin = GetId();
			/*coin->Jump(g);*/
			if (coin->_coinDir == 0)
			{
				coin->_vx = rand() % 5 * -1.0;
				coin->_vx = -1;
			}
			if (coin->_coinDir == 1)
			{
				//coin->_vx = rand() % 5;
				coin->_vx = 1;
			}
			coin->_vy = (15.0 + rand() % 10) * -1.0;
			coin->_jump = true;
			coin->_xJump = true;
			coin->_coinType = Coin::COINTYPE::PLAYERCOIN;


		}
		_fallCoin = false;
	}

	if (_overCoin == true)
	{
		for (int i = 0; i < _overCoinNum; ++i)
		{
			auto coin = new Coin(ObjectBase::OBJECTTYPE::COIN, *modeGame);

			coin->_coinDir = rand() % 2;

			int x = static_cast<int>(_x);/*(coin->_coinDir) ? _x + _w : _x - _w;*/
			int y = static_cast<int>(_y) - 10;
			coin->_grandY = static_cast<int>(_y);

			coin->SetPosition(x, y);

			g._objServer.Add(coin);
			coin->_whoCoin = GetId();
			/*coin->Jump(g);*/
			if (coin->_coinDir == 0)
			{
				coin->_vx = rand() % 5 * -1.0;
				coin->_vx = -1;
			}
			if (coin->_coinDir == 1)
			{
				//coin->_vx = rand() % 5;
				coin->_vx = 1;
			}
			coin->_vy = (15.0 + rand() % 10) * -1.0;
			coin->_jump = true;
			coin->_xJump = true;
			coin->_coinType = Coin::COINTYPE::PLAYERCOIN;


		}

		_overCoin = false;
		_overCoinNum = 0;
	}
	

	_nockBackpos.Normalize();
	_nockBackpos *= 5.0;

	_x += _nockBackpos.x;
	modeGame->_newMapChips->IsHit(*this, static_cast<int>(_nockBackpos.x), 0);
	_y += _nockBackpos.y;
	modeGame->_newMapChips->IsHit(*this, 0, static_cast<int>(_nockBackpos.y));

	if (cnt >= 60 * 0.2)
	{
		ChangeState(STATE::IDLE);
		
	}

	_cooltime--;
}

void Player::Rush(Game& g)
{
	auto cnt = _cnt - _stateCnt;

	auto lifetime = 60 * 1;

	int key = 0;
	key = g._gKey[GetId()];

	ModeGame* modeGame = (ModeGame*)g._serverMode->Get("Game");

	Vector2	_nock{ 0.0,0.0 };

	Vector2	_nockattack{ 0.0,0.0 };

	Vector2 _velocityDir{ 0.0,0.0 };

	Vector2 _velocityDirEffect{ static_cast<double>(_x), static_cast<double>(_y) - 40.0 };

	if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y) != 0) || _isDebuf == true)
	{
		_spd = 2.0;
	}
	
	else if (cnt <= 60 * 0.4)
	{
		_spd = 7.0;
    }
	else
	{
		_spd = 5.0;
	}

	if (key & PAD_INPUT_DOWN) {
		_velocityDir.y = 1.0;
		//_y += _spd;
		_charaDir = 0;
		//g._mapChips.IsHit(*this, 0, 1);
		/*isMove = true;*/

		if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y)) != 0)
		{
			/*modeGame->AddFlarkEffect(_FlarkEffectPos);*/

			_flarkEffect = true;
		}
	}
	if (key & PAD_INPUT_UP) {
		_velocityDir.y = -1.0;
		//_y -= _spd;
		_charaDir = 1;
		//g._mapChips.IsHit(*this, 0, -1);
		/*isMove = true;*/

		if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y)) != 0)
		{
			/*modeGame->AddFlarkEffect(_FlarkEffectPos);*/
			/*_flarkefect->Update(_cnt, g);*/
			/*_flarkefect->Draw(g);*/

			_flarkEffect = true;
		}
	}

	// キー入力を判定して、主人公を移動させる
	if (key & PAD_INPUT_LEFT) {
		_velocityDir.x = -1.0;
		//_x -= _spd;
		_charaDir = 2;
		//g._mapChips.IsHit(*this, -1, 0);
		/*isMove = true;*/

		if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y) != 0))
		{
			/*modeGame->AddFlarkEffect(_FlarkEffectPos);*/
			/*_flarkefect->Update(_cnt, g);*/
			/*_flarkefect->Draw(g);*/

			_flarkEffect = true;
		}
	}
	if (key & PAD_INPUT_RIGHT) {
		_velocityDir.x = 1.0;
		//_x += _spd;
		_charaDir = 3;
		//g._mapChips.IsHit(*this, 1, 0);
		/*isMove = true;*/

		if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y)) != 0)
		{
			/*modeGame->AddFlarkEffect(_FlarkEffectPos);*/
			/*_flarkefect->Update(_cnt, g);*/
			/*_flarkefect->Draw(g);*/

			_flarkEffect = true;
		}
	}

	if (modeGame->_newMapChips->IsHitFlark(*this, static_cast<int>(_x), static_cast<int>(_y)) == 0)
	{
		_flarkEffect = false;
	}

	//if (_charaDir == 0)
	//{
	//	_velocityDir.y = 1.0;

	//	/*_y = _easing(cnt, _rushStart, _rushStop, lifetime);
	//	modeGame->_newMapChips->IsHit(*this, 0, 1);*/
	//}
	//else if (_charaDir == 1)
	//{
	//	_velocityDir.y = -1.0;

	//	/*_y = _easing(cnt, _rushStart, _rushStop, lifetime);
	//	modeGame->_newMapChips->IsHit(*this, 0, -1);*/
	//}
	//else if (_charaDir == 2)
	//{
	//	_velocityDir.x = -1.0;
	//	
	//	/*_x = _easing(cnt, _rushStart, _rushStop, lifetime);
	//	modeGame->_newMapChips->IsHit(*this, -1, 0);*/
	//}

	//else if(_charaDir == 3)
	//{
	//	_velocityDir.x = 1.0;

	//	/*_x = _easing(cnt, _rushStart, _rushStop, lifetime);
	//	modeGame->_newMapChips->IsHit(*this, 1, 0);*/
	//}

	_velocityDir.Normalize();
	_velocityDir *= _spd;

	_x += _velocityDir.x;
	modeGame->_newMapChips->IsHit(*this, static_cast<int>(_velocityDir.x), 0);
	_y += _velocityDir.y;
	modeGame->_newMapChips->IsHit(*this, 0, static_cast<int>(_velocityDir.y));

	//for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
	//{
	//	if ((*ite)->GetType() == _id) {
	//		continue;
	//	}
	//	switch ((*ite)->GetType()) {
	//	case ObjectBase::OBJECTTYPE::PLAYER1:
	//	case ObjectBase::OBJECTTYPE::PLAYER2:
	//	case ObjectBase::OBJECTTYPE::PLAYER3:
	//	case ObjectBase::OBJECTTYPE::PLAYER4:
	//		if (IsHit(*(*ite)) == true) {

	//			if (_rushAttackCoolTime <= 0)
	//			{

	//				auto plynock = dynamic_cast<Player*>(*ite);

	//				if (plynock->_specialMode == true)
	//				{
	//					break;
	//				}

	//				if (_charaDir == 1)
	//				{
	//					(*ite)->_charaDir = 0;
	//				}
	//				else if (_charaDir == 0)
	//				{
	//					(*ite)->_charaDir = 1;
	//				}
	//				else if (_charaDir == 2)
	//				{
	//					(*ite)->_charaDir = 3;
	//				}
	//				else if (_charaDir == 3)
	//				{
	//					(*ite)->_charaDir = 2;
	//				}

	//				/*_hita_x = 0;
	//				_hita_y = 0;
	//				_hita_w = 0;
	//				_hita_h = 0;*/
	//				/*GetCoin(g);*/
	//				/*(*ite)->Damage(g);*/

	//				/*_stateAttack = false;*/

	//				_nock.x = plynock->_x;
	//				_nock.y = plynock->_y;

	//				_nockattack.x = _x;
	//				_nockattack.y = _y;

	//				plynock->_nockBackpos = _nock - _nockattack;

	//				if (plynock->_coin <= 3)
	//				{
	//					plynock->SetOverCoin(true);
	//					plynock->_overCoinNum = plynock->_coin;
	//				}

	//				(*ite)->NockBackMode(g);

	//				
	//				(*ite)->RushDamage(g);
	//				/*DamageGetCoin(g);*/
	//				Collision(g);
	//				(*ite)->Collision();

	//				_rushAttackCoolTime = 60 * 1;

	//				if ((*ite)->_coin <= 0)
	//				{
	//					break;
	//				}

	//				plynock->_fallCoin = true;
	//				
	//			}

	//			else
	//			{
	//				_rushAttackCoolTime--;
	//			}


	//			
	//		}
	//	}

	//}

	_animeMax = 16;
	_animeNo = (cnt / 4) % _animeMax + _charaDir * 16;
	_grHandle = _grAllHandles[_animeNo];

	if (cnt % 3 == 0)
	{
		/*modeGame->AddBlurEffect(_velocityDirEffect, _grHandle, 0.0);*/
		auto newEffect = new BlurEffect(_velocityDirEffect, modeGame->getEffectCnt(), _grHandle, 0.0);
		/*_blurEffects.emplace_back(std::move(newEffect));*/
		g._objServer.Add(newEffect);
	}
	


	/*modeGame->AddExplosionEffect(_velocityDirEffect);*/

	if (cnt >= 60 * 1.0)
	{
		_spd = 4.0;

		_rushAttackCoolTime = 0;

		ChangeState(STATE::IDLE);

	}

	_cooltime--;
}
	

void Player::DiagonalRush(Game& g)
{
	auto cnt = _cnt - _stateCnt;

}

void Player::Collision(Game& g)
{
	_x = _xBack;
	_y = _yBack;
}

void Player::DamageGetCoin(Game& g)
{
	_coin += 6;
}

void Player::GetCoin(Game& g)
{
	_coin += 10;
}

void Player::GetPlayerCoin(Game& g)
{
	_coin += 1;
}

void Player::Damage(Game& g) {
	_coin -= 6;
}

void Player::BananaDamage(Game& g)
{
	_coin -= 10;
}

void Player::RushDamage(Game& g)
{
	_coin -= 4;
}

void Player::StarDamage(Game& g)
{
	_coin -= 4;
}