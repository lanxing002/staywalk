#pragma once

#ifndef _IN_REFLECT
//#include "Common.gen.h"
#include "reflect.h"
#include "imgui.h"
#include <type_traits>

namespace staywalk{
	namespace reflect {
		class UIHelper {
		public:
			template<typename T>
			static void construct_ui(const string& label, T& data) {}

			template<typename T>
			static constexpr bool is_basic() {
				if constexpr (std::is_trivial_v<T> || std::is_same_v<T, std::string>) return true;
				else return false;
			}
		};
	}
}

#include "generated/UIBindAll.gen.h"

namespace staywalk {
	namespace reflect {
		template<>
		void UIHelper::construct_ui(const string& label, string& data);

		template<>
		void UIHelper::construct_ui(const string& label, bool& data);

		template<>
		void UIHelper::construct_ui(const string& label, int& data);

		template<>
		void UIHelper::construct_ui(const string& label, float& data);
	}
}

#endif // !_IN_REFLECT
