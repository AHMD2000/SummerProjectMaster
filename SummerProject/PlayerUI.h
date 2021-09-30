#pragma once

#include "Player.h"

class Game;

class PlayerUI : public Player
{
public:
	PlayerUI(ObjectBase::OBJECTTYPE id, Game& g);
	~PlayerUI();

	void	Init();
	void	Process(Game& g) override;
	void	Draw(Game& g) override;

private:

	std::vector<int> _grAllAttackUIHandles;
	int _grAttackUIHandle;

	std::vector<int> _grAllResultCoinHandles;
	int _grResultCoinHandle;

	int _CoinanimeMax = 6;
	int _CoinAnimeNum = 0;
	/*int _attackUIAnimeMax;
	int _attackUIAnimeNum;*/

	ObjectBase::OBJECTTYPE _id;
};