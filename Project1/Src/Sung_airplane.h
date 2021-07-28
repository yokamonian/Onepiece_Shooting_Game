#pragma once
#include "Object.h"


class Image;
class MissileManager;
/// <summary>
/// 3종의 기체 중 아카이누 기체의 정보를 담는 클래스.
/// 주석은 Jong_Airplane 클래스와 동일.
/// </summary>
class Sung_airplane : public Object
{
private:
	int power; //Power Up을 할 변수
	int missileAngle; // angle을 설정할 변수.
	RECT skillRect;
	int skillWidth, skillHeight;

	bool isGameStartPosition;

	int maxFrameX[4]{ 3, 1, 5, 1 };
	PlayerState playerState;
	int avoidGage;
	bool isAvoid;
	POINT skillPos;
	int fireFrame;
	int fireDelay;
	bool skillOn;
	bool checkpoint;
	int skillCurrFrameX;

	Image* img;
	Image* skillImage;
	MissileManager* missileMgr;

	int elipsedTime;
	int maxKeyFrameX;

	int shootcount;
	bool akaskillcheck;
	bool akaavoid;

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

