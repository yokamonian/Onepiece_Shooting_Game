#pragma once
#include "pch.h"
#include "Object.h"

class Missile;
class EnemyMissile;
class PlayerMissile;
class MissileManager : public Object
{
	vector<EnemyMissile*> vecEnemyMissiles;
	vector<EnemyMissile*>::iterator itEnemyMissiles;

	vector<PlayerMissile*> vecPlayerMissiles;
	vector<PlayerMissile*>::iterator itPlayerMissiles;

	bool isEnemy;
	stack<PlayerMissile*> StP_Missiles;
	stack<EnemyMissile*> StE_Missiles;

	RECT eliteRect; // 엘리트 몬스터의 Rect범위
	RECT bossRect;  // boss의 Rect범위

	Object*	object;
	float RandAngle;
	bool isBoss{ false };
	bool isAceSecondAttack;


	int charNum;


public:
	virtual HRESULT Init(bool isEnemy = false);
	virtual void Release(bool isEnemy = false);
	virtual void Update();
	virtual void Render(HDC hdc);

	bool Fire(float posX, float posY, float angle);
	void SetObject(Object* object) { object = object; }
	void SetIsEnemy(bool _isEnemy) { isEnemy = _isEnemy; }
	void SetSpeed(float _speed) { speed = _speed; }
	void SetIsBoss(bool _isBoss) { isBoss = _isBoss; }
	void SetCharNum(int _charNum) { charNum = _charNum; }

	void SetEliteRect(RECT _rect) { eliteRect = _rect; }
	void SetBossRect(RECT _rect) { bossRect = _rect; }
	void SetIsAceSecondAttack(bool _isAceSecondAttack) { isAceSecondAttack = _isAceSecondAttack; }


	MissileManager();
	~MissileManager();
};

