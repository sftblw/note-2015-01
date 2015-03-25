프로젝트 실무 3
===============

-	참여형 수업
	-	교재를 준비하지 않는 이유
	-	준비 좀 해와라
	-	참여형 수업이 없다고 불평하면서 정작 참여는 안 하는 문제
		-	제 생각엔 이거 교육과정의 문제입니다만?

The Plan
========

오늘 할 일
----------

-	각자 작품 계획 발표
	-	작품 내용, 방법에 대해 토의 **→ 수정**
	-	프레젠테이션 방법 훈련

강의 날짜 조정 및 계획
----------------------

-	27일 : 특강 (북악관)
-	4월 1일 (수) : 오전 9시
	-	시장, 기업조사, 기술 조사를 어떻게 할 것인지
-	이 후
	-	기술 자문
	-	작품 진단 → 중간고사 대신
-	시험에 관해
	-	발표평가, 출결로 대신.
	-	시험은 없지만 *적극적 참여*가 중요
	-	> 여러분 주도로 하는 과목이다

잡담
----

강의 시간을 아예 30분 당겨버리는건 어떤지? (10시부터 12시 반 까지) → 그렇게 하기로

이광엽 교수님은 이 과목 자체에 긍정적인 듯 하게 보이심. 학생의 참여를 촉구하면서 과목을 살리는 방향으로 말하심. 실험적인 과목이라고.

발표
====

발표 1 : Travel Story 앱
------------------------

### 왜, 개요

-	IoT, 앱, 삶의 질적 향상... 뭔 개소리여
-	20대 대상 여행 정보 공유 사이트

### 사전조사

-	위시빈 (WishBeen)
	-	단점
		-	정보가 너무 많다
		-	입력할게 너무 많다
	-	→ 단순하게

### 구현 내용

-	어플리케이션, 웹. 1:1 분할
-	앱
	-	여행스토리
	-	지출
	-	메모
	-	지도 → GPS로 다녀온 곳 표시 (? 구글 나우?)
-	웹
	-	간편한 검색
		-	구글처럼 간단한 검색 (→ 검색이 간단하게 보이시나? 사실 기본적인 건 간단하긴 합니다.)
		-	타 사이트 검색결과도 한꺼번에 포함
	-	정보 마켓
		-	정보에 돈을 내고 구매하는 방식 (? 뭐?)

### 구성도 및 계획

-	시스템 구성도
-	계획 (뭔가 있어보였음)

### 기대효과와 예상효과

-	뭔가 주저리 라는 느낌. 많은데 이해가 안 됨 (여행을 다녀본적이 잘 없는 1人)

톰캣을 사용한다고 했음.

---

### 교수님 발언타임!

#### 사실 질문 안 한다고 한 소리 하시는겁니다.

```
-   지난시간 중국사람 : 질문을 많이 한다 (낯짝이 두껍다) : 질문을 끝도 없이 함
    -   배워야 할 듯.
    -   오불관언 : 나 아니면 다른 사람들은 신경 안 쓴다
    -   주변을 살펴보지 않다보니 불법적인 일도 어느정도 서슴없이 함 → **기술을 많이 가져감!**
-   일본은 반대 : 완전히 국가, 사회중심 : 개인이 없다
    -   우리나라는 IS? 지원한 사람에 대한 국가 탓, 가족이 죄송하다......
    -   → 일본은 개인이 없다 : 사회나가면 말이 없다
    -   다만 숨어서 굉장히 많은 활동, 전문적이다 : 드러나지 않음, 질문도 안 함
-   우리나라는 사회성이 중간에 있는 듯
    -   자기중심적이면서 국가도 생각함
    -   남 탓을 많이 하는 사회
-   결론
-   우리 적극성을 좀 배워야할듯
-   일본처럼 조용히 있단 살아나갈 수 없다
```

#### 앱과 웹의 연동

-	많이 쓰이면서도 작품에서 흔함
-	작품 당일날 보면 *연동이 잘 **안 됨***, *연동의 **의미가 없는** 경우*가 많음
	-	→ 회원 관리 정도로 끝나는 경우가 많음.
