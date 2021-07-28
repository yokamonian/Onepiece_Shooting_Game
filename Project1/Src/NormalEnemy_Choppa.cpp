#include "NormalEnemy_Choppa.h"
#include "Image.h"
#include "MissileManager.h"
#include "macroFunction.h"

HRESULT NormalEnemy_Choppa::Init()
{
	pos.x = WINSIZE_X + 30.0f;
	pos.y = WINSIZE_Y / 2;

	img = ImageMgr::GetSingleton()->AddImage("NormalEnemy", "Image/tichi.bmp", 0, 0, 1200, 400, 6, 4, true, RGB(99, 131, 114));
	isAppear = false;
	currFrameX = 0;
	currFrameY = 0;
	maxKeyFrameX = 3;
	elipsedTime = 0;
	isDamaged = false;
	fireCount = 0;
	isRender = true;
	EnemyMissileMgr = new MissileManager();
	EnemyMissileMgr->Init();
	return S_OK;
}

void NormalEnemy_Choppa::Release()
{
	EnemyMissileMgr->Release();
	SAFE_DELETE(EnemyMissileMgr);
}

void NormalEnemy_Choppa::Update()
{
	EnemyMissileMgr->Update();
	if (isDamaged == false)
	{
		if (isAppear)
		{
			if (pos.x > 0 && pos.y < 900)
			{

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


}

void NormalEnemy_Choppa::Render(HDC hdc)
{
	if (img)
	{
		if (isRender)
		{
			if (isDamaged == false)
				img->FrameRender(hdc, pos.x - 40, pos.y - 35, currFrameX, currFrameY, 1.7f);
			else
				img->FrameRender(hdc, pos.x, pos.y, currFrameX, currFrameY, 1.7f);
		}

	}
	if (EnemyMissileMgr)
	{
		EnemyMissileMgr->Render(hdc);
	}
}

bool NormalEnemy_Choppa::OnHit(FPOINT point)
{
	float length = sqrt(pow(pos.x - point.x, 2) + pow(pos.y - point.y, 2)); // 두개체간의 거리 비교
	if (length < 60)
	{
		return true;
	}
	return false;
}

NormalEnemy_Choppa::NormalEnemy_Choppa()
{
}

NormalEnemy_Choppa::~NormalEnemy_Choppa()
{
}


