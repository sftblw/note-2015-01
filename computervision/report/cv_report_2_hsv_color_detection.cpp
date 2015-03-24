//charFullName[80] = "d:\\dip\\Images\\";
char FullName[80] = "G:/libraries/cv/images/";
char FileName[50] = "fruits.jpg";
/*
	Report #2 code of Computer Vision lecture
	Seokyeong Univ, 2012305087 Choi, Chan-Hwi, Dept of C.E
	
	ver 2 : Satuation control added
	
	based on distributed code.
	by Prof. Kim, Jin-heon

	distributed codes are based on...

	# 1.
	// This file contains material supporting chapter 3 of the cookbook:
	// Computer Vision Programming using the OpenCV Library.   by Robert Laganiere, Packt Publishing, 2011.
	// Files:   colorDetection.h,   colorDetection.cpp,     colordetector.cpp,  correspond to Recipe:
	// Using the Strategy Pattern in Algorithm Design

	# 2.
	// Program to display a video from attached default camera device and detect colored blobs using simple R G and B thresholding
	// Author: Samarth Manoj Brahmbhatt, University of Pennsylvania
	// 이 예제는 다음 자료에서 만들어졌습니다.
	// Practical OpenCV, Listing 5-7: Simple color based object detector
*/

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/*
	Process a frame based on property that this class has, in method of HSV.

	- Assumes frame typed as unsigned char (8bit).
	- Assumes first detected type will not change.

	@member hueRange range of hue. range : 0 -> 180
	@member hueTarget target hue. range : 0 -> 180
*/
class FrameHsvDetector{
private:
	int hueRange = 10;
	int hueTarget = 0;

	int satRange = 100;
	int satTarget = 0;

	cv::Mat result;
	bool resultInit = false;

	//////////
	// processing interfaces
public:
	/*!
	process color detection of BGR spaced frame by HSV.
	*/
	void detectBGR(cv::Mat& frame) {
		cv::Mat conv;
		cvtColor(frame, conv, CV_BGR2HSV);

		// call detection algorithm
		detect(conv);
	}

	//////////
	// processing algorithms
private:
	/*!
	process color detection of HSV cv::Mat.
	*/
	void detect(const cv::Mat& frame) {
		if (resultInit == false)
			result.create(frame.rows, frame.cols, CV_8U);

		// iteration pattern from ColorDetector class

		// get the iterators
		cv::Mat_<cv::Vec3b>::const_iterator it = frame.begin<cv::Vec3b>();
		cv::Mat_<cv::Vec3b>::const_iterator itend = frame.end<cv::Vec3b>();
		cv::Mat_<uchar>::iterator itout = result.begin<uchar>();

		// process each pixel ---------------------
		for (; it != itend; ++it, ++itout) {
			// compute distance from target color
			if (
				(getDistanceHue(*it) <= hueRange)
				&&
				(getDistanceSat(*it) <= satRange)
				) {
				*itout = 255;
			}
			else {
				*itout = 0;
			}
			// end of pixel processing ----------------
		}
	}

	int getDistanceHue(const cv::Vec3b& color) const {
		return abs( (color[0] - hueTarget) % 180 );
	}

	int getDistanceSat(const cv::Vec3b& color) const {
		return abs(color[1] - satTarget);
	}

	/////////////
	// initializer
public:


	///////////
	// getter, setter
public:
	void setHueRange(int& hueRange) {

		if (hueRange > 360/2)
			hueRange = 360/2;
		if (hueRange < 0)
			hueRange = 0;

		this->hueRange = hueRange;
	}

	void setHueTarget(int& hueTarget) {
		
		if (hueTarget > 360/2)
			hueTarget = 360/2;
		if (hueTarget < 0)
			hueTarget = 0;

		this->hueTarget = hueTarget;
	}

	void setSatRange(int& satRange) {

		if (satRange > 360 / 2)
			satRange = 360 / 2;
		if (satRange < 0)
			satRange = 0;

		this->satRange = satRange;
	}

	void setSatTarget(int& satTarget) {

		if (satTarget > 360 / 2)
			satTarget = 360 / 2;
		if (satTarget < 0)
			satTarget = 0;

		this->satTarget = satTarget;
	}


