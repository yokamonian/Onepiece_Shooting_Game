#include "EnemyManager.h"
#include "pch.h"
#include "NormalEnemy_Wapol.h"
#include "NormalEnemy_Shiki.h"
#include "NormalEnemy_Tichi.h"
#include "NormalEnemy_Choppa.h"
#include "NormalEnemy_Franky.h"
#include "Battle.h"
#include "Player.h"
#include "macroFunction.h"

HRESULT EnemyManager::Init()
{
	// 와포루 생성
	NormalWapols.reserve(monsterCount[0]);		// 벡터 공간 할당
	EventCount = 10;
	waveId = 1;

	for (int i = 0; i < EventCount; i++)
	{
		EventTime[i] = 2.5f + 2.5f * (i);
	}

	for (int i = 0; i < monsterCount[0]; i++)
	{
		NormalEnemy_Wapol* wapol = new NormalEnemy_Wapol();		// 와포루 동적할당
		wapol->Init();											// 와포루 초기화
		stNormalWapols.push(wapol);								// 사용중이 아닌 와포루 전부 스택에 push
	}

	// 시키 생성
	NormalShikis.reserve(monsterCount[1]);
	for (int i = 0; i < monsterCount[1]; i++)
	{
		NormalEnemy_Shiki* shiki = new NormalEnemy_Shiki();
		shiki->Init();
		stNormalShikis.push(shiki);
	}
	// 티치 생성
	NormalTichis.reserve(monsterCount[2]);
	for (int i = 0; i < monsterCount[2]; i++)
	{
		NormalEnemy_Tichi* tichi = new NormalEnemy_Tichi();
		tichi->Init();
		stNormalTichis.push(tichi);
	}

	// 프랑키 생성 및 저장
	NormalFrankys.reserve(monsterCount[4]);
	for (int i = 0; i < monsterCount[2]; i++)
	{
		NormalEnemy_Franky* franky = new NormalEnemy_Franky();
		franky->Init();
		stNormalFrankys.push(franky);
	}

	// 쵸파 생성
	NormalChoppa.reserve(monsterCount[3]);
	for (int i = 0; i < monsterCount[3]; i++)
	{
		NormalEnemy_Choppa* choppa = new NormalEnemy_Choppa();
		choppa->Init();
		stNormalChoppa.push(choppa);
	}
	currFrame = 5.0f;

	// 와포루 패턴
	ae0 = new ActionElement(0, 0, 0, 0, 0);
	ae1 = new ActionElement(1, 40.0f, 180.0f, 20.0f, 0.0f, WINSIZE_Y / 2);
	ae5 = new ActionElement(1, 10.0f, 180.0f, 0.0f);
	ae7 = new ActionElement(3, 10.0f, 0.0f, 10.0f, 50.0F,
		WINSIZE_Y / 2);
	ae9_1 = new ActionElement(3, 10.0f, 0.0f, 10.0f, 0.0f, WINSIZE_Y / 2);
	ae9_2 = new ActionElement(2, 20.0f, 120.0f, 10.0f, 0.0f, WINSIZE_Y);

	// 동작 0 없음
	P0.push_back(ae0);
	// 동작 1
	P1.push_back(ae1);
	P5.push_back(ae5);
	P7.push_back(ae7);
	P9.push_back(ae9_1);
	P9.push_back(ae9_2);

	PatternManager::GetSingleton()->AddPattern(P0);  // 0
	PatternManager::GetSingleton()->AddPattern(P1);	 // 1
	PatternManager::GetSingleton()->AddPattern(P5);	 // 2
	PatternManager::GetSingleton()->AddPattern(P7);	 // 3
	PatternManager::GetSingleton()->AddPattern(P9);	 // 4

	// 시키 
	ae3 = new ActionElement(1, 20.0f, 210.0f, 10.0f, 0, WINSIZE_Y / 2);
	ae6 = new ActionElement(1, 20.0f, 180.0f, 10.0f);

	P3.push_back(ae3);
	P6.push_back(ae6);

	PatternManager::GetSingleton()->AddPattern(P3); // 5
	PatternManager::GetSingleton()->AddPattern(P6);	// 6
	// 티치
	ae4 = new ActionElement(1, 20.0f, 180.0f, 22.0f, 200, 0);
	ae8 = new ActionElement(1, 20.0f, 180.0f, 10.0f, 0.0f, WINSIZE_Y / 2);

	P4.push_back(ae4);
	P8.push_back(ae8);

	PatternManager::GetSingleton()->AddPattern(P4);   // 7
	PatternManager::GetSingleton()->AddPattern(P8);	  // 8
	// 프랑키
	ae2 = new ActionElement(1, 20.0f, 180.0f, 10.0f, 0, WINSIZE_Y / 2);
	ae7 = new ActionElement(1, 20.0f, 180.0f, 10.0f, 0.0f, WINSIZE_Y / 2);

	P2.push_back(ae2);
	P7_2.push_back(ae7_2);

	PatternManager::GetSingleton()->AddPattern(P2);   // 9
	PatternManager::GetSingleton()->AddPattern(P7_2);	  // 10
	return S_OK;
}

