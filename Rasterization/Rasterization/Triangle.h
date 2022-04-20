#pragma once
#include <Eigen/Eigen>
#include "Texture.h"

using namespace Eigen;
// 三角形，包括顶点位置，颜色，纹理坐标和法线
class Triangle {

public:
    Vector4f v[3];
    Vector3f color[3]; 
    Vector2f tex_coords[3];
    Vector3f normal[3]; 

    Texture* tex = nullptr;
    Triangle();

    Eigen::Vector4f a() const { return v[0]; }
    Eigen::Vector4f b() const { return v[1]; }
    Eigen::Vector4f c() const { return v[2]; }

    void setVertex(int ind, const Vector4f& ver);
    void setNormal(int ind, const Vector3f& n); 
    void setColor(int ind, float r, float g, float b);

    void setNormals(const std::array<Vector3f, 3>& normals);
    void setColors(const std::array<Vector3f, 3>& colors);
    void setTexCoord(int ind, const Vector2f& uv);
    std::array<Vector4f, 3> toVector4() const;
};

