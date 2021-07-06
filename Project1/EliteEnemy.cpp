#include "EliteEnemy.h"
#include "Image.h"
#include "MissileManager.h"
#include "macroFunction.h"

HRESULT EliteEnemy::Init()
{
	img = ImageMgr::GetSingleton()->AddImage("Whitebeard", "Image/Whitebeard.bmp", 0, 0, 2600, 750, 13, 5, true, RGB(117, 126, 243));

	pos.x = WINSIZE_X + 200;
	pos.y = WINSIZE_Y / 2;

	isDieCheck = false;
	pattern3_OneChance = false;
	width = 100;
	height = 200;
	isHit = false;
	hitOnFrame = 0;
	dieFrame = 0;

	currFrameX = 0;
	currFrameY = 0;

	elipsedTime = 0;
	missileAngle = 0;

	eliteEnemyState = EliteEnemyState::IDLE;

	enemyMissile = new MissileManager();
	enemyMissile->Init(true);
	patternFrameReset = false;

	//isCircle = false;
	speed = 10.0f;
	life = 1000;
	isAppear = true;
	frameRate = 0;
	upState = false;
	downState = false;
	angle = 180;
	patternFrame = 0;
	motionDelay = 0;
	isMotionDelay = false;
	isForwardRotate = true;
	//pattern3Count = 0;
	pattern3On = false;

	fireFrame = 0;
	fireDelay = 1;

	diecheck = false;
	elitebossopen = false;
	return S_OK;
}

void EliteEnemy::Release()
{
	enemyMissile->Release();
	SAFE_DELETE(enemyMissile);
}

