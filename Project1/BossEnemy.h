#pragma once
#include "Enemy.h"

class MissileManager;
/// <summary>
/// BossEnemy : 보스 개체의 정보를 가지고 있는 클래스.
/// </summary>
class BossEnemy : public Enemy
{
protected:

	int width, height;							// 너비, 높이
	RECT hitBox;								// 히트 박스
	bool isHit;									// 피격 여부
	int hitOnFrame;								// 다단히트 처리 방지를 위한 카운트
	int frameRate;								// 프레임
	int patternFrame;							// 패턴 프레임
	int pattern2Frame;							// 패턴 프레임2
	int dieFrame;								// 사망 프레임 수

	bool pattern2On;							// 2페이즈 시작 여부
	float angle;


	bool isDieCheck;
	bool isPattern2;							// 보스 패턴 여부
	bool isPattern3;								
	bool isCurrZero;							// 패턴 전환을 위한 bool 변수

	Image* aceImage;
	bool isAppear;
	bool isSleep;
	int randAngle;

	int elipsedTime;
	int maxFrameX[7]{ 3, 5, 7, 5, 9, 7, 4 };
	BossEnemyState bossEnemyState;
	MissileManager* enemyMissile;
	Image* aceSkillImg;
	int skillCurrFrameX, skillCurrFrameY;
	float skillPosX, skillPosY;
	bool skillRend;
	float skillAngle;
	bool checkpoint;
	bool checkPoint2;


	bool bosspettern1;
	bool bosspettern2;
	bool bosspettern3;
	bool bossopen;
	float skillRadius;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void SetIsAppear(bool _isAppear) { isAppear = _isAppear; }

	bool GetIsAppear() { return isAppear; }
	BossEnemyState GetBossEnemyState() {
		return  bossEnemyState;
	}

	bool Onhit(FPOINT pos);

	void SetLife(int _life) { life = _life; }
	int GetLife() { return life; }
	float GetposX() { return pos.x; }

	RECT GetHitBox() { return hitBox; }
	void SetIsHit(bool _isHit) { isHit = _isHit; }
	bool GetIsHit() { return isHit; }
};

