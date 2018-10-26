#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage;
int g_nTrackbarNumber = 0;		//0表示腐蚀，1表示膨胀
int g_nStructElementSize = 3;	//内核尺寸

void Process();									//膨胀和腐蚀处理函数
void on_TrackbarNumChange(int, void*);
void on_ElementSizeChange(int, void*);

void Process() {
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * g_nStructElementSize + 1, 2 * g_nStructElementSize + 1), Point(g_nStructElementSize, g_nStructElementSize));
	if (g_nTrackbarNumber == 0) {
		erode(g_srcImage, g_dstImage, element);
	}
	else
	{
		dilate(g_srcImage, g_dstImage, element);
	}
	imshow("效果图",g_dstImage);
}		//腐蚀和膨胀之间切换开关的回调函数
	void on_TrackbarNumChange(int, void*) {
		Process();
	}
	void on_ElementSizeChange(int, void*) {
		Process();
	}
	int main() {
		system("color5E");

		g_srcImage = imread("1.jpg");
		if (!g_srcImage.data) {
			printf("读取图片出错！\n");
			return false;
		}
		//显示原始图像
		namedWindow("原图");
		imshow("原图",g_srcImage);

		//进行初次腐蚀操作并显示效果图
		Mat element = getStructuringElement(MORPH_RECT,Size(2*g_nStructElementSize+1,2*g_nStructElementSize+1),Point(g_nStructElementSize,g_nStructElementSize));
		erode(g_srcImage, g_dstImage, element);
		namedWindow("效果图");
		imshow("效果图",g_dstImage);

		//创建轨迹条
		createTrackbar("腐蚀/膨胀", "效果图", &g_nTrackbarNumber, 1, on_TrackbarNumChange);
		createTrackbar("内核尺寸:", "效果图", &g_nStructElementSize, 21, on_ElementSizeChange);

		while(char(waitKey(1))!='q'){}
		return 0;
}


