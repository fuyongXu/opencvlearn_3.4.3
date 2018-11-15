#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat src = imread("1.jpg");
	Mat src1 = src.clone();

	imshow("原始图",src);

	//高阶的canny用法，转成灰度图，降噪，用canny，最后将得到的边缘作为掩码，拷贝原图到效果图上，得到彩色的边缘图。
	Mat dst, edge, gray;

	//1、创建与src同类型和大小的矩阵(dst)
	dst.create(src1.size(), src1.type());

	//2、转成灰度图
	cvtColor(src1,gray,COLOR_BGR2GRAY);

	//3、降噪
	blur(gray,edge,Size(3,3));

	//4、运行canny算子
	Canny(edge,edge,3,9,3);

	//5、将g_dstImage内的所有元素设置为0
	dst = Scalar::all(0);

	//6、使用Canny算子输出的边缘图作为掩码，来将原图拷到目标g_dst中
	src1.copyTo(dst, edge);

	//显示效果图
	imshow("效果图",dst);

	waitKey(0);
	return 0;

	}