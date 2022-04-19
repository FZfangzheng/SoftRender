#pragma once
#include <Eigen/Eigen>
#include "Texture.h"
#include "Light.h"
#include "Triangle.h"


struct fragment_shader_payload
{
    fragment_shader_payload()
    {
        texture = nullptr;
    }

    fragment_shader_payload(const Eigen::Vector3f& col, const Eigen::Vector3f& nor, const Eigen::Vector2f& tc, Texture* tex) :
        color(col), normal(nor), tex_coords(tc), texture(tex) {}


    Eigen::Vector3f view_pos;
    Eigen::Vector3f color;
    Eigen::Vector3f normal;
    Eigen::Vector2f tex_coords;
    Texture* texture;
};

//������ɫ��
class VertexShader {
public:
    // ���ع۲�ռ�ĵ����꣬ out���޸���Ļ�ռ�����꣬�۲�ռ䷨�ߣ����ó�ʼ��ɫ
    std::array<Eigen::Vector3f, 3> use(Triangle* out, Triangle* in);
    // ����MVP����
    void setMVPMatrix(Eigen::Matrix4f m, Eigen::Matrix4f v, Eigen::Matrix4f p);
    // ����Զ��ƽ��
    void setZNearAndZFar(float zNear, float zFar);
private:
    Eigen::Matrix4f model;
    Eigen::Matrix4f view;
    Eigen::Matrix4f projection;
    Eigen::Matrix4f mvp;
    float f1;
    float f2;
    float width = 700;
    float height = 700;
};
//ƬԪ��ɫ��
class FragmentShader {
public:
    // Blinn-Phong����ģ��
    Eigen::Vector3f use(const fragment_shader_payload& payload);
    // ���ù�Դ
    void setLight(PointLight& light);
private:
    std::vector<PointLight> lights;
};