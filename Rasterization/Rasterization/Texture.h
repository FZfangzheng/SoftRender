#pragma once
#include "global.h"
#include <Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture {
private:
    cv::Mat image_data;
    int count = 0;

public:
    int width, height;
    Texture(const std::string& name);
    Eigen::Vector3f getColor(float u, float v);
    Eigen::Vector3f getColor_XY(float u, float v);
};