	// get the result mat array.
	const cv::Mat& getResult() {
		return result;
	}

	const int getHueTarget() {
		return hueTarget;
	}
	const int getHueRange() {
		return hueRange;
	}
	const int getSatTarget() {
		return satTarget;
	}
	const int getSatRange() {
		return satRange;
	}
};
static FrameHsvDetector fhd; // only one existing object

Mat frame;
int track_hueRange;
int track_hueTarget;

void on_hueRange_trackbar(int track_hueRange, void *) {
	fhd.setHueRange(track_hueRange);
}

void on_hueTarget_trackbar(int track_hueTarget, void *) {
	fhd.setHueTarget(track_hueTarget);
}

int track_satRange;
int track_satTarget;

void on_satRange_trackbar(int track_satRange, void *) {
	fhd.setSatRange(track_satRange);
}

void on_satTarget_trackbar(int track_satTarget, void *) {
	fhd.setSatTarget(track_satTarget);
}

Point click;		// 클릭한 점의 좌표
// Callback function for mouse events
static void mouse_callback(int event, int x, int y, int, void *)
{
	// When the left mouse button is pressed, record its position and save it in corner1 
	if (event == EVENT_LBUTTONDOWN)
	{
		click.x = x;
		click.y = y;
		cout << "point (x,y) at " << click << endl;
		cout << "	color(BGR)=" << frame.at<cv::Vec3b>(y, x) << endl;

		cv::Mat roiPoint = frame(cv::Rect(x,y,1,1));
		cv::Mat pixel;
		pixel = roiPoint.clone();

		cvtColor(pixel, pixel, CV_BGR2HSV);

		track_hueTarget = pixel.at<cv::Vec3b>(0, 0)[0];
		track_satTarget = pixel.at<cv::Vec3b>(0, 0)[1];
		
		cout << "hue is " << track_hueTarget << endl;
		cout << "sat is " << track_satTarget << endl;
		fhd.setHueTarget(track_hueTarget);
		fhd.setSatTarget(track_satTarget);
		setTrackbarPos("hue-Target", "Segmentation", track_hueTarget); // update hue track bar
		setTrackbarPos("sat-Target", "Segmentation", track_satTarget); // update hue track bar
		
	}

}



int main()
{
	// Create a VideoCapture object to read from video file
	// 0 is the ID of the built-in laptop camera, change if you want to use other camera
	VideoCapture cap(0);						// 카메라 번호를 잘 선택하세요. 
	//cap.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	//cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240);
	cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	//check if the file was opened properly
	if (!cap.isOpened())
	{
		cout << "Capture could not be opened succesfully" << endl;
		return -1;
	}

	namedWindow("Video");
	namedWindow("Segmentation");

	// devide 2 : unsigned char
	createTrackbar("hue-Range", "Segmentation", &track_hueRange, 360/2, on_hueRange_trackbar);
	createTrackbar("hue-Target", "Segmentation", &track_hueTarget, 360/2, on_hueTarget_trackbar);
	setTrackbarPos("hue-Range", "Segmentation", fhd.getHueRange());
	setTrackbarPos("hue-Target", "Segmentation", fhd.getHueTarget());
	
	createTrackbar("sat-Range", "Segmentation", &track_satRange, 360 / 2, on_satRange_trackbar);
	createTrackbar("sat-Target", "Segmentation", &track_satTarget, 360 / 2, on_satTarget_trackbar);
	setTrackbarPos("sat-Range", "Segmentation", fhd.getSatRange());
	setTrackbarPos("sat-Target", "Segmentation", fhd.getSatTarget());

	// 마우스 클릭 이벤트를 감지한다.
	setMouseCallback("Video", mouse_callback);

	double time = 0;
	unsigned int frames = 0;
	while (char(waitKey(1)) != 0x1b && cap.isOpened())
	{
		frames++;
		double t0 = getTickCount();
		cap >> frame;
		// Check if the video is over
		if (frame.empty())
		{
			cout << "Video over" << endl;
			break;
		}

		fhd.detectBGR(frame);

		imshow("Video", frame);
		imshow("Segmentation", fhd.getResult());
		//time += (getTickCount() - t0) / getTickFrequency();
		//cout << frames / time << " fps" << endl;
	}

	return 0;
}
