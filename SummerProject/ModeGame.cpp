#include "ModeGame.h"
#include "Game.h"
#include "newMapChips.h"
#include "Plexus.h"
#include "StageGimmic.h"
#include "Coin.h"
#include "Crown.h"
#include "SpecialMode.h"
#include <DxLib.h>
#include "ModeResult.h"
#include "ResourceServer.h"
#include "Debuf.h"
#include "Star.h"
#include <sstream>
#include <memory>
#include <algorithm>
#include "Vector.h"

namespace COINAPPEARANCE
{
	constexpr auto COINWAITTIME = 60 * 8;

}

namespace PlayerPos
{
	Vector2 PLAYER1 = { 560.0 , 300.0 };
	Vector2 PLAYER2 = { 1410.0 , 420.0 };
	Vector2 PLAYER3 = { 675.0 , 740.0 };
	Vector2 PLAYER4 = { 1425.0 , 780.0 };
}

bool ModeGame::Initialize(Game& g)
{
	if (!base::Initialize(g)) { return false; }

	_circleHandle = 0;

	_countDownCnt = 60 * 4;

	_gameCnt = 60 * 90;

	/*_gameCnt = 60 * 10;*/

	/*_gameCnt = 60 * 1;*/

	_state = STATE::COUNTDOWN;

	_circleHandle = ResourceServer::GetHandles("UI_circle");

	_grAllCountDownHandles.emplace_back(ResourceServer::GetHandles("CountDown1"));
	_grAllCountDownHandles.emplace_back(ResourceServer::GetHandles("CountDown2"));
	_grAllCountDownHandles.emplace_back(ResourceServer::GetHandles("CountDown3"));
	_grAllCountDownHandles.emplace_back(ResourceServer::GetHandles("CountDownStart"));

	_isAddCoin = true;
	/*_isAddDebuf = true;*/
	
	_coinWaitTime = 0;
	_debufWaitTime = 0;
	_itemWaitTime = 60 * 2;

	//��Q���̐ݒu
	/*auto plexus = new Plexus(ObjectBase::OBJECTTYPE::PLEXUS, Plexus::STATE::BIG);
	g._objServer.Add(plexus);*/
	auto plexus_small1 = new Plexus(ObjectBase::OBJECTTYPE::PLEXUS, Plexus::STATE::SMALL);
	g._objServer.Add(plexus_small1);
	auto plexus_small2 = new Plexus(ObjectBase::OBJECTTYPE::PLEXUS, Plexus::STATE::SMALL);
	plexus_small2->SetPosition(832 + plexus_small2->_w / 2, 375 + plexus_small2->_h);
	g._objServer.Add(plexus_small2);
	auto plexus_small3 = new Plexus(ObjectBase::OBJECTTYPE::PLEXUS, Plexus::STATE::SMALL);
	plexus_small3->SetPosition(930 + plexus_small3->_w / 2, 721 + plexus_small3->_h);
	g._objServer.Add(plexus_small3);
	auto plexus_small4 = new Plexus(ObjectBase::OBJECTTYPE::PLEXUS, Plexus::STATE::SMALL);
	plexus_small4->SetPosition(1711 + plexus_small4->_w / 2, 230 + plexus_small4->_h);
	g._objServer.Add(plexus_small4);
	auto flark_small = new StageGimmic(ObjectBase::OBJECTTYPE::GIMMIC, StageGimmic::STATE::FLARKSMALL);
	_stageGimmics.emplace_back(flark_small);
	auto fallenTree1 = new StageGimmic(ObjectBase::OBJECTTYPE::GIMMIC, StageGimmic::STATE::FALLENTREE);
	g._objServer.Add(fallenTree1);
	auto fallenTree2 = new StageGimmic(ObjectBase::OBJECTTYPE::GIMMIC, StageGimmic::STATE::FALLENTREE2);
	/*fallenTree2->SetPosition(916 + 52, 474 + 200);
	fallenTree2->SetAngle(-1.57);*/
	g._objServer.Add(fallenTree2);
	auto fallenTreeflower = new StageGimmic(ObjectBase::OBJECTTYPE::GIMMIC, StageGimmic::STATE::FALLENTREEFLOWER);
	g._objServer.Add(fallenTreeflower);
	auto rock1 = new StageGimmic(ObjectBase::OBJECTTYPE::GIMMIC, StageGimmic::STATE::ROCK);
	rock1->SetPosition(1504 + rock1->_w / 2, 218 + rock1->_h);
	/*_stageGimmics.emplace_back(rock1);*/
	g._objServer.Add(rock1);
	auto rock2 = new StageGimmic(ObjectBase::OBJECTTYPE::GIMMIC, StageGimmic::STATE::ROCK);
	rock2->SetPosition(199 + rock2->_w / 2, 128 + rock2->_h);
	/*_stageGimmics.emplace_back(rock2);*/
	g._objServer.Add(rock2);
	auto rake = new StageGimmic(ObjectBase::OBJECTTYPE::GIMMIC, StageGimmic::STATE::RAKE);
	_stageGimmics.emplace_back(rake);
	/*auto flark = new StageGimmic(ObjectBase::OBJECTTYPE::GIMMIC, StageGimmic::STATE::FLARKBIG);
	_stageGimmics.emplace_back(flark);*/

	// �v���C���[�𐶐����A�I�u�W�F�N�g�T�[�o�ɓo�^����
	auto ply1 = new Player(ObjectBase::OBJECTTYPE::PLAYER1, g);
	ply1->SetPosition(static_cast<int>(PlayerPos::PLAYER1.x), static_cast<int>(PlayerPos::PLAYER1.y));
	g._objServer.Add(ply1);


	auto ply2 = new Player(ObjectBase::OBJECTTYPE::PLAYER2, g);
	ply2->SetPosition(static_cast<int>(PlayerPos::PLAYER2.x), static_cast<int>(PlayerPos::PLAYER2.y));
	g._objServer.Add(ply2);

	auto ply3 = new Player(ObjectBase::OBJECTTYPE::PLAYER3, g);
	ply3->SetPosition(static_cast<int>(PlayerPos::PLAYER3.x), static_cast<int>(PlayerPos::PLAYER3.y));
	g._objServer.Add(ply3);

	auto ply4 = new Player(ObjectBase::OBJECTTYPE::PLAYER4, g);
	ply4->SetPosition(static_cast<int>(PlayerPos::PLAYER4.x), static_cast<int>(PlayerPos::PLAYER4.y));
	g._objServer.Add(ply4);

	/*auto crown = new Crown(ObjectBase::OBJECTTYPE::CROWN);
	g._objServer.Add(crown);*/

	_crown = std::make_unique<Crown>(ObjectBase::OBJECTTYPE::CROWN);

	if (GetStage() == STAGE::NORMAL)
	{
		_newMapChips = new NewMapChips("res/", "stage");
	}

	/*auto star = new Star(ObjectBase::OBJECTTYPE::STAR, *this);
	star->SetPosition(0, 0);
	g._objServer.Add(star);*/

	/*g._objServer.Add(new Coin());*/
	/*g._objServer.Add(new MapChips());*/


	////BGM���t�J�n
	//_bgm = PlayMusic("res/bgm/gameMusic.mp3", DX_PLAYTYPE_LOOP);
	_stopObjProcess = false;
	return true;
}

