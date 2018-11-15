#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main() {
	Mat srcImage = imread("1.jpg");

	Mat midImage, dstImage;

	//���б�Ե����ת��Ϊ�Ҷ�ͼ
	Canny(srcImage,midImage,50,200,3);
	cvtColor(midImage,dstImage,CV_GRAY2BGR);

	//���л���任
	vector<Vec2f>lines;
	HoughLines(midImage,lines,1,CV_PI/180,150,0,0);

	//������ͼ�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta);
		double b = sin(theta);

		double x0 = a * rho, y0 = b * rho;

		pt1.x = cvRound(x0+1000*(-b));		//cvRound()�����ظ�������ӽ�������ֵ������������
		pt1.y = cvRound(y0+1000*(a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0-1000*(a));

		line(dstImage, pt1,pt2,Scalar(55,100,195),1,LINE_AA);	//����ͨ������Scalar������GBR����ֵ�õ���Ҫ��������ɫ

	}
	imshow("ԭͼ",srcImage);
	imshow("��Ե�����ͼ",midImage);
	imshow("Ч��ͼ",dstImage);

	waitKey(0);
	return 0;
}