-	웹 : 데이터베이스 구축. → 앱으로 구축
-	앱 : 정보 취득 → DB → 필요한 정보 보여줌
-	작품 != 상품 : 작품은 상품처럼 만들 필요는 없다
	-	디테일한 DB X : 회원관리 한다고 1000명 쑤셔박을 필요는 없음
	-	노가다 X : 디자인 고생할 필요는 없음, 이런 건 무의미
	-	작품 == 아이디어
	-	Key Technology : 한 번 정도만 보여주면 됨

#### 디테일한 비평

-	노가다 X : 국가별로 하지 말고 국내 정보만 하면 좋겠다
-	실제로 여름방학때 다녀보기
	-	여행 정보 출력
		-	실질적 어려움 : 기차시간표 같은 게 아니라 시외버스 시간표 등 (계절별로도 버스 시간표가 다르다)
	-	평가 출력
	-	이정도만 해도 작품이 아니겠느냐
-	> 크 ~ 은 서버를 ~ 구축하는 건 의미가 없어 : 그건 웹과 앱이 아니지
-	웹은 업데이트가 느리다 : 앱은 실시간 정보 취득
-	핵심 3박자
	-	정보 취득
	-	앱 → 필요한 정보
	-	를 실시간으로
-	제안이다.

#### 발표의 서론에 대해.

-	IoT 시대를 맞이하여 라는 부분
	-	→ 필요성
	-	> 현재 여기엔 IoT 개념이 전혀 없어
		-	(저랑 같은 생각 하셨군요...)
	-	IoT 에 대한 소개.
		-	옛날엔 M2M 이라는 말도 많이 씀 (Machine to Machine) : 장치끼리 연동
	-	여행의 IoT
		-	ex) 안내 센터에서, 사람이 아니고 물체가 있음 : 필요한 정보를 얻을 수 있음 : 내가 남기고 싶은 게 있...
			-	→ 아 내가 리게이다 앱같은 사용자 의견이 실제 장소에 남는 개념에 대한 이야기, 근데 그걸 해당 장소에서 찍어서 정보 습득 / 저장?
			-	현재 IoT는 그 정도까지는 아직 안 됨.
	-	대표적인 IoT
		-	냉장고 문 연 횟수, 들어있는 음식물, 유통기한 및 곧 상할 거 같은 정보 → 일부 나와있을듯
		-	(개인적으로 스마트 냉장고를 검색해봤는데 그냥 쩌는듯)
	-	제 생각 : IoT는
		1.	여러 **기계를 인터넷과 연결**하여
		2.	**실시간**으로 **현실의 정보**를 수집하여
		3.	유익하게 **활용**하는 것 (난방코딩 등)

#### 졸작에 대해

-	작품은 변경 가능
-	길게 끌지 말고 7, 8월에 다 끝내... 9월되면 취업 준비해야되니까.

---

발표 2
------

-	교수님의 신랄한 지적!
	-	작품 제목이 PPT에 없음 (정해지긴 했다는듯)
	-	작품의 주제와 필요성을 나타내는게 주 목표.
-	드론으로 영상 찍는 거 한다는듯

### 기술

-	물체 추적 트래킹 CV 활용
-	ARM 시스템 : Coretex-M3 혹은 M4 사용

### 드론의 응용분야

### 진행과정

-	설계 구상 → 필요한 부품 구입 → 모듈 조립 → ...

---

### 교수님 코멘트 타임!

-	발표연습 한다 : 설명을 풍부히.

#### 발표 자체에 대해

-	준비!
	-	형식
	-	주제
		-	대부분의 리스너는 무방비하게 온다 : 뭔지 모름

#### 주제에 대해

-	비행체 → 지상 영상 정보를 취득 → 어디에 사용?
-	왜?
	-	드론을 실제로 만듦 : 왜???
	-	부품을 사다 제어까지 직접 프로그램을 짤 것임 : 왜?????
		-	→ 제어 기술임 : 제어 수업을 들었다.. 면 제어 기술만 하면 됨!
			-	왜 카메라를 다는지?
			-	왜 비행체를 굳이 만드는지? (초창기가 아니라 드론 정도는 10만원 정도 주면 살 수 있음)
			-	제어 자체도 직접 만든다면 굉장히 어려울텐데? (작품성이 있다는 의미)
				-	→ 장애물을 피해서 10M를 갔다 : 굉장히 대단한 것
	-	주제가 불확실하다는 이야기인듯
	-	**시간이 없어요!** → 다 하려면 이도 저도 안 됨