void EnemyManager::Release()
{
	// 쵸바
	for (auto& it : NormalChoppa)	// 벡터 release
	{
		it->Release();
		SAFE_DELETE(it);
	}
	NormalChoppa.clear();

	for (int i = 0; i < monsterCount[3]; i++)	// 스택 release
	{
		if (stNormalChoppa.size() > 0)
		{
			stNormalChoppa.pop();
			if (stNormalChoppa.empty())
				break;
		}
	}

	// 프랑키
	for (auto& it : NormalFrankys)	// 벡터 release
	{
		it->Release();
		SAFE_DELETE(it);
	}
	NormalFrankys.clear();


	for (int i = 0; i < monsterCount[4]; i++)	// 스택 release
	{
		if (stNormalFrankys.size() > 0)
		{
			stNormalFrankys.pop();
			if (stNormalFrankys.empty())
				break;
		}
	}

	// 티치
	for (auto& it : NormalTichis)	// 벡터 release
	{
		it->Release();
		SAFE_DELETE(it);
	}
	NormalTichis.clear();

	for (int i = 0; i < monsterCount[2]; i++)	// 스택 release
	{
		if (stNormalTichis.size() > 0)
		{
			stNormalTichis.pop();
			if (stNormalTichis.empty())
				break;
		}
	}


	// 시키
	for (auto& it : NormalShikis)	// 벡터 release
	{
		it->Release();
		SAFE_DELETE(it);
	}
	NormalShikis.clear();

	for (int i = 0; i < monsterCount[1]; i++)	// 스택 release
	{
		if (stNormalShikis.size() > 0)
		{
			stNormalShikis.pop();
			if (stNormalShikis.empty())
				break;
		}
	}

	// 와포루
	for (auto& it : NormalWapols)	// 벡터 release
	{
		it->Release();
		SAFE_DELETE(it);
	}
	NormalWapols.clear();

	for (int i = 0; i < monsterCount[0]; i++)	// 스택 release
	{
		if (stNormalWapols.size() > 0)
		{
			stNormalWapols.pop();
			if (stNormalWapols.empty())
				break;
		}
	}
}

