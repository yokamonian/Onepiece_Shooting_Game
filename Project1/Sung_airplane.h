#pragma once
#include "Object.h"


class Image;
class MissileManager;
/// <summary>
/// 3���� ��ü �� ��ī�̴� ��ü�� ������ ��� Ŭ����.
/// �ּ��� Jong_Airplane Ŭ������ ����.
/// </summary>
class Sung_airplane : public Object
{
private:
	int power; //Power Up�� �� ����
	int missileAngle; // angle�� ������ ����.
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

