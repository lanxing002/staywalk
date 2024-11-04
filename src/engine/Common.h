#pragma once
#include "stdcommon.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <array>

namespace staywalk
{
	using vec2 = glm::vec2;
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

	template<typename T, std::size_t S>
	using array = std::array<T, S>;
	
	using string = std::string;

	using ifstream = std::ifstream;
	using ofstream = std::ofstream;
	using uint = unsigned int;

	constexpr uint kGlValidId = -1;
}