#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

//全局变量声明
Mat g_srcImage, g_dstImage, g_grayImage, g_maskImage;			//原始图、目标图、灰度图、掩模图
int g_nFillMode = 1;											//漫水填充的模式
int g_nLowDifference = 20, g_nUpDifference = 20;				//负差最大值、正差最大值
int g_nConnectivity = 4;										//表示floodfill函数标识符低八位的连通值
int g_bIsColor = true;											//是否为彩色图的标识符
bool g_bUseMask = false;										//是否显示掩模窗口的标识符
int g_nNewMaskValue = 255;										//新的重新绘制的像素值

static void onDown(int event, int x, int y, void*) {
	if (event != EVENT_LBUTTONDOWN)
		return;

	//调用floodFill函数之前的参数准备
	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;		//空范围的漫水填充，此值设为0，否则设为全局的g_nLowDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;

	//标识符的0-7位为g_nConnectivity,8-15位为g_nNewMaskVal左移八位的值,16-23位为CV_FLOODFILL_FIXED_RANGE或者为0
	int flags = g_nConnectivity + (g_nNewMaskValue << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);
	
	//随机生成bgr值
	int b = (unsigned)theRNG() & 255;			//随机返回一个0-255之间的值
	int g = (unsigned)theRNG() & 255;	
	int r = (unsigned)theRNG() & 255;
	Rect ccomp;

	//在重绘区域像素的新值，若为彩色图模式，取Scalar(b,g,r);若是灰度图模式，取Scalar(r*0.299 + g * 0.587 + b * 0.114)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g * 0.587 + b * 0.114);

	Mat dst = g_bIsColor ? g_dstImage : g_grayImage;			//目标图的赋值
	int area;

	if (g_bUseMask) {
		threshold(g_maskImage,g_maskImage,1,128,THRESH_BINARY);
		area = floodFill(dst,g_maskImage,seed,newVal,&ccomp,Scalar(LowDifference,LowDifference,LowDifference),Scalar(UpDifference,UpDifference,UpDifference),flags);
		imshow("mask", g_maskImage);
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference), Scalar(UpDifference, UpDifference, UpDifference), flags);
	}
	imshow("效果图", dst);
	cout << area << " 个像素被重绘\n";
}

int main(int argc,char** argv) {
	g_srcImage = imread("1.jpg", 1);
	if (!g_srcImage.data) {
		printf("读取图片出错 \n");
		return false;
	}
	g_srcImage.copyTo(g_dstImage);
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);			//转换三通道的image0到灰度图
	//初始化掩模
	g_maskImage.create(g_srcImage.rows+2,g_srcImage.cols+2,CV_8UC1);

	namedWindow("效果图", WINDOW_AUTOSIZE);
	createTrackbar("负差最大值","效果图",&g_nLowDifference,255,0);
	createTrackbar("正差最大值","效果图",&g_nUpDifference,255,0);

	//鼠标回调函数
	setMouseCallback("效果图", onDown,0);

	//循环轮询按键
	while (1) {
		//先显示效果图
		imshow("效果图", g_bIsColor ? g_dstImage : g_grayImage);

		//获取键盘按键
		int c = waitKey(0);
		if ((c & 255) == 27) {
			cout << "程序退出......\n";
			break;
		}
		switch ((char)c)
		{
		case '1':
			//效果图在灰度图，彩色图之间互换
			if (g_bIsColor) {
				//原来为彩色则转为灰度图，并且将掩模mask所有元素设置为0
				cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
				g_maskImage = Scalar::all(0);
				g_bIsColor = false;
			}
			else
			{
				g_srcImage.copyTo(g_dstImage);
				g_maskImage = Scalar::all(0);
				g_bIsColor = true;
			}
			break;
		case '2':
			if (g_bUseMask) {
				//如果键盘2被按下，显示/隐藏掩模窗口
				destroyWindow("mask");
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				g_maskImage = Scalar::all(0);
				imshow("mask", g_maskImage);
				g_bUseMask = true;
			}

		case '3':
			//如果按键3被按下，则恢复原始图像
			g_srcImage.copyTo(g_dstImage);
			cvtColor(g_dstImage, g_grayImage, COLOR_BGR2GRAY);
			g_maskImage = Scalar::all(0);
			break;

		case '4':
			//如果按键4被按下，则使用空范围的漫水填充
			g_nFillMode = 0;
			break;
			
		case '5':
			//如果按键5被按下,则使用渐变固定范围的漫水填充
			g_nFillMode = 1;
			break;

		case '6':
			//如果按键6被按下，则使用渐变、浮动范围的漫水填充
			g_nFillMode = 2;
			break;
		case '7':
			//如果按键7被按下，则操作标志符的低八位使用4位的链接模式
			g_nConnectivity = 4;
			break;
		case '8':
			//如果按键8被按下，则操作标志符的低八位使用4位的链接模式
			g_nConnectivity = 8;
			break;
	
		}
	}
	return 0;
}