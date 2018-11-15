#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat src, src_gray, dst, abs_dst;
	src = imread("1.jpg");
	imshow("ԭͼ", src);

	//ʹ�ø�˹�˲�������������
	GaussianBlur(src,src,Size(3,3),0,0,BORDER_DEFAULT);
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(src,src_gray,COLOR_RGB2GRAY);
	//ʹ��Laplacian����
	Laplacian(src_gray,dst,CV_16S,3,1,0,BORDER_DEFAULT);
	//�������ֵ���������ת����8λ
	convertScaleAbs(dst,abs_dst);
	imshow("Ч��ͼ",abs_dst);
	waitKey(0);
	return 0;
}