#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/photo/photo.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "原图"
#define WINDOW_NAME2 "修补后的效果图"

Mat srcImage1, inpaintMask;
Point previousPoint(-1, -1);

static void On_Mouse(int event,int x,int y,int flags,void*) {
	//左键弹起消息
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON)) 
		previousPoint = Point(-1,-1);
	
	//鼠标左键按下消息
	else if (event ==EVENT_LBUTTONDOWN) 
		previousPoint = Point(x,y);
	
	//鼠标按下并移动，进行绘制
	else if(event==EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x < 0)
			previousPoint = pt;
		line(inpaintMask,previousPoint,pt,Scalar::all(255),5,8,0);
		line(srcImage1,previousPoint,pt,Scalar::all(255),5,8,0);
		previousPoint = pt;
		imshow(WINDOW_NAME1,srcImage1);
	}
}

int main() {
	Mat srcImage = imread("1.jpg",-1);
	if (!srcImage.data) {
		printf("读取图片出错\n");
		return false;
	}
	srcImage1 = srcImage.clone();
	inpaintMask = Mat::zeros(srcImage1.size(), CV_8U);

	imshow(WINDOW_NAME1,srcImage1);

	setMouseCallback(WINDOW_NAME1,On_Mouse,0);

	while (true) {
		char c = (char)waitKey();

		if (c == 27)
			break;
		//按下键2的时候，将图像恢复成原图像
		if (c == '2') {
			inpaintMask = Scalar::all(0);
			srcImage.copyTo(srcImage1);
			imshow(WINDOW_NAME1,srcImage1);
		}
		//键值为1或者空格，进行图像修补操作
		if (c == '1' || c == ' ') {
			Mat inpaintedImage;
			inpaint(srcImage1,inpaintMask,inpaintedImage,3,INPAINT_TELEA);
			imshow(WINDOW_NAME2,inpaintedImage);
		}
	}
	
	return 0;
}