#pragma once
#include "Object.h"

class Image;
class MissileManager;
/// <summary>
/// 3���� ��ü �� Ű�ڷ� ��ü�� ������ ��� Ŭ����.
/// </summary>
class Jong_airplane : public Object
{
private:

	int power;							//Power Up�� �� ����
	int missileAngle;					// angle�� ������ ����.

	int maxFrameX[4]{ 3, 1, 11, 7 };
	PlayerState playerState;			// �÷��̾� ���� ����
	
	// ȸ��
	int avoidGage;						// ȸ�� ������
	bool isAvoid;						// ȸ�� ������ ��� ����

	// ��ų
	POINT skillPos;						// ��ų ��ġ
	bool skillOn;						// ��ų���� ����
	RECT skillRect;						// ��ų ������
	int skillWidth, skillHeight;		// ��ų ������ �ʺ� �� ����
	bool kzrskillcheck;

	// ȸ�� ���� bool���� üũ
 	bool checkpoint;
	bool backcheck;
	bool upcheck;
	bool downcheck;
	bool kzravoid;

	// ���� �̹���
	Image* img;
	Image* skillImage;
	Image* skillOnImage;

	// �̻���
	MissileManager* missileMgr;

	int fireFrame;
	int fireDelay;
	int elipsedTime;
	int maxKeyFrameX;

	int shootcount;						// ������Ʈ Ǯ���� �̻��� ī��Ʈ


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

