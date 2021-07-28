#include "Jong_airplane.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Jong_airplane::Init()
{
	speed = 10.0f;
	pos = { 50, WINSIZE_Y / 2 };
	currFrameX = 0;
	currFrameY = 0;
	radius = 0;
	life = 1;
	img = ImageMgr::GetSingleton()->AddImage("Kizaru_Idle", "Image/Kizaru.bmp", 0, 0, 2400, 400, 12, 4, true, RGB(47, 54, 153));
	skillImage = ImageMgr::GetSingleton()->AddImage("kizaruskill", "Image/kizaruskill.bmp", 0, 0, 200, 200, 1, 2, true, RGB(47, 54, 153));

	checkpoint = false;
	skillPos = { -500, -500 };
	skillOn = false;

	backcheck = false;
	upcheck = false;
	downcheck = false;

	maxKeyFrameX = 3;
	missileAngle = 0;

	//0527 추가
	isAvoid = false;			// 회피기를 사용할 수 있는지를 체크할 변수.
	elipsedTime = 0;			// 프레임당 증가하는 변수.
	playerState = PlayerState::IDLE; //기본 상태는 Idle상태이다.
	avoidGage = 0;		// 회피기의 게이지를 담당할 변수
	power = 1;
	missileAngle = 0;

	fireFrame = 0;
	fireDelay = 3;

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetObject(this);

	shootcount = 0;

	kzravoid = false;
	kzrskillcheck = false;

	return S_OK;
}

void Jong_airplane::Release()
{

}

void Jong_airplane::Update()
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
			if (checkpoint == false)
			{
				skillPos.x = pos.x - 200;
				skillPos.y = pos.y;
				checkpoint = true;
			}

			skillPos.x += 30.0f * cosf(0);
			skillPos.y -= 30.0f * sinf(0);

			if (skillPos.x - 200 >= WINSIZE_X + 100)
			{
				checkpoint = false;
				skillOn = false;
			}

			skillRect = { skillPos.x - 350, skillPos.y - 200, skillPos.x + 300, skillPos.y + 200 };
		}

		elipsedTime++;
		fireFrame++;

		if ((isAvoid == false) && (playerState == PlayerState::IDLE || playerState == PlayerState::BACK || playerState == PlayerState::AVOID))
		{
			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
			{
				playerState = PlayerState::IDLE;
				backcheck = false;
				upcheck = false;
				downcheck = false;
				if (pos.x + 30 <= WINSIZE_X - 20)
					pos.x += speed;
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
			{
				playerState = PlayerState::BACK;
				backcheck = true;
				if (pos.x - 30 >= 0)
					pos.x -= speed;
			}

			if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
			{
				playerState = PlayerState::IDLE;
				upcheck = true;
				if (pos.y - 50 >= 10)
					pos.y -= speed;
			}
			else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
			{
				playerState = PlayerState::IDLE;
				downcheck = true;
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
				SoundManager::GetSingleton()->Play("KzrShoot", 0.2f);
				shootcount = 0;
			}
			if (fireFrame > fireDelay)
			{
				fireFrame = 0;

				missileMgr->SetCharNum(2);

				playerState = PlayerState::IDLE;
				currFrameY = 0;

				switch (power)
				{
				case 1:
					missileMgr->Fire(pos.x + 50, pos.y - 33, missileAngle);
					break;

				case 2:
					missileMgr->Fire(pos.x + 50, pos.y - 33, missileAngle - 3);
					missileMgr->Fire(pos.x + 50, pos.y - 33, missileAngle);
					missileMgr->Fire(pos.x + 50, pos.y - 33, missileAngle + 3);
					break;
				case 3:
					missileMgr->Fire(pos.x + 50, pos.y - 33, missileAngle - 6);
					missileMgr->Fire(pos.x + 50, pos.y - 33, missileAngle - 3);
					missileMgr->Fire(pos.x + 50, pos.y - 33, missileAngle);
					missileMgr->Fire(pos.x + 50, pos.y - 33, missileAngle + 3);
					missileMgr->Fire(pos.x + 50, pos.y - 33, missileAngle + 6);
					break;
				}
			}
		}

		if ((playerState == PlayerState::IDLE) || (playerState == PlayerState::BACK))
		{
			if (KeyManager::GetSingleton()->IsOnceKeyDown('C'))
			{
				if (kzravoid == false)
				{
					SoundManager::GetSingleton()->Play("KzrAvoid");
					kzravoid = true;
				}
				if (avoidGage >= 20)
				{
					isAvoid = true;
					playerState = PlayerState::AVOID;
					kzravoid = false;
				}
				else
				{
					playerState = PlayerState::IDLE;
				}

			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown('X') && (skillOn == false) && (isAvoid == false) && (avoidGage >= 100))
		{
			if (kzrskillcheck == false)
			{
				SoundManager::GetSingleton()->Play("KzrSkill");
			}
			skillOn = true;
			avoidGage -= 100;
			playerState = PlayerState::SKILL;
		}

		////파워 업
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

		backcheck = false;
		upcheck = false;
		downcheck = false;
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


	case PlayerState::SKILL:

		currFrameY = 2;

		if (elipsedTime % 3 == 0)
		{
			currFrameX++;
			elipsedTime = 0;
		}

		//if (currFrameX == 5)
		//{
		//	skillOn = true;
		//}

		if (currFrameX > maxFrameX[currFrameY])
		{
			currFrameX = 0;
			playerState = PlayerState::IDLE;
			if (kzrskillcheck == true)
			{
				kzrskillcheck = false;
			}
		}

		break;


	case PlayerState::AVOID:

		currFrameY = 3;

		if (elipsedTime % 2 == 0)
		{
			elipsedTime = 0;
			currFrameX++;

			if (currFrameX == 6)
			{
				if ((backcheck == false) && (upcheck == false) && (downcheck == false))
				{
					if (pos.x <= 1120)
					{
						avoidGage -= 20;
						pos.x += 130;
					}
				}
				else if (backcheck == true)
				{
					if (pos.x >= 180)
					{
						avoidGage -= 20;
						pos.x -= 130;
						backcheck = false;
					}
				}
				else if (upcheck == true)
				{
					if (pos.y >= 180)
					{
						avoidGage -= 20;
						pos.y -= 150;
						upcheck = false;
					}
				}
				else if (downcheck == true)
				{
					if (pos.y <= 720)
					{
						avoidGage -= 20;
						pos.y += 150;
						downcheck = false;
					}

				}
			}

			if (currFrameX > maxFrameX[currFrameY])
			{
				isAvoid = false;

				currFrameX = 0;
				playerState = PlayerState::IDLE;
			}
		}

		break;
	}

	missileMgr->Update();
}


void Jong_airplane::Render(HDC hdc)
{
	if (img)
	{
		//Rectangle(hdc, pos.x - 30, pos.y - 50, pos.x + 30, pos.y + 50);
		img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 1.7f);
	}

	if (skillImage && skillOn)
	{
		//Rectangle(hdc, skillRect.left, skillRect.top, skillRect.right, skillRect.bottom);
		skillImage->FrameRender(hdc, skillPos.x, skillPos.y, 0, 1, 3.0f);
	}

	if (missileMgr)
		missileMgr->Render(hdc);
}

void Jong_airplane::PowerUp()
{
	power++;
	if (power >= 3)
	{
		power = 3;
	}
}
