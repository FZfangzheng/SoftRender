#pragma once
#include <Eigen/SVD>
#include <Eigen/Core>
class Utils {
public:
	//��x�Ƕȣ���y��Ƕȣ���z��Ƕȣ����ű�����λ��
	static Eigen::Matrix4f getModelMatrix(float angleX, float angleY, float angleZ, float ratio, float* move);
};
