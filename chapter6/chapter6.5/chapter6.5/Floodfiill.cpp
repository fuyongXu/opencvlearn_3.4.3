#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

//ȫ�ֱ�������
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;			//ԭʼͼ��Ŀ��ͼ���Ҷ�ͼ����ģͼ
int g_nFillMode = 1;											//��ˮ����ģʽ
int g_nLowDifference = 20, g_nUpDifference = 20;				//�������ֵ���������ֵ
int g_nConnectivity = 4;										//��ʾfloodfill������ʶ���Ͱ�λ����ֵͨ
int g_bIsColor = true;											//�Ƿ�Ϊ��ɫͼ�ı�ʶ��
bool g_bUseMask = false;										//�Ƿ���ʾ��ģ���ڵı�ʶ��
int g_nNewMaskValue = 255;										//�µ����»��Ƶ�����ֵ

static void onDown(int event, int x, int y, void*) {
	if (event != EVENT_LBUTTONDOWN)
		return;

	//����floodFill����֮ǰ�Ĳ���׼��
	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;		//�շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ�ֵ�g_nLowDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;

	//��ʶ����0-7λΪg_nConnectivity,8-15λΪg_nNewMaskVal���ư�λ��ֵ,16-23λΪCV_FLOODFILL_FIXED_RANGE����Ϊ0
	int flags = g_nConnectivity + (g_nNewMaskValue << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	
	//�������bgrֵ
	int b = (unsigned)theRNG() & 255;			//�������һ��0-255֮���ֵ
	int g = (unsigned)theRNG() & 255;	
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;

	//���ػ��������ص���ֵ����Ϊ��ɫͼģʽ��ȡScalar(b,g,r);���ǻҶ�ͼģʽ��ȡScalar(r*0.299 + g * 0.587 + b * 0.114)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g * 0.587 + b * 0.114);

	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;			//Ŀ��ͼ�ĸ�ֵ
	int area;

	if (g_bUseMask) {
		threshold(g_maskImage,g_maskImage,1,128,THRESH_BINARY);
		area = floodFill(dst,g_maskImage,seed,newVal,&ccomp,Scalar(LowDifference,LowDifference,LowDifference),Scalar(UpDifference,UpDifference,UpDifference),flags);
		imshow("mask", g_maskImage);
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference), Scalar(UpDifference, UpDifference, UpDifference), flags);
	}
	imshow("Ч��ͼ", dst);
	cout << area << " �����ر��ػ�\n";
}

int main(int argc,char** argv) {
	g_srcImage = imread("1.jpg", 1);
	if (!g_srcImage.data) {
		printf("��ȡͼƬ���� \n");
		return false;
	}
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);			//ת����ͨ����image0���Ҷ�ͼ
	//��ʼ����ģ
	g_maskImage.create(g_srcImage.rows+2,g_srcImage.cols+2,CV_8UC1);

	namedWindow("Ч��ͼ", WINDOW_AUTOSIZE);
	createTrackbar("�������ֵ","Ч��ͼ",&g_nLowDifference,255,0);
	createTrackbar("�������ֵ","Ч��ͼ",&g_nUpDifference,255,0);

	//���ص�����
	setMouseCallback("Ч��ͼ", onDown,0);

	//ѭ����ѯ����
	while (1) {
		//����ʾЧ��ͼ
		imshow("Ч��ͼ", g_bIsColor ? g_dstImage : g_grayImage);

		//��ȡ���̰���
		int c = waitKey(0);
		if ((c & 255) == 27) {
			cout << "�����˳�......\n";
			break;
		}
		switch ((char)c)
		{
		case '1':
			//Ч��ͼ�ڻҶ�ͼ����ɫͼ֮�以��
			if (g_bIsColor) {
				//ԭ��Ϊ��ɫ��תΪ�Ҷ�ͼ�����ҽ���ģmask����Ԫ������Ϊ0
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);
				g_bIsColor = false;
			}
			else
			{
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;
			}
			break;
		case '2':
			if (g_bUseMask) {
				//�������2�����£���ʾ/������ģ����
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}

		case '3':
			//�������3�����£���ָ�ԭʼͼ��
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;

		case '4':
			//�������4�����£���ʹ�ÿշ�Χ����ˮ���
			g_nFillMode = 0;
			break;
			
		case '5':
			//�������5������,��ʹ�ý���̶���Χ����ˮ���
			g_nFillMode = 1;
			break;

		case '6':
			//�������6�����£���ʹ�ý��䡢������Χ����ˮ���
			g_nFillMode = 2;
			break;
		case '7':
			//�������7�����£��������־���ĵͰ�λʹ��4λ������ģʽ
			g_nConnectivity = 4;
			break;
		case '8':
			//�������8�����£��������־���ĵͰ�λʹ��4λ������ģʽ
			g_nConnectivity = 8;
			break;
	
		}
	}
	return 0;
}