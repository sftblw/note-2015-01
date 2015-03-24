멀티미디어 4강
==============

-	거하게 지각. :)

### 2.4.3 압축 및 저장에 관한 표준

-	압축
	-	무손실 압축 (LossLess Compression) (→ 압축 비율이 낮음) : 원레 데이터 → 압축된 데이터 → (복원) = 원래 데이터
	-	　손실 압축 (Lossy　　Compression) (→ 압축 비율이 높음) : 원레 데이터 → 압축된 데이터 → (복원) != 원래 데이터
-	정지화상 (Still Image)
	-	JPEG (Joint Photographic Experts Group)
	-	PNG
	-	GIF : 회사에서 만듦 : 특허 문제
-	동영상
	-	MPEG : 1, 2, 4, 7, 21 정도만 있다고 봐야.
		-	1 : CD-ROM 품질 : Read-only → 재생시 쓸 수 없다 : 특징 → 쓰는 데 시간제약이 없음 / 읽는데 실시간 요구 (재생)
		-	2 : 화질이 좋아지면서 디지털 TV : 특징 → 읽기 쓰기 모두 실시간 요구
		-	1, 2, 4, 7, 21 방식이 다 다르다
		-	4 : 객체 기반 : 보안 업체에서 사용 : 영상 → 어... 이 제품 뭐야?!
		-	7 : 내용 기반 정보**검색** : 소녀시대 누구가 좋아하는 뭐는 뭐에요? 를 검색 : 동영상도 검색할 수 있도록 (Text, 영상, 오디오)
		-	4, 7 은 세계 IT 업체들이 돈 벌려고 눈 새빨개.. (표현봐...)
		-	21 : 전자상거래 요소 기술
			-	전자상거래 (e-commerce)
	-	기타 동영상 형식
		-	AVI : Audio Video Interleaved
		-	MOV : Apple QuickTime
		-	WMF : Windows Meta File
-	사운드
	-	MP3, WAV, AIFF, AU 등
		-	MP3 : 동영상 압축 표준 개발하다가 소리 표준 만듦 (필요하니까) : MPGE-1 Audio Layer 3)
		-	AIFF (Audio Interchange File Format)
			-	Apple의 `*.wav` 같은 것. (`*.ief`\)
		-	AU (Audio)
			-	Unix 표준 오디오 파일
			-	Java 프로그램에서 Audio 로 쓰기도 함.
	-	MIDI (Musical Instrument Digital Interface)
		-	디지털 악기 간의 인터페이스, 통신 프로토콜, ...
		-	개발 : 디지털 악기 제조업체 및 관련 산업체들의 *컨소시엄* 에서.

### 2.4.4 문서관련표준

-	SGML (Standard Generalized Markup Language)
	-	전자문서 표준
	-	구성 : 문자 종류 선언 / DTD (Document Type Definition) / 실제 문서 (Document Instance)
	-	HTML의 선조격? 발전하여 HTML이 됨?
-	HTML
	-	웹 상에서 이용되는 **하이퍼미디어** 문서를 기술하는 방식
	-	내용 기술시 SGML 사용
	-	(git 신경쓰는 사이에 진도나감...)
-	XML (eXtensible Markup Language)
	-	SGML이 어려움 → 많이 축소시킴
-	오피스 문서 표준
	-	ODF, OOXML

### 2.4.5 그래픽 관련 표준

1.	그래픽
	-	2차원, 3차원 물체를 묘사하고 저장하기 위한 그래픽 API (Application Program Interface) 를 규정
	-	OS 내부를 공개하지 않는데 어떻게 프로그램을 작성할까 → API (기능 인터페이스) 제공 : 이 기능 쓰려면 이걸 써 의 약속. : 소스를 공개할수는 없으니.
		-	OS는 많은 사람이 써야 빛나는 것.
		-	개발자를 위한 약속.
	-	OpenGL
		-	그래픽 API 중 대표적인 것.
		-	Silicon Graphics 사가 만든 2D / 3D 그래픽 표준 API 산업체 표준.
		-	컴퓨터 플랫폼, 운영체제에 독립적 API
			-	→ 널리 쓰인다
		-	함수가 250개 가량 : 단순 도형부터 복잡한 3차원 장면까지 생성가능
		-	활용 : (이걸 굳이 쓸 의미가 있나?) : 컴퓨터 게임, CAD (Computer Aided Design), 가상현실, 정보시각화, 비행 시뮬레이션 등 분야에서 사용
		-	표준화 관여자들 (기능 향상자들) : SIG, IBM, Intel, Microsoft 등
		-	M＄ Direct3D와 함께 시장 양분
		-	체스 그림... 잡담 : IBM의 AIP 컴퓨터 *Deep-Blue*
2.	VRML / X3D 표준
	-	가상현실
		-	현실세계와 같은 느낌이 나도록 조성한 가상의 환경 (컴퓨터로 조성) (Virtual Environment)
		-	세컨드 라이프에 대한 잡담.
	-	VRML (Virtual Reality Modeling Language)
		-	3차언 사이버스페이스를 텍스트 형태로 기술하기 위한 모델링 언어
		-	다양한 사용자와 상호작용 및 Java 등의 다른 언어와 연동 가능
	-	X3D (Extensible 3D)
		-	웹 환경에서 3D 그래픽스를 위해 XML에 기반하여 VRML을 확장한 표준
			-	셰이딩 관련도 있음.
		-	차세대 개방형 표준안

2.5 미디어 플레이어와 플러그인 (Plug-in)
----------------------------------------

### 플러그인과 플레이어

-	미디어 플레이어 (Player) : 플러그인 형태로 제공 (...?)
-	플러그인 : 브라우저 확장기능 : 미디어 데이터를 처리하여 재생
	-	저장 포맷에 따라 상이한 플러그인 사용
-	종류
	-	애니메이션
		-	Flash (어도비)
	-	비디오
		-	QuickTIme Movie
		-	RealPlayer
		-	곰플레이어
	-	이미지 / 그래픽
		-	Adobe SVG Viewer
		-	Quicktime 3D
	-	사운드
		-	Winamp, RealAudio, WMP
	-	문서
		-	Adobe PDF Reader
	-	기타
		-	VRML Cosmo Player
		-	QuickTime VR 등

제 2부. 멀티미디어 데이터의 처리
================================

각 매체별로 자세한 처리기술의 개요를 배움.

제 3장. 이미지와 그래픽 기술
============================

3.1 이미지와 그래픽의 기본 개념
-------------------------------

### 이미지와 그래픽

(스윽 지나감)

### 3.1.1 픽셀의 이해

-	Pixel
	-	Picture Element 의 합성어
	-	화면 구성의 가장 기본 단위
	-	이미지 = 픽셀의 집합, Bitmap 방식으로 저장
-	색상의 수
	-	RGB 적절히 배합 : RGB 색상모델
	-	색상 수 : 픽셀당 할당된 비트(Depth)에 비례 (2^k 개)
		-	비트수와 색상
			-	1 (흑백)
			-	4 (Indexed), 8 (Indexed)
			-	16 (하이컬러 : 5:5:5)
			-	24 (트루컬러 : 8:8:8)
			-	32 (트루컬러 + 알파 (8비트))
		-	알파 채널 : RGB 외의 투명도, 색상 정보 가지지 않음
		-	문제는 돈이다 : 결국 압축해야. → 용도에 따라 또 다름.
