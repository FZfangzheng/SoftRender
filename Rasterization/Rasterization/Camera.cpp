#include "Camera.h"
Camera::Camera(Eigen::Vector3f eye_pos) {
    this->Position = eye_pos;
}

Eigen::Matrix4f Camera::lookAt(Eigen::Vector3f eye_pos, Eigen::Vector3f lookat, Eigen::Vector3f upAxis) {
    this->Position = eye_pos;
    //����ƽ�ƾ��󣬽�����ƶ���ԭ��
    Eigen::Matrix4f translate;
    translate << 1, 0, 0, -Position[0],
        0, 1, 0, -Position[1],
        0, 0, 1, -Position[2],
        0, 0, 0, 1;
    //������ת���󣬽�e,t,g��ת��x,y,z
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
    //����V����
    translate << 1, 0, 0, -Position[0],
        0, 1, 0, -Position[1],
        0, 0, 1, -Position[2],
        0, 0, 0, 1;
    return translate;
}

Eigen::Matrix4f Camera::getProjectionMatrix(float eye_fov, float aspect_ratio, float zNear, float zFar) {
    Eigen::Matrix4f persp_to_ortho;
    Eigen::Matrix4f ortho;

    //͸��ͶӰ������ͶӰ�ı任����
    persp_to_ortho << zNear, 0, 0, 0,
        0, zNear, 0, 0,
        0, 0, zNear + zFar, -(zNear * zFar),
        0, 0, 1, 0;

    //�ӳ��Ǳ�Ϊ������
    double eye_radian = eye_fov / 180.0 * MY_PI;
    //�����ӳ��Ǻͽ�ƽ�����ߣ�һ�룩
    double t = -zNear * tan(eye_radian / 2);
    //���ÿ�߱Ⱥ͸߼����һ�룩
    double r = t * aspect_ratio;

    //����ͶӰ����
    ortho << 1 / r, 0, 0, 0,
        0, 1 / t, 0, 0,
        0, 0, 2 / (zNear - zFar), -(zNear + zFar) / (zNear - zFar),
        0, 0, 0, 1;

    auto persp = ortho * persp_to_ortho;
    return persp;
}