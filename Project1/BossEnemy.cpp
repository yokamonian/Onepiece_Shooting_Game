#include "BossEnemy.h"
#include "Image.h"
#include "MissileManager.h"
#include "macroFunction.h"
#include "Battle.h"
#include "Player.h"

HRESULT BossEnemy::Init()
{
	aceImage = ImageMgr::GetSingleton()->AddImage("BossEnemy", "Image/ace.bmp", 0, 0, 2000, 700, 10, 7, true, RGB(62, 102, 68));
	aceSkillImg = ImageMgr::GetSingleton()->AddImage("Pattern3", "Image/aceskill.bmp", 0, 0, 1600, 600, 8, 3, true, RGB(62, 102, 68));

	pos = { WINSIZE_X + 400, WINSIZE_Y / 2 };
	speed = 10.0f;
	life = 1000;
	isPattern3 = false;
	isDieCheck = false;
	isCurrZero = false;
	checkPoint2 = false;

	angle = 0;

	isHit = false;
	frameRate = 0;
	dieFrame = 0;
	isAppear = false;
	pattern2On = false;
	pattern2Frame = 0;
	patternFrame = 0;

	currFrameX = 0;
	skillCurrFrameX = 0;
	skillCurrFrameY = 0;
	skillPosX = pos.x;
	skillPosY = pos.y - 100.0f;
	skillRend = false;
	skillAngle = DEGREE_TO_RADIAN(225.0f);
	checkpoint = false;

	width = 100;
	height = 240;


	skillRadius = 55.0f;

	bossEnemyState = BossEnemyState::IDLE;

	enemyMissile = new MissileManager();
	enemyMissile->Init(true);

	randAngle = 0;

	elipsedTime = 0;
	isSleep = false;

	bosspettern1 = false;
	bosspettern2 = false;
	bosspettern3 = false;
	bossopen = false;
	return S_OK;
}

void BossEnemy::Release()
{
	enemyMissile->Release();
	SAFE_DELETE(enemyMissile);
}

