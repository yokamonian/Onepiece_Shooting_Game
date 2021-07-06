#pragma once
#include "GameNode.h"

class Image;
class Battle;
class SceneManager : public GameNode
{
private:
	int sceneNum;
	int charNum;

	Image* selectBGImg;
	Image* selectPointerImg;
	Image* outroImg;
	Image* gameover;
	Image* introImg;
	Image* acedeadframe;
	//Image* introImg;

	//test¿ë º¯¼ö
	//FPOINT pos;
	float selectPosX[3]{ 200, 600, 1000 };
	int width, height;
	int currFrameX, currFrameY;
	int test;
	bool isSelected;
	Battle* battle;

	bool opench;
	bool ending;

public:
	virtual HRESULT Init();
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);

	int CharSelect();
};

