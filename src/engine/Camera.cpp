#include "Camera.h"
#include "Actor.h"
#include "Logger.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace staywalk {
	Camera::Camera(const string& name)
		:GameObject(name) {

	}
	void Camera::tick(float delta){
		//view = glm::mat4_cast(transform.rotation);
		//view = glm::translate(view, transform.location);

		projection = glm::perspective(glm::radians(fov), aspect, near, far);
	}

	void Camera::look_actor(ActorRef actor) {
		if (actor == nullptr) return;
		auto aabb = actor->get_aabb();
		auto v = vec3(0.5773502691896257);
		if (aabb.valid()) {
			auto center = (aabb.min + aabb.max) * 0.5f;
			auto radius = glm::length(center - aabb.min) * 1.2f;
			float l = radius / (glm::tan(glm::radians(fov)) + 0.0001);
			auto pos = center + v * l;
			auto mat = glm::lookAt(pos, center, glm::vec3(0, 0, 1.0));
			transform.location = mat[3];
			transform.rotation = glm::quat_cast(glm::mat3(mat));
			view = mat;
			log(fmt::format("Camera::look_actor --> look to {}", actor->name));
		}
	}

}