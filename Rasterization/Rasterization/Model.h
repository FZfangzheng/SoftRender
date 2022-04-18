#pragma once
#include <string>
#include "Triangle.h"
class Model {
public:
	static void loadModel(const std::string path, std::vector<Triangle*>& TriangleList);
};
