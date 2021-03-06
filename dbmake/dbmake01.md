정보시스템설계및구축
====================

-	강의소개

강의안내
--------

-	과목명 : 정보시스템 설계 및 구축
-	목표 : **데이터베이스 모델링** 능력 함양
-	마지막 3주는 과제 : 텀프로젝트
	-	12, 13, 14주차 Team Projec 수행 결과 발표
	-	2인 1조
	-	Entity가 20개 이상 도출될 수 있는 업무를 대상으로
-	평가
	-	중간 30 기말 30 과제 30 출석 10
-	교재 : 데이터베이스 설계와 구축 (성능까지 고려한 데이터 모델링)
	-	DB 설계 관련 책이 적당한 게 잘 없음

주별 진도계획
-------------

-	개요
	-	정보시스템을 설계, 구축하는 일은 매우 큰 일이다 : 학교 예) 작게잡아도 1년 반 (100억 이상)
	-	근간이 되는 것 : DB : 많은 경우에 대강 만든다
-	정보시스템 제작 절차

	1.	ISP / BPR : Information Stratege Planning / Business Process Engineering...
		-	컨설팅 회사에서.
		-	BPR : 기존의 업무 구조 재정의?
		-	전체의 10% 정도의 비용
		-	대부분의 상황에서는 이 과정을 제외 -> *달라진 게 뭔데?*
		-	속도야 반년만에 다시 늦어짐
	2.	ER Modeling / 정규화, 역정규화, 칼
		-	엔티티가 뭐냐 등
		-	정보시스템 내부에 있는것들, 그리고 그 관계
		-	전체 프로젝트 비용의 40%, 4명 정도
		-	ER 모델링 -> ER 다이어그램
	3.	DB 구축
	4.	Application 개발
		-	80명 정도
		-	테이블 대충 만들며 개발 -> 억지로 ERD 만들기 : ......
	5.	검수
	6.	100% 비용
		-	유지보수에는 대충 10% 닮
	7.	시행

-	-> DB 가 아무데도 남아있지 않게 될 수도.

---

-	토마토시스템 eXERD 를 실습실에 설치해놓을 예정
	-	documentation 기능이 많이 있음
		-	나중에 운영, 관리하기 위한 목적
	-	40 copy : 521호

---

진도 계획
---------

1.	1주 : 데이터 모델링 주요 개념
	-	1970년대에 나온 이야기.
	-	관계, 슈퍼타입, 서브타입, 서브젝트 에어리어, 정규화, ERD 표기법 ...
	-	누구나 다 그릴 수 있다, 하지만 모자른 나머지 30점을 채우는 건 누구나 할 수 없다
2.	2주 : 데이터 분석 및 모델링
	-	어떻게 타입, 관계를 뽑아낼 것인가
	-	식별자 (Key)를 어떻게 정의
	-	**어떻게 도출**해낼 것인가
	-	책 : 여러 사례들에 대한 권고 : 정답이 따로 없다
3.	실전 데이터 모델링 이슈
	-	M:N 관계 : 냅둘래, 합칠래? : 별도 관계 테이블을 만든다던가
	-	1:1 관계 : 해소 방법 : 냅둘래, 합칠래?
	-	코드 데이터 : 시리얼 넘버 같은 거? : 데이터 접근 시 굉장히 중요한 정보
	-	도미노 속성, 메시지 엔티티, 이력 엔티티 : (입출금 등의) 히스토리를 모아서 관리하면!
4.	프로세스, 상관 모델링
	-	어플리케이션 = 프로세스 : 어떻게 하나의 독립된 작업(프로세스)을 도출해낼 것인가
	-	각각의 프로세스와 각각의 데이터들 간의 연관관계 : CRUD Matrix (Create, Retrieve, Update, Delete) 상관 모델링
		-	권한 표 느낌. : 개발자가 만들면서 어디에서 어떻게 가능할지 고려
	-	단위시스템 : 커밋의 기준 : 어떻게 단위시스템의 기준을 알 것인가
	-	프로그래머가 직접 파악하면 안 되는데 많은 경우 이렇게 함!
	-	ex) 송금 = 인출 + 출금 -> 하나의 트랜젝션이 둘로 나뉘어지면 -> ㅇㅁㅇ -> 시스템 디자이너가 정한다
	-	단위프로세스의 도출, 데이터...
5.	5주 : 모델 검토
	-	혹시 잘못된 게 없나
6.	6주 : DB 구축 준비
	-	ER 모델링의 산출물과 관계형 DB가 너무나도 궁합이 잘 맞음
		-	자동으로 테이블을 만들어낼 정도
	-	ERD : 이해하기가 쉬움
	-	이야기하면서 ERD를 그려나감.현애
	-	피드백이
	-	두 가지 : 표?
	-	반 정규화 등
7.	7주 : 중간시험
8.	8주 : 성능 데이터 모델링
	-	성능 관련
	-	2개 이상으로 p.key를 잡은 경우, A, B? B, ? , 칼
9.	데이터베이스 튜닝, 데이터 마이닝 등의 고급 주제 : 못 할 가능성이 높음
10.	11주 : ER Modeling Tool : 사용법 소개
11.	12주 이후 ~ 14주 : 프로젝트
	-	엔티티 갯수 : 한 20개 이상은 나와야
		-	대상 어플리케이션을 정해야 (ex : 회사, 우리 학교, 보험회사, 건강검진센터 등)
		-	상상을 할 수도 있다.
		-	우리학교는 200개 정도의 테이블.
		-	엔티티를 많이 도출할 수 있는 대상을 생각해보기!
