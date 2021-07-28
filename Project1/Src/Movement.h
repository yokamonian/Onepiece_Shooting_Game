#pragma once
#include "pch.h"

/// <summary>
/// Movement : 이동과 미사일 이동의 패턴 조합을 위한 이동 함수 모음.
/// </summary>
/// <param name="posX"></param>
/// <param name="posY"></param>
/// <param name="angle"></param>
/// <param name="speed"></param>
inline void N_anglemove(float *posX, float *posY, float angle, float speed)
{
	angle = -angle;
	(*posX) += cosf(DEGREE_TO_RADIAN(angle))*speed;
	(*posY) += sinf(DEGREE_TO_RADIAN(angle))*speed;
}

inline void N_circle(float *posX, float *posY, float angle, float *holdX, float *holdY)// 한점을 잡아서 반지름의 100만큼을 윗호를 그리면서 angle만큼 이동하는 함수
{
	(*posX) = *holdX + 100 * cosf(DEGREE_TO_RADIAN(angle));
	(*posY) = *holdY - 100 * sinf(DEGREE_TO_RADIAN(angle));
}

inline void N_poin_point(float *posX, float *posY, float *destposX, float *destposY, float *holdX, float *holdY, float duration)
{
	*posX += (*destposX - *holdX) / duration;
	*posY += (*destposY - *holdY) / duration;
}


