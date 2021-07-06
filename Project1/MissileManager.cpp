#include "MissileManager.h"
#include "Missile.h"
#include "Battle.h"
#include "Object.h"
#include "EnemyManager.h"
#include "PlayerMissile.h"
#include "EnemyMissile.h"
#include "Player.h"
#include "BossEnemy.h"
#include "EliteEnemy.h"
#include "macroFunction.h"

HRESULT MissileManager::Init(bool isEnemy)
{
	if (!isEnemy)
	{
		vecPlayerMissiles.reserve(100);
		for (int i = 0; i < 100; i++)
		{
			PlayerMissile* P_missile = new PlayerMissile();
			P_missile->Init();
			StP_Missiles.push(P_missile);
		}
	}
	else
	{
		vecEnemyMissiles.reserve(200);
		for (int i = 0; i < 200; i++)
		{
			EnemyMissile* E_missile = new EnemyMissile();
			E_missile->Init();
			StE_Missiles.push(E_missile);
		}
	}
	
	object = nullptr;

	RandAngle = rand() % 10;
	return S_OK;
}

void MissileManager::Release(bool isEnemy)
{
	if (!isEnemy)
	{
		for (auto& it : vecPlayerMissiles)
		{
			it->Release();
			SAFE_DELETE(it);
		}
		vecPlayerMissiles.clear();

		for (int i = 0; i < 100; i++)
		{
			if (StP_Missiles.size() > 0)
			{
				StP_Missiles.pop();
				if (StP_Missiles.empty())
					break;
			}
		}
	}
	else
	{
		for (auto& it : vecEnemyMissiles)
		{
			it->Release();
			SAFE_DELETE(it);
		}
		vecEnemyMissiles.clear();

		for (int i = 0; i < 200; i++)
		{
			if (StE_Missiles.size() > 0)
			{
				StE_Missiles.pop();
				if (StE_Missiles.empty())
					break;
			}
		}
	}
}

void MissileManager::Update()
{
	// 플레이어의 미사일 vs Enemy.
	if ((vecPlayerMissiles.size()) > 0)
	{
		for (vector<PlayerMissile*>::iterator p = vecPlayerMissiles.begin(); p != vecPlayerMissiles.end(); p++)
		{
			(*p)->Update();

			//플레이어의 미사일이 WINSIZE를 넘어가는 경우. ( +,- 100은 여유를 위해 설정. )
 			if ((*p)->GetPos().x >= WINSIZE_X + 100 || (*p)->GetPos().y <= 0 - 100 || (*p)->GetPos().y >= WINSIZE_Y + 100)
			{
				(*p)->SetIsFire(false);
				StP_Missiles.push((*p));
				p = vecPlayerMissiles.erase(p);
				if (p == vecPlayerMissiles.end())
					break;
			}
			
			//엘리트 에너미와 플레이어 미사일과의 충돌
			else if ( (Battle::instance->GetEliteEnemy()->GetLife() > 0) &&
				RectangleWithCircle( (*p)->GetPos().x, (*p)->GetPos().y, (*p)->GetRadius(),
				Battle::instance->GetEliteEnemy()->GetHitBox() ))
			{
				if( !(Battle::instance->GetEliteEnemy()->GetEliteEnemyState() == EliteEnemyState::PATTERN3) )
					Battle::instance->GetEliteEnemy()->SetLife(
						Battle::instance->GetEliteEnemy()->GetLife() - 3
					);

				(*p)->SetIsFire(false);
				StP_Missiles.push((*p));
				p = vecPlayerMissiles.erase(p);
				if (p == vecPlayerMissiles.end())
					break;
			}

			//보스와 플레이어 미사일과의 충돌
			else if ( (Battle::instance->GetBossEnemy()->GetLife() > 0 ) &&
				(Battle::instance->GetBossEnemy()->GetBossEnemyState() != BossEnemyState::PATTERN3) &&
				(Battle::instance->GetBossEnemy()->GetBossEnemyState() != BossEnemyState::PATTERN2) &&
				RectangleWithCircle((*p)->GetPos().x, (*p)->GetPos().y, (*p)->GetRadius(),
				Battle::instance->GetBossEnemy()->GetHitBox()))
			{
				Battle::instance->GetBossEnemy()->SetLife(
					Battle::instance->GetBossEnemy()->GetLife() - 1
				);

				(*p)->SetIsFire(false);
				StP_Missiles.push((*p));
				p = vecPlayerMissiles.erase(p);
				if (p == vecPlayerMissiles.end())
					break;
			}


			// * * * * * 아래 두 개는 위에서 처리해주는거라 주석 처리 했습니다! * * * * * //

			// 엘리트 에너미와 충돌하는 코드
			//if (Battle::instance->GetEliteEnemy()->Onhit((*p)->GetPos()))
			//{
			//	Battle::instance->GetEliteEnemy()->SetLife(
			//		Battle::instance->GetEliteEnemy()->GetLife() - 10
			//	);
			//}

			// 보스와 충돌하는 코드
			//if (Battle::instance->GetBossEnemy()->Onhit((*p)->GetPos()))
			//{
			//	//보스의 체력을 깎는 코드
			//	Battle::instance->GetBossEnemy()->SetLife(
			//		Battle::instance->GetBossEnemy()->GetLife() - 10
			//	);
			//}


			// * * * * * 아래 코드는 주석 다음 껄로 대체 했습니다! * * * * * //
			
			//if ((*p)->GetPos().x >= WINSIZE_X + 100 || (*p)->GetPos().y <= 0 - 100 || (*p)->GetPos().y >= WINSIZE_Y + 100
			//	|| Battle::instance->GetEnemyMgr()->Onhit((*p)->GetPos()) || 
			//	(Battle::instance->GetBossEnemy()->Onhit((*p)->GetPos()) && !(Battle::instance->GetBossEnemy()->GetLife() <= 0)) ||
			//	(Battle::instance->GetEliteEnemy()->Onhit((*p)->GetPos()) && !(Battle::instance->GetEliteEnemy()->GetLife() <= 0)))
			//{
			//	if ( Battle::instance->GetEliteEnemy()->Onhit((*p)->GetPos()) )
			//	{
			//		Battle::instance->GetEliteEnemy()->SetLife(
			//			Battle::instance->GetEliteEnemy()->GetLife() - 10
			//		);
			//	}

			//	if (Battle::instance->GetBossEnemy()->Onhit((*p)->GetPos()))
			//	{
			//		//보스의 체력을 깎는 코드
			//		Battle::instance->GetBossEnemy()->SetLife( 
			//			Battle::instance->GetBossEnemy()->GetLife()-10
			//		);
			//	}

			//	(*p)->SetIsFire(false);
			//	StP_Missiles.push((*p));
			//	p = vecPlayerMissiles.erase(p);
			//	if (p == vecPlayerMissiles.end())
			//		break;
			//}

			else if (Battle::instance->GetEnemyMgr()->Onhit((*p)->GetPos()))
			{
				(*p)->SetIsFire(false);
				StP_Missiles.push((*p));
				p = vecPlayerMissiles.erase(p);
				if (p == vecPlayerMissiles.end())
					break;
			}
		}
	}

	// 에너미 미사일 vs Player Circle 충돌
	if ((vecEnemyMissiles.size()) > 0)
	{
		for (vector<EnemyMissile*>::iterator e = vecEnemyMissiles.begin(); e != vecEnemyMissiles.end(); e++)
		{
			(*e)->Update();
			
			if ((Battle::instance->GetPlayer()->GetPlayerState() != PlayerState::AVOID) && Battle::instance->GetPlayer()->Onhit((*e)->GetPos()) )
			{
				(*e)->SetIsFire(false);
				StE_Missiles.push((*e));
				e = vecEnemyMissiles.erase(e);
				if (e == vecEnemyMissiles.end())
					break;
			}
			else if ((*e)->GetIsAceSecondAttack() == true)
			{
				if ((*e)->GetPos().y + 40 >= WINSIZE_Y)
				{
					//충돌이 일어났음을 전해주자.
					if ((*e)->GetIsFloorCollision() == false)
					{
						(*e)->SetEffectPos((*e)->GetPos());
						(*e)->SetIsFloorCollision(true);
					}
					/*(*e)->SetIsFire(false);
					StE_Missiles.push((*e));
					e = vecEnemyMissiles.erase(e);
					if (e == vecEnemyMissiles.end())
						break;*/
				}

			}

			else if ( ((*e)->GetPos().x <= 0 - 100 || (*e)->GetPos().x >= WINSIZE_X + 100 || (*e)->GetPos().y <= 0 - 100 || (*e)->GetPos().y >= WINSIZE_Y) ) 
			{
				(*e)->SetIsFire(false);
				StE_Missiles.push((*e));
				e = vecEnemyMissiles.erase(e);
				if (e == vecEnemyMissiles.end())
					break;
			} //적 미사일과 플레이어의 스킬 렉트가 충돌했을 경우
			else if ( (Battle::instance->GetPlayer()->GetSkillOn() == true) && 
				RectangleWithCircle((*e)->GetPos().x, (*e)->GetPos().y, (*e)->GetRadius(), 
					Battle::instance->GetPlayer()->GetSkillRect()) )
			{
				(*e)->SetIsFire(false);
				StE_Missiles.push((*e));
				e = vecEnemyMissiles.erase(e);
				if (e == vecEnemyMissiles.end())
					break;
			}
		}
	}
}