bool ModeGame::Terminate(Game& g) {
	base::Terminate(g);

	delete _newMapChips;
	g._objServer.Clear();
	return true;
}

bool ModeGame::Process(Game& g) {
	base::Process(g);

	/*_newMapChips->Process(g);*/

	

	if (_stopObjProcess == false)
	{
		if (_state == STATE::COUNTDOWN)
		{
			// �I�u�W�F�N�g�T�[�o�ɓo�^����Ă���I�u�W�F�N�g��Process()���Ăяo��
			g._objServer.Process(g);

			// �G�t�F�N�g���X�V����
			for (auto&& effect : _effects) {
				effect->Update(_effectCount, g);
			}
			// ���񂾃G�t�F�N�g���폜����
			_effects.erase(
				std::remove_if(_effects.begin(), _effects.end(),
					[](auto&& eft) {return eft->isDead(); }),
				_effects.end());

			_crown->Process(g);
		}

		else
		{
			AddCoin(g);
			/*AddDebuf(g);
			AddStar(g);*/
			AddItem(g);
			// �I�u�W�F�N�g�T�[�o�ɓo�^����Ă���I�u�W�F�N�g��Process()���Ăяo��
			g._objServer.Process(g);

			_crown->Process(g);

			// �G�t�F�N�g���X�V����
			for (auto&& effect : _effects) {
				effect->Update(_effectCount, g);
			}
			// ���񂾃G�t�F�N�g���폜����
			_effects.erase(
				std::remove_if(_effects.begin(), _effects.end(),
					[](auto&& eft) {return eft->isDead(); }),
				_effects.end());

			_gameCnt--;//�Q�[���̐�������
		}

		if (_gameCnt <= 0)
		{
			for (auto ite = g._objServer.List()->begin(); ite != g._objServer.List()->end(); ite++)
			{
				switch ((*ite)->GetType()) {
				case ObjectBase::OBJECTTYPE::PLAYER1:
					(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER1);
					_plyRanking.emplace_back((*ite)->_plyCoin);
					break;
				case ObjectBase::OBJECTTYPE::PLAYER2:
					(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER2);
					_plyRanking.emplace_back((*ite)->_plyCoin);
					break;
				case ObjectBase::OBJECTTYPE::PLAYER3:
					(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER3);
					_plyRanking.emplace_back((*ite)->_plyCoin);
					break;
				case ObjectBase::OBJECTTYPE::PLAYER4:
					(*ite)->_plyCoin = std::make_pair((*ite)->_coin, ObjectBase::OBJECTTYPE::PLAYER4);
					_plyRanking.emplace_back((*ite)->_plyCoin);
					break;

				}
			}

			std::sort(_plyRanking.begin(), _plyRanking.end(), std::greater<std::pair<int, ObjectBase::OBJECTTYPE>>());

			_stopObjProcess = true;

			// BGM�Đ��I��
			StopMusic();


			//// UI���[�h���폜
			//g._serverMode->Del(g._serverMode->Get("UI"));

			//g._serverMode->Del(this);

			ModeResult* modeResult = new ModeResult();
			g._serverMode->Add(modeResult, 3, "Result");
		}
		
	}

	/*_mapChips.Process(g);*/

	if (_state == STATE::COUNTDOWN)
	{
		_countDownCnt--;
		_effectCount++;

		if (_countDownCnt <= 0)
		{
			_state = STATE::PLAYGAME;
		}
	}

	else {
		_cnt++;
		_effectCount++;
	}
	

	return true;
}