void EliteEnemy::Update()
{
	if (isAppear)
	{
		if (elitebossopen == false)
		{
			SoundManager::GetSingleton()->Stop("BG");
			SoundManager::GetSingleton()->Play("whiteopen", 0.5f);
			elitebossopen = true;
		}
		elipsedTime++;

		if (isHit == true)
		{
			hitOnFrame++;
		}

		if (hitOnFrame > 45)
		{
			hitOnFrame = 0;
			isHit = false;
		}

#pragma region pattern3Fire;
		if (pattern3On)
		{
			patternFrame++;
		}

		if (pattern3On && (patternFrame == 15))
		{
			for (int i = 0; i < 12; i++)
			{
				enemyMissile->Fire(i * 100, 0, angle);
			}
		}

		if (pattern3On && (patternFrame == 30))
		{
			for (int i = 0; i < 12; i++)
			{
				enemyMissile->Fire(i * 100 + 50, 0, angle);
			}

			patternFrame = 0;
		}
#pragma endregion

		if (life <= 0)
		{
			eliteEnemyState = EliteEnemyState::DIE;
			if (isDieCheck == false)
			{
				isDieCheck = true;
				currFrameX = 1;
			}
		}
		else if (life <= 1500 / 2)
		{
			if (patternFrameReset == false)
			{
				patternFrameReset = true;
				patternFrame = 0;
			}

			if (pattern3_OneChance == false)
			{
				currFrameY = 2;
				currFrameX = 0;
				eliteEnemyState = EliteEnemyState::PATTERN3;
				pattern3_OneChance = true;
			}
		}
		else if (eliteEnemyState == EliteEnemyState::IDLE)
		{
			frameRate++; //상태 변화를 주기 위한 프레임 변수.

			if (frameRate >= 120) //처음에 등장하고 120프레임이 지나면(4초) Pattern1상태로 변화.
			{
				frameRate = 0;
				currFrameY = 1;
				upState = true;
				eliteEnemyState = EliteEnemyState::PATTERN1;
			}
		}

		if (pos.x > WINSIZE_X / 2 + 400)
		{
			pos.x -= speed;
		}

		hitBox = { (int)pos.x - width / 2, (int)pos.y - height / 2 + 70, (int)pos.x + width / 2, (int)pos.y + height / 2 + 70 };
		enemyMissile->SetEliteRect(hitBox); // 엘리트 몬스터의 Rect설정.


		switch (eliteEnemyState)
		{
		case EliteEnemyState::IDLE:

			if (elipsedTime % 4 == 0)
			{
				currFrameX++;
				elipsedTime = 0;
			}

			if (currFrameX > maxFrameX[currFrameY])
			{
				currFrameX = 0;
			}

			break;


		case EliteEnemyState::PATTERN1:

			fireFrame++;
			enemyMissile->SetIsEnemy(true);
			enemyMissile->SetSpeed(900);

			// angle값을 변화해주는 코드
			if (isMotionDelay == false)
			{
				patternFrame++;

				if (patternFrame <= 15)
				{
					angle += 2;
					if (patternFrame == 15)
					{
						isMotionDelay = true;
					}
				}
				else
				{
					angle -= 2;

					if (patternFrame == 30)
					{
						patternFrame = 0;
						isMotionDelay = true;
					}
				}
			}

			// Fire 딜레이를 주는 코드
			if (fireFrame > patternDelay[(int)EliteEnemyState::PATTERN1])
			{
				if (isMotionDelay)
				{
					motionDelay++;

					if (motionDelay > 5)
					{
						motionDelay = 0;
						isMotionDelay = false;
						nextPatternFrame++;

						if (nextPatternFrame >= patternCount[0]) //패턴 카운트의 0번 횟수 보다 크거나 같으면 
						{
							nextPatternFrame = 0;
							eliteEnemyState = EliteEnemyState::PATTERN2;
						}
					}
				}
				else
				{
					fireFrame = 0;

					enemyMissile->Fire(pos.x - 75, pos.y + 5, angle - 80);
					enemyMissile->Fire(pos.x - 75, pos.y + 5, angle - 40);
					enemyMissile->Fire(pos.x - 75, pos.y + 5, angle);
					enemyMissile->Fire(pos.x - 75, pos.y + 5, angle + 40);
					enemyMissile->Fire(pos.x - 75, pos.y + 5, angle + 80);
				}
			}

			if (elipsedTime % 3 == 0)
			{
				currFrameX++;
				elipsedTime = 0;
			}

			if (currFrameX > maxFrameX[currFrameY])
			{
				currFrameX = maxFrameX[currFrameY];
			}

			break;

		case EliteEnemyState::PATTERN2:

#pragma region Pattern2

			fireFrame++;
			patternFrame++;
			enemyMissile->SetIsEnemy(true);
			enemyMissile->SetSpeed(900);

			if (isForwardRotate && patternFrame >= 150) //5초가 지나면 역회전으로 미사일을 날린다.
			{
				patternFrame = 0;
				fireFrame = 0;
				frameRate = 0;

				isForwardRotate = false;
			}

			if (!isForwardRotate && patternFrame >= 150) //5초가 지나면, Idle상태로 간다.
			{
				patternFrame = 0;
				fireFrame = 0;
				angle = 180;
				frameRate = 0;
				isForwardRotate = true;

				eliteEnemyState = EliteEnemyState::IDLE;

				currFrameX = 0;
				currFrameY = 0;
			}

			if (isForwardRotate)
			{
				angle += 2;
			}
			else
			{
				angle -= 2;
			}

			if (fireFrame > fireDelay)
			{
				fireFrame = 0;

				enemyMissile->Fire(pos.x - 75, pos.y + 5, angle);
				enemyMissile->Fire(pos.x - 75, pos.y + 5, angle + 90);
				enemyMissile->Fire(pos.x - 75, pos.y + 5, angle + 180);
				enemyMissile->Fire(pos.x - 75, pos.y + 5, angle + 270);
			}

			if (elipsedTime % 3 == 0)
			{
				currFrameX++;
				elipsedTime = 0;
			}

			if (currFrameX > maxFrameX[currFrameY])
			{
				currFrameX = maxFrameX[currFrameY];
			}

#pragma endregion

			break;

		case EliteEnemyState::PATTERN3:

			angle = 90;
			enemyMissile->SetIsEnemy(true);
			enemyMissile->SetSpeed(900 / 2);

			if (currFrameX == 7)
			{
				if (elipsedTime % 10 == 0)
				{
					currFrameX++;
					elipsedTime = 0;
				}
			}
			else
			{
				if (elipsedTime % 5 == 0)
				{
					currFrameX++;
					elipsedTime = 0;
				}
			}

			if (currFrameX > maxFrameX[currFrameY])
			{
				currFrameX = 0;
				pattern3On = true;
				pattern3_OneChance = true;
				currFrameY = 0;
				eliteEnemyState = EliteEnemyState::IDLE;
			}

			break;

		case EliteEnemyState::DIE:
			if (diecheck == false)
			{
				SoundManager::GetSingleton()->Play("WhiteMan");
				diecheck = true;
			}
			currFrameY = 4;
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

			if (dieFrame >= 70)
			{
				isAppear = false;
			}

			break;
		}

		if (enemyMissile && (eliteEnemyState != EliteEnemyState::DIE))
		{
			enemyMissile->Update();
		}
	}
}

void EliteEnemy::Render(HDC hdc)
{
	if (enemyMissile && (eliteEnemyState != EliteEnemyState::DIE))
	{
		enemyMissile->Render(hdc);
	}

	if (img && (isAppear == true))
	{
		//Rectangle(hdc, hitBox.left, hitBox.top, hitBox.right, hitBox.bottom);
		img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 2.5f);
	}
}

bool EliteEnemy::Onhit(FPOINT _pos)
{
	float length = sqrt(pow(_pos.x - pos.x, 2) + pow(_pos.y - pos.y, 2)); // 두개체간의 거리 비교
	if (length < 60)
	{
		return true;
	}
	return false;
}
