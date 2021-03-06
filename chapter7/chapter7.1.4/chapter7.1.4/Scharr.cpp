#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat grad_x, grad_y, abs_grad_x, abs_grad_y, dst;
	Mat src = imread("1.jpg");

	imshow("原始图",src);

	//求X方向的梯度
	Scharr(src,grad_x,CV_16S,1,0,1,0,BORDER_DEFAULT);
	convertScaleAbs(grad_x,abs_grad_x);
	imshow("x方向的效果图",abs_grad_x);

	//求Y方向的梯度
	Scharr(src,grad_y,CV_16S,1,0,1,0,BORDER_DEFAULT);
	convertScaleAbs(grad_y,abs_grad_y);
	imshow("y方向的效果图",abs_grad_y);

	//合并梯度
	addWeighted(abs_grad_x,0.5,abs_grad_y,0.5,0,dst);

	imshow("合并梯度后的效果图",dst);

	waitKey(0);
	return 0;
}