cv05 mopology
=============

-	지난시간 : 피라미드 라플라스의 변경
	-	low level, high level
	-	포토샵 정도는 다 해봤을거라 가정했는데 그렇지 않은 학생들
-	RGB 기반 클래스 → HS 기반 → 히스토그램 (다음주)

모폴로지 연산
=============

-	모폴로지 : 형태학 (생물학 계통)
	-	우리 : 형태 기반으로 연산하겠다

개요
----

-	이미지의 노이즈와 디테일을 줄인다
	-	가우시안 필터 : 경계선이 무너짐...
	-	양선형*biliteral* 필터 : 연산 cost가 크다 (HW가 크거나 SW가 오래걸린다)
		-	깨끗함
	-	→ 모폴로지 필터
		-	뭉개짐
-	목차
	-	모폴로지 필터
	-	모폴로지 모서리 탐지 → feature detection 때
	-	세그멘테이션 → 다른데서

크게 두 가지
------------

-	침식 *Erosion*, 팽창 *Dilation*
-	외곽을 찾는 알고리즘 → 루프를 많이 돌아야 → 연산이 크다 → 잘 안 한다
-	3 x 3 square **Structuring element** : 가우시안의 커널과 유사
-	가우시안 커널
	-	항상 보던 그 그림
	-	coefficient

연산
----

-	Structuring element 의...
	-	침식 : 안에 있는 화소가 하나라도 0이면 0

활용
----

-	계조 영상 : 밝은 화소는 줄어들고 어두운 화소가 증가

코드 `ch04_1_01_ErodeDilate.cpp`
--------------------------------

-	여러번
	-	1 x 3 → 가로로 늘어남
	-	1 x 3 을 두 번 → 1 x 5 와 유사 (완전히 같지는 않음!)
		-	3번에 같다?
		-	1회 → 3과 같다
		-	2회 → 5과 같다
		-	3회 → 7과 같다
	-	7 x 1 → 세로로 늘어남
-	openCV의 커널은 0이면 처리하지 않음
	-	별도로 erode, dilation 함수가 있음
-	erosion : 외곽이 걱정 없을 때.
	-	erosion 후에 dilation : 사소한 잡음이 사라짐

OpenCV
------

-	getStructuringElement() : cv::Mat 리턴, 커널 생성해서 반환 → 얘 쓰면 편함
-	erode() ← kernel 인자에 cv::Mat 필요 (↑ 쓰면 편함) -
	-	다른 방법 : 직접 쓰기

```cpp
cv::Mat KernelHV(7, 7, CV_8U, cv::Scalar(0));		// structuring element가 모두 0이므로 처리할 대상 화소가 없어 사실상 원본 영상과 같다.
KernelHV.at<uchar>(3, 0) = 1;
KernelHV.at<uchar>(3, 1) = 1;
KernelHV.at<uchar>(3, 2) = 1;
KernelHV.at<uchar>(3, 3) = 1;
KernelHV.at<uchar>(3, 4) = 1;
KernelHV.at<uchar>(3, 5) = 1;
KernelHV.at<uchar>(3, 6) = 1;
cv::dilate(image, dilated, KernelHV);
```

-	흑백반전으로 해봄 → erode 했는데 오히려 검은색 글씨가 늘어남 (처리 대상이...)
-	이진화 안 하고, 그냥 영상으로 처리하면 →?
-	erosion 하면 어두워짐
-	붓터치 알고리즘은 따로 있음 → dilation?
-	dilation은 더 밝아짐 : max 값을 보기 때문에.

### CV에서...

-	노이즈 제거시.
	-	가우시안으로는 안 될 경우
	-	median 도 하나의 방법
	-	이 방법도 하나의 방법
-	컬러 영상은 잘 하지 않는다

