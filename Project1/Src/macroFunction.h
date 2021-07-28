// macroFunction.h
#pragma once
#include "pch.h"

inline float TwoPointAngle(float x1, float y1, float x2, float y2)
{
	return atan2f(-(y2 - y1), x2 - x1);
}

inline bool CircleCollision(float x1, float y1, float x2, float y2)
{
	if (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) < 80)
	{
		return true;
	}
	else
		return false;
}

inline void DrawEllipse(HDC hdc, float centerX, float centerY, float radius)
{
	Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);
}

inline bool IsPointInCircle(float cx, float cy, float cr, float px, float py)
{
	float deltaX = cx - px;
	float deltaY = cy - py;
	float length = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (length > cr)
		return false;

	return true;
}

inline bool RectCollision(RECT rc1, RECT rc2)
{
	if (rc1.right < rc2.left || rc1.bottom < rc2.top || rc1.left > rc2.right || rc1.top > rc2.bottom)
	{
		return false;
	}

	return true;
}

//x1, y1 원의 중심 좌표, radius : 반지름, rc : 사각형
inline bool RectangleWithCircle(float circleCenterX, float circleCenterY, float radius, RECT rect)
{
	RECT rc = rect;

	if ((rect.left <= circleCenterX && circleCenterX <= rect.right) ||
		(rect.top <= circleCenterY && circleCenterY <= rect.bottom))
	{
		//radius만큼 +된 사각형을 만든다.
		rc.left -= radius;
		rc.top -= radius;
		rc.right += radius;
		rc.bottom += radius;

		if ((circleCenterX >= rc.left && circleCenterX <= rc.right)
			&& (circleCenterY >= rc.top && circleCenterY <= rc.bottom))
		{
			return true;
		}
	}
	else
	{
		if (IsPointInCircle(circleCenterX, circleCenterY, radius, (float)rect.left, (float)rect.top)) return true;
		if (IsPointInCircle(circleCenterX, circleCenterY, radius, (float)rect.left, (float)rect.bottom)) return true;
		if (IsPointInCircle(circleCenterX, circleCenterY, radius, (float)rect.right, (float)rect.top)) return true;
		if (IsPointInCircle(circleCenterX, circleCenterY, radius, (float)rect.right, (float)rect.bottom)) return true;
	}

	return false;	
}

