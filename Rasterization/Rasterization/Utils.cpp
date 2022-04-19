#include "Utils.h"
#include "global.h"
Eigen::Vector4f Utils::to_vec4(const Eigen::Vector3f& v3, float w) {
    return Eigen::Vector4f(v3.x(), v3.y(), v3.z(), w);
}
Eigen::Matrix4f Utils::getModelMatrix(float angleX, float angleY, float angleZ, float ratio, float* move) {
    //ÈÆXÖáÐý×ª¾ØÕó
    Eigen::Matrix4f rotationX;
    angleX = angleX * MY_PI / 180.f;
    rotationX << 1, 0, 0, 0,
        0, cos(angleX), -sin(angleX), 0,
        0, sin(angleX), cos(angleX), 0,
        0, 0, 0, 1;
    //ÈÆYÖáÐý×ª¾ØÕó
    Eigen::Matrix4f rotationY;
    angleY = angleY * MY_PI / 180.f;
    rotationY << cos(angleY), 0, sin(angleY), 0,
        0, 1, 0, 0,
        -sin(angleY), 0, cos(angleY), 0,
        0, 0, 0, 1;
    //ÈÆZÖáÐý×ª¾ØÕó
    Eigen::Matrix4f rotationZ;
    angleZ = angleZ * MY_PI / 180.f;
    rotationZ << cos(angleZ), -sin(angleZ), 0, 0,
        sin(angleZ), cos(angleZ), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1;
    Eigen::Matrix4f rotation = rotationX * rotationY * rotationZ;
    //Ëõ·Å¾ØÕó
    Eigen::Matrix4f scale;
    scale << ratio, 0, 0, 0,
        0, ratio, 0, 0,
        0, 0, ratio, 0,
        0, 0, 0, 1;
    //Î»ÒÆ¾ØÕó
    Eigen::Matrix4f translate;
    translate << 1, 0, 0, move[0],
        0, 1, 0, move[1],
        0, 0, 1, move[2],
        0, 0, 0, 1;
    delete move;
    return translate * rotation * scale;
}