#pragma once
#include<vector>
#include<string>
#include <Eigen/Eigen>
#include<opencv2/opencv.hpp>
//���ڹ����࣬����ͼ����ʾ
class Window {
private:
	int width;
	int height;
public:
	Window(int width = 700, int height = 700);
	void imageShow(std::vector<Eigen::Vector3f>& frame_buffer);
};