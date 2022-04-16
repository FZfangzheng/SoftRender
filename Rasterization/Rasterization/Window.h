#pragma once
#include<vector>
#include<string>
#include <Eigen/Eigen>
#include<opencv2/opencv.hpp>
//窗口管理类，负责图像显示
class Window {
private:
	int width;
	int height;
public:
	Window(int width = 700, int height = 700);
	void imageShow(std::vector<Eigen::Vector3f>& frame_buffer);
};