#include "Battle.h"
#include "Young_airplane.h"
#include "Jong_airplane.h"
#include "Sung_airplane.h"
#include "Image.h"
#include "EnemyManager.h"
#include "Player.h"
#include "EliteEnemy.h"
#include "BossEnemy.h"
#include "macroFunction.h"
#include "PowerUp.h"

Battle* Battle::instance = 0;

HRESULT Battle::Init(int selectIdx)
{
	instance = this;
	backgroundImg1 = ImageMgr::GetSingleton()->AddImage("backgroundImg1", "Image/onepiecebg2.bmp", WINSIZE_X, WINSIZE_Y);
	//backgroundImg1 = ImageMgr::GetSingleton()->AddImage("backgroundImg1", "Image/Background.bmp", WINSIZE_X, WINSIZE_Y);
	//backgroundImg2 = ImageMgr::GetSingleton()->AddImage("backgroundImg2", "Image/Background2.bmp", 10000, WINSIZE_Y, true, RGB(255, 255, 255));
	blankHP = ImageMgr::GetSingleton()->AddImage("BlankHP", "Image/blankHP.bmp", 306, 46);
	fillHP = ImageMgr::GetSingleton()->AddImage("FillHP", "Image/FillHP.bmp", 300, 40);
	eliteBlankHP = ImageMgr::GetSingleton()->AddImage("bossBlankHp", "Image/bossBlankHp.bmp", 1005, 45, true, RGB(255,255,255));
	eliteFillHP = ImageMgr::GetSingleton()->AddImage("bossFillHp", "Image/bossFillHp.bmp", 1000, 40, true, RGB(255, 255, 255));


	bossBlankHP = ImageMgr::GetSingleton()->AddImage("bossBlankHp", "Image/bossBlankHp.bmp", 1005, 45, true, RGB(255, 255, 255));
	bossFillHP = ImageMgr::GetSingleton()->AddImage("bossFillHp", "Image/bossFillHp.bmp", 1000, 40, true, RGB(255, 255, 255));

	powerUpImage = ImageMgr::GetSingleton()->AddImage("powerUpImage", "Image/bustercall.bmp", 100, 100);
	
	powerUp = new PowerUp();
	powerUp->Init();
	powerUp->SetCenter({WINSIZE_X/2, WINSIZE_Y/2});

	powerUpPos = { -500, -500 };

	bg1SourceX = 0;
	bg2SourceX = 0;
	playerGage = 100;

	charNum = selectIdx;
	sourceX = 0;

	enemyMgr = new EnemyManager();
	enemyMgr->Init();

	eliteEnemy = new EliteEnemy();
	bossEnemy = new BossEnemy();
	eliteEnemy->Init();
	bossEnemy->Init();

	player = new Player();
	player->Init(charNum);
	return S_OK;
}

