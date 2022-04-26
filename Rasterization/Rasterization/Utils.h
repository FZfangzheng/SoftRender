#pragma once
#include <Eigen/SVD>
#include <Eigen/Core>
#include "global.h"
class Utils {
public:
	//绕x角度，绕y轴角度，绕z轴角度，缩放比例，位移
	static Eigen::Matrix4f getModelMatrix(float angleX, float angleY, float angleZ, float ratio, float* move);
	//三维向量变四维向量
	static Eigen::Vector4f to_vec4(const Eigen::Vector3f& v3, float w = 1.0f);
};
