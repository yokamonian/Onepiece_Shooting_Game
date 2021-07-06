#pragma once
#include "pch.h"

inline void N_anglemove(float *posX, float *posY, float angle, float speed)
{
	angle = -angle;
	(*posX) += cosf(DEGREE_TO_RADIAN(angle))*speed;
	(*posY) += sinf(DEGREE_TO_RADIAN(angle))*speed;
}

inline void N_circle(float *posX, float *posY, float angle, float *holdX, float *holdY)// ������ ��Ƽ� �������� 100��ŭ�� ��ȣ�� �׸��鼭 angle��ŭ �̵��ϴ� �Լ�
{
	(*posX) = *holdX + 100 * cosf(DEGREE_TO_RADIAN(angle));
	(*posY) = *holdY - 100 * sinf(DEGREE_TO_RADIAN(angle));
}

inline void N_poin_point(float *posX, float *posY, float *destposX, float *destposY, float *holdX, float *holdY, float duration)
{
	*posX += (*destposX - *holdX) / duration;
	*posY += (*destposY - *holdY) / duration;
}


