#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage;
int g_nTrackbarNumber = 0;		//0��ʾ��ʴ��1��ʾ����
int g_nStructElementSize = 3;	//�ں˳ߴ�

void Process();									//���ͺ͸�ʴ������
void on_TrackbarNumChange(int, void*);
void on_ElementSizeChange(int, void*);

void Process() {
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point(g_nStructElementSize, g_nStructElementSize));
	if (g_nTrackbarNumber == 0) {
		erode(g_srcImage, g_dstImage, element);
	}
	else
	{
		dilate(g_srcImage, g_dstImage, element);
	}
	imshow("Ч��ͼ",g_dstImage);
}		//��ʴ������֮���л����صĻص�����
	void on_TrackbarNumChange(int, void*) {
		Process();
	}
	void on_ElementSizeChange(int, void*) {
		Process();
	}
	int main() {
		system("color5E");

		g_srcImage = imread("1.jpg");
		if (!g_srcImage.data) {
			printf("��ȡͼƬ����\n");
			return false;
		}
		//��ʾԭʼͼ��
		namedWindow("ԭͼ");
		imshow("ԭͼ",g_srcImage);

		//���г��θ�ʴ��������ʾЧ��ͼ
		Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),Point(g_nStructElementSize,g_nStructElementSize));
		erode(g_srcImage, g_dstImage, element);
		namedWindow("Ч��ͼ");
		imshow("Ч��ͼ",g_dstImage);

		//�����켣��
		createTrackbar("��ʴ/����", "Ч��ͼ", &g_nTrackbarNumber, 1, on_TrackbarNumChange);
		createTrackbar("�ں˳ߴ�:", "Ч��ͼ", &g_nStructElementSize, 21, on_ElementSizeChange);

		while(char(waitKey(1))!='q'){}
		return 0;
}


