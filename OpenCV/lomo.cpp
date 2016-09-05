#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

float lomo (int i, float degree) {
	float f = (float)i/256.0;
	return cv::saturate_cast<uchar>(256*(1/(1 + std::pow(std::exp(1), -((f-0.5)/degree)))));
}

int main(int argc, char** argv) {
	const char* keys = {
		"{help h usage | | Help text}"
		"{@image | | Image for applying Lomo filter}"
		"{@strength | 10 | Strength of the filter to be applied}"
	};
	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Vivek's Lomo effect");
	if (parser.has("help")) {
		parser.printMessage();
		return 0;
	}
	std::string file = parser.get<std::string>(0);
	int strength = parser.get<int>(1);
	if (!parser.check()) {
		parser.printErrors();
		return 0;
	}
	if (file == "") {
		std::cout << "Please supply a file name\n";
		return 0;
	}
	std::cout << "Loading...\n";
	std::vector<uchar> LUT(256);
	for (int i = 0; i < 256; ++i) {
		if (strength == 0)
			LUT[i] = i;
		else
			LUT[i] = lomo(i, 1.0/strength);
	}
	cv::Mat image = cv::imread(file);
	cv::imshow("Original Image", image);
	std::vector<cv::Mat> channels;
	cv::split(image, channels);
	cv::LUT(channels[2], LUT, channels[2]);
	cv::merge(channels, image);
	std::cout << "Done\n";
	cv::imshow("Lomo Image", image);
	cv::waitKey(0);
	cv::imwrite("lomo.jpg", image);
	return 0;
}
