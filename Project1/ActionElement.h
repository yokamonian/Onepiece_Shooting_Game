#pragma once
#include "pch.h"

/// <summary>
/// ActionElement : 패턴 저장 데이터 변수들의 집합 클래스.
/// </summary>
class ActionElement
{
public :
	int id;
	int duration;
	float angle;

	float speed;
	float GoalX;
	float GoalY;

	ActionElement(int id, int duration, float angle, float speed = 1.0f, float GoalX = 0.0f, float GoalY = 0.0f)
	{
		this->id = id;
		this->duration = duration;
		this->angle = angle;	
		this->speed = speed;
		this->GoalX = GoalX;
		this->GoalY = GoalY;
	}
};