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
    Eigen::Vector3f eye_pos = { 0,2,10 };
    Camera myCamera(eye_pos);
    Eigen::Vector3f lookat = { 0,0,0 };
    Eigen::Vector3f upAxis = { 0,1,0 };

    // 创建光源，位置暂时是观察坐标
    PointLight l1({ 20, 20, 20 }, { 500, 500, 500 });
    //PointLight l2({ 0, 20, -10 }, { 500, 500, 500 });
    PointLight l2({ -20, 20, 0 }, { 500, 500, 500 });
    // 加载模型

    // 加载模型——小牛模型
    std::string obj_path = "./models/spot/";
    std::string obj_name = "spot_triangulated_good.obj";
    std::vector<Triangle*> TriangleList;
    Model::loadModel(obj_path + obj_name, TriangleList);
    // 小牛模型——加载纹理
    auto texture_path = "spot_texture.png";
    Texture texture(obj_path + texture_path);
    // 小牛模型——创建shader
    VertexShader vs;
    FragmentShader fs;
    //fs.setLight(l1);
    fs.setLight(l2);
    //fs.setAmbLightIntensity({ 15,15,15 });

    // 加载模型——立方体模型
    std::vector<Triangle*> TriangleList_CUBE;
    Model::loadModel(CUBE, TriangleList_CUBE);
    // 立方体模型——加载纹理
    auto texture_path2 = "resources/container2.png";
    Texture texture2(texture_path2);
    // 立方体模型——创建shader
    VertexShader vs2;
    FragmentShader fs2;
    //fs2.setLight(l1);
    fs2.setLight(l2);

    // 加载模型——地面模型
    std::vector<Triangle*> TriangleList_PLANE;
    Model::loadModel(PLANE, TriangleList_PLANE);
    // 地面模型——加载纹理
    auto texture_path3 = "resources/wood.png";
    Texture texture3(texture_path3);
    // 地面模型——创建shader
    VertexShader vs3;
    FragmentShader fs3;
    fs3.setLight(l1);
    fs3.setLight(l2);
    fs3.setSampleType(XY);

    // MVP矩阵
    float m1_move[3] = { -1,1,0 };
    Eigen::Matrix4f m = Utils::getModelMatrix(0, 140, 0, 1.5, m1_move);
    float m2_move[3] = { 1,1,0 };
    Eigen::Matrix4f m2 = Utils::getModelMatrix(45, 140, 0, 1, m2_move);
    //Eigen::Matrix4f m2 = Utils::getModelMatrix(0, 0, 0, 1, new float[3]());
    Eigen::Matrix4f m3 = Utils::getModelMatrix(0, 0, 0, 1, new float[3]());
    Eigen::Matrix4f v = myCamera.lookAt(eye_pos, lookat, upAxis);
    Eigen::Matrix4f p = myCamera.getProjectionMatrix(45.0, 1, -0.1, -50);
    vs.setMVPMatrix(m, v, p);
    vs.setZNearAndZFar(-0.1, -50);
    vs2.setMVPMatrix(m2, v, p);
    vs2.setZNearAndZFar(-0.1, -50);
    vs3.setMVPMatrix(m3, v, p);
    vs3.setZNearAndZFar(-0.1, -50);
    //光栅化
    rst::rasterizer r(width, height);
    // 小牛模型
    r.set_texture(0, texture); //设置纹理
    r.set_object(0, TriangleList); // 设置物体
    r.set_vertex_shader(0, vs); // 设置vertex_shader
    r.set_fragment_shader(0, fs); // 设置fragment_shader
    // 立方体模型
    r.set_texture(1, texture2); //设置纹理
    r.set_object(1, TriangleList_CUBE); // 设置物体
    r.set_vertex_shader(1, vs2); // 设置vertex_shader
    r.set_fragment_shader(1, fs2); // 设置fragment_shader
    // 地面平面
    r.set_texture(2, texture3); //设置纹理
    r.set_object(2, TriangleList_PLANE); // 设置物体
    r.set_vertex_shader(2, vs3); // 设置vertex_shader
    r.set_fragment_shader(2, fs3); // 设置fragment_shader

    //创建窗口
    Window window(width, height);
    //清空颜色缓冲、深度缓冲
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);
    //开始绘制
    //r.draw(TriangleList);
    r.draw();
    window.imageShow(r.frame_buffer());
    return 0;
}
