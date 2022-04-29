#pragma once
#include <Eigen/Eigen>
#include "Texture.h"
#include "Light.h"
#include "Triangle.h"

enum SampleType {
    XY,
    UV
};
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
    void setMVPMatrix(const Eigen::Matrix4f& m, const Eigen::Matrix4f& v, const Eigen::Matrix4f& p);
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
    //virtual Eigen::Vector3f use(const fragment_shader_payload& payload, std::vector<float>& shadow_buf);
    virtual Eigen::Vector3f use(int x, int y, const fragment_shader_payload& payload, std::vector<float>& shadow_buf);
    // ���ù�Դ
    void setLight(const PointLight& light);
    // ���û���������
    void setAmbLightIntensity(const Vector3f amb);
    // ����sample type
    void setSampleType(const SampleType sampleType);
    SampleType getSampleType();
    std::vector<PointLight> getLights();
    Eigen::Matrix4f getView();
    Eigen::Vector3f getAmbLightIntensity();
    void setViewMatrix(const Eigen::Matrix4f& v);
private:
    Eigen::Matrix4f view;
    std::vector<PointLight> lights;
    SampleType sampletype = UV;
    Eigen::Vector3f amb_light_intensity = { 10,10,10 };
};
//ƬԪ��ɫ��-shadow
class FragmentShader_Shadow :public FragmentShader {
public:
    //Blinn-Phong����ģ��&��Ӱ
    //virtual Eigen::Vector3f use(const fragment_shader_payload& payload, std::vector<float>& shadow_buf);
    virtual Eigen::Vector3f use(int x, int y,const fragment_shader_payload& payload, std::vector<float>& shadow_buf);
    void setLightViewMatrix(const Eigen::Matrix4f& v);
    void setLightProjectionMatrix(const Eigen::Matrix4f& p);
    void setZNearAndZFar(float zNear, float zFar);
    float get_index(int x, int y){ return (height - y) * width + x; }
private:
    Eigen::Matrix4f light_view;
    Eigen::Matrix4f light_projection;
    float f1;
    float f2;
    float width = 700;
    float height = 700;
};