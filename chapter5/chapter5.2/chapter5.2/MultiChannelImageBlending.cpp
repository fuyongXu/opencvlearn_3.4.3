#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

bool MultiChannelBlending();

//��ͨ����ϵ�ʵ�ֺ���
bool MultiChannelBlending() {
	Mat srcImage;
	Mat logoImage;
	vector<Mat>channels;
	Mat imageBlueChannel;

	//��ɫ��������
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");
	if (!logoImage.data) {
		printf("��ȡdota_logo���� \n");
		return false;
	}
	if (!srcImage.data) {
		printf("��ȡdata_jugg����! \n");
		return false;
	}
	split(srcImage, channels);		//����ɫ��ͨ��
	//��ԭͼ����ɫͨ�����÷��ظ�imageBlueChannel��ע�������á�
	imageBlueChannel = channels.at(0);
	//��ԭͼ����ɫͨ���ģ�500,250���������·���һ�������logoͼ����м�Ȩ���������õ��Ļ�Ͻ���浽imageBlueChannel��
	addWeighted(imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0.0, imageBlueChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
	//��������ͨ�����ºϲ�Ϊһ����ͨ��
	merge(channels, srcImage);
	namedWindow("ԭͼ+logo��ɫͨ��");
	imshow("ԭͼ+logo��ɫͨ��", srcImage);

	//��ɫ��������
	Mat imageGreenChannel;

	//���¶���ͼƬ
	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data) {
		printf("����dota_logo���� \n");
		return false;
	}
	if (!srcImage.data) {
		printf("����dota_jugg���� \n");
		return false;
	}
	split(srcImage, channels);
	imageGreenChannel = channels.at(1);
	addWeighted(imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0., imageGreenChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);

	namedWindow("ԭͼ+Greenͨ��");
	imshow("ԭͼ+Greenͨ��", srcImage);

	//��ɫ��������
	Mat imageRedChannel;

	logoImage = imread("dota_logo.jpg", 0);
	srcImage = imread("dota_jugg.jpg");

	if (!logoImage.data) {
		printf("����dota_logo.jpg����\n");
		return false;
	}
	if (!srcImage.data) {
		printf("����dota_jugg���� \n");
		return false;
	}
	split(srcImage, channels);
	imageRedChannel = channels.at(2);
	addWeighted(imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)), 1.0, logoImage, 0.5, 0.0, imageRedChannel(Rect(500, 250, logoImage.cols, logoImage.rows)));
	merge(channels, srcImage);

	namedWindow("ԭͼ+��ɫͨ��");
	imshow("ԭͼ+��ɫͨ��", srcImage);
	return true;
}
int main(){
	system("color 9F");
	if (MultiChannelBlending()) {
		cout << endl << "���гɹ�";
	}
	waitKey(0);
	return true;
}