void MissileManager::Render(HDC hdc)
{
	if ((vecEnemyMissiles.size()) > 0)
	{
		for (auto& it : vecEnemyMissiles)
		{
			it->Render(hdc);
		}
	}

	if ((vecPlayerMissiles.size()) > 0)
	{
		for (auto& it : vecPlayerMissiles)
		{
			it->Render(hdc);
		}
	}
}

bool MissileManager::Fire(float posX, float posY, float angle)
{
	EnemyMissile* E_Bullet;
	PlayerMissile* P_Bullet;

	if (isEnemy)
	{
		if (StE_Missiles.size() > 0)
		{
			E_Bullet = StE_Missiles.top();
			StE_Missiles.pop();
			vecEnemyMissiles.push_back(E_Bullet);
			for (auto& it : vecEnemyMissiles)
			{
				if (it->GetIsFire())
				{
					continue;
				}

				//it->SetIsBoss(isBoss);
				it->SetAngle(DEGREE_TO_RADIAN(angle));
				if (isBoss == true)
				{
					it->SetisAceSecondAttack(isAceSecondAttack);
					it->SetMissileType(0);
				}
				else
					it->SetMissileType(1);
				it->SetSpeed(speed);
				it->SetIsFire(true);
				it->SetPos(posX, posY);
			}
		}
	}
	else if(!isEnemy)
	{
		if (StP_Missiles.size() > 0)
		{
			P_Bullet = StP_Missiles.top();
			StP_Missiles.pop();
			vecPlayerMissiles.push_back(P_Bullet);
			for (auto& it : vecPlayerMissiles) //////// 사이즈가 0/
			{
				if (it->GetIsFire())
				{
					continue;
				}

				it->SetMissileType(charNum);
				it->SetAngle(DEGREE_TO_RADIAN(angle));
				it->SetIsFire(true);
				it->SetPos(posX, posY);
			}
		}
		
	}
	return true;
}



MissileManager::MissileManager()
{
}


MissileManager::~MissileManager()
{
}
