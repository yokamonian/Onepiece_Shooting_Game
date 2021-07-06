#pragma once
#include "GameNode.h"

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

