////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// samples\cpp\camshiftdemo.cpp
// OpenCV 샘플 프로그램을 주석문을 붙여 이해를 돕도록 하였다.
// CamShift 알고리즘을 실험해 볼 수 있는 프로그램.
// 기능 
//	검출할 대상을 마우스 드랙을 이용해 영역을 지정하면 이후 CamShift 알고리즘을 적용하여 대상를 추적한다.
//	검출된 영역은 붉은 선으로 표기하여 tracking한다.
//  캠카메라를 사용하는데 캠카메라의 설정은 0번으로 가정한다.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <ctype.h>

using namespace cv;
using namespace std;

int camNum =0;					// 캠카메라의 번호
bool backprojMode = false;		// 백프로젝션 결과는 흑백으로 표현하는 모드.
bool selectObject = false;		// 템플레이트 선택이 시작되었음을 알리는 플래그. left button을 누르면 true가 됨.
int trackObject = 0;			// 트랙킹 중지=0, 템플레이트 선택이 끝나면 -1로 설정된다., 트랙킹 시작=1. 
bool showHist = true;

// 화면을 정지시켜서 템플레이트를 취득할 목적으로 메뉴를 제공한다.
// p 메뉴를 사용해 화면을 정지시키고 마우스 드래그로 템플레이트를 선정하는 중에 템플레이트를 이동시켜 놓으면 대상체를 못 찾을 수도 있다.
bool paused = false;			// 현재 정지 화면 상태임. 화면 정지하면 정지된 화면을 출력하면서 모든 동작이 멈춘다. 

Point origin;						// 템플레이트의 왼쪽 상단 지점. 이 부분부터 드래그하여 영역을 선택한다.
Rect selection;					// 템플레이트 영역. 사각형. 이 부분은 역상으로 표현된다.
int		vmin = 10, vmax = 256;		//	value 값의 경계. vmin~vmax 까지의 휘도 값을 갖는 화소가 검출 대상이다.
int		smin = 30;		// 최소 채도 값. smin~255까지의 채도 값을 갖는 화소가 검출 대상이다.

Mat image;

static void onMouse( int event, int x, int y, int, void* )
{
    if( selectObject )		// 초기치는 0. 템플레이트 선택이 시작되었으면 선택 영역 ROI의 크기를 설정한다. 
    {
        selection.x = MIN(x, origin.x);         selection.y = MIN(y, origin.y);
        selection.width = std::abs(x - origin.x);         selection.height = std::abs(y - origin.y);
        selection &= Rect(0, 0, image.cols, image.rows);		// 원본 영상의 크기와의 & 연산을 통해 선택된 크기가 원본 영상을 넘지 않게 한다. 
    }

    switch( event )
    {
    case CV_EVENT_LBUTTONDOWN:
        origin = Point(x,y);				// 템플레이트의 왼쪽 상단 지점. 이 부분부터 드래그하여 영역을 선택한다.
        selection = Rect(x,y,0,0);		// 높이와 폭은 일단 0으로 설정한다.
        selectObject = true;			// 템플레이트 선택이 시작되었음을 알리는 플래그.
        break;
    case CV_EVENT_LBUTTONUP:
        selectObject = false;			// 템플레이트 선택은 끝났음을 알린다.
        if( selection.width > 0 && selection.height > 0 )
            trackObject = -1;			// 트랙킹 시작. 템플레이트 선택을 마치면 1
        break;
    }
}

static void help()
{
    cout << "\nThis is a demo that shows mean-shift based tracking\n"
            "You select a color objects such as your face and it tracks it.\n" << endl;
            //"This reads from video camera (0 by default, or the camera number the user enters\n"
            //"Usage: \n"
            //"   ./camshiftdemo [camera number]\n";

    cout << "\n\nHot keys: \n"
            "\tESC - quit the program\n"
            "\tc - stop the tracking\n"
            "\tb - switch to/from backprojection view\n"
            "\th - show/hide object histogram\n"
            "\tp - pause video\n"
            "To initialize tracking, select the object with mouse\n";
}

const char* keys =
{
    "{1|  | 0 | camera number}"
};

