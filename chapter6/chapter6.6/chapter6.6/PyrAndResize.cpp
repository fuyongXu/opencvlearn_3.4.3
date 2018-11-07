#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "�����򴰿ڡ�"
Mat g_srcImage, g_dstImage, g_tmpImage;

int main()
{
	g_srcImage = imread("1.jpg");
	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, g_srcImage);
	g_tmpImage = g_srcImage;
	g_dstImage = g_tmpImage;
	int key = 0;
	while (1) //��ѯ��ȡ������Ϣ
	{
		key = waitKey(9); //��ȡ��ֵ��key������
		switch (key) {
		case 27:  //����ESC
		case 'q':
			return 0;
			break;
		case '1':
			pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			cout << "��⵽������1�������£���ʼ���л��ڡ�pyrUp��������ͼƬ�Ŵ�ͼƬ�ߴ�*2" << endl;
			break;
		case '2':
			pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			cout << "��⵽������2�������£���ʼ���л��ڡ�pyrDown��������ͼƬ��С��ͼƬ�ߴ�/2" << endl;
			break;
		case '3':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			cout << "��⵽������3�������£���ʼ���л��ڡ�resize��������ͼƬ�Ŵ�ͼƬ�ߴ�*2" << endl;
			break;
		case '4':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			cout << "��⵽������4�������£���ʼ���л��ڡ�pyrUp��������ͼƬ��С��ͼƬ�ߴ�/2" << endl;
			break;
		}
		imshow(WINDOW_NAME, g_dstImage);
		g_tmpImage = g_dstImage; //��dst��ֵ��tmp��������һ��ѭ��
	}

	return 0;
}