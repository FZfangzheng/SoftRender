#pragma once
#include <Eigen/Eigen>

#include "global.h"
class Camera {
private:
	Eigen::Vector3f Position;
public:
	Camera(Eigen::Vector3f eye_pos);
	Eigen::Matrix4f lookAt(Eigen::Vector3f eye_pos, Eigen::Vector3f lookat, Eigen::Vector3f upAxis);
	//默认看向原点
	Eigen::Matrix4f getViewMatrix();
	//输入参数：视场角，宽高比，近平面，远平面
	Eigen::Matrix4f getProjectionMatrix(float eye_fov, float aspect_ratio, float zNear, float zFar);
};
