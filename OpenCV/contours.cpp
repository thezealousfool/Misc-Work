#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

int main(int argc, char ** argv) {
	cv::namedWindow("Image");
	cv::Mat img = cv::imread(argv[1]);
	cv::imshow("Image", img);
	cv::waitKey(0);
	return 0;
}
