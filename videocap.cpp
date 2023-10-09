#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	Mat    src;        // The current frame from the video stream
	bool   isColor;    // is the source video color or not?
	int    codec;      // the desired codec
	double fps = 25.0; // framerate of the created video stream

	// Check for the minimum number of command line arguments
	if (argc != 2)
	{
		cerr << "ERROR! need to be passed the stream to do analysis on\n";
		return 1;
	}

	// Create a new video capture and check for failure
	VideoCapture cap(argv[1]);
	if (!cap.isOpened()) {
		cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	// Get one frame from camera to know frame size and type,
	// check for success
	cap >> src;
	if (src.empty()) {
		cerr << "ERROR! blank frame grabbed\n";
		return -1;
	}

	// determine if input video is color or not
	isColor = (src.type() == CV_8UC3);

	// PROBABLY NEED TO REMOVE THIS   
	// Create a new VideoWriter, and check if we succeeded
	Mat roi;
	if (!cap.read(src)) {
		cerr << "ERROR! blank frame grabbed\n";
		return 1;       	
	}

	/* 720, 480
	 * 36 x 20
	 */
	int startX = 684,
	    startY = 460,
	    width  = 36,
	    height = 20;

	roi = Mat(src, Rect(startX,startY,width,height));
	rectangle(src, Rect(startX,startY,width,height), cv::Scalar(0,255,0));
	// show live and wait for a key with timeout long enough to show images
	imwrite("test.png", roi);

	// the videofile will be closed and released automatically in VideoWriter destructor
	return 0;
}