#### 비행체와 영상처리에 대해

-	비행체의 영상처리의 Key Point? : 영상은 어디에서 찍는가에 따라 다 다름
	1.	2D → 3D로 : 증강현실 : 높은데서 보면 다 똑같이 보임 : 지상 정보가 상당히 부정확함
		-	해보는 것 자체도 만만치 않을 것
	2.	파노라마
		-	가면서 찍으면 다 겹침, 가면서 흔들리고 겹치고... 중복된 부분 자르고...
		-	와... 나 같으면 제어는 오픈소스 쓰고 GPS랑 영상처리에 올인할듯
		-	요즘엔 프로그램이 다 제공됨 → 쉬운건 OpenCV 같은 걸 쓰면..
			-	→ 제공된 걸 활용하는 것도 쉽지 않음
	3.	흔 들 린 다 !
-	하려는게 너무 과도하다.
	-	욕심이 난다 : 두 개를 합치는 길 (어려움) : 영상제어 (영상 → 제어)
		-	ex) 크루즈 미사일 등. 고수. 바로 국방 연구원에서 데려갈 듯
-	한 가지에만 Focusing 하라, 주력분야에 Focusing 하라
	-	만드는 건 의미가 없는게, 기계공학과에서 진짜 만든다ㅏㅏㅏ → Motor의 Mechanical (발음 : 미케니컬) 한 것 (모터의 회전량) 까지 해석 가능, 유체공학, ...
	-	→ 걔들은 지능 을 못한다 : 영상처리, 알고리즘, ... : 우리 주특기를 잘 살릴 생각을 하라
	-	홈페이지 디자인... → 산디과 (산업디자인) 에 못 이김. → 감이 있어서 왔다! 이런 것. 색상과 구도부터 다름
	-	시로바코의 제작진행이 생각나네요. 이런 역할도 있는데. (저)

#### 소요기술 → CPU

-	Coretex-M3, M4 : 그거갖고 아무것도 못해! 영상처리! (와 신랄하다...) : 정지영상 정도는 가능
	-	ARM 시리즈 중 가장 성능이 떨어짐
	-	지난학기부터 교재를 바꾼 그 CPU : 왜? →
		-	ARM 이 70% 점령
		-	임베디드 CPU의 스펙트럼이 넓어졌다 : 아주 저성능에서 아주 고성능까지 → ARM 이라는 한 가지로는 만족시키기 어려워졌다
		-	→ 코어텍스 A, M, R 로 분할
			-	A : 고성능 : 저전력이 포인트 : 10분 날아가면 꺼진다면?
				-	엑시노스 라는 보드가 나와있음 → 리눅스 포팅해야 → OpenCV...
			-	M : 저성능 → 각광 : **IoT** 때문에!
				-	> 스마트폰 이후의 차세대 먹거리로 IoT를 잡고있잖아.
				-	저성능 시장이 커짐! 10년정도 후진해서 시장이 생김!
			-	R : 잘 안 씀
		-	이러한 시대에 맞춰서 교재를 바꿈. (임베디드 시스템...) 키트도 바꿈.
-	고려사항
	-	CPU
	-	OS 탑재할거냐, Firmware를 잡을거냐
	-	...
	-	→ Bottom-up 이 아니라 Top-down 임

발표 3
------

영상처리를 통한 게임 (09 문정우 선배)

### 응용기술

-	키넥트, 오큘러스 리프트, Virtuix Omni (인터넷에 돌았던 *러닝 컨트롤러* → 걸음을 이용한 컨트롤러)
-	눈동자 인식
-	게임 자체는 오픈소스 이용
	-	벽돌깨기 등
