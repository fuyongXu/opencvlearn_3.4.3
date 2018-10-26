#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat srcImage1 = imread("1.jpg");
	imshow("原图",srcImage1);
	
	Mat detImage1;
	blur(srcImage1, detImage1, Size(7,7));

	imshow("效果赛", detImage1);
	waitKey(0);

	return 0;

}