void EnemyManager::Update()
{
	for (auto& it : NormalWapols)	// 벡터에 있는 매개변수(begin ~ end까지)
	{
		//it->SetAngle(TwoPointAngle(it->GetPos().x, it->GetPos().y, playerPos.x, playerPos.y)); // 와포루가 계속 쫓아가게하는 코드
		it->SetPlayerPos(playerPos);
		it->Update();				// 업데이트

		if (RectangleWithCircle(it->GetPos().x, it->GetPos().y, 50, Battle::instance->GetPlayer()->GetSkillRect()) )
		{
			it->SetLife(0);
		}
	}
	for (auto& it : NormalShikis)	// 벡터에 있는 매개변수(begin ~ end까지)
	{
		//it->SetAngle(TwoPointAngle(it->GetPos().x, it->GetPos().y, playerPos.x, playerPos.y)); // 와포루가 계속 쫓아가게하는 코드
		it->SetPlayerPos(playerPos);
		it->Update();				// 업데이트

		if (RectangleWithCircle(it->GetPos().x, it->GetPos().y, 50, Battle::instance->GetPlayer()->GetSkillRect()))
		{
			it->SetLife(0);
		}
	}
	for (auto& it : NormalTichis)	// 벡터에 있는 매개변수(begin ~ end까지)
	{
		//it->SetAngle(TwoPointAngle(it->GetPos().x, it->GetPos().y, playerPos.x, playerPos.y)); // 와포루가 계속 쫓아가게하는 코드
		it->SetPlayerPos(playerPos);
		it->Update();				// 업데이트

		if (RectangleWithCircle(it->GetPos().x, it->GetPos().y, 50, Battle::instance->GetPlayer()->GetSkillRect()))
		{
			it->SetLife(0);
		}
	}
	for (auto& it : NormalFrankys)	// 벡터에 있는 매개변수(begin ~ end까지)
	{
		//it->SetAngle(TwoPointAngle(it->GetPos().x, it->GetPos().y, playerPos.x, playerPos.y)); // 와포루가 계속 쫓아가게하는 코드
		it->SetPlayerPos(playerPos);
		it->Update();				// 업데이트

		if (RectangleWithCircle(it->GetPos().x, it->GetPos().y, 50, Battle::instance->GetPlayer()->GetSkillRect()))
		{
			it->SetLife(0);
		}
	}
	for (auto& it : NormalChoppa)	// 벡터에 있는 매개변수(begin ~ end까지)
	{
		//it->SetAngle(TwoPointAngle(it->GetPos().x, it->GetPos().y, playerPos.x, playerPos.y)); // 와포루가 계속 쫓아가게하는 코드
		it->SetPlayerPos(playerPos);
		it->Update();				// 업데이트

		if (RectangleWithCircle(it->GetPos().x, it->GetPos().y, 50, Battle::instance->GetPlayer()->GetSkillRect()))
		{
			it->SetLife(0);
		}
	}

	if (isWaveTime(EventTime[0], 0, 5)) // 웨이브 시간 조건 비교(참 리턴시 실행), 캐릭터id와 마리수 저장 함수
	{
		if (waveId == 1)
		{
			for (int j = 0; j < monsterTypeCount; j++) // 위의 매개면수로 저장된 monsterTypeCount값(4)
			{
				for (int i = 0; i < waveMonsterCount[j]; i++)
				{
					SetUp(enemyNum[j], 1300.0f + (250 * i), 200.0f);								// 오브젝트 풀링(스택 >> 벡터)

					SetWaveCount(enemyNum[0], 1);					// 웨이브 번호 전달
				}
			}
			waveId++;
		}
	}

	if (isWaveTime(EventTime[1], 3, 8)) // 웨이브 시간 조건 비교(참 리턴시 실행), 캐릭터id와 마리수 저장 함수
	{
		if (waveId == 2)
		{
			for (int j = 0; j < monsterTypeCount; j++) // 위의 매개면수로 저장된 monsterTypeCount값(4)
			{
				for (int i = 0; i < waveMonsterCount[j]; i++)
				{
					SetUp(enemyNum[j], 1300.0f + (100 * i), 100.0f + (150 * i));								// 오브젝트 풀링(스택 >> 벡터)

					SetWaveCount(enemyNum[0], 2);					// 웨이브 번호 전달
				}
			}
			waveId++;
		}
	}

	if (isWaveTime(EventTime[2], 1, 5)) // 웨이브 시간 조건 비교(참 리턴시 실행), 캐릭터id와 마리수 저장 함수
	{
		if (waveId == 3)
		{
			for (int j = 0; j < monsterTypeCount; j++) // 위의 매개면수로 저장된 monsterTypeCount값(4)
			{
				for (int i = 0; i < waveMonsterCount[j]; i++)
				{
					SetUp(enemyNum[j], 1300.0f, 50.0f + (100 * i));								// 오브젝트 풀링(스택 >> 벡터)

					SetWaveCount(enemyNum[0], 3);					// 웨이브 번호 전달
				}
			}
			waveId++;
		}
	}

	if (isWaveTime(EventTime[3], 2, 5)) // 웨이브 시간 조건 비교(참 리턴시 실행), 캐릭터id와 마리수 저장 함수
	{
		if (waveId == 4)
		{
			for (int j = 0; j < monsterTypeCount; j++) // 위의 매개면수로 저장된 monsterTypeCount값(4)
			{
				for (int i = 0; i < waveMonsterCount[j]; i++)
				{
					SetUp(enemyNum[j], 1300.0f, 100.0f + (100 * i));								// 오브젝트 풀링(스택 >> 벡터)

					SetWaveCount(enemyNum[0], 4);					// 웨이브 번호 전달
				}
			}
			waveId++;
		}
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (auto& it : NormalWapols)
	{
		it->Render(hdc);			// 벡터 실행문
	}

	for (auto& it : NormalShikis)
	{
		it->Render(hdc);			// 벡터 실행문
	}

	for (auto& it : NormalTichis)
	{
		it->Render(hdc);			// 벡터 실행문
	}

	for (auto& it : NormalFrankys)
	{
		it->Render(hdc);			// 벡터 실행문
	}

	for (auto& it : NormalChoppa)
	{
		it->Render(hdc);			// 벡터 실행문
	}

}

bool EnemyManager::Onhit(FPOINT pos)
{
	for (NW_iter = NormalWapols.begin(); NW_iter != NormalWapols.end(); NW_iter++)
	{
		if ((*NW_iter)->OnHit(pos))
		{
			NormalEnemy_Wapol* Wapol;
			(*NW_iter)->SetDamaged(true);
			//Wapol = NormalWapols.back();
			//NormalWapols.pop_back();
			//stNormalWapols.push(Wapol);
			return true;
		}
	}

	for (NS_iter = NormalShikis.begin(); NS_iter != NormalShikis.end(); NS_iter++)
	{
		if ((*NS_iter)->OnHit(pos))
		{
			NormalEnemy_Shiki* Shiki;
			(*NS_iter)->SetDamaged(true);
			/*Shiki = NormalShikis.back();
			NormalShikis.pop_back();
			stNormalShikis.push(Shiki);*/
			return true;
		}
	}

	for (NT_iter = NormalTichis.begin(); NT_iter != NormalTichis.end(); NT_iter++)
	{
		if ((*NT_iter)->OnHit(pos))
		{
			NormalEnemy_Tichi* Tichi;
			(*NT_iter)->SetDamaged(true);
			/*	Tichi = NormalTichis.back();
				NormalTichis.pop_back();
				stNormalTichis.push(Tichi);*/
			return true;
		}
	}

	for (NF_iter = NormalFrankys.begin(); NF_iter != NormalFrankys.end(); NF_iter++)
	{
		if ((*NF_iter)->OnHit(pos))
		{
			NormalEnemy_Franky* Franky;
			(*NF_iter)->SetDamaged(true);
			/*	Franky = NormalFrankys.back();
				NormalFrankys.pop_back();
				stNormalFrankys.push(Franky);*/
			return true;
		}
	}

	for (NC_iter = NormalChoppa.begin(); NC_iter != NormalChoppa.end(); NC_iter++)
	{
		if ((*NC_iter)->OnHit(pos))
		{
			NormalEnemy_Choppa* Choppa;
			(*NC_iter)->SetDamaged(true);
			Choppa = NormalChoppa.back();
			NormalChoppa.pop_back();
			stNormalChoppa.push(Choppa);
			return true;
		}
	}
	return false;
}

void EnemyManager::SetUp(int EnemyNum, float posX, float posY) // 오브젝트 풀링(스택 >> 벡터)
{
	switch (EnemyNum)
	{
	case 0:
		NormalEnemy_Wapol* Wapols;			// 임시 변수
		if (!stNormalWapols.empty())		// 스택안에 데이터가 있을때 실행
		{
			Wapols = stNormalWapols.top();	// 스택의 맨 첫 인자를 반환
			stNormalWapols.pop();			// 스택의 첫 인자를 삭제

			NormalWapols.push_back(Wapols); // 벡터에 저장

			Wapols->SetPos(posX, posY);
		}
		break;
	case 1:
		NormalEnemy_Shiki* Shikis;
		if (!stNormalShikis.empty())
		{
			Shikis = stNormalShikis.top();
			stNormalShikis.pop();

			NormalShikis.push_back(Shikis);
			Shikis->SetPos(posX, posY);
		}
		break;
	case 2:
		NormalEnemy_Tichi* Tichis;
		if (!stNormalTichis.empty())
		{
			Tichis = stNormalTichis.top();
			stNormalTichis.pop();

			NormalTichis.push_back(Tichis);
			Tichis->SetPos(posX, posY);
		}
		break;
	case 3:
		NormalEnemy_Franky* Frankys;
		if (!stNormalFrankys.empty())
		{
			Frankys = stNormalFrankys.top();
			stNormalFrankys.pop();

			NormalFrankys.push_back(Frankys);
			Frankys->SetPos(posX, posY);
		}
		break;
	case 4:
		NormalEnemy_Choppa* Choppa;
		if (!stNormalChoppa.empty())
		{
			Choppa = stNormalChoppa.top();
			stNormalChoppa.pop();

			NormalChoppa.push_back(Choppa);
			Choppa->SetPos(posX, posY);
		}
		//NormalEnemy* Choppa;
		break;
	}

}

void EnemyManager::SetWaveCount(int enemyNum, int waveNum)	// 웨이브 번호 전송
{
	switch (enemyNum)
	{
	case 0:
		for (auto& it : NormalWapols)
			it->SetWaveId(waveNum);
		break;
	case 1:
		for (auto& it : NormalShikis)
			it->SetWaveId(waveNum);
		break;
	case 2:
		for (auto& it : NormalTichis)
			it->SetWaveId(waveNum);
		break;
	case 3:
		for (auto& it : NormalFrankys)
			it->SetWaveId(waveNum);
		break;
	case 4:
		for (auto& it : NormalChoppa)
			it->SetWaveId(waveNum);
		break;
	}
}

// 웨이브에서 출현하는 몬스터의 종류가 하나일때 조건문 및 세팅
bool EnemyManager::isWaveTime(float EventTime, int _EnemyNum0, int _EnemyCount0)
{
	if (TimeManager::GetSingleton()->GetWorldCount() >= EventTime)
	{
		enemyNum[0] = _EnemyNum0;
		waveMonsterCount[0] = _EnemyCount0;
		monsterTypeCount = 1;
		return true;
	}
	return false;
}

// 웨이브에서 출현하는 ~ 종류가 둘일때 ~
bool EnemyManager::isWaveTime(float EventTime, int _EnemyNum0, int _EnemyCount0, int _EnemyNum1, int _EnemyCount1)
{
	if (TimeManager::GetSingleton()->GetWorldCount() >= EventTime)
	{
		enemyNum[0] = _EnemyNum0;
		enemyNum[1] = _EnemyNum1;
		waveMonsterCount[0] = _EnemyCount0;
		waveMonsterCount[1] = _EnemyCount1;
		monsterTypeCount = 2;
		return true;
	}
	return false;
}

// 웨이브에서 출현하는 ~종류가 셋일 때 ~
bool EnemyManager::isWaveTime(float EventTime, int _EnemyNum0, int _EnemyCount0, int _EnemyNum1, int _EnemyCount1,
	int _EnemyNum2, int _EnemyCount2)
{
	if (TimeManager::GetSingleton()->GetWorldCount() >= EventTime)
	{
		enemyNum[0] = _EnemyNum0;
		enemyNum[1] = _EnemyNum1;
		enemyNum[2] = _EnemyNum2;
		waveMonsterCount[0] = _EnemyCount0;
		waveMonsterCount[1] = _EnemyCount1;
		waveMonsterCount[2] = _EnemyCount2;
		monsterTypeCount = 3;
		return true;
	}
	return false;
}