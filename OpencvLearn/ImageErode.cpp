#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg");
	//Mat srcImage = imread("D:\\ѧϰ\\OpenCV3-examples\\src\\��1����һ��\\��3��ͼ��ʴ\\3_ͼ��ʴ\\1.jpg");
	//��ʾԭͼ
	imshow("ԭͼ", srcImage);
	//��ʴͼƬ
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  //�ú�������ָ����״�ʹ�С�ĽṹԪ��(�ں˾���)
	//Mat detImage;
	//erode(srcImage, detImage, element);
	//imshow("��ʴͼƬ", detImage);

	//blur(srcImage, detImage, Size(7, 7));
	//imshow("ģ��ͼƬ", detImage);

	//��Ե��⣬�Ƚ�ͼ��תΪ�Ҷ�ͼ
	Mat dstImage, edge, grayImage;

	dstImage.create(srcImage.size(), srcImage.type());

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	//��ʹ�ã�3,3�����ں˽��н���
	blur(grayImage, edge, Size(3, 3));

	//����Canny����
	Canny(edge, edge, 3, 9, 3);
	
	imshow("Ч��ͼ", edge);


	waitKey(0);
	return 0;
}