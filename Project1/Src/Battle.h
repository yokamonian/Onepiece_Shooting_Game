#pragma once
#include "GameNode.h"


class PowerUp;
class Image;
class EnemyManager;
class Player;
class EliteEnemy;
class BossEnemy;
/// <summary>
/// Battle : �÷��� �� Ŭ����
/// </summary>
class Battle : public GameNode
{
private:

	Image* backgroundImg1;		// 1P ��׶��� �̹���
	Image* backgroundImg2;		// 2P ��׶��� �̹��� 
	Image* blankHP;				// �Ҹ�� HP �̹���
	Image* fillHP;				// Ǯ HP �̹���
	Image* eliteBlankHP;
	Image* eliteFillHP;
	Image* bossBlankHP;
	Image* bossFillHP;

	Image* powerUpImage;		// �Ŀ��� �̹���
	POINT powerUpPos;			// �Ŀ��� ������ ��ġ��

	PowerUp* powerUp;

	//Image* backgroundImg;
	int sourceX;				// ����� �����̰� �ϱ� ���� ����.
	int bg1SourceX;				// 1P �̹��� �ҽ� X
	int bg2SourceX;				// 2P �̹��� �ҽ� X
	
	Player* player;
	int playerGage;

	int charNum;
	
	EnemyManager* enemyMgr;
	EliteEnemy* eliteEnemy;
	BossEnemy* bossEnemy;
	

public:
	virtual HRESULT Init(int selectIdx);
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);

	void SetCharNum(int _charNum) { charNum = _charNum; }
	static Battle* instance;
	EnemyManager* GetEnemyMgr() { return enemyMgr; }
	int GetCharNum() { return charNum; }
	FPOINT GetPlayerPos();
	Player* GetPlayer() { return player; }
	BossEnemy* GetBossEnemy() { return bossEnemy; }
	EliteEnemy* GetEliteEnemy() { return eliteEnemy; }

};

