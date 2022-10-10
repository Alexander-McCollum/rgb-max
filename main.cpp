#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void maximize_intensity(uchar* b, uchar* g, uchar* r)
{
	if (*b > *g) {
		if (*b > *r) {
			*b = 255;
			*g = 0;
			*r = 0;
		}
		else {
			*b = 0;
			*g = 0;
			*r = 255;
		}
	}
	else {
		if (*g > *r) {
			*b = 0;
			*g = 255;
			*r = 0;
		}
		else {
			*b = 0;
			*g = 0;
			*r = 255;
		}
	}
}

int main()
{
	//create the capture object
	VideoCapture cap(CAP_ANY);
	while (1)
	{
		// Get the frame
		Mat frame;
		cap >> frame;
		//Check if frame is empty or not
		if (frame.empty())
		{
			cerr << " could not get frame." << endl;
			return -1;
		}
		for (int y = 0; y < frame.rows; y++) {
			for (int x = 0; x < frame.cols; x++) {
				// Get BGR info for one pixel
				Vec3b intensity = frame.at<Vec3b>(y, x);
				uchar blue = intensity.val[0];
				uchar green = intensity.val[1];
				uchar red = intensity.val[2];
				// Set the colour value with the highest intensity to max intensity (255)
				maximize_intensity(&blue, &green, &red);
				frame.at<Vec3b>(y, x)[0] = blue;
				frame.at<Vec3b>(y, x)[1] = green;
				frame.at<Vec3b>(y, x)[2] = red;
			}
		}
		imshow("Live video stream", frame);
		if (waitKey(33) >= 0) {
			break;
		}
	}
	return 0;
}