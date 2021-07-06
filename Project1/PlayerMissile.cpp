#include "PlayerMissile.h"
#include "Image.h"
#include "macroFunction.h"

HRESULT PlayerMissile::Init(/*int charNum*/)
{
	pos = { 0, 0 };
	speed = 900.0f;
	currFrameX = 0;
	currFrameY = 0;
	angle = 0.0f;
	radius = 10.0f;

	ImageMgr::GetSingleton()->AddImage("aokiji_missile_1", "Image/aokiji_missile_1.bmp", 109, 58, true, RGB(86, 102, 88));
	ImageMgr::GetSingleton()->AddImage("akainu_missile_1", "Image/akainu_missile_1.bmp", 36, 37, true, RGB(88, 95, 142));
	ImageMgr::GetSingleton()->AddImage("kizaru_missile_1", "Image/kizaru_missile_1.bmp", 29, 31, true, RGB(47, 54, 153));

	return S_OK;
}

void PlayerMissile::Update()
{
	pos.x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
	pos.y -= speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
}

void PlayerMissile::Release()
{

}

void PlayerMissile::Render(HDC hdc)
{
	switch (missileType)
	{
	case 0: //아오키지
		playerMissileImg = ImageMgr::GetSingleton()->AddImage("aokiji_missile_1", "Image/aokiji_missile_1.bmp", 109, 58, true, RGB(86, 102, 88));
		break;

	case 1: //아카이누
		playerMissileImg = ImageMgr::GetSingleton()->AddImage("akainu_missile_1", "Image/akainu_missile_1.bmp", 36, 37, true, RGB(88, 95, 142));
		break;

	case 2: //키자루
		playerMissileImg = ImageMgr::GetSingleton()->AddImage("kizaru_missile_1", "Image/kizaru_missile_1.bmp", 29, 31, true, RGB(47, 54, 153));
		break;
	}

	if (playerMissileImg)
	{
		playerMissileImg->Render(hdc, pos.x, pos.y);
	}

}