void BossEnemy::Update()
{
	if (isAppear)
	{
		if (bossopen == false)
		{
			SoundManager::GetSingleton()->Stop("whiteopen");
			SoundManager::GetSingleton()->Play("aceopen", 0.5f);
			bossopen = true;
		}
		elipsedTime++;

		//보스가 플레이어의 필살기에 여러 프레임동안 맞지 않게 하기 위해 처리.
		if (isHit == true)
		{
			hitOnFrame++;
		}

		if (hitOnFrame > 40)
		{
			hitOnFrame = 0;
			isHit = false;
		}
		//

#pragma region pattern2Fire;
		if (pattern2On)
		{
			patternFrame++;
			pattern2Frame++;
		}

		if (pattern2On && (patternFrame == 15))
		{
			for (int i = 0; i < 12; i++)
			{
				enemyMissile->SetIsAceSecondAttack(true);
				enemyMissile->SetSpeed(900 / 2);
				enemyMissile->SetIsBoss(true);
				enemyMissile->Fire(i * 150 - 150, -20, -70);
			}
		}

		if (pattern2On && (patternFrame == 30))
		{
			for (int i = 0; i < 13; i++)
			{
				enemyMissile->SetIsAceSecondAttack(true);
				enemyMissile->SetSpeed(900 / 2);
				enemyMissile->SetIsBoss(true);
				enemyMissile->Fire(i * 150 - 100, -20, -70);
			}

			patternFrame = 0;
		}
#pragma endregion
		if (pattern2On && (pattern2Frame > 200))
		{
			pattern2On = false;
			checkPoint2 = true;
			pattern2Frame = 0;
		}


		if (life <= 0)
		{
			bossEnemyState = BossEnemyState::DIE;
			if (isDieCheck == false)
			{
				isDieCheck = true;
				currFrameX = 0;
			}
		}
		else if (life < 800 && life > 500)
		{
			if ((isPattern3 == false) && (pos.x <= WINSIZE_X / 2 + 450))
			{
				bossEnemyState = BossEnemyState::PATTERN3;
				if (checkpoint == false)
				{
					skillPosX = pos.x;
					checkpoint = true;
				}
			}
			else
			{
				bossEnemyState = BossEnemyState::PATTERN1;
			}
		}
		else if (life <= 500)
		{
			if (isCurrZero == false)
			{
				currFrameX = 0;
				isCurrZero = true;
			}

			if ((checkPoint2 == false))
			{
				bossEnemyState = BossEnemyState::PATTERN2;
			}
			else
			{
				if (bossEnemyState == BossEnemyState::PATTERN2)
					bossEnemyState = BossEnemyState::IDLE;

				frameRate++; //상태 변화를 주기 위한 프레임 변수.

				if (frameRate >= 120) //처음에 등장하고 120프레임이 지나면(4초) Pattern1상태로 변화.
				{
					frameRate = 0;
					bossEnemyState = BossEnemyState::PATTERN1;
				}
			}

		}
		else if (bossEnemyState == BossEnemyState::IDLE)
		{
			if (pos.x <= WINSIZE_X)
			{
				frameRate++; //상태 변화를 주기 위한 프레임 변수.

				if (frameRate >= 120) //처음에 등장하고 120프레임이 지나면(4초) Pattern1상태로 변화.
				{
					frameRate = 0;
					bossEnemyState = BossEnemyState::PATTERN1;
				}
			}
		}

		if (pos.x > WINSIZE_X / 2 + 400)
		{
			pos.x -= 3;
		}

		if (life <= 0)
		{
			bossEnemyState = BossEnemyState::DIE;
		}

		if (skillRend == true)
		{
			if (elipsedTime % 2 == 0)
			{
				skillCurrFrameX++;

				if (skillCurrFrameX > 7)
				{
					skillCurrFrameX = 4;
				}
			}

			skillPosX += 15.0f * cosf(skillAngle);
			skillPosY -= 15.0f * sinf(skillAngle);

			if ((skillPosY - skillRadius * 2 <= 0) ||
				(skillPosY + skillRadius * 2 >= WINSIZE_Y))
			{
				skillAngle = PI * 2 - skillAngle;
			}

			if ((skillPosX + skillRadius * 2 >= WINSIZE_X) ||
				(skillPosX - skillRadius * 2 <= 0))
			{
				skillAngle = PI - skillAngle;
			}

			if (sqrt(pow(skillPosX - Battle::instance->GetPlayerPos().x, 2) +
				pow(skillPosY - Battle::instance->GetPlayerPos().y, 2)) < 150)
			{
				Battle::instance->GetPlayer()->SetLife(0);
			}
		}

		hitBox = { (int)pos.x - width / 2, (int)pos.y - height / 2 + 70, (int)pos.x + width / 2, (int)pos.y + height / 2 };
		enemyMissile->SetBossRect(hitBox); // 엘리트 몬스터의 Rect설정.

		switch (bossEnemyState)
		{
		case BossEnemyState::IDLE:
			currFrameY = 0;

			if (elipsedTime % 5 == 0)
			{
				currFrameX++;
				elipsedTime = 0;

				if (currFrameX > maxFrameX[currFrameY])
				{
					currFrameX = 0;
					if (isSleep == true)
					{
						bossEnemyState = BossEnemyState::PATTERN4;
					}
				}
			}

			break;

		case BossEnemyState::PATTERN1:
			if (bosspettern1 == false)
			{
				SoundManager::GetSingleton()->Play("AceP1", 0.5f);
				bosspettern1 = true;
			}
			enemyMissile->SetIsEnemy(true);
			enemyMissile->SetSpeed(900);

			currFrameY = 1;

			if (currFrameX >= 0 && currFrameX <= 1)
			{
				if (elipsedTime % 20 == 0)
				{
					currFrameX++;
					elipsedTime = 0;
				}
			}
			else if (currFrameX <= 5)
			{
				if (elipsedTime % 5 == 0)
				{
					enemyMissile->SetIsBoss(true);

					for (int i = 0; i < 10; i++)
					{
						randAngle = rand() % 120 + 120;
						enemyMissile->SetIsAceSecondAttack(false);
						enemyMissile->SetSpeed(900);
						enemyMissile->Fire(pos.x - 30, pos.y, randAngle);
					}

					currFrameX++;
					elipsedTime = 0;
				}

				if (currFrameX >= maxFrameX[currFrameY])
				{
					currFrameX = 0;
					currFrameY = 0;
					bossEnemyState = BossEnemyState::PATTERN1;
				}
			}

			break;

		case BossEnemyState::GUARD:

			currFrameY = 2;

			if (elipsedTime % 5 == 0)
			{
				currFrameX++;
				elipsedTime = 0;

				if (currFrameX > maxFrameX[currFrameY]) // 2~3일때는 탄 막게
				{
					currFrameX = 0;
				}
			}

			break;

		case BossEnemyState::PATTERN2: //비내리기

			currFrameY = 3;

			if (bosspettern2 == false)
			{
				SoundManager::GetSingleton()->Play("AceP2");
				bosspettern2 = true;
			}

			if (currFrameX < 3)
			{
				if (elipsedTime % 20 == 0)
				{
					currFrameX++;
					elipsedTime = 0;
				}
			}
			else if (elipsedTime % 5 == 0)
			{
				currFrameX++;
				elipsedTime = 0;

				if (currFrameX > maxFrameX[currFrameY])
				{
					pattern2On = true;
					currFrameX = maxFrameX[currFrameY];
				}
			}

			break;

		case BossEnemyState::PATTERN3:

			currFrameY = 4;
			if (bosspettern3 == false)
			{
				SoundManager::GetSingleton()->Play("AceP3");
				bosspettern3 = true;
			}
			if (currFrameX >= 0 && currFrameX <= 1)
			{
				if (elipsedTime % 12 == 0)
				{
					skillCurrFrameX++;

					if (skillCurrFrameX >= 3)
					{
						skillPosY -= 50;
					}
				}

				if (elipsedTime % 30 == 0)
				{
					elipsedTime = 0;
					currFrameX++;
				}
			}
			else if (currFrameX >= 2 && currFrameX < maxFrameX[currFrameY])
			{
				if (elipsedTime % 3 == 0)
				{
					skillCurrFrameX++;

					if (skillCurrFrameX == 8)
					{
						skillCurrFrameX = 5;
					}
				}

				if (elipsedTime % 5 == 0)
				{
					elipsedTime = 0;
					currFrameX++;
				}
			}
			else
			{
				skillCurrFrameX = 7;

				if (elipsedTime % 30 == 0)
				{
					elipsedTime = 0;
					currFrameX++;
				}

				if (currFrameX == maxFrameX[currFrameY])
				{
					skillRend = true;
				}

				if (currFrameX > maxFrameX[currFrameY])
				{
					currFrameX = 0;
					currFrameY = 0;
					elipsedTime = 0;
					bossEnemyState = BossEnemyState::IDLE;
					isPattern3 = true;
				}
			}
			break;

		case BossEnemyState::DIE:
			currFrameY = 6;
			dieFrame++;

			if (elipsedTime % 10 == 0)
			{
				currFrameX++;
				elipsedTime = 0;
			}

			if (currFrameX > maxFrameX[currFrameY])
			{
				currFrameX = maxFrameX[currFrameY];
			}

			if (dieFrame >= 100)
			{
				isAppear = false;
			}

			break;
		}

		if (enemyMissile && (bossEnemyState != BossEnemyState::DIE))
		{
			enemyMissile->Update();
		}
	}
}

void BossEnemy::Render(HDC hdc)
{
	if (aceImage && isAppear == true)
	{
		//Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
		aceImage->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 2.5f);
	}

	if (aceSkillImg && (bossEnemyState != BossEnemyState::DIE))
	{
		aceSkillImg->FrameRender(hdc, skillPosX, skillPosY, skillCurrFrameX, skillCurrFrameY, 2.0f);
	}

	if (enemyMissile && (bossEnemyState != BossEnemyState::DIE))
	{
		enemyMissile->Render(hdc);
	}
}

bool BossEnemy::Onhit(FPOINT _pos)
{
	float length = sqrt(pow(_pos.x - pos.x, 2) + pow(_pos.y - pos.y, 2)); // 두개체간의 거리 비교
	if (length < 60)
	{
		return true;
	}
	return false;
}
