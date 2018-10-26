#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg");
	//Mat srcImage = imread("D:\\学习\\OpenCV3-examples\\src\\【1】第一章\\【3】图像腐蚀\\3_图像腐蚀\\1.jpg");
	//显示原图
	imshow("原图", srcImage);
	//腐蚀图片
	//Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  //该函数返回指定形状和大小的结构元素(内核矩阵)
	//Mat detImage;
	//erode(srcImage, detImage, element);
	//imshow("腐蚀图片", detImage);

	//blur(srcImage, detImage, Size(7, 7));
	//imshow("模糊图片", detImage);

	//边缘检测，先将图像转为灰度图
	Mat dstImage, edge, grayImage;

	dstImage.create(srcImage.size(), srcImage.type());

	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);

	//先使用（3,3）的内核进行降噪
	blur(grayImage, edge, Size(3, 3));

	//运行Canny算子
	Canny(edge, edge, 3, 9, 3);
	
	imshow("效果图", edge);


	waitKey(0);
	return 0;
}