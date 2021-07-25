#pragma once
#include "pch.h"
#include "SingletonBase.h"

class Timer;
/// <summary>
/// TimeManager : Time Ŭ������ Ȱ��. ���� �� ���� Ÿ�̸� �Ŵ��� Ŭ����.
/// </summary>
class TimeManager : public SingletonBase<TimeManager>
{
private:
	Timer* timer;			// Ÿ�̸�
	char strText[256];		
	bool isGameStart;		// ���ӽ��� ����

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update(float lockFPS = 0.0f);
	virtual void Render(HDC hdc);


	float GetWorldCount();
	float GetCurrTime();

	float GetDeltaTime();
	void SetIsGameStart(bool _isGameStart) { isGameStart = _isGameStart; }

	void ResetWt();
	Timer* GetTimer() { return timer; }
};

