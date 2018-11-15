#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "原始窗口"
#define WINDOW_NAME2 "经过Wrap后的图像"
#define WINDOW_NAME3 "经过Wrap和Rotate后的图像"

int main() {
	system("color 1A");

	//定义两种点，代表两个三角形
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];

	//定义一些Mat变量
	Mat rotMat(2,3,CV_32FC1);
	Mat warpMat(2,3,CV_32FC1);
	Mat srcImage, dstImage_wrap, dstImage_wrap_rotate;

	//加载图像
	srcImage = imread("1.jpg",1);
	if (!srcImage.data) {
		printf("读取图片出错！\n");
		return false;
	}
	dstImage_wrap = Mat::zeros(srcImage.rows,srcImage.cols,srcImage.type());

	srcTriangle[0] = Point2f(0,0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols-1),0);
	srcTriangle[2] = Point2f(0,static_cast<float>(srcImage.rows-1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65),static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15),static_cast<float>(srcImage.rows*0.6));
	
	//求得仿射变换
	warpMat = getAffineTransform(srcTriangle,dstTriangle);

	//对源图像应用刚刚求的仿射变换
	warpAffine(srcImage,dstImage_wrap,warpMat,dstImage_wrap.size());

	//对图像进行缩放后再旋转
	Point center = Point(dstImage_wrap.cols/2,dstImage_wrap.rows/2);

	double angle = -30.0;
	double scale = 0.8;

	//通过上面的旋转细节信息求得旋转矩阵
	rotMat = getRotationMatrix2D(center,angle,scale);
	warpAffine(dstImage_wrap,dstImage_wrap_rotate,rotMat,dstImage_wrap.size());

	imshow(WINDOW_NAME1,srcImage);
	imshow(WINDOW_NAME2,dstImage_wrap);
	imshow(WINDOW_NAME3,dstImage_wrap_rotate);

	waitKey(0);
	return 0;
}