void Battle::Update()
{
	player->Update();

	//WINSIZE_X까지 갔을 경우, 0으로 설정.
	bg1SourceX += 1;
	bg2SourceX += 5;

	if (bg1SourceX > WINSIZE_X)
	{
		bg1SourceX = 0;
	}

	if (enemyMgr)
	{
		enemyMgr->SetPlayerPos(player->GetPlayerPos());
		enemyMgr->Update();
	}

	if ( eliteEnemy && (TimeManager::GetSingleton()->GetWorldCount() > 20.0f) &&  eliteEnemy->GetIsAppear())
	{
		eliteEnemy->Update();
	}

	if ( bossEnemy && (eliteEnemy->GetIsAppear() == false) && bossEnemy->GetIsAppear())
	{
		bossEnemy->Update();
	}

	//엘리트 에너미 체력 다는 코드
	if ((TimeManager::GetSingleton()->GetWorldCount() > 5.0f) && (eliteEnemy->GetEliteEnemyState() != EliteEnemyState::DIE))
	{
		if (eliteEnemy)
		{
			eliteEnemy->SetIsAppear(true);
			//플레이어의 스킬을 사용했을 때 엘리트 에너미와 맞았는지를 체크하는 코드
			if ( (player->GetSkillOn() == true) && (eliteEnemy->GetIsHit() == false) && (eliteEnemy->GetPos().x + 100 <= WINSIZE_X)
				
				&& RectCollision(eliteEnemy->GetHitBox(), player->GetSkillRect())  )
			{
				eliteEnemy->SetIsHit(true);
				eliteEnemy->SetLife(eliteEnemy->GetLife() - 200);
			}
		}
	}

	//에이스 체력 다는 코드
	if ((TimeManager::GetSingleton()->GetWorldCount() > 5.0f) &&
		(eliteEnemy->GetEliteEnemyState() == EliteEnemyState::DIE) && (bossEnemy->GetBossEnemyState() != BossEnemyState::DIE) )
	{
		if (bossEnemy)
		{
			bossEnemy->SetIsAppear(true);
			//bossEnemy->Update();

			//플레이어의 스킬을 사용했을 때 보스에너미와 맞았는지를 체크하는 코드
			if ((player->GetSkillOn() == true) && (bossEnemy->GetIsHit() == false) && (bossEnemy->GetPos().x + 100 <= WINSIZE_X) &&
				RectCollision(bossEnemy->GetHitBox(), player->GetSkillRect()))
			{
				bossEnemy->SetIsHit(true);
				bossEnemy->SetLife(bossEnemy->GetLife() - 200);
			}
		}
	}

	if (powerUp)
	{
		powerUp->Update();
	}

	if (CircleCollision(player->GetPos().x, player->GetPos().y, powerUp->GetCenter().x, powerUp->GetCenter().y))
	{
		powerUp->SetIsCollision(true);
		player->PowerUp();
	}

}

void Battle::Release()
{
	if (bossEnemy)
	{
		bossEnemy->Release();
		SAFE_DELETE(bossEnemy);
	}

	if (eliteEnemy)
	{
		eliteEnemy->Release();
		SAFE_DELETE(eliteEnemy);
	}

	if (enemyMgr)
	{
		enemyMgr->Release();
		SAFE_DELETE(enemyMgr);
	}

	if (powerUp)
	{
		powerUp->Release();
		SAFE_DELETE(powerUp);
	}

	if (player)
	{
		player->Release();
		SAFE_DELETE(player);
	}
}

void Battle::Render(HDC hdc)
{
	if (backgroundImg1)
	{
		backgroundImg1->Render(hdc, 0, 0, bg1SourceX, 0);
	}

	if (backgroundImg2)
	{
		//backgroundImg2->BGRender(hdc, 0, 0, bg2SourceX, 0);
	}

	if (enemyMgr)
	{
		enemyMgr->Render(hdc);
	}

	if (eliteEnemy)
	{
		eliteEnemy->Render(hdc);
	}

	if (bossEnemy)
	{
		bossEnemy->Render(hdc);
	}

	if (powerUp)
	{
		powerUp->Render(hdc);
	}

	if (player)
	{
		player->Render(hdc);
	}



	//eliteHP
	if ( (eliteEnemy->GetIsAppear() == true) && (eliteEnemy->GetPos().x <= WINSIZE_X / 2 + 400))
	{
		if (eliteBlankHP)
		{
			eliteBlankHP->BlankRender(hdc, 100, 30);
		}

		if (eliteFillHP)
		{
			eliteFillHP->GageRender(hdc, 104, 32, eliteEnemy->GetLife());
		}

	}//bossHP
	else if ((bossEnemy->GetLife() > 0) && (eliteEnemy->GetLife() <= 0) && (bossEnemy->GetposX() <= WINSIZE_X / 2 + 400))
	{
		if (bossBlankHP)
		{
			bossBlankHP->BlankRender(hdc, 100, 30);
		}

		if (bossFillHP)
		{
			bossFillHP->GageRender(hdc, 104, 32, bossEnemy->GetLife());
		}
	}


	//PlayerGage
	if (blankHP)
	{
		blankHP->Render(hdc, 50, 800);/* 여기에 hp바 값 구현. */
	}

	if (fillHP)
	{
		fillHP->GageRender(hdc, 54, 804, player->GetGage());
	}
}

FPOINT Battle::GetPlayerPos()
{
	return player->GetPos();
}
