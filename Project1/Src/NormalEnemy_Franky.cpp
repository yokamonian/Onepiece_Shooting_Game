#include "NormalEnemy_Franky.h"
#include "Image.h"
#include "MissileManager.h"
#include "macroFunction.h"
#include "Movement.h"
#include "Battle.h"
#include "Player.h"

HRESULT NormalEnemy_Franky::Init()
{
	pos.x = WINSIZE_X + 30.0f;
	pos.y = WINSIZE_Y / 3;

	life = 7;
	img = ImageMgr::GetSingleton()->AddImage("NormalEnemy_Franky", "Image/franky.bmp", 0, 0, 400, 200, 2, 2, true, RGB(50, 104, 87));
	isAppear = false;
	currFrameX = 0;
	currFrameY = 0;
	maxKeyFrameX = 1;
	elipsedTime = 0;
	isDamaged = false;
	fireCount = 0;
	isRender = true;
	EnemyMissileMgr = new MissileManager();
	EnemyMissileMgr->Init(true);
	frame = 0;
	angle = 100.0f;
	waveId = 0;
	myWaveId = -1;




	return S_OK;
}

void NormalEnemy_Franky::Release()
{
	EnemyMissileMgr->Release(true);
	SAFE_DELETE(EnemyMissileMgr);
}

void NormalEnemy_Franky::Update()
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
	}
}

void NormalEnemy_Franky::Render(HDC hdc)
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

bool NormalEnemy_Franky::OnHit(FPOINT point)
{
	if (!isHit)
	{
		float length = sqrt(pow(pos.x - point.x, 2) + pow(pos.y - point.y, 2)); // 두개체간의 거리 비교
		if (length < 60)
		{
			if (life <= 0)
				return false;
			life--;
			return true;
		}
	}

	return false;
}

NormalEnemy_Franky::NormalEnemy_Franky()
{
}

NormalEnemy_Franky::~NormalEnemy_Franky()
{
}


