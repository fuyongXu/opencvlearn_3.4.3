#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat srcImage1 = imread("1.jpg");
	imshow("ԭͼ",srcImage1);
	
	Mat detImage1;
	blur(srcImage1, detImage1, Size(7,7));

	imshow("Ч����", detImage1);
	waitKey(0);

	return 0;

}