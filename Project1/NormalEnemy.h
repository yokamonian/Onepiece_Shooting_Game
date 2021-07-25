#pragma once
#include "Enemy.h"

/// <summary>
/// NormalEnemy : 기본 적군 기체 상위 클래스.
/// </summary>
class NormalEnemy : public Enemy
{
protected:


public:
	virtual HRESULT Init() = 0;		
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;
};

