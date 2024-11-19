#pragma once

#ifndef _IN_REFLECT
#include "reflect.h"
#include "imgui.h"
#include "fmt/format.h"
#include <type_traits>

namespace staywalk{
	namespace reflect {
		namespace UIHelper {
			template<typename T>
			void construct_ui(const string& label, T& data);
			
			template<typename T>
			void construct_ui(const string& label, Ref<T> data);

			template<typename T>
			void construct_ui(const string& label, vector<T>& data);

			template<typename TKey, typename TVal>
			void construct_ui(const string& label, map<TKey, TVal>& data);

			void construct_enum_ui(const string& label, int& data, const std::vector<std::pair<int, std::string>>& enum_labels);

			template<typename T>
			constexpr bool is_basic() {
				if constexpr (std::is_trivial_v<T> || 
					std::is_same_v<T, std::string> ||
					std::is_same_v<T, fs::path>) return true;
				else return false;
			}
		};
	}
}

#include "generated/UIBindAll.gen.h"

namespace staywalk {
	namespace reflect {
		template<typename T>
		void UIHelper::construct_ui(const string& label, T& data) {
			constexpr bool is_obj = std::is_same_v<T, staywalk::Object> 
				|| std::is_base_of_v<staywalk::Object, T>;
			//static_assert(is_obj && "must drived from staywalk::object");
			if constexpr (std::is_enum_v<T>){
				int idata = static_cast<int>(data);
				construct_enum_ui(label, idata, get_enum_label<T>());
				data = static_cast<T>(data);
			}
			else if (!is_obj) {
				construct_ui(label, data);
			}
			else {
				string tname = data.get_meta_info().tname.substr(10);
				if (ImGui::TreeNode(fmt::format("{}<{}>", label, tname).c_str())) {
					data.construct_ui();
					ImGui::TreePop();
				}
			}
		}

		template<typename T>
		void UIHelper::construct_ui(const string& label, Ref<T> data) {
			constexpr bool is_obj = std::is_same_v<T, staywalk::Object>
				|| std::is_base_of_v<staywalk::Object, T>;
			static_assert(is_obj && "must drived from staywalk::object");
			if (data == nullptr) return;
			string tname = data->get_meta_info().tname.substr(10);
			if (ImGui::TreeNode(fmt::format("{}<{}>", label, tname).c_str())) {
				data->construct_ui();
				ImGui::TreePop();
			}
		}

		template<>
		void UIHelper::construct_ui(const string& label, string& str);

		template<>
		void UIHelper::construct_ui(const string& label, fs::path& path);

		template<>
		void UIHelper::construct_ui(const string& label, bool& bb);

		template<>
		void UIHelper::construct_ui(const string& label, int& ii);

		template<>
		void UIHelper::construct_ui(const string& label, float& ff);

		template<>
		void UIHelper::construct_ui(const string& label, Transform& tf);

		template<>
		void UIHelper::construct_ui(const string& label, vec3& tf);

		template<>
		void UIHelper::construct_ui(const string& label, quat& q);

		template<typename T>
		void UIHelper::construct_ui(const string& label, vector<T>& data) {
			if (ImGui::TreeNode(fmt::format("{}<vector>", label).c_str())) {
				for (int i = 0; i < data.size(); i++) {
					construct_ui(fmt::format("{}-{}", label, i), data[i]);
				}
				ImGui::TreePop();
			}
		}

		template<typename TKey, typename TVal>
		void UIHelper::construct_ui(const string& label, map<TKey, TVal>& data) {
			if (ImGui::TreeNode(fmt::format("{}<map>", label).c_str())) {
				for (auto& [key, value] : data){
					construct_ui(fmt::format("{}-{}", label, key), value);
				}
				ImGui::TreePop();
			}
		}
	}
}

#endif // !_IN_REFLECT
