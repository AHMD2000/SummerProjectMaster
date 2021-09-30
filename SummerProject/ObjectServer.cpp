#include "DxLib.h"
#include "ObjectServer.h"
#include	<algorithm>

ObjectServer::ObjectServer()
{
	_vObject.clear();
	_vAdd.clear();
	_vDel.clear();
}

ObjectServer::~ObjectServer()
{
	Clear();
}

// リストに登録されているオブジェクトをすべて消す
void	ObjectServer::Clear()
{
	for (auto ite = _vObject.begin(); ite != _vObject.end(); ite++)
	{
		delete (*ite);
	}
	_vObject.clear();
}

// Addリストにオブジェクトを登録する
void	ObjectServer::Add(ObjectBase* obj)
{
	_vAdd.push_back(obj);
}

// Delリストにオブジェクトを登録する
void	ObjectServer::Del(ObjectBase* obj)
{
	_vDel.push_back(obj);
}

// Addリストのオブジェクトを追加する
void	ObjectServer::AddListObjects()
{
	for (auto iteAdd = _vAdd.begin(); iteAdd != _vAdd.end(); iteAdd++)
	{
		_vObject.push_back((*iteAdd));
	}
	_vAdd.clear();
}

// Delリストのオブジェクトを削除する
void	ObjectServer::DelListObjects()
{
	for (auto iteDel = _vDel.begin(); iteDel != _vDel.end(); iteDel++)
	{
		for (auto ite = _vObject.begin(); ite != _vObject.end();)
		{
			if ((*ite) == (*iteDel))
			{
				delete (*ite);
				ite = _vObject.erase(ite);
			}
			else
			{
				ite++;
			}
		}
	}
	_vDel.clear();
}


// Process()を登録順に回す
void	ObjectServer::Process(Game& g)
{
	// Addリストにあるオブジェクトをリストに登録する
	AddListObjects();

	// Process()の呼び出し
	for (auto ite = _vObject.begin(); ite != _vObject.end(); ite++)
	{
		(*ite)->Process(g);

		(*ite)->Update(_effectCnt, g);
	}

	// yによるソート
	std::sort(
		_vObject.begin(),
		_vObject.end(),
		[](const ObjectBase* ch1, const ObjectBase* ch2) {return ch1->_y < ch2->_y; }
	);

	// Delリストにあるオブジェクトをリストから削除する
	DelListObjects();

	_effectCnt++;
}

// Draw()を登録順に回す
void	ObjectServer::Draw(Game& g)
{
	for (auto ite = _vObject.begin(); ite != _vObject.end(); ite++)
	{
		(*ite)->Draw(g);
	}
}
