컴퓨터 비전 3
=============

과제 2
======

-	Hue, Satuation 기반의 Color Detection
-	C++ 연습이 목적.
-	Lab 에 있는 거 : rgb로 디텍트. (심지어 더 엉성하다)

나머지 자료
===========

-	C++ 연습 0번 자료의 설명.
-	갑자기 아두이노 썰 푸심. (아티스트용 보드)
-	C++ 템플릿 (C++ 강의에서 안 배움) → STL (마찬가지로 안 배움)
	-	→ 필요하니까 배움
	-	Color Detection의 시시한 알고리즘을 하면서 학습.
-	01 PracticeProcessing 은 설명이 없음 → 디지털 영상처리. 따로 보기
-	오늘 할 거 : C++ 연습 (00), 색상탐지 (02, C++ STL 연습)

STL
===

-	표준 C++ 라이브러리

Function Templates vs Template Function
---------------------------------------

-	Function Template : 인자가 템플릿
-	Template Function : 템플릿 활용가능한 함수
-	타입과 관계없이 하겠다.

함수 템플릿
-----------

```
template <class T>
T GetMax (T a, T b) {
  T result;
  result = (a>b)? a:b;
  return (result);
}
```

```
k = GetMax<int>(i, j);
```

-	함수 정의. 인자가 템플릿 클래스

클래스 템플릿
-------------

```
template <class T> class Mypair {
  public:
  T values[2];
  mypair(T first, T second) {
    values[0] = first;
    values[1] = second;
  }
}
```

```
Mypair<int> myobject(115, 36);
```

---

휴식

---

Static 관련된 이야기.
=====================

