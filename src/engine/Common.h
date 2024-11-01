#pragma once
#include "stdcommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

namespace staywalk
{
	using vec3 = glm::vec3;
	using vec4 = glm::vec4;
	using mat4 = glm::mat4;
	using quat = glm::quat;

	template<typename T>
	using shared_ptr = std::shared_ptr<T>;

	template<typename T>
	using vector = std::vector<T>;

	template<typename T, typename VT>
	using hashtable = std::unordered_map<T, VT>;
	
	using string = std::string;
}