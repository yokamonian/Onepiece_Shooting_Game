#include "EliteEnemyMissile.h"
#include "Image.h"

HRESULT EliteEnemyMissile::Init()
{
	pos = { 0, 0 };
	speed = 900.0f;
	currFrameX = 0;
	currFrameY = 0;
	angle = 0.0f;

	img = ImageMgr::GetSingleton()->AddImage("B_Missile", "Image/B_Missile.bmp", 40, 37, true, RGB(0, 0, 0));

	return S_OK;
}

void EliteEnemyMissile::Update()
{
	pos.x += speed * cosf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
	pos.y -= speed * sinf(angle) * TimeManager::GetSingleton()->GetDeltaTime();
}

void EliteEnemyMissile::Release()
{
}

void EliteEnemyMissile::Render(HDC hdc)
{
	if (img)
	{
		img->Render(hdc, pos.x, pos.y);
	}
}
