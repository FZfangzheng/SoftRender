#include "Window.h"
Window::Window(int width, int height) {
	this->width = width;
	this->height = height;
}
void Window::imageShow(std::vector<Eigen::Vector3f>& frame_buffer) {
	cv::Mat image(700, 700, CV_32FC3, frame_buffer.data());
	image.convertTo(image, CV_8UC3, 1.0f);
	cv::cvtColor(image, image, cv::COLOR_RGB2BGR);
	cv::imshow("image", image);
	cv::waitKey(0);
	cv::imwrite("output.png", image);
}