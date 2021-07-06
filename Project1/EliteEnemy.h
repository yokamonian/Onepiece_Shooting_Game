#pragma once
#include "Enemy.h"

class Iamge;
class MissileManager;
class EliteEnemy : public Enemy
{
protected:

	//0601
	int width, height;
	RECT hitBox;
	bool isHit;
	int hitOnFrame;
	bool patternFrameReset; //PatternFrame�� 0���� �ʱ�ȭ ���ֱ� ���� ����
	int pattern3Frame;
	int dieFrame;
	bool isDieCheck;


	int patternDelay[3]{ 2, 1, 0 };
	int patternCount[3]{ 4, 0, 0 }; ////////////
	int nextPatternFrame;

	bool isForwardRotate;

	int motionDelay;
	bool isMotionDelay;
	//int pattern3Count; //�Ѿ��� ������ Ƚ��
	bool pattern3On;
	bool pattern3_OneChance;

	//0527 ���� �߰�
	int maxFrameX[4]{ 3, 2, 8, 3 };
	//int patternFrame[3]{ 120,  };
	//bool isCircle;



	Image* img;
	int elipsedTime;
	bool isAppear;
	int myState; //�ƽ� ������ x�� �ε����� ����� ����

	float missileAngle;

	MissileManager* enemyMissile;
	EliteEnemyState eliteEnemyState;

	bool upState;
	bool downState;
	int frameRate;

	int fireFrame;
	int fireDelay;
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

