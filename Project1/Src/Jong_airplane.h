#pragma once
#include "Object.h"

class Image;
class MissileManager;
/// <summary>
/// 3종의 기체 중 키자루 기체의 정보를 담는 클래스.
/// </summary>
class Jong_airplane : public Object
{
private:

	int power;							//Power Up을 할 변수
	int missileAngle;					// angle을 설정할 변수.

	int maxFrameX[4]{ 3, 1, 11, 7 };
	PlayerState playerState;			// 플레이어 상태 정보
	
	// 회피
	int avoidGage;						// 회피 게이지
	bool isAvoid;						// 회피 게이지 사용 여부

	// 스킬
	POINT skillPos;						// 스킬 위치
	bool skillOn;						// 스킬상태 여부
	RECT skillRect;						// 스킬 게이지
	int skillWidth, skillHeight;		// 스킬 게이지 너비 및 높이
	bool kzrskillcheck;

	// 회피 관련 bool변수 체크
 	bool checkpoint;
	bool backcheck;
	bool upcheck;
	bool downcheck;
	bool kzravoid;

	// 각종 이미지
	Image* img;
	Image* skillImage;
	Image* skillOnImage;

	// 미사일
	MissileManager* missileMgr;

	int fireFrame;
	int fireDelay;
	int elipsedTime;
	int maxKeyFrameX;

	int shootcount;						// 오브젝트 풀링용 미사일 카운트


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

