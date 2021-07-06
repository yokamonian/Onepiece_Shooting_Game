#pragma once
#include "GameNode.h"


class SceneManager;
class Image;
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

