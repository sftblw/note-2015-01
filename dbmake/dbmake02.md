정보 시스템 설계 및 구축 2
==========================

수업전 잠깐 : 예상 수업 범위
============================

-	1부 논리설계
	-	1장 데이터 모델링 주요 개념
		-	엔티티타입, 속성, 식별자, 관계, 엔티티 슈퍼타입과 서브타입, 서브젝트 에어리어, 정규화, ERD 표기법

---

출석 부름

---

1장. 데이터 모델링 개념
=======================

데이터 모델링에 대한 전반적인 개념을 주욱 설명.

과정 : 업무 시스템 구축 흐름 (14p 그림)
---------------------------------------

이번학기동안 하는 게 데이터 모델링 부분.

![](dbmake02-01.JPG)

-	ISP + BPR
-	분석
	-	**데이터 모델링** : 이번학기
	-	프로세스 모델링 : App 쪽
	-	→ (+합쳐서) → CRUD (상관 모델링)

3가지 관점에서의 모델링
-----------------------

-	데이터 관점
	-	업무와 데이터의 관계 : 업무가 어떤 데이터와
	-	데이터 간의 관계
-	프로세스 관점
	-	ex) 영업에는 뭐가 필요한지 뭘 해야하는지
-	상관 관점
	-	? 일처리방법 → 데이터 영향?

데이터 모델링 개요
------------------

### 데이터 모델링이란

(놓침)

`정보화 시스템을 구축하기 위해 어떤 데이터가 존재하는지 또는 업무에 필요한 정보는 무엇인지 분석하는 방법`

### 데이터 모델링 주체

-	참여자
	-	현업 업무전문가
	-	개발자 : SE, BA, DBA **모델러** : 규모가 작은 경우 개발자가 같이 하기도.
-	프로젝트 참여자 모두가 이해하고, **주체**여야.
	-	데이터 모델러만 이해해선 곤란.
	-	많은 경우 모델러만 방치... 곤란.
		-	`당신이 전문가니 당신이 다 만드세요!`
		-	→ 업무자의 의견이 반영되지 않게 됨!, 조직 특화정보가...
		-	모델러가 잘 구슬려서 의견을 들어야.
	-	바뀌는 요구사항과 밀리는 일정에 대해
		-	SI 사업 : 개발자 인건비가 많은 비용.
-	산출물 : ER 다이어그램.
	-	현업자도 이해할 수 있어야. → 현업자에게... 가르쳐야 함...
		-	`말 했으니까 다 끝났어` → 곤란
		-	ERD 이해의 쉬움 : 그리는게 어려운거지, 이해시키는건 크게 어렵지 않다
-	→ **의사소통**

### 데이터 모델링 기본 개념 (18p)

-	뭐 (What) - 엔티티
-	뭐 간의 관계 - 릴레이션..
-	뭐의 성격 - 엔티티의 어트리뷰트

엔티티 타입
-----------

### 엔티티 타입의 개념 : 엔티티 타입=?

여러가지 정의.

![](dbmake02-02.JPG)

-	피터 첸의 정의
	-	현실세계를 컴퓨터로 구현하기 → 기본적인 사고 = **존재론** (온톨로지)
	-	존재론 → 식별
-	요약?
	-	변별할 수 있는 무언가
	-	정보 저장

---

-	→ 정의 → 업무에 필요하고 유용한 정보를 **저장하고 관리하기 위한 것**으로 **영속적으로 존재**하는 단위
-	엔티티 타입 ← 구조적 / 엔티티 ← 인스턴스
-	네모 모양으로 표시
	-	1:多를 표시 : crow-foot 표기법
		-	![](dbmake02-03.png)
	-	일반적인 것 : IDEEIX (IDE Extension) : 多 가 색칠 동그라미 꼴.

---

-	실제 과정은 어떨까?
	-	데이터 모델링 경진대회 같은 게 있음. 업무가 좌악~ 있다 → 이걸 기반으로 따로 분리해내야...
	-	책 처럼 처음부터 "강의실", "과목", "강사" 같이 있는 게 아님.

### 엔티티 타입의 특징

1.	반드시 필요, 관리하려는 정보
	-	Don't over : 현업에서 얘기도 안 했는데 개발자가 오버, 자가발전 하는 경우가 있다 : 엔티티가 될 거 같으면 막 쑤셔넣음 (찔린다...
		-	발주자들은 100 보다 120을 원함, 물론 20을 공짜로 해주길 원하지만, 20이 문제가 생기면 누가 책임을 지는가. (계약 포함?
		-	하지만 아리까리할때도 → 나중에 향후 발전을 고려해야해요! 라고 할 지도 몰라요 → 이런것도 계약 범위에 포함해둬야. (아님 중간에 계약 바꿔야?
2.	유일하게 식별 가능해야 (유일한 식별자로)
	-	식별자가 없다 : 인공적으로 만들기.
	-	중복 존재 X!
	-	식별의 문제상황 : 한 사람이 두 가지 일을 하는 경우? (겸직 : 총무, 재무?)
		-	직원 A 한 명에 대해 직원 A-1 (총무용), 직원 A-2 (재무용) 이 옳은가?
		-	→ 한 엔티티 타입에 넣으면 문제
		-	→ 별도의 엔티티에 분리
3.	집합 : 두 개 이상
	-	테이블 안에 row가 달랑 하나밖에 없는 걸 만들어야 할까? → 의미가 없다.
		-	ex) 회사의 그 회사 테이블, 병원의 그 병원 테이블. (...
4.	이용되어야 : 업무 프로세스(Business Process)가 엔티티 타입을
	-	안 쓰이면 결국 지우게 됨.
	-	업무 분석이 제대로 안 되었다는 반증 (업무 프로세스 모델링 부분이 미진...)
		-	→ 안 쓰이는걸 바로 삭제하는게 아니라, 업무 프로세스 도출이 덜 되거나 잘못된 부분이 있는지 먼저 찾아보고.
	-	insert, delete, update만 하고 select는 안 한다면? -_-;
	-	→ CRUD Matrix (Create, Retrieve, Update, Delete)를 그려야 하는 이유.
5.	속성 (Attribute) 이 있어야, 여럿 있어야.
	-	날씨 테이블 : 흐림, 맑음, 비용, 눈 옴 뿐이라면? **속성이 하나 뿐**이라면?
	-	→ `속성이 하나뿐인 엔티티 타입은 적절하지 않다`
	-	→ 차라리 Domain 의 Constraint를 지정하는 경우로.
	-	예외 : 날씨 가 다양한 값을 가질 수 있는 경우. : 코드 테이블...
		-	`책의 내용은 권장사항이다` → 에외가 있을 수 있음.
		-	`가이드라인을 벗어나는 경우 의심을 할 필요가 있다`
6.	관계가 있어야 (엔티티타입 간의) (한 개 이상의)
	-	하나만 달랑 있으면 무언가 잘못된 것
		-	과도한 엔티티 타입 도출
		-	관계 파악 미진 : 관계 도출을 빠트린 게 아닌가
	-	과도한 관계시 생략하기도 : 코드 테이블
		-	화면이 너무 작다... 관계선을 피해가면서 그리는게 힘들다
			-	잡담 : 제일 좋은 툴은 화이트보드... : 그리고, 사진찍고, Post-it 붙이고.
		-	![](dbmake02-04.JPG)