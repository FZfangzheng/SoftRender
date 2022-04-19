#include "Light.h"
Eigen::Vector3f PointLight::getPosition() {
	return position;
}
Eigen::Vector3f PointLight::getIntensity() {
	return intensity;
}