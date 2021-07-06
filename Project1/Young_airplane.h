#pragma once
#include "Object.h"


class Image;
class MissileManager;
class Young_airplane : public Object
{
private:

	//0529
	int power; //Power Up�� �� ����
	int missileAngle; // angle�� ������ ����.
	RECT skillRect;
	int skillWidth, skillHeight;


	//0527 ���� �߰�
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

	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)
	void PowerUp();


	int GetGage() { return avoidGage; }
	int Getlife() { return life; }
	void Setlife(int _life) { life = _life; }
	PlayerState GetPlayerState() { return playerState; }
	RECT GetSkillRect() { return skillRect; }
	bool GetSkillOn() { return skillOn; }
};

