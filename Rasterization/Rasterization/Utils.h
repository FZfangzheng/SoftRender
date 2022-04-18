#pragma once
#include <Eigen/SVD>
#include <Eigen/Core>
class Utils {
public:
	//绕x角度，绕y轴角度，绕z轴角度，缩放比例，位移
	static Eigen::Matrix4f getModelMatrix(float angleX, float angleY, float angleZ, float ratio, float* move);
};
