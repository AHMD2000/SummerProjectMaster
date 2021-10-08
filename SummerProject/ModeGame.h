#pragma once

#include	"ModeBase.h"
#include    "StageGimmic.h"
#include	"BackGround.h"
#include	"Player.h"
#include    "Coin.h"
#include    "newMapchips.h"
#include	<memory>
#include	<vector>
#include	"Effect.h"
#include	"Crown.h"

//class Player;

class ModeGame : public ModeBase
{
	typedef ModeBase base;
public:

	enum class STATE {
		FADEOUT,
		COUNTDOWN,
		PLAYGAME,
	};

	enum class STAGE
	{
		NORMAL,
	};

	virtual bool Initialize(Game& g);
	virtual bool Terminate(Game& g);
	virtual bool Process(Game& g);
	virtual bool Draw(Game& g);

	void	AddCoin(Game& g);
	void	AddDebuf(Game& g);
	void	AddStar(Game& g);
	void	AddItem(Game& g);
	/*static	void ChangeisAddCoin();*/

	//�t�F�[�h�G�t�F�N�g�̒ǉ�
	void AddFadeEffect(int color);

	// �����G�t�F�N�g�̒ǉ�
	void AddExplosionEffect(const Vector2& pos);

	// �c���G�t�F�N�g�̒ǉ�
	void AddBlurEffect(const Vector2& pos, int grHandle, double angle);

	// �M���G�t�F�N�g�̒ǉ�
	void AddSparkEffect(const Vector2& pos);

	//�A�C�e���P�̃G�t�F�N�g
	void AddItem1Effect(const Vector2& pos, int no);

	// �A�C�e���P�ȊO�̃q�b�g�G�t�F�N�g�̒ǉ�
	void AddHitEffect(const Vector2& pos);

	// �R�C���Q�b�g�̃G�t�F�N�g�̒ǉ�
	void AddCoinGetEffect(const Vector2& pos);

	// �X�^�[��Ԃ̃G�t�F�N�g�̒ǉ�
	void AddStarStateEffect(const Vector2& pos, Player* ply);

	// �A�C�e���Q�b�g�G�t�F�N�g�̒ǉ�
	void AddItemGetEffect(const Vector2& pos);

	// �D���G�t�F�N�g�̒ǉ�
	void AddFlarkEffect(const Vector2& pos, Player* ply);


	bool    _isAddCoin;
	bool    _isAddDebuf;
	bool	_stopObjProcess;
	int _gameBGM = 0;

	std::vector<std::pair<int, ObjectBase::OBJECTTYPE>> _plyRanking;
	/*std::vector<std::unique_ptr<Player>> _plyRanking;*/

	// �}�b�v�`�b�v
	NewMapChips* _newMapChips;

	int	getGameCnt() { return _gameCnt;}

	//�G�t�F�N�g�̃J�E���g
	int	getEffectCnt() { return _effectCount; }

	STAGE GetStage() { return _stage; }

	STATE getState() { return _state; }

	STAGE _stage;

private:

	STATE	_state;

	int _effectCount = 0; //�G�t�F�N�g�̃J�E���g

	int _fadeOutCnt = 0;

	int _a = 255;

	int	_circleHandle = 0;

	int _debufWaitTime;
	int _starWaitTime;
	int _coinWaitTime = 0;
	int _itemWaitTime;
	int _cnt = 0;
	int _countDownCnt;
	int _gameCnt;//�Q�[���̐�������

	// �w�i
	BackGround	_bg;

	std::vector<int> _grAllCountDownHandles;// ���ׂẴJ�E���g�_�E���̃O���t�B�b�N�n���h��

	//�t�B�j�b�V���̉摜
	int _finishHandle;

	//����
	std::unique_ptr<Crown> _crown;


	// �G�t�F�N�g�̃��j�[�N�|�C���^�̓��I�z��
	std::vector<std::unique_ptr<Effect>> _effects;
	//��Q���̃��j�[�N�|�C���^�̓��I�z��
	std::vector<std::unique_ptr<StageGimmic>> _stageGimmics;

};