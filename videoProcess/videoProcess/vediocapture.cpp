#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	VideoCapture capture;
	capture.open("1.avi");

	while (1) {
		Mat frame;
		capture >> frame;
		imshow("∂¡»° ”∆µ", frame);
		waitKey(30);
	}
	return 0;
}