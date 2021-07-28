#pragma once
#include "pch.h"

/// <summary>
/// GameNode : ������ ��� ������Ʈ ��� Ŭ������ ���� Ŭ����.
/// </summary>
class GameNode
{
public:
	virtual HRESULT Init();		// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();		// �޸� ����
	virtual void Update();		// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	GameNode();
	~GameNode();
};