bool ModeGame::Draw(Game& g) {
	base::Draw(g);


	if (_state == STATE::COUNTDOWN)
	{

		_bg.Draw();	// �w�i�摜�`��
		 // ��Q����`�悷��
		for (auto&& gimmic : _stageGimmics) {
			gimmic->Draw(g);
		}
		/*_mapChips.Draw();*/

		g._objServer.Draw(g);// �I�u�W�F�N�g�̕`��

		_newMapChips->Draw();

		_crown->Draw(g);

		// �G�t�F�N�g��`�悷��
		for (auto&& effect : _effects) {
			effect->Draw(g);
		}

		
		if (_countDownCnt / 60 == 3)
		{
			DrawRotaGraph(SCREEN_W / 2, SCREEN_H / 2, 1.0, 0.0, _grAllCountDownHandles[2], TRUE, FALSE);
		}
		else if (_countDownCnt / 60 == 2)
		{
			DrawRotaGraph(SCREEN_W / 2, SCREEN_H / 2, 1.0, 0.0, _grAllCountDownHandles[1], TRUE, FALSE);
		}
		else if (_countDownCnt / 60 == 1)
		{
			DrawRotaGraph(SCREEN_W / 2, SCREEN_H / 2, 1.0, 0.0, _grAllCountDownHandles[0], TRUE, FALSE);
		}
		else if (_countDownCnt / 60 <= 0)
		{
			DrawRotaGraph(SCREEN_W / 2, SCREEN_H / 2, 1.0, 0.0, _grAllCountDownHandles[3], TRUE, FALSE);
		}

		if (_countDownCnt == 239)
		{
			// SE�Đ�
			PlaySoundMem(g._se["CountDown"], DX_PLAYTYPE_BACK);
		}
		else if (_countDownCnt == 179)
		{
			// SE�Đ�
			PlaySoundMem(g._se["CountDown"], DX_PLAYTYPE_BACK);
		}
		else if (_countDownCnt == 119)
		{
			// SE�Đ�
			PlaySoundMem(g._se["CountDown"], DX_PLAYTYPE_BACK);
		}

		else if (_countDownCnt == 59)
		{
			// SE�Đ�
			PlaySoundMem(g._se["CountDown"], DX_PLAYTYPE_BACK);
		}
		
	}

	else
	{
		//// �`�悷�镶����̃T�C�Y��ݒ�
		//SetFontSize(20);

		/*std::stringstream ss;*/

		_bg.Draw();	// �w�i�摜�`��
		/*_mapChips.Draw();*/

		 // ��Q����`�悷��
		for (auto&& gimmic : _stageGimmics) {
			gimmic->Draw(g);
		}

		g._objServer.Draw(g);// �I�u�W�F�N�g�̕`��

		_newMapChips->Draw();

		_crown->Draw(g);
		
		


		

		 // �G�t�F�N�g��`�悷��
		for (auto&& effect : _effects) {
			effect->Draw(g);
		}

		/*DrawCircleGauge(SCREEN_W / 2, SCREEN_H / 2, 100.0,_circleHandle,0);*/

		/*for (auto i = 0; i < _plyRanking.size(); ++i) {
			ss << "(" << _plyRanking.at(i).second << ")" << "; ";
		}
		DrawString(SCREEN_W / 2, SCREEN_H / 2, ss.str().c_str(), GetColor(255, 255, 255));*/
	}

	

	return true;
}

