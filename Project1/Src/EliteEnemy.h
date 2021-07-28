#pragma once
#include "Enemy.h"

class Iamge;
class MissileManager;
/// <summary>
/// EliteEnemy : ���� ���� �����ϴ� �غ����� ������ ������ �ִ� Ŭ����.
/// BossEnemy Ŭ���� �ּ��� ������ ���� ������ �Լ��� ������ ����.
/// </summary>
class EliteEnemy : public Enemy
{
protected:

	int width, height;
	RECT hitBox;
	bool isHit;
	int hitOnFrame;
	bool patternFrameReset;				// PatternFrame�� 0���� �ʱ�ȭ ���ֱ� ���� ����
	int pattern3Frame;
	int dieFrame;
	bool isDieCheck;


	int patternDelay[3]{ 2, 1, 0 };		// ���� ������
	int patternCount[3]{ 4, 0, 0 };		// ���� ī��Ʈ
	int nextPatternFrame;

	bool isForwardRotate;				// ��ȸ�� ��ų�� ���� bool ����

	int motionDelay;					// ��� ������
	bool isMotionDelay;					// ������ ������ ����
	bool pattern3On;
	bool pattern3_OneChance;

	int maxFrameX[4]{ 3, 2, 8, 3 };




	Image* img;
	int elipsedTime;
	bool isAppear;
	int myState;						// �ƽ� ������ x�� �ε����� ����� ����

	float missileAngle;

	MissileManager* enemyMissile;
	EliteEnemyState eliteEnemyState;	// EliteEnemy ���� ����

	int frameRate;

	int fireFrame;						// ���� �̻��� �߻� ������
	int fireDelay;						// ���� �̻��� ������
	int patternFrame;

	float angle;

	bool diecheck;
	bool elitebossopen;

public:

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetIsAppear(bool _isAppear) { isAppear = _isAppear; }

	bool GetIsAppear() { return isAppear; }
	int GetLife() { return life; }
	void SetLife(int _life) { life = _life; }

	EliteEnemyState GetEliteEnemyState() { return  eliteEnemyState; }
	bool Onhit(FPOINT _pos);
	RECT GetHitBox() { return hitBox; }
	void SetIsHit(bool _isHit) { isHit = _isHit; }
	bool GetIsHit() { return isHit; }
	//bool GetIsAppear() { return isAppear; }

};

