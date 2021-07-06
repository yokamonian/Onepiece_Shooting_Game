#pragma once
#include "GameNode.h"
#include "pch.h"

class NormalEnemy_Tichi;
class NormalEnemy_Shiki;
class NormalEnemy_Choppa;
class NormalEnemy_Wapol;
class NormalEnemy_Franky;
class ActionElement;
class EnemyManager : public GameNode
{
private:

	//0527 ���� �߰�.
	FPOINT playerPos;

	vector<NormalEnemy_Wapol*> NormalWapols;
	vector<NormalEnemy_Wapol*>::iterator NW_iter;

	stack<NormalEnemy_Wapol*> stNormalWapols;

	// ��Ű
	vector<NormalEnemy_Shiki*> NormalShikis;
	vector<NormalEnemy_Shiki*>::iterator NS_iter;

	stack<NormalEnemy_Shiki*> stNormalShikis;

	// Ƽġ
	vector<NormalEnemy_Tichi*> NormalTichis;
	vector<NormalEnemy_Tichi*>::iterator NT_iter;

	stack<NormalEnemy_Tichi*> stNormalTichis;

	// ����Ű
	vector<NormalEnemy_Franky*> NormalFrankys;
	vector<NormalEnemy_Franky*>::iterator NF_iter;

	stack<NormalEnemy_Franky*> stNormalFrankys;

	// ����
	vector<NormalEnemy_Choppa*> NormalChoppa;
	vector<NormalEnemy_Choppa*>::iterator NC_iter;

	stack<NormalEnemy_Choppa*> stNormalChoppa;

	// ������ ����
	ActionElement* ae0;
	ActionElement* ae1;
	ActionElement* ae5;
	ActionElement* ae7;
	ActionElement* ae9_1;
	ActionElement* ae9_2;

	vector<ActionElement*> P0;
	vector<ActionElement*> P1;
	vector<ActionElement*> P5;
	vector<ActionElement*> P7;
	vector<ActionElement*> P9;
	// ��Ű ����
	ActionElement* ae3;
	ActionElement* ae6;

	vector<ActionElement*> P3;
	vector<ActionElement*> P6;
	// Ƽġ ����
	ActionElement* ae4;
	ActionElement* ae8;

	vector<ActionElement*> P4;
	vector<ActionElement*> P8;
	// ����Ű ����
	ActionElement* ae2;
	ActionElement* ae7_2;

	vector<ActionElement*> P2;
	vector<ActionElement*> P7_2;
	float currFrame;
	int EventCount = 10;
	float *EventTime = new float[EventCount];
	int waveId;
	int monsterCount[4] = { 10, 10, 10, 10 };
	int waveMonsterCount[4] = {};
	int monsterTypeCount;

	int enemyNum[5] = {};
public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	bool Onhit(FPOINT pos);
	void SetUp(int enemyNum, float posX, float posY);
	void SetPlayerPos(FPOINT _playerPos) { playerPos = _playerPos; }
	void SetWaveCount(int enemyNum, int waveNum);
	bool isWaveTime(float EventTime, int _EnemyNum0, int _EnemyCount0);
	bool isWaveTime(float EventTime, int _EnemyNum0, int _EnemyCount0, int _EnemyNum1, int _EnemyCount1);
	bool isWaveTime(float EventTime, int _EnemyNum0, int _EnemyCount0, int _EnemyNum1, int _EnemyCount1
		, int _EnemyNum2, int _EnemyCount2);
};

