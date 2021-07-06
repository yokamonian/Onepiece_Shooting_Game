#pragma once
#include "Object.h"

class Image;
class MissileManager;
class Jong_airplane : public Object
{
private:

	//0529
	int power; //Power Up을 할 변수
	int missileAngle; // angle을 설정할 변수.

	RECT skillRect;
	int skillWidth, skillHeight;

	int maxFrameX[4]{ 3, 1, 11, 7 };
	PlayerState playerState;
	int avoidGage;
	bool isAvoid;

	POINT skillPos;
	bool skillOn;
	bool checkpoint;

	bool backcheck;
	bool upcheck;
	bool downcheck;

	Image* img;
	Image* skillImage;
	Image* skillOnImage;

	MissileManager* missileMgr;

	int fireFrame;
	int fireDelay;
	int elipsedTime;
	int maxKeyFrameX;

	int shootcount;

	bool kzrskillcheck;
	bool kzravoid;

public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Release();
	virtual void Render(HDC hdc);
	void PowerUp();

	int GetGage() { return avoidGage; }
	int Getlife() { return life; }
	void Setlife(int _life) { life = _life; }
	PlayerState GetPlayerState() { return playerState; }
	RECT GetSkillRect() { return skillRect; }
	bool GetSkillOn() { return skillOn; }
};

