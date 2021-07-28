#include "Sung_airplane.h"
#include "Image.h"
#include "MissileManager.h"

HRESULT Sung_airplane::Init()
{
	speed = 10.0f;
	pos = { 50, WINSIZE_Y / 2 };

	currFrameX = 0;
	currFrameY = 0;
	radius = 0;
	life = 1;
	img = ImageMgr::GetSingleton()->AddImage("Akainu.Idle", "Image/akainu.bmp", 0, 0, 2400, 400, 12, 4, true, RGB(88, 95, 142));
	skillImage = ImageMgr::GetSingleton()->AddImage("Akainu_Skill", "Image/akainu_skill.bmp", 0, 0, 327, 73, 5, 1, true, RGB(88, 95, 142));
	skillCurrFrameX = 0;

	checkpoint = false;
	skillPos = { -500, -500 };
	skillOn = false;
	isGameStartPosition = true;

	maxKeyFrameX = 3;
	fireFrame = 0;
	fireDelay = 3;
	//0527 추가
	isAvoid = false;			// 회피기를 사용할 수 있는지를 체크할 변수.
	elipsedTime = 0;			// 프레임당 증가하는 변수.
	playerState = PlayerState::IDLE; //기본 상태는 Idle상태이다.
	avoidGage = 0;		// 회피기의 게이지를 담당할 변수
	power = 1;


	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetObject(this);

	shootcount = 0;
	akaskillcheck = false;
	akaavoid = false;
	return S_OK;
}

void Sung_airplane::Release()
{

}

void Sung_airplane::Update()
{
	if (life == 1)
	{
		/*if (isGameStartPosition == true)
		{
			pos.x += speed;

			if (pos.x >= 50)
			{
				isGameStartPosition = false;
				return;
			}
		}*/

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

				if (skillCurrFrameX > 4)
				{
					skillCurrFrameX = 0;
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

			skillRect = { skillPos.x - 200, skillPos.y - 200, skillPos.x + 200, skillPos.y + 200 };

		}
		elipsedTime++;
		fireFrame++;

		if (/*(isAvoid == false) && */(playerState == PlayerState::IDLE || playerState == PlayerState::BACK || playerState == PlayerState::AVOID))
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
				if (pos.y + 80 <= WINSIZE_Y)
					pos.y += speed;
			}

			if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LEFT))
			{
				playerState = PlayerState::IDLE;
			}
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown('Z'))
		{
			shootcount++;
			if (shootcount >= 8)
			{
				SoundManager::GetSingleton()->Play("AkaShoot", 0.3f);
				shootcount = 0;
			}
			if (fireFrame > fireDelay)
			{
				fireFrame = 0;

				missileMgr->SetCharNum(1);

				playerState = PlayerState::IDLE;
				currFrameY = 0;

				switch (power)
				{
				case 1:
					missileMgr->Fire(pos.x + 10, pos.y, missileAngle);
					break;

				case 2:
					missileMgr->Fire(pos.x + 10, pos.y, missileAngle - 3);
					missileMgr->Fire(pos.x + 10, pos.y, missileAngle);
					missileMgr->Fire(pos.x + 10, pos.y, missileAngle + 3);
					break;

				case 3:
					missileMgr->Fire(pos.x + 10, pos.y, missileAngle - 6);
					missileMgr->Fire(pos.x + 10, pos.y, missileAngle - 3);
					missileMgr->Fire(pos.x + 10, pos.y, missileAngle);
					missileMgr->Fire(pos.x + 10, pos.y, missileAngle + 3);
					missileMgr->Fire(pos.x + 10, pos.y, missileAngle + 6);
					break;
				}
			}
		}

		if (KeyManager::GetSingleton()->IsStayKeyDown('C'))
		{
			shootcount++;
			if (shootcount >= 10)
			{
				SoundManager::GetSingleton()->Play("AkaAvoid");
				shootcount = 0;
			}
			if (avoidGage >= 0)
			{
				avoidGage -= 6;
				playerState = PlayerState::AVOID;
			}
			else
			{
				playerState = PlayerState::IDLE;
			}
		}

		if (KeyManager::GetSingleton()->IsOnceKeyDown('X') && skillOn == false && (avoidGage >= 100))
		{
			if (akaskillcheck == false)
			{
				SoundManager::GetSingleton()->Play("AkaSkill");
				akaskillcheck = true;
			}
			skillOn = true;
			avoidGage -= 100;
			playerState = PlayerState::SKILL;
		}

		if (KeyManager::GetSingleton()->IsOnceKeyUp('C'))
		{
			playerState = PlayerState::IDLE;
		}
		/*if (KeyManager::GetSingleton()->IsOnceKeyDown('Q'))
		{
			if (power < 3)
			{
				power++;
			}
		}*/
	}

	switch (playerState)
	{
	case PlayerState::IDLE:
		if (akaskillcheck == true)
		{
			akaskillcheck = false;
		}
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

		//if (currFrameX == 2)
		//{
		//	skillOn = true;
		//}

		if (currFrameX > maxFrameX[currFrameY])
		{
			currFrameX = 0;
			playerState = PlayerState::IDLE;
		}

		break;


	case PlayerState::AVOID:

		currFrameY = 3;

		if (elipsedTime % 3 == 0)
		{
			currFrameX++;
			elipsedTime = 0;
		}


		if (currFrameX > maxFrameX[currFrameY])
		{
			currFrameX = 0;
		}


		break;
	}

	missileMgr->Update();
}

void Sung_airplane::Render(HDC hdc)
{
	if (img)
	{
		img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 1.7f);
	}
	if (skillImage && skillOn)
	{
		//Rectangle(hdc, skillRect.left, skillRect.top, skillRect.right, skillRect.bottom);
		skillImage->FrameRender(hdc, skillPos.x, skillPos.y, skillCurrFrameX, currFrameY, 5.0f);
	}
	if (missileMgr)
		missileMgr->Render(hdc);
}

void Sung_airplane::PowerUp()
{
	power++;
	if (power >= 3)
	{
		power = 3;
	}
}
