#pragma once
#include <Eigen/SVD>
#include <Eigen/Core>
#include "global.h"
class Utils {
public:
	//��x�Ƕȣ���y��Ƕȣ���z��Ƕȣ����ű�����λ��
	static Eigen::Matrix4f getModelMatrix(float angleX, float angleY, float angleZ, float ratio, float* move);
	//��ά��������ά����
	static Eigen::Vector4f to_vec4(const Eigen::Vector3f& v3, float w = 1.0f);
};
