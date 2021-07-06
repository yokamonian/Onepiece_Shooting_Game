#include "NormalEnemy_Shiki.h"
#include "Image.h"
#include "MissileManager.h"
#include "macroFunction.h"
#include "Movement.h"
#include "Battle.h"
#include "Player.h"

HRESULT NormalEnemy_Shiki::Init()
{
	pos.x = WINSIZE_X + 30.0f;
	pos.y = WINSIZE_Y / 2;

	img = ImageMgr::GetSingleton()->AddImage("NormalEnemy_Shiki", "Image/shiki.bmp", 0, 0, 1200, 400, 6, 4, true, RGB(0, 165, 0));
	isAppear = false;
	currFrameX = 0;
	currFrameY = 0;
	maxKeyFrameX = 3;
	elipsedTime = 0;
	isDamaged = false;
	fireCount = 0;
	isRender = true;
	EnemyMissileMgr = new MissileManager();
	EnemyMissileMgr->Init(true);
	myWaveId = -1;
	waveId = 0;


	return S_OK;
}

void NormalEnemy_Shiki::Release()
{
	EnemyMissileMgr->Release(true);
	SAFE_DELETE(EnemyMissileMgr);
}

void NormalEnemy_Shiki::Update()
{
	EnemyMissileMgr->Update();

	if (life > 0)
	{

		if (pos.x > 0 && pos.y < 900)
		{
			frame++;

			if (frame == 1)
			{
				holdX = pos.x;
				holdY = pos.y;
			}

			elipsedTime++;


			if (elipsedTime % 3 == 0)
			{
				currFrameX++;
				elipsedTime = 0;
			}

			if (currFrameX > maxFrameX[myState])
			{
				currFrameX = 0;
			}
			if (myWaveId != waveId)
			{
				switch (waveId)
				{
				case 0:
					break;
				case 1:


					break;
				case 2:
					patterns = PatternManager::GetSingleton()->GetPattern(9);

					break;
				case 3:


					break;
				case 4:


					break;
				case 5:


					break;
				case 6:


					break;
				case 7:



					break;
				case 8:
					patterns = PatternManager::GetSingleton()->GetPattern(10);
					break;
				default:
				{
					patterns.clear();
				}
				break;
				}
			}
			pIdx = -1;
			myWaveId = waveId;
			if (!patterns.empty())
			{
				if (pIdx == -1 || TimeManager::GetSingleton()->GetWorldCount() > endTime)
				{
					pIdx++;
					endTime = -1;
				}
				if (pIdx < patterns.size())
				{
					ActionElement* Action = patterns[pIdx];

					if (endTime == -1)
					{
						endTime = waveTime + Action->duration;
					}

					switch (Action->id)
					{
					case 1:
						N_anglemove(&pos.x, &pos.y, Action->angle, Action->speed);
						break;
					case 2:
						N_circle(&pos.x, &pos.y, Action->angle, &holdX, &holdY);
						break;
					case 3:
						N_poin_point(&pos.x, &pos.y, &Action->GoalX, &Action->GoalY, &holdX, &holdY, Action->duration * 5);
					}
				}

			}

		}
	}

	else if (life <= 0)
	{
		isHit = true;
		elipsedTime++;
		currFrameY = 1;
		currFrameX = 0;
		maxKeyFrameX = 0;
		if (elipsedTime == 8)
		{
			isRender = false;
		}

		/*if (isDamaged == false)
		{

			if (pos.x > 0 && pos.y < 900)
			{
				elipsedTime++;
				fireCount++;
				if (frame == 1)
				{
					holdX = pos.x;
					holdY = pos.y;
				}
				if (CircleCollision(pos.x, pos.y, playerPos.x, playerPos.y))
				{
					currFrameY = 1;
					myState = 1;
				}
				else
				{
					currFrameY = 0;
					myState = 0;
				}

				if (elipsedTime % 3 == 0)
				{
					currFrameX++;
					elipsedTime = 0;
				}

				if (currFrameX > maxFrameX[myState])
				{
					currFrameX = 0;
				}

				if (fireCount % 15 == 14)
				{
					EnemyMissileMgr->SetIsEnemy(true);
					EnemyMissileMgr->Fire(pos.x, pos.y, 180);
				}
				if (myWaveId != waveId)
				{
					switch (waveId)
					{
					case 0:
						break;
					case 1:


						break;
					case 2:


						break;
					case 3:
						patterns = PatternManager::GetSingleton()->GetPattern(5);

						break;
					case 4:


						break;
					case 5:


						break;
					case 6:
						patterns = PatternManager::GetSingleton()->GetPattern(6);

						break;
					case 7:


						break;
					case 8:

						break;
					default:
					{
						patterns.clear();
					}
					break;
					}
				}
				pIdx = -1;
				myWaveId = waveId;
				if (!patterns.empty())
				{
					if (pIdx == -1 || TimeManager::GetSingleton()->GetWorldCount() > endTime)
					{
						pIdx++;
						endTime = -1;
					}
					if (pIdx < patterns.size())
					{
						ActionElement* Action = patterns[pIdx];

						if (endTime == -1)
						{
							endTime = waveTime + Action->duration;
						}

						switch (Action->id)
						{
						case 1:
							N_anglemove(&pos.x, &pos.y, Action->angle, Action->speed);
							break;
						case 2:
							N_circle(&pos.x, &pos.y, Action->angle, &holdX, &holdY);
							break;
						case 3:
							N_poin_point(&pos.x, &pos.y, &Action->GoalX, &Action->GoalY, &holdX, &holdY, Action->duration * 5);
						}
					}
				}
			}
			else if (isDamaged)
			{
				pos.y -= 2.0;
				elipsedTime++;
				currFrameY = 3;
				currFrameX = 0;
				maxKeyFrameX = 2;
				if (elipsedTime == 12)
				{
					isRender = false;
				}
			}
		}*/
	}
}

void NormalEnemy_Shiki::Render(HDC hdc)
{
	if (img)
	{
		if (isRender)
		{
			if (isDamaged == false)
				img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 1.7f);
			else
				img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 1.7f);
		}

	}
	if (EnemyMissileMgr)
	{
		EnemyMissileMgr->Render(hdc);
	}
}

bool NormalEnemy_Shiki::OnHit(FPOINT point)
{

	float length = sqrt(pow(pos.x - point.x, 2) + pow(pos.y - point.y, 2)); // 두개체간의 거리 비교
	if (length < 60)
	{
		isDamaged = true;
		pos.y = -100;
		return true;
	}
	return false;
}

NormalEnemy_Shiki::NormalEnemy_Shiki()
{
}

NormalEnemy_Shiki::~NormalEnemy_Shiki()
{
}


