#include "SimpleType.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


using namespace staywalk;

mat4 staywalk::Transform::matrix() const{
	auto result = glm::mat4(1.0);
	result = glm::translate(result, location);
	result = result * glm::mat4_cast(glm::quat(glm::radians(rotation)));
	result = glm::scale(result, scale);
	return result;
}