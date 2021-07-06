#include "Player.h"
#include "Jong_airplane.h"
#include "Sung_airplane.h"
#include "Young_airplane.h"
#include "MissileManager.h"
#include "Image.h"

HRESULT Player::Init(int selectIdx)
{
	charNum = selectIdx;

	switch (charNum)
	{
	case 0:

		young = new Young_airplane();
		young->Init();


		break;

	case 1:

		sung = new Sung_airplane();
		sung->Init();


		break;

	case 2:

		jong = new Jong_airplane();
		jong->Init();

		break;
	}

	speed = 5.0f;
	playerlife = 1;
	radius = 0;

	missileMgr = new MissileManager();
	missileMgr->Init();
	missileMgr->SetObject(this);

	return S_OK;
}

void Player::Update()
{
	if (playerlife > 0)
	{
		if (charNum == 0)
		{
			young->Update();
			playerPos = young->GetPos();
			playerGage = young->GetGage();
			playerlife = young->Getlife();
			playerState = young->GetPlayerState();
			skillRect = young->GetSkillRect();
			skillOn = young->GetSkillOn();
			pos = young->GetPos();
		}
		else if (charNum == 1)
		{
			sung->Update();
			playerPos = sung->GetPos();
			playerGage = sung->GetGage();
			playerlife = sung->Getlife();
			playerState = sung->GetPlayerState();
			skillRect = sung->GetSkillRect();
			skillOn = sung->GetSkillOn();
			pos = sung->GetPos();
		}
		else if (charNum == 2)
		{
			jong->Update();
			playerPos = jong->GetPos();
			playerGage = jong->GetGage();
			playerlife = jong->Getlife();
			playerState = jong->GetPlayerState();
			skillRect = jong->GetSkillRect();
			skillOn = jong->GetSkillOn();
			pos = jong->GetPos();
		}

		missileMgr->Update();
	}
}

void Player::Release()
{
	switch (charNum)
	{
	case 0:

		young->Release();
		SAFE_DELETE(young);

		break;

	case 1:

		sung->Release();
		SAFE_DELETE(sung);

		break;

	case 2:

		jong->Release();
		SAFE_DELETE(jong);

		break;
	}
}

void Player::Render(HDC hdc)
{
	if (playerlife > 0)
	{
		if (charNum == 0)
			young->Render(hdc);
		else if (charNum == 1)
			sung->Render(hdc);
		else if (charNum == 2)
			jong->Render(hdc);

		if (missileMgr)
			missileMgr->Render(hdc);
	}

}

bool Player::Onhit(FPOINT point)
{
	float length = sqrt(pow(point.x - playerPos.x, 2) + pow(point.y - playerPos.y, 2)); // 두개체간의 거리 비교z
	if (length < 20)
	{
		if (isDamaged == false)
			playerlife -= 1;

		isDamaged = true;

		return true;
	}
	return false;
}

void Player::PowerUp()
{
	switch (charNum)
	{
	case 0: //아오키지
		young->PowerUp();
		break;

	case 1:	//아카이누
		sung->PowerUp();
		break;

	case 2:	//키자루
		jong->PowerUp();
		break;

	}


}
