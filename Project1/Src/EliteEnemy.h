#pragma once
#include "Enemy.h"

class Iamge;
class MissileManager;
/// <summary>
/// EliteEnemy : 보스 전에 등장하는 준보스의 정보를 가지고 있는 클래스.
/// BossEnemy 클래스 주석과 동일한 명의 변수나 함수는 설명을 생략.
/// </summary>
class EliteEnemy : public Enemy
{
protected:

	int width, height;
	RECT hitBox;
	bool isHit;
	int hitOnFrame;
	bool patternFrameReset;				// PatternFrame을 0으로 초기화 해주기 위한 변수
	int pattern3Frame;
	int dieFrame;
	bool isDieCheck;


	int patternDelay[3]{ 2, 1, 0 };		// 패턴 딜레이
	int patternCount[3]{ 4, 0, 0 };		// 패턴 카운트
	int nextPatternFrame;

	bool isForwardRotate;				// 역회전 스킬을 위한 bool 변수

	int motionDelay;					// 모션 딜레이
	bool isMotionDelay;					// 딜레이 중인지 여부
	bool pattern3On;
	bool pattern3_OneChance;

	int maxFrameX[4]{ 3, 2, 8, 3 };




	Image* img;
	int elipsedTime;
	bool isAppear;
	int myState;						// 맥스 프레임 x의 인덱스를 담당할 변수

	float missileAngle;

	MissileManager* enemyMissile;
	EliteEnemyState eliteEnemyState;	// EliteEnemy 상태 정보

	int frameRate;

	int fireFrame;						// 패턴 미사일 발사 프레임
	int fireDelay;						// 패턴 미사일 딜레이
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

