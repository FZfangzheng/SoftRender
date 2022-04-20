#pragma once
#include <Eigen/Eigen>

#include "global.h"
class Camera {
private:
	Eigen::Vector3f Position;
public:
	Camera(const Eigen::Vector3f& eye_pos);
	Eigen::Matrix4f lookAt(const Eigen::Vector3f& eye_pos, const Eigen::Vector3f& lookat, const Eigen::Vector3f& upAxis);
	//默认看向原点
	Eigen::Matrix4f getViewMatrix();
	//输入参数：视场角，宽高比，近平面，远平面
	Eigen::Matrix4f getProjectionMatrix(const float eye_fov, const float aspect_ratio, const float zNear, const float zFar);
};