```cpp
//***************************************************************************************
// Eroding and Dilating Images using Morphological Filters
// 침식과 팽창 동작을 익히고 그 특징을 관찰한다.
//***************************************************************************************


char	FileName[50] = "D:/CV/Images/MORPHO.png";			// 흑백 영상	. 흰 색이 object인 사례.
//char	FileName[50] = "D:/CV/Images/patterns.jpg";				// 흑백 영상	. 검은 색이 object인 사례.

//char	FileName[50] = "D:/CV/Images/lenna.jpg";
//char	FileName[50] = "D:/CV/Images/fruits.jpg";
//char	FileName[50] = "D:/CV/Images/pens.jpg";
//char	FileName[50] = "D:/CV/Images/monument1.jpg";
//char	FileName[50] = "D:/CV/Images/dog.jpg";
//char	FileName[50] = "D:/CV/Images/cameraman.jpg";


#include <iostream>
//#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
	// Read input image
	cv::Mat image= cv::imread(FileName, 0);			// 흑백 계조 영상으로 읽기. 1 채널
	//cv::Mat image= cv::imread(FileName, 1);				// 칼라 계조 영상으로 읽기. 3채널
	if (!image.data)		return 0;
			// image = 255-image;							// 역상.
	cv::namedWindow("Input File");	cv::imshow("Input File",image);


	// 에지, 이진화 등을 목적에 따라 선택적으로 사용할 수 있다.
	//cv::Canny(image,image,100,200);				// 에지.

	cv::threshold(image,image,128,255,cv::THRESH_BINARY);
	//cv::threshold(image, image,128,255,cv::THRESH_BINARY_INV);		// Invert the image
	cv::namedWindow("Input Image");	cv::imshow("Input Image",image); 	cv::waitKey();


	//---------------------------------------------------------------------------------------------------
	// 실습 1 : Erosion(침식)
	//---------------------------------------------------------------------------------------------------
	// 계조영상 : 커널 안에서 가장 작은 값을 반환하는 연산을 행한다.
	// 이진영상 : 커널 안에 하나라도 모두 0이 있으면 0을 출력. 물체의 가장자리가 줄어드는 효과가 나타난다.
	//*
	cv::Mat eroded;
	cv::erode(image,eroded,cv::Mat());	// if element=Mat() , a 3 x 3 rectangular structuring element is used.
	cv::namedWindow("(1)Erosion:3*3");	cv::imshow("(1)Erosion:3*3",eroded); 	cv::waitKey();

	//cv::Mat KernelH(3,3,CV_8U,cv::());	// 5번 침식
	cv::erode(image,eroded,cv::Mat(), cv::Point(-1,-1) ,5);
	cv::namedWindow("(1a)Erosion:3*3, 5 times");	cv::imshow("(1a)Erosion:3*3, 5 times",eroded);  cv::waitKey();


	cv::Mat KernelH(1,7,CV_8U,cv::Scalar(1));	// 가로 줄 방향의 침식
	cv::erode(image,eroded,KernelH);
	cv::namedWindow("(2)Erosion:1*7, H-direction");	cv::imshow("(2)Erosion:1*7, H-direction",eroded);  cv::waitKey();

	cv::Mat KernelV(7,1,CV_8U,cv::Scalar(1));	// 세로줄 방향의 침식
	cv::erode(image,eroded,KernelV);
	cv::namedWindow("(3)Erosion:7*1, V-direction");	cv::imshow("(3)Erosion:7*1, V-direction",eroded);  cv::waitKey();

	cv::Mat KernelHV(7,7,CV_8U,cv::Scalar(0));	//structuring element가 모두 0이므로 처리할 대상 화소가 없어 사실상 원본 영상과 같다.
	cv::erode(image,eroded,KernelHV);
	cv::namedWindow("(4)Erosion:7*7, with null kernel");	cv::imshow("(4)Erosion:7*7, with null kernel",eroded);   cv::waitKey();

	// 7*7,그러나 가운데 줄 만 erode 대상이다. 결과는 (2)번의 가로줄 방향의 침식과 같다.
	// for (int i=0; i<7; i++) KernelHV.at<uchar>(3,i)= 1;
	KernelHV.at<uchar>(3,0)= 1;
	KernelHV.at<uchar>(3,1)= 1;
	KernelHV.at<uchar>(3,2)= 1;
	KernelHV.at<uchar>(3,3)= 1;
	KernelHV.at<uchar>(3,4)= 1;
	KernelHV.at<uchar>(3,5)= 1;
	KernelHV.at<uchar>(3,6)= 1;
	cv::erode(image,eroded,KernelHV);
	cv::namedWindow("(5)Erosion:7*7, with center horizontal line valid");	cv::imshow("(5)Erosion:7*7, with center horizontal line valid",eroded);
	cv::waitKey();

	// Erode the image 2 times.=7*7 커널과 결과가 같다. 2회 반복 = 7*7 커널. 3회 반복 = ?*? 커널.
	// 침식을 반복할 수록 1의 면적은 줄어든다.
	cv::erode(image,eroded,cv::Mat(1,3,CV_8U,cv::Scalar(1)),cv::Point(-1,-1),2);	// 1*3 커널로 2회 반복. (2)번의 1*7커널로 1회 수행한 것과 같다.
	cv::namedWindow("(6)Erosion:1*3, H-direction, 2 times"); 	cv::imshow("(6)Erosion:1*3, H-direction, 2 times",eroded); cv::waitKey();
	return 0;
	//*/

	//---------------------------------------------------------------------------------------------------
	// 실습 2 : Dilation(팽창)
	//---------------------------------------------------------------------------------------------------
	// 계조영상 : 커널 안에서 가장 큰 값을 반환하는 연산을 행한다.
	// 이진영상 : 커널안에 주변이 하나라도 1이 있으면 1을 출력한다.
	// 물체의 가장자리가 늘어나는 효과가 나타난다.
	//*
	cv::Mat dilated;
	cv::dilate(image,dilated,cv::Mat());		// cv::Mat() = 3*3 rectangular structuring element is used
	cv::imshow("(1)Dilation:3*3",dilated);  cv::waitKey();

	cv::dilate(image,dilated,cv::Mat(), cv::Point(-1,-1), 5);
	cv::imshow("(1a)Dilation:3*3, 5 times",dilated);  cv::waitKey();

	cv::Mat KernelH(1,7,CV_8U,cv::Scalar(1));	// 가로 줄 방향의 팽창
	cv::dilate(image,dilated,KernelH);
	cv::imshow("(2)Dilation:1*7, H-direction",dilated);  cv::waitKey();

	cv::Mat KernelV(7,1,CV_8U,cv::Scalar(1));	// 세로 줄 방향의 팽창
	cv::dilate(image,dilated,KernelV);
	//cv::namedWindow("(3)Dilation:7*1, V-direction");
	cv::imshow("(3)Dilation:7*1, V-direction",dilated);  cv::waitKey();

	cv::Mat KernelHV(7,7,CV_8U,cv::Scalar(0));		// structuring element가 모두 0이므로 처리할 대상 화소가 없어 사실상 원본 영상과 같다.
	cv::dilate(image,dilated,KernelHV);
	//cv::namedWindow("(4)Dilation:7*7, with null kernel");
	cv::imshow("(4)Dilation:7*7, with null kernel",dilated); cv::waitKey();

	// for (int i=0; i<7; i++) KernelHV.at<uchar>(3,i)= 1;
	KernelHV.at<uchar>(3,0)= 1;
	KernelHV.at<uchar>(3,1)= 1;
	KernelHV.at<uchar>(3,2)= 1;
	KernelHV.at<uchar>(3,3)= 1;
	KernelHV.at<uchar>(3,4)= 1;
	KernelHV.at<uchar>(3,5)= 1;
	KernelHV.at<uchar>(3,6)= 1;
	cv::dilate(image,dilated,KernelHV);
	//cv::namedWindow("(5)Dilation:7*7, with center horizontal line valid");
	cv::imshow("(5)Dilation:7*7, with center horizontal line valid",dilated); cv::waitKey();

	// Dilate the image 2 times.=7*7 커널과 결과가 같다. 2회 반복 = 7*7 커널. 3회 반복 = ?*? 커널.
	// 팽창을 반복할 수록 1의 면적은 늘어난다.
	cv::dilate(image,dilated,cv::Mat(1,3,CV_8U,cv::Scalar(1)),cv::Point(-1,-1),2);	// 1*3 커널로 2회 반복. 1*7커널로 1회 수행한 것과 같다.
	//cv::namedWindow("(6)Dilation:1*3, H-direction, 2 times");
	cv::imshow("(6)Dilation:1*3, H-direction, 2 times",dilated); cv::waitKey();
	return 0;
	//*/
}
```

