#include "Camera.h"
#include "Actor.h"
#include "Logger.h"
#include "Engine.h"
#include "InputManager.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace staywalk {
	Camera::Camera(const string& name)
		:GameObject(name) {

	}
	void Camera::tick(float delta){
		auto& im = Engine::get_engine()->get_input_mgr();
		if (im.right_click())
		{
			auto look_vec = glm::inverse(glm::mat3(view)) * vec3(.0, .0, -1.0);
			float offset = .0;
			if (im.press(Keyboard::W)) offset = 1.0;
			else if (im.press(Keyboard::S)) offset - 1.0;

			transform.location += look_vec * offset * 0.03f;
		}

		view = glm::mat4_cast(transform.rotation)* glm::translate(glm::mat4(1.0), -transform.location);
		projection = glm::perspective(glm::radians(fov), aspect, near, far);
	}

	void Camera::look_actor(ActorRef actor) {
		if (actor == nullptr) return;
		auto aabb = actor->get_aabb();
		auto v = vec3(0.5773502691896257);
		if (aabb.valid()) {
			auto center = (aabb.min + aabb.max) * 0.5f;
			auto radius = glm::length(center - aabb.min) * 1.2f;
			float l = radius / (glm::tan(glm::radians(fov * 0.5)) + 0.0001);
			auto pos = center + v * l;
			auto mat = glm::lookAt(pos, center, glm::vec3(0, 0, 1.0));
			transform.location = pos;
			transform.rotation = glm::quat_cast(glm::mat3(mat));
			log(fmt::format("Camera::look_actor --> look to {}", actor->name));
		}
	}

}