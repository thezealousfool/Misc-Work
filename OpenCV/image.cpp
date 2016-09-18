#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, const char** argv) {
	cv::Mat color = cv::imread("img.jpg");
	cv::Mat gray = cv::imread("img.jpg", 0);

	cv::imwrite("img_gray.jpg", gray);
	cv::imshow("Colored Image", color);
	cv::imshow("Gray Image", gray);
	cv::waitKey(0);
	return 0;
}