void ModeGame::AddCoin(Game& g)
{


	if (_isAddCoin)
	{
		if (_coinWaitTime > 0)
		{
			_coinWaitTime--;
		}
		else
		{
			auto coin = new Coin(ObjectBase::OBJECTTYPE::COIN, *this);
			g._objServer.Add(coin);
			_isAddCoin = false;
			_coinWaitTime = COINAPPEARANCE::COINWAITTIME;

			// SE�Đ�
			PlaySoundMem(g._se["StarCoinAppearance"], DX_PLAYTYPE_BACK);
		}
		
	}
}

void ModeGame::AddDebuf(Game& g)
{
	/*if (_isAddDebuf)
	{*/
		if (_debufWaitTime >= 0)
		{
			_debufWaitTime--;
		}
		else
		{
			auto debuf = new Debuf(ObjectBase::OBJECTTYPE::DEBUF, *this);
			g._objServer.Add(debuf);
			/*_isAddDebuf = false;*/
			_debufWaitTime = 60 * 10;
		}
	/*}*/
}

void ModeGame::AddStar(Game& g)
{
	if (_starWaitTime >= 0)
	{
		_starWaitTime--;
	}
	else
	{
		auto star = new Star(ObjectBase::OBJECTTYPE::STAR, *this);
		g._objServer.Add(star);
		/*_isAddDebuf = false;*/
		_starWaitTime = 60 * 10;
	}
}

