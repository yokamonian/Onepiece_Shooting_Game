# 원피스 슈팅 게임(Onepiece_Shooting_Game)

## Title : 정상대전

> ####  장르 : 횡스크롤 슈팅
> ####  개발 : 3인
> ####  플렛폼 : PC
> ####  사용 프로그램 : WinAPI, Visual C++
> ####  제작 기간 : 20.05.26 ~ 20.06.02 제작(21.07.25 코드 수정 및 깃허브 커밋)
> ####  간단 설명 : 원피스 리소스를 활용한 횡스크롤 비행 슈팅 게임

## 기능 구현 및 클래스 설명

> + 기능 구현
>   + 컨트롤(Control)
>     + ```이동 및 공격(선택)```
>     + ```캐릭 별 스킬 구현(회피 및 특수기)```
>     + ~~엘리트 유닛, 보스 유닛 패턴 구현(팀원 구현)~~
>     + ~~파워업 아이템 구현(미사일 발사 갯수 증가)(팀원 구현)~~
>   + 캐릭터 선택(3종의 플레이어블 캐릭터 및 캐릭터 선택창 구현)
>   + 씬 매니저
>     + ~~오프닝 씬 ~ 클리어 씬 까지 구현(팀원 구현)~~.
>   + 패턴 매니저
>     + ```각종 패턴 제작을 위한 이동 함수 구현```
>     + ```패턴 매니저를 통하여 탄막류 슈팅 게임에 활용 가능한 이동 패턴을 저장.(웨이브 및 프레임 간 이동 함수들을 저장)```
>   + 기타
>     + ```오브젝트 풀링 패턴을 활용하여 리소스 절약```

## 프로젝트 구조
 + 시스템 디자인(UML)
 ![Onepiece](https://user-images.githubusercontent.com/63716789/129311736-03fcf063-f347-4262-be90-f637ad1f4794.png)
 + 중요코드
  + 오브젝트 풀(ObjectPool) 패턴
  + 
