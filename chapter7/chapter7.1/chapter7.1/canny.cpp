#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat src = imread("1.jpg");
	Mat src1 = src.clone();

	imshow("ԭʼͼ",src);

	//�߽׵�canny�÷���ת�ɻҶ�ͼ�����룬��canny����󽫵õ��ı�Ե��Ϊ���룬����ԭͼ��Ч��ͼ�ϣ��õ���ɫ�ı�Եͼ��
	Mat dst, edge, gray;

	//1��������srcͬ���ͺʹ�С�ľ���(dst)
	dst.create(src1.size(), src1.type());

	//2��ת�ɻҶ�ͼ
	cvtColor(src1,gray,COLOR_BGR2GRAY);

	//3������
	blur(gray,edge,Size(3,3));

	//4������canny����
	Canny(edge,edge,3,9,3);

	//5����g_dstImage�ڵ�����Ԫ������Ϊ0
	dst = Scalar::all(0);

	//6��ʹ��Canny��������ı�Եͼ��Ϊ���룬����ԭͼ����Ŀ��g_dst��
	src1.copyTo(dst, edge);

	//��ʾЧ��ͼ
	imshow("Ч��ͼ",dst);

	waitKey(0);
	return 0;

	}