-	물었더니 답을 못 하는 학생 wwww
-	DLL 사용 여부.
-	말주변이 딸리는 것도 죄다. (wwww
-	답은 요구한대로 쓰라 (......)

Template, more.
===============

Template Specialization
-----------------------

```
template<class T>
class mycontainer{
  T element;
  public:
    mycontainer(T arg) {element = arg;}
    T increase() {return ++element;}
}


template <>
class mycontainer <char> {
  char element;
  public:
  mycontainer(char arg) { element = arg; }
  char upperCase() {
    if ((element>='a') && (element <= 'z'))
      element += 'A' - 'a';
    return element;
  }
}
```

-	타입을 일부러 밝혀버리는 방식.
-	혼자 쓰는 건 의미없음, 템플릿 중 특화된 경우 표현.

Non-Type parameters for template
--------------------------------

```
template <class T=int, int N=10>
template <class T, int N>
...
```

-	파라미터가 상수로 대체됨. 상수 대체용.

STL
===

Vector
------

-	시퀀스 컨테이너
-	앞 쪽이 막혀있는 구조.
-	메소드
	-	조회
		-	front()
		-	back()
	-	추가 / 삭제
		-	push_back()
		-	pop_back()
		-	insert()

---

-	`template <class T, class Alloc = allocator<T>> class vector;`
-	allocator는 교수님도 잘 모름.

---

-	크기확인
	-	size()
	-	max_size()
	-	capacity() : Vector만 가지고 있음!

Iterator
--------

`std::class_name<template_parameters>::iterator name`

-	일종의 포인터.
-	data container 접근용 객체 (vector, map, list 등)

실습
----

### 일반 벡터

```
int main()
{
	vector<int> myvector;
	int myint;

	cout << "숫자를 적으셔요" << endl;
	do {
		cin >> myint;
		myvector.push_back(myint);
	} while (myint);
	myvector.pop_back();

	cout << "myvector stores " << int(myvector.size()) << " numbers!" << endl;
	return 0;
}
```

### Iterator

```
int main() {
	vector<int> myvector;
	for (int i = 1; i <= 5; i++)
		myvector.push_back(i);

	cout << "myvec contains : ";
	for (vector<int>::iterator it = myvector.begin();
		it != myvector.end();
		++it
		)
		cout << ' ' << *it;
	cout << endl;
	return 0;
}
```

### Vector size

---

휴식

---

ch03_1_01_UsingStragegyPattern.cpp
==================================

-	imshow로 새로운 윈도 킴.
-	간단한 RGB 인식 : RGB 값의 범위를 활용.
-	자동차 번호판 인식 : 녹색을 파란색으로 믿었던 실패사례 : 편견.
	-	영상처리를 그렇게 하면 말도 안 되는 일이...
-	캐나다 대학의 교수가 써놓은 코드의 정리
	-	ColorDetector 클래스 선언
		-	minDist : 범위값.
		-	target : 타겟 픽셀값.
			-	→ non-type parameter : 실제 클래스는 cv::Vec
			-	`cv::Vec3b` ← `typedef cv::Vec<uchar, 3> Vec3b`
		-	getter, setter
		-	process 함수
			-	이터레이터로 Mat의 값을 순회
			-	`getDistance(*it)`로 길이에 따라 itout 에 값 출력.

```
//************************************************************************************
// This file contains material supporting chapter 3 of the cookbook:  
// Computer Vision Programming using the OpenCV Library.   by Robert Laganiere, Packt Publishing, 2011.
// Files: 	colorDetection.h, 	colorDetection.cpp, 	colordetector.cpp,  correspond to Recipe:
// Using the Strategy Pattern in Algorithm Design

// 영상에서 특정 색상을 영상에서 찾아내어 1로 표시하고 나머지는 0으로 표시한다.
// 본 사례의 경우에는 setTargetColor(130,190,230) method 기법을 사용하였다.
// class를 등록하고 이를 활용하는 기법을 보인다

// 검토 :
// 숙제 : 칼라 검출의 다른 사례를 참조하여 마우스 클릭으로 색상을 지정해서 그 색상을 검출하는 프로그램을 설계하라.
// 다른 사례 : Practical OpenCV, Listing 5-7: Simple color based object detector
// 힌트 : 데모 프로그램 camshiftdemo.cpp는 사용한 알고리즘은 다르지만(칼라 히스토그램 등을 사용) 비슷한 색상을 마우스로 지정하여 이를 찾아낸다.
//************************************************************************************
#include <iostream>
using namespace std;

#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


#if !defined COLORDETECT
#define COLORDETECT

class ColorDetector {
  private:
	  int minDist;		// minimum acceptable distance
	  // target color
	  cv::Vec3b target;			// typedef Vec<uchar, 3> Vec3b;  in "core.hpp". BGR로 이루어진 uchar 형의 3개 어레이 변수
	  cv::Mat result;			// image containing resulting binary map

	  // inline private member function
	  // Computes the distance from target color.
	  int getDistance(const cv::Vec3b& color) const {
		 // return static_cast<int>(cv::norm<int,3>(cv::Vec3i(color[0]-target[0],color[1]-target[1],color[2]-target[2])));
		  return abs(color[0]-target[0])+
					abs(color[1]-target[1])+
					abs(color[2]-target[2]);
	  }

  public:
	  // empty constructor
	  ColorDetector() : minDist(100) {
	  // default parameter initialization here
	  target[0]= target[1]= target[2]= 0;
	  }

	  // Sets the color distance threshold.
	  // Threshold must be positive, otherwise distance threshold is set to 0.
	  void setColorDistanceThreshold(int distance) {
		  if (distance<0) 		  distance=0;
		  minDist= distance;
	  }

	  // Gets the color distance threshold
	  int getColorDistanceThreshold() const {
		  return minDist;
	  }

	  // Sets the color to be detected
	  void setTargetColor(unsigned char red, unsigned char green, unsigned char blue) {
		  target[2]= red;
		  target[1]= green;
		  target[0]= blue;
	  }

	  // Sets the color to be detected
	  void setTargetColor(cv::Vec3b color) {
		  target= color;
	  }

	  // Gets the color to be detected
	  cv::Vec3b getTargetColor() const {
		  return target;
	  }

	  // Processes the image. Returns a 1-channel binary image.
	  cv::Mat process(const cv::Mat &image);
};


#endif



cv::Mat ColorDetector::process(const cv::Mat &image) {

	  // re-allocate binary map if necessary
	  // same size as input image, but 1-channel
	  result.create(image.rows,image.cols,CV_8U);			// result는 ColorDetector클래스안에 선언된 private 변수

	  // get the iterators
	  cv::Mat_<cv::Vec3b>::const_iterator it= image.begin<cv::Vec3b>();
	  cv::Mat_<cv::Vec3b>::const_iterator itend= image.end<cv::Vec3b>();
	  cv::Mat_<uchar>::iterator itout= result.begin<uchar>();

		// process each pixel ---------------------
	  for ( ; it!= itend; ++it, ++itout) {
		  // compute distance from target color
		  if (getDistance(*it)<minDist) {
			  *itout= 255;
		  } else {
			  *itout= 0;
		  }
        // end of pixel processing ----------------
	  }
	  return result;
}




int main( ) {
	// Create image processor object
	ColorDetector cdetect;

	// Read input image
	//cv::Mat image= cv::imread("d:\\ComputerVision\\images\\fruits.jpg");
	cv::Mat image= cv::imread("d:/CV/images/boldt.jpg");
	if (!image.data)
		return 0;

	cdetect.setColorDistanceThreshold(100);

   // set input parameters
	cdetect.setTargetColor(130,190,230); // here blue sky

   // Read image, process it and display the result
	cv::namedWindow("result");
	cv::imshow("result",cdetect.process(image));
	cv::waitKey();
	return 0;
}
```

RGB Click Threshold (ch03-2, ch03-3)
====================================

-	UI 연습 목적?
	-	TrackBar
	-	Click
-	Threshold 를 위한 트랙바 부분은 대폭 수정한다고 생각하기.
-	다 없애버리고 트랙은 하나만 있도록.
	-	클릭해서 선택한 색의 10%, 20%, 30%, ...
-	Point 객체 : 클릭한 지점 위치 저장용
-	color : bgr 순서
-	margin 값을 트랙바로 옮기게 하라.

과제에 관한 설명 다시.
======================

-	cvtColor로 색상 좌표계 변경.
	-	영상이 RGB가 아니라 BGR임에 유의.
		-	CV_BGR2HSV
	-	밝기, 어둡기는 관심 없음. 색상만 보기
	-	rgb보다 낫지만 좋지는 않음.