void ModeGame::AddItem(Game& g)
{
	if (_itemWaitTime > 0)
	{
		_itemWaitTime--;
	}

	else
	{
		int itemProbabilityTable[] = { 40, 40, 20, };

		int probability = 0;

		int itemIndex = -1; //���I���ꂽ�A�C�e���̃C���f�b�N�X

		for (int i = 0; i < 3; ++i)
		{
			probability += itemProbabilityTable[i];
			int r = rand() % 100;

			if (r < probability)
			{
				//�A�C�e�������I���ꂽ
				itemIndex = i;
				break;
			}
		}

		if (itemIndex == 0)
		{

			auto star = new Star(ObjectBase::OBJECTTYPE::STAR, *this);
			g._objServer.Add(star);

			// SE�Đ�
			PlaySoundMem(g._se["ItemAppearance"], DX_PLAYTYPE_BACK);
		}
		else if (itemIndex == 1)
		{
			auto specialMode = new SpecialMode(ObjectBase::OBJECTTYPE::SPECIALMODE, *this);
			g._objServer.Add(specialMode);

			// SE�Đ�
			PlaySoundMem(g._se["ItemAppearance"], DX_PLAYTYPE_BACK);
		}
		else
		{
			auto debuf = new Debuf(ObjectBase::OBJECTTYPE::DEBUF, *this);
			g._objServer.Add(debuf);

			// SE�Đ�
			PlaySoundMem(g._se["ItemAppearance"], DX_PLAYTYPE_BACK);
		}

		_itemWaitTime = 60 * 10;
	}

}

//�t�F�[�h�G�t�F�N�g�̒ǉ�
void ModeGame::AddFadeEffect(int color)
{
	auto newFadeEffect = std::make_unique<FadeEffect>(_effectCount, color);
	_effects.emplace_back(std::move(newFadeEffect));
}

void ModeGame::AddExplosionEffect(const Vector2& pos)
{
	auto newEffect = std::make_unique<ExplosionEffect>(pos, _effectCount);
	_effects.emplace_back(std::move(newEffect));
}

// �c���G�t�F�N�g�̒ǉ�
void ModeGame::AddBlurEffect(const Vector2& pos, int grHandle, double angle)
{
	auto newEffect = std::make_unique<BlurEffect>(pos, _effectCount, grHandle, angle);
	_effects.emplace_back(std::move(newEffect));
}

//�M���G�t�F�N�g�̒ǉ�
void ModeGame::AddSparkEffect(const Vector2& pos)
{
	auto newEffect = std::make_unique<FlashEffect>(pos, _effectCount);
	_effects.emplace_back(std::move(newEffect));
}

//�A�C�e���P�̃G�t�F�N�g
void ModeGame::AddItem1Effect(const Vector2& pos, int no)
{
	auto newEffect = std::make_unique<Item1Effect>(pos, _effectCount, no);
	_effects.emplace_back(std::move(newEffect));
}

//�A�C�e���P�ȊO�̃q�b�g�G�t�F�N�g
void ModeGame::AddHitEffect(const Vector2& pos)
{
	auto newEffect = std::make_unique<HitEffect>(pos, _effectCount);
	_effects.emplace_back(std::move(newEffect));
}

//�X�^�[�R�C�����莞�̃G�t�F�N�g�̒ǉ�
void ModeGame::AddCoinGetEffect(const Vector2& pos)
{
	auto newEffect = std::make_unique<CoinGetEffect>(pos, _effectCount);
	_effects.emplace_back(std::move(newEffect));
}

//�X�^�[��Ԃ̃G�t�F�N�g�̒ǉ�
void ModeGame::AddStarStateEffect(const Vector2& pos, Player* ply)
{
	auto newEffect = std::make_unique<StarStateEffect>(pos, _effectCount, ply);
	_effects.emplace_back(std::move(newEffect));
}

//�A�C�e�����莞�̃G�t�F�N�g
void ModeGame::AddItemGetEffect(const Vector2& pos)
{
	auto newEffect = std::make_unique<ItemGetEffect>(pos, _effectCount);
	_effects.emplace_back(std::move(newEffect));
}

//�D���̃G�t�F�N�g
void ModeGame::AddFlarkEffect(const Vector2& pos, Player* ply)
{
	auto newEffect = std::make_unique<FlarkEffect>(pos, _effectCount, ply);
	_effects.emplace_back(std::move(newEffect));
}

//void ModeGame::ChangeisAddCoin()
//{
//	_isAddCoin = true;
//}