#include "Young_airplane.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Young_airplane::Init()
{
	speed = 10.0f;
	pos = { 50, WINSIZE_Y / 2 };
	//pos = {0, 0};
	currFrameX = 0;
	currFrameY = 0;
	radius = 0;
	life = 1;
	img = ImageMgr::GetSingleton()->AddImage("Aokiji_Idle", "Image/aokiji.bmp", 0, 0, 2400, 400, 12, 4, true, RGB(86, 102, 88));
	skillImage = ImageMgr::GetSingleton()->AddImage("aokiji_skill", "Image/aokiji_skill.bmp", 0, 0, 812, 104, 7, 1, true, RGB(86, 102, 88));
	skillCurrFrameX = 0;

	checkpoint = false;
	skillPos = { -500, -500 };
	skillOn = false;

	isAvoid = false;

	elipsedTime = 0;
	fireFrame = 0;
	fireDelay = 3;
	playerState = PlayerState::IDLE;
	avoidGage = 0;
	power = 1;
	missileAngle = 0;

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetObject(this);

	shootcount = 0;
	aokskillcheck = false;
	aokavoid = false;
	return S_OK;
}

void Young_airplane::Release()
{

}

void Young_airplane::Update()
{
	if (life == 1)
	{
		if (isAvoid == false)
		{
			avoidGage++;
			if (avoidGage >= 300) avoidGage = 300;
		}

		if (skillOn == true)
		{
			if (elipsedTime % 3 == 0)
			{
				skillCurrFrameX++;

				if (skillCurrFrameX > 2)
				{
					skillCurrFrameX = 2;
				}
			}

			if (checkpoint == false)
			{
				skillPos.x = pos.x;
				skillPos.y = pos.y;
				checkpoint = true;
			}

			skillPos.x += 30.0f * cosf(0);
			skillPos.y -= 30.0f * sinf(0);

			if (skillPos.x - 200 >= WINSIZE_X + 100)
			{
				checkpoint = false;
				skillOn = false;
				skillCurrFrameX = 0;
			}

			skillRect = { skillPos.x - 200, skillPos.y - 200, skillPos.x + 300, skillPos.y + 200 };
		}

		elipsedTime++;
		fireFrame++;

		if ((isAvoid == false) && (playerState == PlayerState::IDLE || playerState == PlayerState::BACK))
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
			{
				playerState = PlayerState::IDLE;
				if (pos.x + 30 <= WINSIZE_X - 20)
					pos.x += speed;
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
			{
				playerState = PlayerState::BACK;
				if (pos.x - 30 >= 0)
					pos.x -= speed;
			}

			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
			{
				playerState = PlayerState::IDLE;
				if (pos.y - 50 >= 10)
					pos.y -= speed;
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
			{
				playerState = PlayerState::IDLE;
				if (pos.y + 50 <= WINSIZE_Y)
					pos.y += speed;
			}

			if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT))
			{
				playerState = PlayerState::IDLE;
			}
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown('Z') && (isAvoid == false))
		{
			shootcount++;
			if (shootcount >= 10)
			{
				SoundManager::GetSingleton()->Play("AokShoot");
				shootcount = 0;
			}
			if (fireFrame > fireDelay)
			{
				fireFrame = 0;

				missileMgr->SetCharNum(0);

				playerState = PlayerState::IDLE;
				currFrameY = 0;

				switch (power)
				{
				case 1:
					missileMgr->Fire(pos.x, pos.y, missileAngle);
					break;

				case 2:
					missileMgr->Fire(pos.x, pos.y, missileAngle - 3);
					missileMgr->Fire(pos.x, pos.y, missileAngle);
					missileMgr->Fire(pos.x, pos.y, missileAngle + 3);
					break;

				case 3:
					missileMgr->Fire(pos.x, pos.y, missileAngle - 6);
					missileMgr->Fire(pos.x, pos.y, missileAngle - 3);
					missileMgr->Fire(pos.x, pos.y, missileAngle);
					missileMgr->Fire(pos.x, pos.y, missileAngle + 3);
					missileMgr->Fire(pos.x, pos.y, missileAngle + 6);
					break;
				}
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))
		{
			if (aokavoid == false)
			{
				SoundManager::GetSingleton()->Play("AokAvoid");
			}
			isAvoid = !isAvoid;
			currFrameX = 0;
			playerState = PlayerState::AVOID;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown('X') && (skillOn == false) && (isAvoid == false) && (avoidGage >= 100))
		{
			if (aokskillcheck == false)
			{
				SoundManager::GetSingleton()->Play("AokSkill");
			}
			skillOn = true;
			avoidGage -= 100;
			playerState = PlayerState::SKILL;
		}

		////ÆÄ¿ö ¾÷
		//if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
		//{
		//	if (power < 3)
		//	{
		//		power++;
		//	}
		//}
	}

	switch (playerState)
	{
	case PlayerState::IDLE:

		currFrameY = 0;

		if (elipsedTime % 5 == 0)
		{
			currFrameX++;
			elipsedTime = 0;
		}

		if (currFrameX > maxFrameX[currFrameY])
		{
			currFrameX = 0;
		}

		break;

	case PlayerState::BACK:

		currFrameY = 1;

		if (elipsedTime % 5 == 0)
		{
			currFrameX++;
			elipsedTime = 0;
		}

		if (currFrameX > maxFrameX[currFrameY])
		{
			currFrameX = 0;
		}

		break;

	case PlayerState::AVOID:

		currFrameY = 3;

		if (elipsedTime % 3 == 0)
		{
			currFrameX++;
			elipsedTime = 0;
		}

		if (isAvoid == true)
		{
			if (currFrameX > maxFrameX[currFrameY] - 2)
			{
				currFrameX = maxFrameX[currFrameY] - 2;
			}

			avoidGage -= 3;

			if (avoidGage <= 0)
			{
				isAvoid = !isAvoid;
			}
		}
		else
		{
			if (currFrameX < maxFrameX[currFrameY] - 2)
			{
				currFrameX = maxFrameX[currFrameY] - 2;
			}

			if (currFrameX > maxFrameX[currFrameY])
			{
				currFrameX = 0;
				playerState = PlayerState::IDLE;
				aokavoid = false;
			}
		}

		break;

	case PlayerState::SKILL:

		currFrameY = 2;

		if (elipsedTime % 3 == 0)
		{
			currFrameX++;
			elipsedTime = 0;
		}

		//if (currFrameX == 4)
		//{
		//	skillOn = true;
		//}

		if (currFrameX > maxFrameX[currFrameY])
		{
			currFrameX = 0;

			playerState = PlayerState::IDLE;
			aokskillcheck = false;
		}
		break;
	}

	missileMgr->Update();
}

void Young_airplane::Render(HDC hdc)
{
	if (img)
	{
		img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 1.7f);
	}
	if (skillImage && skillOn)
	{
		//Rectangle(hdc, skillRect.left, skillRect.top, skillRect.right, skillRect.bottom);
		skillImage->FrameRender(hdc, skillPos.x, skillPos.y, skillCurrFrameX, currFrameY, 4.0f);
	}

	if (missileMgr)
		missileMgr->Render(hdc);
}

void Young_airplane::PowerUp()
{
	power++;
	if (power >= 3)
	{
		power = 3;
	}
}
