#include "SceneManager.h"
#include "Image.h"
#include "Battle.h"
#include "BossEnemy.h"
#include "Player.h"
#include "EliteEnemy.h"

HRESULT SceneManager::Init()
{
	selectBGImg = new Image();
	selectPointerImg = new Image();
	battle = new Battle();
	introImg = new Image();
	outroImg = new Image();
	gameover = new Image();
	acedeadframe = new Image();
	//introImg = new Image();

	//이미지의 가로 크기, 세로 크기
	width = 1200;
	height = 900;

	introImg->Init("Image/open.bmp", 0, 0, 9600, 900, 8, 1);
	selectBGImg->Init("Image/test.bmp", width, height);
	selectPointerImg->Init("Image/arrow.bmp", 0, 0, 240, 180, 8, 3, true, RGB(255, 0, 0));
	gameover->Init("Image/gameover.bmp", 1200, 900, true, RGB(3, 12, 67));
	acedeadframe->Init("Image/AceDeadFrame.bmp", 0, 113, 48000, 675, 40, 1);
	//introImg->Init("Image/opening.bmp", 1200, 900);

	if (FAILED(outroImg->Init("Image/acediecredit.bmp", 0, 0, 62400, 900, 52, 1)))
	{
		MessageBox(g_hWnd, "dd", "asdf", MB_OK);
	}
	//battle->Init();

	//pos = {0, 0};
	isSelected = false;
	sceneNum = 0;
	charNum = 0;
	currFrameX = 0;
	currFrameY = 0;
	test = 0;
	//testCount = 0;

	opench = false;
	ending = false;
	return S_OK;
}

void SceneManager::Update()
{
	if (sceneNum == 0)
	{
		if (opench == false)
		{
			SoundManager::GetSingleton()->Play("open", 0.5f);
			opench = true;
		}
		if (introImg)
		{
			test++;
			if (test % 4 == 3)
			{
				currFrameX++;
				test = 0;
				if (currFrameX == 8)
				{
					currFrameX = 0;
					test = 0;
				}
			}
		}
		if (KeyManager::GetSingleton()->IsOnceKeyDown('Z'))
		{
			sceneNum = 1;
		}
	}
	else if (sceneNum == 1)
	{
		if (selectPointerImg)
		{
			test++;

			if (currFrameY == 0)
			{
				if (test % 3 == 2)
				{
					currFrameX++;
					test = 0;
					if (currFrameX == 7)
					{
						currFrameX = 0;
						currFrameY = 1;
					}
				}
			}
			else if (currFrameY == 1)
			{
				if (test % 3 == 2)
				{
					currFrameX++;
					test = 0;
					if (currFrameX == 8)
					{
						currFrameY = 2;
						currFrameX = 0;
					}
				}
			}
			else
			{
				if (test % 3 == 2)
				{
					currFrameX++;
					test = 0;
					if (currFrameX == 6)
					{
						currFrameY = 0;
						currFrameX = 0;
					}
				}
			}


			if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LEFT))
			{
				if (charNum == 0)
					charNum = 2;
				else
					charNum--;
			}
			else if ((KeyManager::GetSingleton()->IsOnceKeyDown(VK_RIGHT)))
			{
				if (charNum == 2)
					charNum = 0;
				else
					charNum++;
			}

			//rc = { center.x, 0, center.x + width, 560 }

			if ((KeyManager::GetSingleton()->IsOnceKeyDown('Z')))
			{
				//charNum = 0;
				battle->Init(charNum);
				sceneNum = 2;
				//TimeManager::GetSingleton()->
				//battle->SetCharNum(charNum);
				TimeManager::GetSingleton()->ResetWt();
				SoundManager::GetSingleton()->Stop("open");
				SoundManager::GetSingleton()->Play("BG", 0.1f);
			}
		}

	}
	else if (sceneNum == 2)
	{
		battle->Update();

		if (outroImg && Battle::instance->GetBossEnemy()->GetLife() <= 0)
		{
			test++;
			if (test % 5 == 4)
			{
				currFrameX++;
				test = 0;
				if (currFrameX >= 51)
				{
					currFrameX = 0;
				}
			}
		}
	}


}

void SceneManager::Release()
{
	acedeadframe->Release();
	SAFE_DELETE(acedeadframe);

	introImg->Release();
	SAFE_DELETE(introImg);

	gameover->Release();
	SAFE_DELETE(gameover);

	outroImg->Release();
	SAFE_DELETE(outroImg);

	battle->Release();
	SAFE_DELETE(battle);

	selectPointerImg->Release();
	SAFE_DELETE(selectPointerImg);

	selectBGImg->Release();
	SAFE_DELETE(selectBGImg);

}

void SceneManager::Render(HDC hdc)
{
	if (sceneNum == 0)
	{
		if (introImg)
		{
			introImg->FrameRender(hdc, 0, 0, currFrameX, currFrameY);
		}
	}
	else if (sceneNum == 1)
	{
		if (selectBGImg)
		{
			if (CharSelect())
			{
				selectBGImg->Render(hdc, 0, 0);
			}
		}

		if (selectPointerImg)
		{
			if (CharSelect())
			{
				selectPointerImg->FrameRender(hdc, selectPosX[charNum], 410, currFrameX, currFrameY, 2.0f);
			}
		}
	}
	else if (sceneNum == 2)
	{
		battle->Render(hdc);

		if (outroImg &&
			(Battle::instance->GetEliteEnemy()->GetEliteEnemyState() == EliteEnemyState::DIE) &&
			(Battle::instance->GetBossEnemy()->GetIsAppear() == false))
		{
			outroImg->FrameRender(hdc, 0, 0, currFrameX, currFrameY);
			if (ending == false)
			{
				SoundManager::GetSingleton()->Stop("aceopen");
				SoundManager::GetSingleton()->Play("acedead");
				ending = true;
			}
		}
		else if (gameover && Battle::instance->GetPlayer()->GetLife() <= 0)
		{
			if (opench == true)
			{
				SoundManager::GetSingleton()->Play("DIE");
				opench = false;
				SoundManager::GetSingleton()->Stop("BG");
				SoundManager::GetSingleton()->Stop("WhiteMan");
				SoundManager::GetSingleton()->Stop("AceP1");
				SoundManager::GetSingleton()->Stop("whiteopen");
				SoundManager::GetSingleton()->Stop("aceopen");
			}
			gameover->Render(hdc, WINSIZE_X / 2, WINSIZE_Y / 2);


		}
	}


}

int SceneManager::CharSelect()
{
	return 1;
}
