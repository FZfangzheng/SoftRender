#pragma once
#include <string>
#include "Triangle.h"
enum OBJTYPE {
	CUBE,
	PLANE
};
class Model {
public:
	static void loadModel(const std::string path, std::vector<Triangle*>& TriangleList);
	static void loadModel(OBJTYPE objtype, std::vector<Triangle*>& TriangleList);
};