int main( int argc, const char** argv )
{
    help();

    VideoCapture cap;
    Rect trackWindow;			// 템플레이트와 같은 것으로 검색된 선택 영역.
    int hsize = 16;					// hue의 bin의 개수. 
    float hranges[] = {0,180};
    const float* phranges = hranges;
    //CommandLineParser parser(argc, argv, keys);
    //int camNum = parser.get<int>("1");

    cap.open(camNum);

    if( !cap.isOpened() )	    {
        help();
        cout << "***Could not initialize capturing...***\n";
        //cout << "Current parameter's value: \n";
        //parser.printParams();
        return -1;
    }

    namedWindow( "Histogram", 0 );
    namedWindow( "CamShift Demo", 0 );
    setMouseCallback( "CamShift Demo", onMouse, 0 );
    createTrackbar( "Vmin", "CamShift Demo", &vmin, 256, 0 );			// HSV 공간 상에서 검색할 Value의 최소 값. 휘도가 일정 범위에 들지 않는 것은 템플레이트 색상 선정에서 제거한다.
    createTrackbar( "Vmax", "CamShift Demo", &vmax, 256, 0 );			// HSV 공간 상에서 검색할 Value의 최대 값. 휘도가 일정 범위에 들지 않는 것은 템플레이트 색상 선정에서 제거한다.
    createTrackbar( "Smin", "CamShift Demo", &smin, 256, 0 );				// HSV 공간 상에서 검색할 채도의 최소 값.	 채도가 적은 것은 템플레이트 색상 선정에서 제거한다.

    Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;

    for(;;)
    {
        if( !paused )		{			// 정지 화면이 아니면 영상을 화면에 출력
            cap >> frame;
            if( frame.empty() )
                break;
        }

        frame.copyTo(image);

        if( !paused )
        {	//========================================================================================
            cvtColor(image, hsv, CV_BGR2HSV);

            if( trackObject )			// 초기치는 0.  0만 아니면 수행됨. 새로 템플레이트가 선택되었으면 -1. 일단 
            {			// ------------------------------------------------------------------------------------------------------------------
                int _vmin = vmin, _vmax = vmax;

                // inRange : Checks if array elements lie between the elements of two other arrays.
				// void inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst)
				inRange(hsv,			// InputArray src
							Scalar(0, smin, MIN(_vmin,_vmax)),		// InputArray lowerb
							Scalar(180, 256, MAX(_vmin, _vmax)),		// InputArray upperb
																				// Hue=0~180. Saturartion = smin~256. Value = MIN(_vmin,_vmax)~MAX(_vmin, _vmax).
							mask);		// OutputArray dst. hsv 영상에서 HSV가 모두 위에서 지정한 범위에 있는 화소만을 골라 mask에 넣는다.
                int ch[] = {0, 0};		// src 영상의 채널 0를 dst 영상의 채널 0에 복사하고자 함.
                hue.create(hsv.size(), hsv.depth());
				// mixChannels : Copies specified channels from input arrays to the specified channels of output arrays.
				// void mixChannels(const Mat* src, size_t nsrcs, Mat* dst, size_t ndsts, const int* fromTo, size_t npairs)
				// src 영상에서 dst 영상으로 fromTo에서 지정한 채널 순서로 복사하는 함수. opencv.org의 매뉴얼의 본 함수 설명에 있는 예제 참고,
                mixChannels(&hsv,	// input array or vector of matricesl
						1,					// number of matrices in src
						&hue,				// output array or vector of matrices; all the matrices must be allocated; their size and depth must be the same as in src[0].
						1,					// ndsts – number of matrices in dst
						ch,					// array of index pairs specifying which channels are copied and where; fromTo[k*2] is a 0-based index of the input channel in src, fromTo[k*2+1] is an index of the output channel in dst
						1);					// npairs – number of index pairs in fromTo
				// hsv 영상의  채널 0을 hue 영상의 채널 0에 복사한다. -> 즉, hsv 영상의 hue 채널을 hue 영상의 채널 0에 복사한다.

                if( trackObject < 0 )		// 0이 아니면 수행됨. -1은 트랙킹이 시작되었음을 의미.
                {
					Mat roi(hue, selection);				// hue 영상에서 선택한 부분만 오린 ROI 영상. 입력 영상의 hue 정보가 담겨 있는 영상에서 해당 영역만 자른 영상.
					Mat maskroi(mask, selection);		// mask 영상에서 선택한 부분만 오린 ROI 영상. 채도 휘도가 지정된 범위안에 있는 화소 중에서 해당 영역만 자른 영상.
                    // calcHist : Calculates a histogram of a set of arrays.
					// void calcHist(const Mat* images, int nimages, const int* channels, InputArray mask, OutputArray hist, int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false )
					// 템플레이트, roi에 대해 hue 히스토그램을 구한다. roi 전 영역을 대상으로 하지 않고 maskroi 부분(Saturation, Value가 특정 범위에 있는)에 해당하는 부분만 구한다.
					calcHist(&roi,		// Source arrays. 
							1,				// nimages – Number of source images.
							0,				// channels – List of the dims channels used to compute the histogram. 
							maskroi,		// 0이 아닌 요소의 위치의 화소에 대해 히스토그램 연산을 시행한다.
							hist,			// Output histogram
							1,				// dims – Histogram dimensionality that must be positive and not greater than CV_MAX_DIMS 
							&hsize,		// histSize – Array of histogram sizes in each dimension.	hue의 histogram bin 수를 말함. 현재 16으로 설정되어 있음.
							&phranges);	// {0,180}
					// normalize : Normalizes the norm or value range of an array.
                    // void normalize(InputArray src, OutputArray dst, double alpha=1, double beta=0, int norm_type=NORM_L2, int dtype=-1, InputArray mask=noArray() )
					// 템플레이트의 히스토그램을 0~255로 정규화 한다.
					normalize(hist,		// src – input array.
							hist,			// dst – output array of the same size as src
							0,				// alpha – norm value to normalize to or the lower range boundary in case of the range normalization.
							255,			// beta – upper range boundary in case of the range normalization; it is not used for the norm normalization.
							CV_MINMAX);	// normType – normalization type. CV_MINMAX 정규화 타입은 정규화된 값을 alpha~beta 사에 있게 만드는 가장 일반적인 정규화인 것으로 판단된다.

                    trackWindow = selection;			// 처음 시작이니 일단 템플레이트를 검출한 부분(selection)을 새로 찾아진 부분(trackWindow)으로 할당한다.
                    trackObject = 1;						// 트랙킹을 시작한다.?

                    histimg = Scalar::all(0);
                    int binW = histimg.cols / hsize;		// hue의 bin 1개의 넓이 해상도. hsize(=16)는 hue의 bin의 개수이다.
                    Mat buf(1, hsize, CV_8UC3);				// hue 값에 따른 색상을 담을 수 있는 버퍼
                    for( int i = 0; i < hsize; i++ )			// hue의 각 bin이 증가함에 따라 그 색상을 채도와 휘도는 255로 한 채로 버퍼에 기록한다.
                        buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180./hsize), 255, 255);
                    cvtColor(buf, buf, CV_HSV2BGR);

					// 히스토그램 버퍼에 템플레이트의 색상을 그려넣는다. 이때 채도와 휘도는 255로 고정한다.
					// hsize(=16) 단계의 hue의 변화에 대한 템플레이트 영상의 분포도를 막대 그래프로 그린다.  
                    for( int i = 0; i < hsize; i++ )
                    {
                        int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows/255);	// Hue i 에 대한 분포도. hist가 최대 255로 정규화되었음으로 val의 최대 값은 시스토그램 영상의 세로 높이.
                        // rectangle : Draws a simple, thick, or filled up-right rectangle.
						// void rectangle(Mat& img, Point pt1, Point pt2, const Scalar& color, int thickness=1, int lineType=8, int shift=0)
						rectangle( histimg,								// img – Image. 4각형을 그릴 대상 영상
							Point(i*binW,histimg.rows),					// pt1 – Vertex of the rectangle. 히스토그램 바(bar)의 왼 쪽 맨 아래 부분.
							Point((i+1)*binW,histimg.rows - val),		// pt2 – Vertex of the rectangle opposite to pt1. 히스토그램 바(bar)의 오른 쪽 맨 위 부분. 분포가 높으면 위로 올라 간다.
							Scalar(buf.at<Vec3b>(i)),						// color – Rectangle color or brightness (grayscale image).
							-1,		// thickness – Thickness of lines that make up the rectangle. Negative values, like CV_FILLED , mean that the function has to draw a filled rectangle.
							8 );	// lineType – Type of the line. 8=8-connected line.
                    }
                }
				// calcBackProject : Calculates the back projection of a histogram.
				// void calcBackProject(const Mat* images, int nimages, const int* channels, InputArray hist, OutputArray backProject, const float** ranges, double scale=1, bool uniform=true )

				//int tmp_channels[] = { 0, 1 };		// 2 채널을 백 프로젝션 시킬 경우. 채널 0과 1이 사용된다.
				int tmp_channels[] = { 0 };			// 1 채널을 백 프로젝션 시킬 경우. 채널 0이 사용된다.
				calcBackProject(&hue,		// images – Source arrays. taget image. 현재 0번째 채널만 hsv 영상에서 복사되어 있다.
					1,			// nimages – Number of source images.
					
					//0,					// channels – 0번 1채널만 쓸 때는 간단히 0이라고만 써도 된다.
					tmp_channels,		// channels – The list of channels used to compute the back projection. 1 채널일 때는 0으로 써도 된다.
				
					hist,			// hist – Input histogram that can be dense or sparse
					backproj,		// backProject – Destination back projection array that is a single-channel array of the same size and depth as images[0]
					&phranges);		// {0,180}. ranges – Array of arrays of the histogram bin boundaries in each dimension.
                
				// smin<Saturartion<256. vmin<Value<vmax. 마스크와의 AND 동작을 통해 이 2개의 조건과 일치하는 Hue의 density 결과를 구한다.
				backproj &= mask;		// 채도가 크고 휘도가 일정 범위내의 Hue 일치 결과만을 사용한다.

				// CamShift - Finds an object center, size, and orientation. The function implements the CAMSHIFT object tracking algorithm [Bradski98].
				// First, it finds an object center using meanShift() and then adjusts the window size and finds the optimal rotation. 
				// RotatedRect CamShift(InputArray probImage, Rect& window, TermCriteria criteria)
                RotatedRect trackBox		// The next position of the search window can be obtained with RotatedRect::boundingRect()
					= CamShift(				// The function returns the rotated rectangle structure that includes the object position, size, and orientation. 
					backproj,					// probImage – Back projection of the object histogram.
					trackWindow,			// window – Initial search window. 
                    TermCriteria(			//  Stop criteria for the iterative search algorithm. class의 생성자- TermCriteria(int type, int maxCount, double epsilon);
					CV_TERMCRIT_EPS | CV_TERMCRIT_ITER,		// the type of termination criteria. 변화량이 EPS보다 작던지, maxCount 만큼 반복했다면 중심점 이동을 종료한다.
					10,		// maxCount. the maximum number of iterations. iterartion 반복 최대 회수. 
					1 ));	// epsilon. the desired accuracy. 변화량이 이보다 작으면 종료한다.
                
				if( trackWindow.area() <= 1 )
                {
                    int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5)/6;
                    trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
                                       trackWindow.x + r, trackWindow.y + r) &
                                  Rect(0, 0, cols, rows);
                }

                if( backprojMode )		// 백프로젝션 결과는 흑백으로 표현한다.
                    cvtColor( backproj, image, CV_GRAY2BGR );
                
				// ellipse - Draws a simple or thick elliptic arc or fills an ellipse sector.
				// void ellipse(Mat& img, const RotatedRect& box, const Scalar& color, int thickness=1, int lineType=8)
				// 붉은 색 타원형으로 검색된 영역을 표시
				ellipse( image, 
					trackBox,			// box – Alternative ellipse representation via RotatedRect or CvBox2D. This means that the function draws an ellipse inscribed in the rotated rectangle.
					Scalar(0,0,255), // color – Ellipse color.
					3,					// thickness – Thickness of the ellipse arc outline, if positive. Otherwise, this indicates that a filled ellipse sector is to be drawn.
					CV_AA );			// CV_AA - antialiased line.

				// // The next position of the search window can be obtained with RotatedRect::boundingRect()
				Rect brect = trackBox.boundingRect();
				rectangle(image, brect, Scalar(255,0,0));			// 파란 색 박스로 검색된 영역을 표시
            }		// ------------------------------------------------------------------------------------------------------------------
        }	//========================================================================================
        else if( trackObject < 0 )			// 템플레이트 선택이 끝나면 -1로 설정된다. 
            paused = false;					// 템플레이트 선택이 끝나면 화면 중지는 자동 해제 된다.

		// 왼쪽 버튼을 누른 상태에서 ROI가 선택되면 해당 영역을 역상으로 표시한다.
        if( selectObject && selection.width > 0 && selection.height > 0 )		{
            Mat roi(image, selection);
            bitwise_not(roi, roi);		// 역상 표시
        }

        imshow( "CamShift Demo", image );
        imshow( "Histogram", histimg );

        char c = (char)waitKey(10);
        if( c == 27 )
            break;
        switch(c)
        {
        case 'b':
            backprojMode = !backprojMode;
            break;
        case 'c':
            trackObject = 0;
            histimg = Scalar::all(0);
            break;
        case 'h':
            showHist = !showHist;
            if( !showHist )
                destroyWindow( "Histogram" );
            else
                namedWindow( "Histogram", 1 );
            break;
        case 'p':
            paused = !paused;
            break;
        default:
            ;
        }
    }

    return 0;
}
