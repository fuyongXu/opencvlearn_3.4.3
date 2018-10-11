#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

int main() {
	Mat girl = imread("girl.jpg");
	namedWindow("picture1");
	imshow("picture1", girl);

	//混合两张图片
	Mat image = imread("dota.jpg");
	namedWindow("picture2");
	imshow("picture2", image);

	Mat logo = imread("dota_logo.jpg");
	namedWindow("picture3");
	imshow("picture3", logo);

	//定义一个用于存储ROI的Mat
	Mat imageROI;

	imageROI = image(Rect(800, 350, logo.cols, logo.rows));

	//将Logo加到原图上
	addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);

	//显示结果
	namedWindow("dota+logo");
	imshow("data+logo", image);

	imwrite("dataAndlogo.jpg", image);

	waitKey(0);
	return 0;
}