#include <iostream>
#include <Eigen/SVD>
#include <Eigen/Core>
#include<iostream>
#include<opencv2/opencv.hpp>


#include "global.h"
#include "rasterizer.h"
#include "Triangle.h"
#include "Texture.h"

#include "Window.h"
#include "Camera.h"
#include "Model.h"
#include "Utils.h"
#include "Light.h"
#include "Shader.h"
//#include "OBJ_Loader.h"

int main(int argc, const char** argv)
{
    //设置界面大小
    int width = 700;
    int height = 700;
    // 设置相机初始位置
    Eigen::Vector3f eye_pos = { 0,0,10 };
    Camera myCamera(eye_pos);
    Eigen::Vector3f lookat = { 0,0,0 };
    Eigen::Vector3f upAxis = { 0,1,0 };
    // 设置模型旋转角度
    float angle = 140.0;
    // 加载模型
    std::string obj_path = "./models/spot/";
    std::string obj_name = "spot_triangulated_good.obj";
    std::vector<Triangle*> TriangleList;
    Model::loadModel(obj_path + obj_name, TriangleList);
    // 创建光源
    PointLight l1({ 20, 20, 20 }, { 500, 500, 500 });
    PointLight l2({ -20, 20, 0 }, { 500, 500, 500 });
    // 加载纹理
    auto texture_path = "spot_texture.png";
    Texture texture(obj_path + texture_path);
    // 创建shader
    VertexShader vs;
    // MVP矩阵
    Eigen::Matrix4f m = Utils::getModelMatrix(0, angle, 0, 2.5, new float[3]());
    Eigen::Matrix4f v = myCamera.lookAt(eye_pos, lookat, upAxis);
    Eigen::Matrix4f p = myCamera.getProjectionMatrix(45.0, 1, -0.1, -50);
    vs.setMVPMatrix(m, v, p);
    vs.setZNearAndZFar(-0.1, -50);
    FragmentShader fs;
    fs.setLight(l1);
    fs.setLight(l2);

    //光栅化
    rst::rasterizer r(width, height);
    r.set_texture(texture); //设置纹理
    r.set_vertex_shader(vs); // 设置vertex_shader
    r.set_fragment_shader(fs); // 设置fragment_shader

    //创建窗口
    Window window(width, height);
    //清空颜色缓冲、深度缓冲
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);
    //开始绘制
    r.draw(TriangleList);
    window.imageShow(r.frame_buffer());
    return 0;
}
