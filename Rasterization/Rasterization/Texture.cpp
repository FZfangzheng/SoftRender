#include <string>
#include "Texture.h"

Texture::Texture(const std::string& name) {
    image_data = cv::imread(name);
    cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
    width = image_data.cols;
    height = image_data.rows;
}
Eigen::Vector3f Texture::getColor(float u, float v) {
    //��u��v����ת����ͼ������
    auto u_img = u * width;
    auto v_img = (1 - v) * height;
    //���ڳ����߽�����
    if (u_img >= 0 && u_img < width && v_img >= 0 && v_img < height) {
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }
    else {
        std::cout << "u:" << u << "v:" << v << std::endl;
        if (u_img < 0) u_img = 0;
        if (u_img >= width) u_img = width - 1;
        if (v_img < 0) v_img = 0;
        if (v_img >= width) v_img = height - 1;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }
}
Eigen::Vector3f Texture::getColor_XY(float u, float v) {
    //��u��v����ת����ͼ������
    auto u_img = u * width;
    auto v_img = v * height;
    //���ڳ����߽�����
    if (u_img >= 0 && u_img < width && v_img >= 0 && v_img < height) {
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }
    else {
        std::cout << "u:" << u << "v:" << v << std::endl;
        if (u_img < 0) u_img = 0;
        if (u_img >= width) u_img = width - 1;
        if (v_img < 0) v_img = 0;
        if (v_img >= width) v_img = height - 1;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }
}