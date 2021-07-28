#pragma once
#include "GameNode.h"


class SceneManager;
class Image;
/// <summary>
/// MainGame : WinAPI를 통해 게임 콘솔창을 만드는 클래스.
/// 플레이 시, 모든 씬(Scene)의 게임플레이를 관리하는 클래스.
/// </summary>
class MainGame : public GameNode
{
private:
	bool isInit;

	Image* backBuffer;
	HDC hdc;
	SceneManager* sceneMgr;
	static MainGame* Instance;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage,
		WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

