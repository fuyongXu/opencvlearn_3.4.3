#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "程序窗口"

Mat g_srcImage, g_dstImage;
Mat g_map_x, g_map_y;

int update_map(int key);

int update_map(int key) {
	for (int j = 0; j < g_srcImage.rows; j++) {
		for (int i = 0; i < g_srcImage.cols; i++) {
			switch (key)
			{
			case '1':
				if (i > g_srcImage.cols*0.25&&i<g_srcImage.cols*0.75&&j>g_srcImage.rows*0.25&&j < g_srcImage.rows*0.75) {
					g_map_x.at<float>(j, i) = static_cast<float>(2 * (i - g_srcImage.cols*0.25) + 0.5);
					g_map_y.at<float>(j, i) = static_cast<float>(2 * (j - g_srcImage.rows*0.25) + 0.5);
				}
				else {
					g_map_x.at<float>(j, i) = 0;
					g_map_y.at<float>(j, i) = 0;
				}
				break;
			case '2':
				g_map_x.at<float>(j, i) = static_cast<float>(i);
				g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows-j);
				break;
			case '3':
				g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j, i) = static_cast<float>(j);
				break;
			case '4':
				g_map_x.at<float>(j, i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j, i) = static_cast<float>(g_srcImage.rows - j);
				break;
			}
		}
	}
	return 1;
}
int main() {
	system("color 2F");

	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) {
		printf("读取图片出错！\n");
		return false;
	}
	imshow("原始图",g_srcImage);

	g_dstImage.create(g_srcImage.size(),g_srcImage.type());
	g_map_x.create(g_srcImage.size(),CV_32FC1);
	g_map_y.create(g_srcImage.size(),CV_32FC1);

	namedWindow(WINDOW_NAME,WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME,g_srcImage);

	while (1) {
		int key = waitKey(0);
		if ((key & 255) == 27) {
			cout << "程序退出\n";
			break;
		}
		update_map(key);
		remap(g_srcImage,g_dstImage,g_map_x,g_map_y,INTER_LINEAR,BORDER_CONSTANT,Scalar(0,0,0));
		imshow(WINDOW_NAME,g_dstImage);

	}
	return 0;
}