### 잡담

-	월드 뭐시기 - 이건희 회장
-	저는... "왜?" 를 언제나 물어야한다고 생각합니다. 애플 이전에도 내놓은 비슷한 상품들이 있었지만 굳이 애플이 성공한 이유가 "왜?" 에 있다고 봅니다.
-	소니가 무너지는 것
-	MIT가 밀리는 거 많음 → 항상 옳지는 않다
	-	인공지능 : LISP 머신 망함
-	뽑으면 내일 당장 일할 수 있는 사람 : 중소기업 사장은 돈이 많지 않다
-	그래도 기본은 되어야 → 토익 700 이상 등 : 대기업 갈 스펙을 채워놔야
	1.	대기업에 시험
	2.	떨어지면 중소기업 (웃음)

### CV에서.. (2)

-	morphologyEx
	-	MORPH_OPEN : erode → dilate : 잡음제거
	-	MORPH_CLOSE : dilate → erode : 객체의 연결 확인
	-	MORPH_TOPHAT : 원본 - MORPH_OPEN : 엣지
	-	MORPH_BLACKHAT : MORPH_CLOSE - 원본 : 엣지
		-	→ 연산 코스트가 작을 수 있다

```cpp
//***************************************************************************************
// Opening and Closing Images using Morphological Filters
//***************************************************************************************

char	FullName[80] = "E:/cv/Images/";
char	FileName[50] = "MORPHO.png";		// 이진 영상
//char	FileName[50] = "patterns.jpg";
//char	FileName[50] = "lenna.jpg";
//char	FileName[50] = "fruits.jpg";
//char	FileName[50] = "boldt.jpg";
//char	FileName[50] = "monument1.jpg";
//char	FileName[50] = "dog.jpg";
//char	FileName[50] = "bar.bmp";
//char	FileName[50] = "cameraman.jpg";


#include <iostream>
//#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main()
{
	// Read input image
	strcat(FullName, FileName);
	cv::Mat image = cv::imread(FullName, 0);
	if (!image.data)		return 0;
	// image = 255-image;					// 역상.
	cv::namedWindow("Input Image");	cv::imshow("Input Image", image);
	cv::Mat image2;			// 임시 버퍼
	//cv::Canny(image,image,100,200);		// 에지.
	//cv::threshold(image,edge2,128,255,cv::THRESH_BINARY_INV);		// Invert the image
	cv::threshold(image, image2, 128, 255, cv::THRESH_BINARY);
	cv::namedWindow("Binary Image");	cv::imshow("Binary Image", image2); 	cv::waitKey();


	//---------------------------------------------------------------------------------------------------
	// 경계선 = 적절한 팽창 - 적절한 침식
	//---------------------------------------------------------------------------------------------------

	cv::Mat eroded;
	cv::erode(image, eroded, cv::Mat());	// if element=Mat() , a 3 x 3 rectangular structuring element is used.
	cv::imshow("Erosion:3*3", eroded);  cv::waitKey();

	cv::Mat dilated;
	cv::dilate(image, dilated, cv::Mat());		// cv::Mat() = 3*3 rectangular structuring element is used
	cv::imshow("Dilation:3*3", dilated);  cv::waitKey();

	cv::Mat edge;
	edge = dilated - eroded;
	cv::imshow("(1)Edge(dilated-eroded)", edge); cv::waitKey(); //return 0 ;

	//---------------------------------------------------------------------------------------------------
	// Closing
	// 팽창 후 침식 연산 : 팽창을 먼저 하기 때문에 구멍 혹은 끊긴 선이 연결되고 이후 침식 연산에서 다시 줄어들어 원래 크기 보존
	//---------------------------------------------------------------------------------------------------

	cv::Mat element5(5, 5, CV_8U, cv::Scalar(1));
	cv::Mat closed;
	cv::morphologyEx(image, closed, cv::MORPH_CLOSE, element5);
	cv::imshow("(2)Closed Image", closed);  cv::waitKey();

	//---------------------------------------------------------------------------------------------------
	// Opening
	// 침식 후 팽창 연산 : 침식을 먼저 시행하여 잡음이 줄어들면서 다시 팽창. 원래 크기 보존.
	//---------------------------------------------------------------------------------------------------
	cv::Mat opened;
	cv::morphologyEx(image, opened, cv::MORPH_OPEN, element5);
	cv::imshow("(3)Opened Image", opened); cv::waitKey();

	//---------------------------------------------------------------------------------------------------
	// Close and Open the image
	//---------------------------------------------------------------------------------------------------
	cv::morphologyEx(image, image2, cv::MORPH_CLOSE, element5);
	cv::morphologyEx(image2, image2, cv::MORPH_OPEN, element5);
	cv::imshow("(4)Closed and Opened Image", image2); cv::waitKey();
	//cv::imwrite("Close_Open.jpg",image2);

	//---------------------------------------------------------------------------------------------------
	// Open and Close the image
	//---------------------------------------------------------------------------------------------------
	cv::morphologyEx(image, image2, cv::MORPH_OPEN, element5);
	cv::morphologyEx(image2, image2, cv::MORPH_CLOSE, element5);
	cv::imshow("(5)Opened and Closed Image", image2); 	cv::waitKey();

	//---------------------------------------------------------------------------------------------------
	// Top-Hat and Black-Hat
	//---------------------------------------------------------------------------------------------------

	cv::morphologyEx(image, image2, cv::MORPH_TOPHAT, element5);		// Top-Hat = src-open
	cv::imshow("(6)Top Hat(Src-Open) Image", image2 * 3); 	cv::waitKey();
	cv::morphologyEx(image, image2, cv::MORPH_BLACKHAT, element5);		// Black-Hat = src-closed
	cv::imshow("(7)Black Hat(Src-Closed) Image", image2 * 3); 	cv::waitKey();
	return 0;
}
```

### 응용가능사례

-	번호판 → 가로 모양 : 가로 커널로 erode

### 나머지

-	트랙바는 집에서 해보세요
