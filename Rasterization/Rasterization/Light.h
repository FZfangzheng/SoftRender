#pragma once
#include <Eigen/Eigen>
class PointLight {
public:
	PointLight(const Eigen::Vector3f& position, const Eigen::Vector3f& intensity):position(position),intensity(intensity){}
	Eigen::Vector3f getPosition();
	Eigen::Vector3f getIntensity();
private:
	Eigen::Vector3f position;
	Eigen::Vector3f intensity;
};
