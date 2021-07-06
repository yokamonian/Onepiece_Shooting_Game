#pragma once
#include "Object.h"


class Image;
class MissileManager;
class Young_airplane : public Object
{
private:

	//0529
	int power; //Power Up을 할 변수
	int missileAngle; // angle을 설정할 변수.
	RECT skillRect;
	int skillWidth, skillHeight;


	//0527 변수 추가
	int maxFrameX[4]{ 3, 1, 8, 6 };
	PlayerState playerState;
	int avoidGage;
	bool isAvoid;
	int fireFrame;
	int fireDelay;


	Image* img;
	Image* skillImage;
	MissileManager* missileMgr;


	POINT skillPos;
	bool skillOn;
	bool checkpoint;
	int skillCurrFrameX;
	int elipsedTime;
	int maxKeyFrameX;

	int shootcount;
	bool aokskillcheck;
	bool aokavoid;

public:

	virtual HRESULT Init();		// 멤버 변수 초기화, 메모리 할당
	virtual void Release();		// 메모리 해제
	virtual void Update();		// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render(HDC hdc);	// 프레임 단위 출력 (이미지, 텍스트 등)
	void PowerUp();


	int GetGage() { return avoidGage; }
	int Getlife() { return life; }
	void Setlife(int _life) { life = _life; }
	PlayerState GetPlayerState() { return playerState; }
	RECT GetSkillRect() { return skillRect; }
	bool GetSkillOn() { return skillOn; }
};

