#pragma once
#include <Eigen/Eigen>

#include "global.h"
class Camera {
private:
	Eigen::Vector3f Position;
public:
	Camera(Eigen::Vector3f eye_pos);
	Eigen::Matrix4f lookAt(Eigen::Vector3f eye_pos, Eigen::Vector3f lookat, Eigen::Vector3f upAxis);
	//Ĭ�Ͽ���ԭ��
	Eigen::Matrix4f getViewMatrix();
	//����������ӳ��ǣ���߱ȣ���ƽ�棬Զƽ��
	Eigen::Matrix4f getProjectionMatrix(float eye_fov, float aspect_ratio, float zNear, float zFar);
};
