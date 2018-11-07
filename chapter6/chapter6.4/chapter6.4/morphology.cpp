#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

//全局变量声明
Mat g_srcImage, g_dstImage;
int g_nElementShape = MORPH_RECT;

//变量接收的TrackBar位置参数
int g_nMaxIterationNum = 10;
int g_nErodeDilateNum = 0;
int g_nOpenCloseNum = 0;
int g_nTopBlackHatNum = 0;

//全局函数声明
static void on_ErodeDilate(int, void*);
static void on_OpenClose(int, void*);
static void on_TopBlackHat(int,void*);

static void on_ErodeDilate(int, void*) {
	//定义一个偏移量
	int offset = g_nErodeDilateNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;			//偏移量绝对值
	//自定义核
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		erode(g_srcImage, g_dstImage, element);
	else
		dilate(g_srcImage, g_dstImage, element);
	imshow("腐蚀/膨胀", g_dstImage);

}

static void on_OpenClose(int, void*) {
	int offset = g_nOpenCloseNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1), Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_OPEN, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	imshow("开运算/闭运算", g_dstImage);
}

static void on_TopBlackHat(int,void*) {
	int offset = g_nTopBlackHatNum - g_nMaxIterationNum;
	int Absolute_offset = offset > 0 ? offset : -offset;
	Mat element = getStructuringElement(g_nElementShape,Size(Absolute_offset*2+1,Absolute_offset*2+1),Point(Absolute_offset,Absolute_offset));
	if (offset < 0)
		morphologyEx(g_srcImage, g_dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(g_srcImage, g_dstImage, MORPH_BLACKHAT, element);
	imshow("顶帽/黑帽",g_dstImage);
}

int main() {
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) {
		printf("读取图片出错! \n");
		return false;
	}
	//显示原始图
	namedWindow("原图");
	imshow("原图", g_srcImage);

	//创建三个窗口
	namedWindow("腐蚀/膨胀",1);
	namedWindow("开运算/闭运算",1);
	namedWindow("顶帽/黑帽",1);

	//参数赋值
	g_nErodeDilateNum = 9;
	g_nOpenCloseNum = 9;
	g_nTopBlackHatNum = 2;

	//为三个窗口创建滚动条
	createTrackbar("迭代值:","腐蚀/膨胀",&g_nErodeDilateNum,g_nMaxIterationNum*2+1,on_ErodeDilate);
	createTrackbar("迭代值:","开运算/闭运算", &g_nOpenCloseNum, g_nMaxIterationNum * 2 + 1, on_OpenClose);
	createTrackbar("迭代值:", "顶帽/黑帽", &g_nTopBlackHatNum, g_nMaxIterationNum * 2 + 1, on_TopBlackHat);

	//轮询获得按键信息
	while (1) {
		int c;

		//执行回调函数
		on_ErodeDilate(g_nErodeDilateNum,0);
		on_OpenClose(g_nOpenCloseNum,0);
		on_TopBlackHat(g_nTopBlackHatNum,0);

		c = waitKey(0);					//如果x=0，那么无限等待下去，直到有按键按下
		if ((char)c == 'q' || (char)c == 27)
			break;
		if ((char)c == 49)
			g_nElementShape = MORPH_ELLIPSE;		//当按下1时，则使用椭圆
		else if ((char)c == 50)
			g_nElementShape = MORPH_RECT;			//当按2时，则使用矩形
		else if ((char)c == 51)
			g_nElementShape = MORPH_CROSS;			//当按3时，则使用十字型
		else if ((char)c == ' ')
			g_nElementShape = (g_nElementShape + 1) % 3;		//当按下space键时，在三者之间循环
	}
	return 0;
}
