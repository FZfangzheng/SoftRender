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
    //���ý����С
    int width = 700;
    int height = 700;
    // ���������ʼλ��
    Eigen::Vector3f eye_pos = { 0,0,10 };
    Camera myCamera(eye_pos);
    Eigen::Vector3f lookat = { 0,0,0 };
    Eigen::Vector3f upAxis = { 0,1,0 };
    // ����ģ����ת�Ƕ�
    float angle = 140.0;
    // ����ģ��
    std::string obj_path = "./models/spot/";
    std::string obj_name = "spot_triangulated_good.obj";
    std::vector<Triangle*> TriangleList;
    Model::loadModel(obj_path + obj_name, TriangleList);
    // ������Դ
    PointLight l1({ 20, 20, 20 }, { 500, 500, 500 });
    PointLight l2({ -20, 20, 0 }, { 500, 500, 500 });
    // ��������
    auto texture_path = "spot_texture.png";
    Texture texture(obj_path + texture_path);
    // ����shader
    VertexShader vs;
    // MVP����
    Eigen::Matrix4f m = Utils::getModelMatrix(0, angle, 0, 2.5, new float[3]());
    Eigen::Matrix4f v = myCamera.lookAt(eye_pos, lookat, upAxis);
    Eigen::Matrix4f p = myCamera.getProjectionMatrix(45.0, 1, -0.1, -50);
    vs.setMVPMatrix(m, v, p);
    vs.setZNearAndZFar(-0.1, -50);
    FragmentShader fs;
    fs.setLight(l1);
    fs.setLight(l2);

    //��դ��
    rst::rasterizer r(width, height);
    r.set_texture(texture); //��������
    r.set_vertex_shader(vs); // ����vertex_shader
    r.set_fragment_shader(fs); // ����fragment_shader

    //��������
    Window window(width, height);
    //�����ɫ���塢��Ȼ���
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);
    //��ʼ����
    r.draw(TriangleList);
    window.imageShow(r.frame_buffer());
    return 0;
}