-	진행과정
	-	OpenCV
	-	논문 작성자가 튜토리얼 사이트를 만듦 [사이트](http://note.sonotscom/SciSoftware/Haartraing.html)
	-	**Haar** 에 대해 자료 수집중

---

### 교수님 코멘트 타임!

-	한 번도 안 빠지고 나오는 단골 소재
	-	앱, 웹 처럼 완성도가 없는 분야 중 하나
-	HMD를 쓰겠다? → 아니오
	-	HMD에 들어가는 알고리즘을 쓰겠다 : Face Detection
	-	장치 : PC 캠.
-	> 결론부터 얘기할게 : PC캠으로 눈동자 인식 못 해~
	-	멀리 떨어져있음
	-	하지 말라는게 아니고.
-	영상인식 → 필요 → 작동
-	필요한 거긴 하지만, 실제 상황에서 하기 어렵다
	-	눈동자를 인식한다 : 트래킹이 어려움 (한 번 찾고 놓칠것이다)
-	그래서 하다보니까 안 되서 작품들이 키넥트를 이용했다
	-	적외선 센서가 추가로 거리를 측정함
	-	MS에서 라이브러리를 엄청 지원
	-	그나마 키넥트로 한 작품들은 기초적인 제스처 인식을 했다
-	일단 Eye detection 은 안 된다고 보는게 → 더군다나 Tracking?!
	-	게임에 할 정도의 트래킹은 어렵다.
-	눈을 이용한 제품들은 대부분 실패한다 : → 눈의 혹사 → 눈 컨트롤 게임 : 학생 작품으로는 힘만 들지 결과가 없을 것임. 굉장히 힘들고.
	-	차라리 제스처 인식을
-	기성 제품을 이용하면 문제 : 가공할 수 없다 (라이브러리의 API만 공개하니...) : 정확도는 높지만 맘대로 사용하기가 어렵다
-	(나 : 트래킹을 리듬게임에 적용한다면? (헉) → 생각해보니 단에보... → 다른 가능성도 많을듯)
-	논문을 언급한 것에 대해 : 논문을 보고 작품을 만든다 → 어렵다고 보는게
-	OpenCV는 정말 잘 되어있다 : 책도 많음 (책이 적다는 것에 대한 코멘트)
-	영상인식은 생각보다 여러분들이 구사하기 쉽지 않다 (서적은 끝도 없지만) : 아이디어가 내 맘대로 작동을 안 할 것.
	-	컴퓨터공학과 학생들의 문제 : 프로그램만 짜다 보니 버추얼 세계에 있다 : **세상에 무서운 게 없다** : 세상에 안 되는게 없다 라는 생각 : 짜기만 하면 짠 대로 작동한다 : 실제 Physical 세계도 그렇게 동작할거라고 생각
	-	전자과 학생들은 다르다 : 뭔가 하나 작동시키려면 오래 걸린다 : 거꾸로 생각이 위축되어 있다 : **피해의식**
-	주가 뭐냐를 정해야 : 게임이냐, 영상 인식이냐?

발표 4
------

아이디어는 좋은데 슬라이드가 개판인듯. 개요가 서술형... 그 외 슬라이드는 좋았음.

-	차량 및 바이크, 자전거 등을 위한 블랙박스.
-	카메라 블박 / 앱 연동 / GPS 장치 이용 위치 파악
-	Java, 안드로이드 프로그래밍, 이클립스 정도
-	일정 : 기능구상 → 기본 어플리케이션 구현 → 카메라 이용한 녹화 등의 기능 구현 → ...

---

### 교수님 코멘트 타임!

-	앞으로 영상에 대해서는 노코멘트
-	필요성?
	-	도둑이 더 훔칠듯. → 절도율 ↑
	-	차는 못 들고가지만?
	-	상품은 아니지만 필요성이 있긴 해야. (만드는 방법에서 상품성을 빼라는 말)
	-	오토바이 블랙박스는 있음 : 대인사고증빙용 (도난대비는 아님!)
	-	차라리 상황인식 카메라가 좋지 않을까.
-	요즘 이슈 : 상황인식 → Machine Learning, 인공지능 : 결정을 기계가 함. → 다 확률통계임.
	-	박태룡 교수님, 대학원 기계학습 과목

마무리 코멘트
-------------

-	구상만 하지 말고 진행을 하고 있어야

언급하지 않은 아이디어
----------------------

-	작품성이 없...나? : 자전거 분실은 실질적인 문제임. MTB 등은 상당히 비쌈. 영상처리를 포기하는 대신, 핸드폰과 블루투스 페어링 등을 통해, 근처에 핸드폰이 없을 때 일정 이상의 진동이 발생한다거나 할 경우 경보음 발생과 함께 위치를 핸드폰에 전송. 예 : 비싼 차량의 키를 근처에 들고있기만 해도 문을 열 수 있는 것