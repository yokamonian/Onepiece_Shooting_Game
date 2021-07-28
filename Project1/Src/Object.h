#pragma once
#include "GameNode.h"

/// <summary>
/// 모든 오브젝트 클래스의 상위 클래스.
/// </summary>
class Object : public GameNode
{
protected:

	FPOINT pos;
	float speed;
	int life;
	int currFrameX;
	int currFrameY;
	float radius;

public:

	virtual HRESULT Init();
	virtual void Update();
	virtual void Release();
	virtual void Render();
	FPOINT GetPos() { return pos; }
};

