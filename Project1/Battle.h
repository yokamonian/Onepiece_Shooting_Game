#pragma once
#include "GameNode.h"


class PowerUp;
class Image;
class EnemyManager;
class Player;
class EliteEnemy;
class BossEnemy;
class Battle : public GameNode
{
private:

	//0529변수
	int bg1SourceX;
	int bg2SourceX;
	Image* backgroundImg1;
	Image* backgroundImg2;
	Image* blankHP;
	Image* fillHP;
	Image* eliteBlankHP;
	Image* eliteFillHP;
	Image* bossBlankHP;
	Image* bossFillHP;

	Image* powerUpImage;
	POINT powerUpPos;

	PowerUp* powerUp;

	//0526 변수 
	//Image* backgroundImg;
	int sourceX; //배경을 움직이게 하기 위한 변수.
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

