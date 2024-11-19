#pragma once

#ifndef _IN_REFLECT
#include "reflect.h"
#include "imgui.h"
#include <type_traits>

namespace staywalk{
	namespace reflect {
		namespace UIHelper {
			template<typename T>
			void construct_ui(const string& label, T& data);
			
			template<typename T>
			void construct_ui(const string& label, shared_ptr<T> data);

			template<typename T>
			void construct_ui(const string& label, vector<T>& data);

			template<typename TKey, typename TVal>
			void construct_ui(const string& label, map<TKey, TVal>& data);

			template<typename T>
			constexpr bool is_basic() {
				if constexpr (std::is_trivial_v<T> || std::is_same_v<T, std::string>) return true;
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
			string tname = data.get_meta_info().tname.substr(10);
			data.construct_ui(false, tname);
		}

		template<typename T>
		void UIHelper::construct_ui(const string& label, Ref<T> data) {
			constexpr bool is_obj = std::is_same_v<T, staywalk::Object>
				|| std::is_base_of_v<staywalk::Object, T>;
			static_assert(is_obj && "must drived from staywalk::object");
			string tname = data->get_meta_info().tname.substr(10);
			data->construct_ui(false, tname);
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
		void construct_ui(const string& label, vector<T>& data) {
			//if (ImGui::CollapsingHeader("Basic", ImGuiTreeNodeFlags_None)) {
			//	//ImGui::Separator();
			//	if (ImGui::BeginTable("##properties", 2, ImGuiTableFlags_Resizable))
			//	{
			//		ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
			//		ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthStretch, 1.0f);
			//		for(auto& item : data) item->con
			//		ImGui::EndTable();
			//	}
			//}
		}

		template<typename TKey, typename TVal>
		void construct_ui(const string& label, map<TKey, TVal>& data) {

		}
	}
}

#endif // !_IN_REFLECT
