#include "Camera.h"
#include "Actor.h"
#include "Logger.h"
#include "Engine.h"
#include "InputManager.h"
#include "Event.h"

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
			Event::Editor_ShowHideCursor(false);
			auto look_vec = glm::inverse(glm::mat3(view)) * vec3(.0, .0, -1.0);
			auto cam_left_vec = glm::inverse(glm::mat3(view)) * vec3(-1.0, .0, 0.0);
			float zoffset = .0; float xoffset = .0;
			if (im.press(Keyboard::W))  zoffset = 1.0;
			else if (im.press(Keyboard::S))  zoffset = -1.0;
			if (im.press(Keyboard::A)) xoffset = 1.0;
			else if (im.press(Keyboard::D)) xoffset = -1.0;
			transform.location += (look_vec * zoffset + cam_left_vec * xoffset) * 0.03f;

			auto mouse_offset = im.mouse_offset();
			if (std::abs(mouse_offset.x) > 1e-6) {
				transform.rotation.y += mouse_offset.x * 0.024f;
			}

			if (std::abs(mouse_offset.y) > 1e-6) {
				transform.rotation.x += mouse_offset.y * 0.024f;
			}

			//transform.rotation.y = std::min(-45.0f, std::max(45.0f, transform.rotation.y));
			transform.rotation.x = std::max(-89.5f, std::min(89.5f, transform.rotation.x));
		}
		else Event::Editor_ShowHideCursor(true);

		view = glm::mat4_cast(glm::quat(glm::radians(transform.rotation))) * glm::translate(glm::mat4(1.0), -transform.location);
		projection = glm::perspective(glm::radians(fov), aspect, near, far);
	}

	void Camera::look_actor(ActorRef actor) {
		if (actor == nullptr) return;
		auto aabb = actor->get_aabb();
		auto v = vec3(0.5773502691896257f);
		if (aabb.valid()) {
			auto center = (aabb.min + aabb.max) * 0.5f;
			auto radius = glm::length(center - aabb.min) * 1.2f;
			float l = radius / (glm::tan(glm::radians(fov * 0.5f)) + 0.0001f);
			auto pos = center + v * l;
			auto mat = glm::lookAt(pos, center, glm::vec3(0, 0, 1.0));
			transform.location = pos;
			transform.rotation = glm::degrees(glm::eulerAngles(glm::quat_cast(glm::mat3(mat))));
			transform.rotation.z = .0;
			log(fmt::format("Camera::look_actor --> look to {}", actor->name_));
		}
	}

}