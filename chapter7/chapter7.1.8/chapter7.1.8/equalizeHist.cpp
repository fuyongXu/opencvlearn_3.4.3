#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
int main() {
	Mat srcImage = imread("1.jpg",1);
	Mat dstImage;
	if (!srcImage.data) {
		printf("��ȡͼƬ����");
		return false;
	}

	cvtColor(srcImage,srcImage,COLOR_BGR2GRAY);
	imshow("ԭʼͼ",srcImage);

	equalizeHist(srcImage, dstImage);
	imshow("Ч��ͼ",dstImage);

	waitKey(0);
	return 0;
 }