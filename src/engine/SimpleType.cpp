#include "SimpleType.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>


using namespace staywalk;

mat4 staywalk::Transform::matrix() const{
	auto result = glm::mat4(1.0);
	result = glm::scale(result, scale);
	result = glm::toMat4(rotation) * result;
	result = glm::translate(result, location);
	return result;
}