#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace staywalk {
	Camera::Camera(const string& name)
		:GameObject(name) {

	}
	void Camera::tick(float delta){
		view = glm::toMat4(transform.rotation);
		view = glm::translate(view, transform.location);

		projection = glm::perspective(glm::radians(fov), aspect, near, far);
	}
}