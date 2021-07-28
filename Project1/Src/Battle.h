#pragma once
#include "GameNode.h"


class PowerUp;
class Image;
class EnemyManager;
class Player;
class EliteEnemy;
class BossEnemy;
/// <summary>
/// Battle : 플레이 씬 클래스
/// </summary>
class Battle : public GameNode
{
private:

	Image* backgroundImg1;		// 1P 백그라운드 이미지
	Image* backgroundImg2;		// 2P 백그라운드 이미지 
	Image* blankHP;				// 소모된 HP 이미지
	Image* fillHP;				// 풀 HP 이미지
	Image* eliteBlankHP;
	Image* eliteFillHP;
	Image* bossBlankHP;
	Image* bossFillHP;

	Image* powerUpImage;		// 파워업 이미지
	POINT powerUpPos;			// 파워업 아이템 위치값

	PowerUp* powerUp;

	//Image* backgroundImg;
	int sourceX;				// 배경을 움직이게 하기 위한 변수.
	int bg1SourceX;				// 1P 이미지 소스 X
	int bg2SourceX;				// 2P 이미지 소스 X
	
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

