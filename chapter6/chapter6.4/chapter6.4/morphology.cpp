#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

//ȫ�ֱ�������
Mat g_srcImage, g_dstImage;
int g_nElementShape = MORPH_RECT;

//�������յ�TrackBarλ�ò���
int g_nMaxIterationNum = 10;
int g_nErodeDilateNum = 0;
int g_nOpenCloseNum = 0;
int g_nTopBlackHatNum = 0;

//ȫ�ֺ�������
static void on_ErodeDilate(int, void*);
static void on_OpenClose(int, void*);
static void on_TopBlackHat(int,void*);

static void on_ErodeDilate(int, void*) {
	//����һ��ƫ����
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;			//ƫ��������ֵ
	//�Զ����
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);
	imshow("��ʴ/����", g_dstImage);

}

static void on_OpenClose(int, void*) {
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	imshow("������/������", g_dstImage);
}

static void on_TopBlackHat(int,void*) {
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	imshow("��ñ/��ñ",g_dstImage);
}

int main() {
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) {
		printf("��ȡͼƬ����! \n");
		return false;
	}
	//��ʾԭʼͼ
	namedWindow("ԭͼ");
	imshow("ԭͼ", g_srcImage);

	//������������
	namedWindow("��ʴ/����",1);
	namedWindow("������/������",1);
	namedWindow("��ñ/��ñ",1);

	//������ֵ
	g_nErodeDilateNum = 9;
	g_nOpenCloseNum = 9;
	g_nTopBlackHatNum = 2;

	//Ϊ�������ڴ���������
	createTrackbar("����ֵ:","��ʴ/����",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
	createTrackbar("����ֵ:","������/������", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("����ֵ:", "��ñ/��ñ", &g_nTopBlackHatNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);

	//��ѯ��ð�����Ϣ
	while (1) {
		int c;

		//ִ�лص�����
		on_ErodeDilate(g_nErodeDilateNum,0);
		on_OpenClose(g_nOpenCloseNum,0);
		on_TopBlackHat(g_nTopBlackHatNum,0);

		c = waitKey(0);					//���x=0����ô���޵ȴ���ȥ��ֱ���а�������
		if ((char)c == 'q' || (char)c == 27)
			break;
		if ((char)c == 49)
			g_nElementShape = MORPH_ELLIPSE;		//������1ʱ����ʹ����Բ
		else if ((char)c == 50)
			g_nElementShape = MORPH_RECT;			//����2ʱ����ʹ�þ���
		else if ((char)c == 51)
			g_nElementShape = MORPH_CROSS;			//����3ʱ����ʹ��ʮ����
		else if ((char)c == ' ')
			g_nElementShape = (g_nElementShape + 1) % 3;		//������space��ʱ��������֮��ѭ��
	}
	return 0;
}
