#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main() {
	Mat srcImage = imread("1.jpg",1);
	Mat dstImage;
	if (!srcImage.data) {
		printf("读取图片出错");
		return false;
	}

	cvtColor(srcImage,srcImage,COLOR_BGR2GRAY);
	imshow("原始图",srcImage);

	equalizeHist(srcImage, dstImage);
	imshow("效果图",dstImage);

	waitKey(0);
	return 0;
 }