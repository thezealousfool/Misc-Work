#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main (int argc, char** argv) {
	const char* keys = {
		"{help h usage | | Help text}"
		"{@image | | Image for applying Vignette}"
	};
	cv::CommandLineParser parser (argc, argv, keys);
	if (parser.has("help")) {
		parser.printMessage();
		return 0;
	}
	std::string image_file = parser.get<std::string>(0);
	cv::Mat image = cv::imread(image_file);
	int radius = std::min(image.rows, image.cols) / 2;
	cv::Mat mask(cv::Size(image.cols, image.rows), CV_32FC3, cv::Scalar(0.3,0.3,0.3));
	cv::circle(mask, cv::Point(image.cols/2, image.rows/2), radius, cv::Scalar(1,1,1), -1);
	cv::blur(mask, mask, cv::Size(radius*0.7,radius*0.7));
	cv::Mat img_float;
	image.convertTo(img_float, CV_32FC3);
	cv::multiply(img_float, mask, img_float);
	img_float.convertTo(image, CV_8UC3);
	cv::imshow("Vignette", image);
	cv::imwrite("vignette.jpg", image);
	cv::waitKey(0);
	return 0;
}
