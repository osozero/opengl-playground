#include "Math.h"


 glm::mat4 Math::LookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
	glm::vec3 direction = glm::normalize(position - target);

	glm::vec3 right = glm::normalize(glm::cross(glm::normalize(worldUp), direction));
	glm::vec3 up = glm::normalize(glm::cross(right, direction));

	glm::mat4 translation (1.0f);
	translation[3][0] = position.x;
	translation[3][1] = position.y;
	translation[3][2] = position.z;

	glm::mat4 rotation(1.0f);
	rotation[0][0] = right.x;
	rotation[1][0] = right.y;
	rotation[2][0] = right.z;

	rotation[0][1] = up.x;
	rotation[1][1] = up.y;
	rotation[2][1] = up.z;

	rotation[0][2] = direction.x;
	rotation[1][2] = direction.x;
	rotation[2][2] = direction.x;

	// translates first and then rotates
	return rotation * translation;


}

Math::Math()
{
}


Math::~Math()
{
}
