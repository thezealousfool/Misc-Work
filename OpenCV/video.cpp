#include <iostream>
#include <string>
#include <vector>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

const char* keys = {
	"{help h usage | | print this message}"
	"{@video | | Video file path, if not defined use webcam}"
};

int main( int argc, const char** argv ) {
	cv::CommandLineParser parser(argc, argv, keys);
	parser.about("Vivek's Video Feed v1.0.0");

	if(parser.has("help")) {
		parser.printMessage();
		return 0;
	}

	std::string video_file = parser.get<std::string>(0);

	if(!parser.check()) {
		parser.printErrors();
		return 0;
	}

	cv::VideoCapture cap;
	if (video_file != "")
		cap.open(video_file);
	else
		cap.open(0);

	if(!cap.isOpened())
		return -1;

	cv::namedWindow("Normal Video");
	cv::namedWindow("Green Video");
	cv::namedWindow("Blue Video");
	cv::namedWindow("Red Video");
	while (true) {
		cv::Mat frame;
		std::vector<cv::Mat> BGRFrames;
		std::vector<cv::Mat> RFrame;
		std::vector<cv::Mat> BFrame;
		std::vector<cv::Mat> GFrame;
		cap >> frame;
		cv::split(frame, BGRFrames);
		RFrame.push_back(cv::Mat::zeros(frame.size(), CV_8U));
		RFrame.push_back(cv::Mat::zeros(frame.size(), CV_8U));
		RFrame.push_back(BGRFrames[2]);
		GFrame.push_back(cv::Mat::zeros(frame.size(), CV_8U));
		GFrame.push_back(BGRFrames[1]);
		GFrame.push_back(cv::Mat::zeros(frame.size(), CV_8U));
		BFrame.push_back(BGRFrames[0]);
		BFrame.push_back(cv::Mat::zeros(frame.size(), CV_8U));
		BFrame.push_back(cv::Mat::zeros(frame.size(), CV_8U));
		cv::imshow("Normal Video", frame);
		cv::Mat rframe(frame.rows, frame.cols, CV_8UC3);
		cv::Mat gframe(frame.rows, frame.cols, CV_8UC3);
		cv::Mat bframe(frame.rows, frame.cols, CV_8UC3);
		cv::merge(RFrame, rframe);
		cv::merge(GFrame, gframe);
		cv::merge(BFrame, bframe);
		cv::imshow("Red Video", rframe);
		cv::imshow("Green Video", gframe);
		cv::imshow("Blue Video", bframe);
		char choice = cv::waitKey(30);
		if(choice == ' ') {
			do {
				choice = cv::waitKey(0);
			} while(choice != ' ' && choice != 'q' && choice != 'Q');
		}
		if(choice == 'q' || choice=='Q')
			break;
	}

	cap.release();
	return 0;
}
