#include "MainGame.h"
#include "macroFunction.h"
#include "Image.h"
#include "SceneManager.h"

MainGame* MainGame::Instance = 0;

HRESULT MainGame::Init()
{
	hdc = GetDC(g_hWnd);

	backBuffer = new Image();
	backBuffer->Init(WINSIZE_X, WINSIZE_Y);

	KeyManager::GetSingleton()->Init();
	ImageMgr::GetSingleton()->Init();
	TimeManager::GetSingleton()->Init();
	SoundManager::GetSingleton()->Init();

	SoundManager::GetSingleton()->AddSound("open", "Sound/opening.mp3", true, true);
	SoundManager::GetSingleton()->AddSound("BG", "Sound/bg.mp3", true, true);
	SoundManager::GetSingleton()->AddSound("aceopen", "Sound/aceopen.mp3", true, true);
	SoundManager::GetSingleton()->AddSound("acedead", "Sound/acedead.mp3", true, true);
	SoundManager::GetSingleton()->AddSound("whiteopen", "Sound/whiteopen.mp3", true, true);
	SoundManager::GetSingleton()->AddSound("DIE", "Sound/노갓플리즈.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("KzrShoot", "Sound/kzrshoot.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("KzrSkill", "Sound/kzrskill.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("KzrAvoid", "Sound/kzravoid.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("WhiteMan", "Sound/onepieceisreal.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("AkaShoot", "Sound/akashoot.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("AkaSkill", "Sound/akaskill.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("AkaAvoid", "Sound/akaavoid.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("AokShoot", "Sound/aokshoot.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("AokSkill", "Sound/aokskill.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("AokAvoid", "Sound/aokavoid.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("AceP1", "Sound/acepattern1.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("AceP2", "Sound/acepattern2.mp3", false, false);
	SoundManager::GetSingleton()->AddSound("AceP3", "Sound/acepattern3.mp3", false, false);


	sceneMgr = new SceneManager();
	sceneMgr->Init();

	isInit = true;
	return S_OK;
}

void MainGame::Release()
{
	sceneMgr->Release();
	SAFE_DELETE(sceneMgr);

	KeyManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->ReleaseSingleton();

	ImageMgr::GetSingleton()->Release();
	ImageMgr::GetSingleton()->ReleaseSingleton();

	TimeManager::GetSingleton()->Release();
	TimeManager::GetSingleton()->ReleaseSingleton();

	SoundManager::GetSingleton()->Release();
	SoundManager::GetSingleton()->ReleaseSingleton();

	backBuffer->Release();
	delete backBuffer;

	ReleaseDC(g_hWnd, hdc);
}


void MainGame::Update()
{
	if (sceneMgr)
	{
		sceneMgr->Update();
	}

	InvalidateRect(g_hWnd, NULL, false); //backbuffer에 넣어준 후에는 false로 만들어주기
}

void MainGame::Render()
{
	sceneMgr->Render(backBuffer->GetMemDC());
	TimeManager::GetSingleton()->Render(backBuffer->GetMemDC());
	backBuffer->Render(hdc, 0, 0);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		}

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}



MainGame::MainGame()
	: isInit(false)
{
}


MainGame::~MainGame()
{
}
