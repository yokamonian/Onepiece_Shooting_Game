#include "EnemyMissile.h"
#include "Image.h"
#include "Movement.h"

HRESULT EnemyMissile::Init()
{
	pos = { 0, 0 };
	speed = 900.0f;
	currFrameX = 0;
	currFrameY = 0;
	angle = 0.0f;
	radius = 10.0f;
	isFloorCollision = false;
	isAceSecondAttack = false;

	img = ImageMgr::GetSingleton()->AddImage("EnemyMissile", "Image/NormalMissile.bmp", 0, 0, 100, 200, 1, 2, true, RGB(255, 255, 0));
	pattern2Img = ImageMgr::GetSingleton()->AddImage("Pattern3", "Image/aceskill.bmp", 0, 0, 1600, 600, 8, 3, true, RGB(62, 102, 68));
	currFrameX = 0;
	currFrameY = 1;
	elapsedTime = 0;

	return S_OK;
}

void EnemyMissile::Update()
{
	if (isAceSecondAttack == false)
	{
		pos.x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y += speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
	}
	else
	{
		pos.x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
		pos.y -= speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();

		if (isFloorCollision == true)
		{
			elapsedTime++;

			if (elapsedTime % 3 == 0)
			{
				elapsedTime = 0;
				currFrameX++;

				if (currFrameX > 7)
				{
					currFrameX = 0;
					isFloorCollision = false;

				}
			}
		}
	}
}

void EnemyMissile::Release()
{

}

void EnemyMissile::Render(HDC hdc)
{
	if (isAceSecondAttack == false)
	{
		if (img)
		{
			img->FrameRender(hdc, pos.x, pos.y, 0, missileType, 0.5f);
		}
	}
	else
	{
		if (pattern2Img)
		{
			if (isFloorCollision)
			{
				pattern2Img->FrameRender(hdc, effectPos.x, effectPos.y - 40, currFrameX, currFrameY, 2.0f);
			}
			else
			{
				pattern2Img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 1.0f);
			}
		}
	}
}
