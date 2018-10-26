#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

//实现ROI的线性混合
bool ROI_LinearBlending() {
	Mat srcImage1 = imread("dota_pa.jpg",1);
	Mat logoImage = imread("dota_logo.jpg");

	if (!srcImage1.data) {
		printf("读取dota_pa.jpg错误！ \n");
		return false;
	}
	if (!logoImage.data) {
		printf("读取dota_logo.jpg错误 \n");
		return false;
	}

	Mat imageROI;
	imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));
	//imageROI = srcImage1(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);
	namedWindow("ROI线性混合窗口");
	imshow("区域线性混合示例窗口", srcImage1);
	return true;
}

//利用感兴趣区域ROI实现图像叠加

bool ROI_AddImage() {
	Mat srcImage2 = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage2.data) {
		printf("读取srcImage2错误！\n");
		return false;
	}
	if (!logoImage.data) {
		printf("读取logoImage错误！\n");
		return false;
	}
	Mat imageROI = srcImage2(Rect(200,250,logoImage.cols,logoImage.rows));
	//加载掩模(必须是灰度图)
	Mat mask = imread("dota_logo.jpg", 0);
	//将掩模复制到ROI
	logoImage.copyTo(imageROI, mask);
	namedWindow("利用ROI实现图像叠加的窗口");
	imshow("利用ROI实现图像叠加的窗口",srcImage2);
	return true;
}

//使用cv::addWeighted()函数实现图像线性混合
bool LinearBlending() {
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage3, srcImage4, dstImage;
	srcImage3 = imread("mogu.jpg");
	srcImage4 = imread("rain.jpg");
	if (!srcImage3.data) {
		printf("读取srcImage3错误！ \n");
		return false;
	}
	if (!srcImage4.data) {
		printf("读取srcImage4错误！ \n");
		return false;
	}
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage3,alphaValue,srcImage4,betaValue,0.0,dstImage);

	namedWindow("原图",1);
	imshow("原图", srcImage3);

	namedWindow("效果图", 1);
	imshow("效果图",dstImage);
	return true;
}

int main() {
	system("color 5E");
	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending()) {
		cout << endl << "运行成功";
	}
	waitKey(0);
	return 0;
}