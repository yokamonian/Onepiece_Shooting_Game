#include "PowerUp.h"
#include "Image.h"

HRESULT PowerUp::Init()
{
	powerUpImg = ImageMgr::GetSingleton()->AddImage("powerUpImg", "Image/bustercall.bmp", 100, 100, true, RGB(255, 0, 255));
	angle = 160;
	radius = 70.0f;

	center = { pos.x - radius / 2, pos.y - radius / 2 };

	return S_OK;
}

void PowerUp::Update()
{
	if (isCollision == false)
	{
		center.x += 10 * cosf(DEGREE_TO_RADIAN(angle));
		center.y -= 10 * sinf(DEGREE_TO_RADIAN(angle));

		if ((center.y - radius * 2 <= 0) ||
			(center.y + radius * 2 >= WINSIZE_Y))
		{
			angle = 180 * 2 - angle;
		}

		if ((center.x + radius * 2 >= WINSIZE_X) ||
			(center.x - radius * 2 <= 0))
		{
			angle = 180 - angle;
		}
	}
	else
	{
		center.x = -1000;
		center.y = -1000;
	}
}

void PowerUp::Release()
{
}

void PowerUp::Render(HDC hdc)
{
	if (powerUpImg && (isCollision == false))
	{
		//Ellipse(hdc, center.x - radius / 2, center.y - radius / 2, center.x + radius / 2, center.y + radius / 2);
		powerUpImg->Render(hdc, center.x, center.y, 0, 0);
	}
}
