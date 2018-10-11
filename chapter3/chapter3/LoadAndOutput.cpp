#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

int main() {
	Mat girl = imread("girl.jpg");
	namedWindow("picture1");
	imshow("picture1", girl);

	//�������ͼƬ
	Mat image = imread("dota.jpg");
	namedWindow("picture2");
	imshow("picture2", image);

	Mat logo = imread("dota_logo.jpg");
	namedWindow("picture3");
	imshow("picture3", logo);

	//����һ�����ڴ洢ROI��Mat
	Mat imageROI;

	imageROI = image(Rect(800, 350, logo.cols, logo.rows));

	//��Logo�ӵ�ԭͼ��
	addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);

	//��ʾ���
	namedWindow("dota+logo");
	imshow("data+logo", image);

	imwrite("dataAndlogo.jpg", image);

	waitKey(0);
	return 0;
}