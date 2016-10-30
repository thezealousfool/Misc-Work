#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

int main(int argc, char** argv)
{

	const char* keys = {
		"{help h usage | | Help text}"
		"{@image | | Image for filtering}"
	};

	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Vivek's Binarizer");

	if (parser.has("help")) {
		parser.printMessage();
		return 0;
	}

	std::string file = parser.get<std::string>(0);

	if (!parser.check()) {
		parser.printErrors();
		return 0;
	}

	if (file == "") {
		std::cout << "Please supply a file name\n";
		return 0;
	}

	std::cout << "Loading...\n";

	cv::Mat image = cv::imread(file, 0);
	cv::imshow("Original image", image);
	std::cout << "Done!\n";

	cv::Mat hist;
	int channels[] = {0};
	int range[] = {0,256};
	int bins[] = {10};
	cv::calcHist(&image, 1, channels, cv::Mat(), hist, 1, bins, range);

	cv::waitKey(0);
	return 0;
}