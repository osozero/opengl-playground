#pragma once
#include <glm/glm.hpp>
class Math
{
public:
	static glm::mat4 LookAt(glm::vec3 position, glm::vec3 target, glm::vec3 up);
	Math();
	~Math();
};

