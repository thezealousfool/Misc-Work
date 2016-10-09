#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>

const char* keys = {
	"{help h usage | | print this message}"
	"{@output_file o | | Video file path, if not defined use video.mp4}"
};

int main(int argc, char const *argv[])
{
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

	if (video_file == "") {
		video_file = "video.mp4";
	}

	cv::VideoCapture cap(0);
	if (!cap.isOpened()) {
		std::cout << "Unable to open webcam\n\n";
		return 1;
	}

	std::cout << "Input FPS\t: " << cap.get(CV_CAP_PROP_FPS) << "\n";
	cv::VideoWriter out(video_file, cv::VideoWriter::fourcc( 'X','2','6','4' ), cap.get(CV_CAP_PROP_FPS), cv::Size(cap.get(CV_CAP_PROP_FRAME_WIDTH), cap.get(CV_CAP_PROP_FRAME_HEIGHT)));
	cv::namedWindow("Video");
	while (true) {
		cv::Mat frame;
		cap >> frame;
		out << frame;
		cv::imshow("Video", frame);
		char ch = cv::waitKey(1);
		if (ch == ' ') {
			ch = cv::waitKey(0);
		}
		if (ch == 'q') {
			break;
		}
	}
	return 0;
}