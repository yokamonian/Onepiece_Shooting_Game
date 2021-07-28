#pragma once
#include "Enemy.h"

class MissileManager;
/// <summary>
/// BossEnemy : ���� ��ü�� ������ ������ �ִ� Ŭ����.
/// </summary>
class BossEnemy : public Enemy
{
protected:

	int width, height;							// �ʺ�, ����
	RECT hitBox;								// ��Ʈ �ڽ�
	bool isHit;									// �ǰ� ����
	int hitOnFrame;								// �ٴ���Ʈ ó�� ������ ���� ī��Ʈ
	int frameRate;								// ������
	int patternFrame;							// ���� ������
	int pattern2Frame;							// ���� ������2
	int dieFrame;								// ��� ������ ��

	bool pattern2On;							// 2������ ���� ����
	float angle;


	bool isDieCheck;
	bool isPattern2;							// ���� ���� ����
	bool isPattern3;								
	bool isCurrZero;							// ���� ��ȯ�� ���� bool ����

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

