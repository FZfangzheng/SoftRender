#include "Camera.h"
Camera::Camera(Eigen::Vector3f eye_pos) {
    this->Position = eye_pos;
}

Eigen::Matrix4f Camera::lookAt(Eigen::Vector3f eye_pos, Eigen::Vector3f lookat, Eigen::Vector3f upAxis) {
    this->Position = eye_pos;
    //构建平移矩阵，将相机移动到原点
    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -Position[0],
        0, 1, 0, -Position[1],
        0, 0, 1, -Position[2],
        0, 0, 0, 1;
    //构建旋转矩阵，将e,t,g旋转到x,y,z
    Eigen::Matrix4f rotate;
    Eigen::Vector3f g = (eye_pos - lookat).normalized();
    Eigen::Vector3f e = (upAxis.cross(g)).normalized();
    Eigen::Vector3f t = (g.cross(e)).normalized();

    rotate << e[0], e[1], e[2], 0,
        t[0], t[1], t[2], 0,
        g[0], g[1], g[2], 0,
        0, 0, 0, 1;
    return rotate * translate;
}

Eigen::Matrix4f Camera::getViewMatrix() {
    Eigen::Matrix4f translate;
    //构建V矩阵
    translate << 1, 0, 0, -Position[0],
        0, 1, 0, -Position[1],
        0, 0, 1, -Position[2],
        0, 0, 0, 1;
    return translate;
}

Eigen::Matrix4f Camera::getProjectionMatrix(float eye_fov, float aspect_ratio, float zNear, float zFar) {
    Eigen::Matrix4f persp_to_ortho;
    Eigen::Matrix4f ortho;

    //透视投影到正交投影的变换矩阵
    persp_to_ortho << zNear, 0, 0, 0,
        0, zNear, 0, 0,
        0, 0, zNear + zFar, -(zNear * zFar),
        0, 0, 1, 0;

    //视场角变为弧度制
    double eye_radian = eye_fov / 180.0 * MY_PI;
    //利用视场角和近平面计算高（一半）
    double t = -zNear * tan(eye_radian / 2);
    //利用宽高比和高计算宽（一半）
    double r = t * aspect_ratio;

    //正交投影矩阵
    ortho << 1 / r, 0, 0, 0,
        0, 1 / t, 0, 0,
        0, 0, 2 / (zNear - zFar), -(zNear + zFar) / (zNear - zFar),
        0, 0, 0, 1;

    auto persp = ortho * persp_to_ortho;
    return persp;
}