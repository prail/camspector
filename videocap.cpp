#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
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
    string filename;   // name of the output video file

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
    
    
    // Create a new VideoWriter, and check if we succeeded
    VideoWriter writer;
    codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
    filename = "./live.avi";
    writer.open(filename, codec, fps, src.size(), isColor);
    if (!writer.isOpened()) {
        cerr << "Could not open the output video file for write\n";
        return -1;
    }
    
    // Create a new car cascade classifier
    // from here:
    // https://github.com/Aman-Preet-Singh-Gulati/Vehicle-count-detect/blob/main/Required%20Files/cars.xml
    
    CascadeClassifier car_cascade;
    if (!car_cascade.load("cars.xml"))
    {
      cerr << "ERROR! unable to load car cascade classifier 'cars.xml'\n";
      return 1;
    }
    
    // Loop until a keypress is received
    cout << "Writing videofile: " << filename << endl
         << "Press any key to terminate" << endl;
    while (waitKey(5) < 0)
    {
        // Abort if unable to read a frame from the capture
        if (!cap.read(src)) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }
        
        Mat frame_gray;
        
        cvtColor(src, frame_gray, COLOR_BGR2GRAY);
        equalizeHist(frame_gray, frame_gray);
        
        std::vector<Rect> cars;
        car_cascade.detectMultiScale(frame_gray, cars);
        
        for (size_t i = 0; i < cars.size(); i++)
        {
            rectangle(src, cars[i], cv::Scalar(0, 255, 0));
        }
        
        // encode the frame into the videofile stream
        writer.write(src);
        
        // show live and wait for a key with timeout long enough to show images
        imshow("Live", src);
    }
    // the videofile will be closed and released automatically in VideoWriter destructor
    return 0;
}
