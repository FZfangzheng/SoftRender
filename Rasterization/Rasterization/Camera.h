#pragma once
#include <Eigen/Eigen>

#include "global.h"
class Camera {
private:
	Eigen::Vector3f Position;
public:
	Camera(const Eigen::Vector3f& eye_pos);
	Eigen::Matrix4f lookAt(const Eigen::Vector3f& eye_pos, const Eigen::Vector3f& lookat, const Eigen::Vector3f& upAxis);
	//Ĭ�Ͽ���ԭ��
	Eigen::Matrix4f getViewMatrix();
	//����������ӳ��ǣ���߱ȣ���ƽ�棬Զƽ��
	Eigen::Matrix4f getProjectionMatrix(const float eye_fov, const float aspect_ratio, const float zNear, const float zFar);
};
