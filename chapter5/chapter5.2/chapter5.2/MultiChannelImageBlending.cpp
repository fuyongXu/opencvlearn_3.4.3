#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

bool MultiChannelBlending();

//多通道混合的实现函数
bool MultiChannelBlending() {
	Mat srcImage;
	Mat logoImage;
	vector<Mat>channels;
	Mat imageBlueChannel;

	//蓝色分量部分
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data) {
		printf("读取dota_logo错误！ \n");
		return false;
	}
	if (!srcImage.data) {
		printf("读取data_jugg错误! \n");
		return false;
	}
	split(srcImage, channels);		//分离色彩通道
	//将原图的蓝色通道引用返回给imageBlueChannel，注意是引用。
	imageBlueChannel = channels.at(0);
	//将原图的蓝色通道的（500,250）坐标右下方的一块区域和logo图像进行加权操作，将得到的混合结果存到imageBlueChannel中
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0.0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
	//将三个单通道重新合并为一个三通道
	merge(channels, srcImage);
	namedWindow("原图+logo蓝色通道");
	imshow("原图+logo蓝色通道", srcImage);

	//绿色分量部分
	Mat imageGreenChannel;

	//重新读入图片
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data) {
		printf("读入dota_logo错误！ \n");
		return false;
	}
	if (!srcImage.data) {
		printf("读入dota_jugg错误！ \n");
		return false;
	}
	split(srcImage, channels);
	imageGreenChannel = channels.at(1);
	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0., imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);

	namedWindow("原图+Green通道");
	imshow("原图+Green通道", srcImage);

	//红色分量部分
	Mat imageRedChannel;

	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data) {
		printf("读入dota_logo.jpg错误！\n");
		return false;
	}
	if (!srcImage.data) {
		printf("读入dota_jugg错误！ \n");
		return false;
	}
	split(srcImage, channels);
	imageRedChannel = channels.at(2);
	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0.0, imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);

	namedWindow("原图+红色通道");
	imshow("原图+红色通道", srcImage);
	return true;
}
int main(){
	system("color 9F");
	if (MultiChannelBlending()) {
		cout << endl << "运行成功";
	}
	waitKey(0);
	return true;
}