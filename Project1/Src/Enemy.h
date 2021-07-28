#pragma once
#include "Object.h"

/// <summary>
/// Enemy : �� ������Ʈ���� ���� Ŭ����
/// </summary>
class Enemy : public Object
{
protected:


public:
	virtual HRESULT Init() = 0;
	virtual void Release() = 0;
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	Enemy();
	~Enemy();
};
