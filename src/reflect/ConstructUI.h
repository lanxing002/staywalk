#pragma once

#ifndef _IN_REFLECT
#include "reflect.h"
#include "imgui.h"
#include "fmt/format.h"
#include "Engine.h"
#include <type_traits>

namespace staywalk{
	namespace reflect {
		namespace UIHelper {
			constexpr std::string_view kChooseObjPop = "--ChooseObjPop";
			
			template<typename T>
			void choice_object(Ref<T>& obj);

			template<typename T>
			void construct_ui(const string& label, T& data, bool read_only);
			
			template<typename T>
			void construct_ui(const string& label, Ref<T>& data, bool read_only);

			template<typename T>
			void construct_ui(const string& label, vector<T>& data, bool read_only);

			template<typename TKey, typename TVal>
			void construct_ui(const string& label, map<TKey, TVal>& data, bool read_only);

			void construct_enum_ui(const string& label, int& data, const std::vector<std::pair<int, std::string>>& enum_labels, bool read_only);

			template<typename T>
			constexpr bool is_basic() {
				if constexpr (std::is_trivial_v<T> || 
					std::is_same_v<T, std::string> ||
					std::is_same_v<T, fs::path>) return true;
				else return false;
			}

			template <typename T, typename = void>
			struct is_public_field : std::false_type {};

			template <typename T>
			struct is_public_field<T, std::void_t<decltype(std::declval<T>().name)>> : std::true_type {};
		};
	}
}

#include "generated/UIBindAll.gen.h"

namespace staywalk {
	namespace reflect {
		template<typename T>
		void UIHelper::construct_ui(const string& label, T& data, bool read_only) {
			constexpr bool is_obj = std::is_same_v<T, staywalk::Object> 
				|| std::is_base_of_v<staywalk::Object, T>;
			//static_assert(is_obj && "must drived from staywalk::object");
			if constexpr (std::is_enum_v<T>){
				int idata = static_cast<int>(data);
				construct_enum_ui(label, idata, get_enum_label<T>(), read_only);
				data = static_cast<T>(idata);
			}
			else if (!is_obj) {
				construct_ui(label, data, read_only);
			}
			else {
				auto tname = data.get_meta_info().tname;
				tname.remove_prefix(10);
				if (ImGui::TreeNode(fmt::format("{}<{}>", label, tname).c_str())) {
					data.construct_ui(read_only);
					ImGui::TreePop();
				}
			}
		}

		template<typename T>
		void UIHelper::construct_ui(const string& label, Ref<T>& data, bool read_only) {
			constexpr bool is_obj = std::is_same_v<T, staywalk::Object>
				|| std::is_base_of_v<staywalk::Object, T>;
			static_assert(is_obj && "must drived from staywalk::object");
			if (data == nullptr) return;
			auto tname = data->get_meta_info().tname;
			tname.remove_prefix(10);
			ImVec4 textColor = ImVec4(0.12f, 0.8f, 0.1f, 1.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, textColor);
			if (ImGui::TreeNode(fmt::format("{}<{}>", label, tname).c_str())) {
				ImGui::PopStyleColor();
				UIHelper::choice_object(data);
				data->construct_ui(read_only);
				ImGui::TreePop();
			}
			else { ImGui::PopStyleColor(); }

		}

		template<>
		void UIHelper::construct_ui(const string& label, string& str, bool read_only);

		template<>
		void UIHelper::construct_ui(const string& label, fs::path& path, bool read_only);

		template<>
		void UIHelper::construct_ui(const string& label, bool& bb, bool read_only);

		template<>
		void UIHelper::construct_ui(const string& label, int& ii, bool read_only);

		template<>
		void UIHelper::construct_ui(const string& label, float& ff, bool read_only);

		template<>
		void UIHelper::construct_ui(const string& label, Transform& tf, bool read_only);

		template<>
		void UIHelper::construct_ui(const string& label, vec3& tf, bool read_only);

		template<>
		void UIHelper::construct_ui(const string& label, quat& q, bool read_only);

		template<typename T>
		void UIHelper::construct_ui(const string& label, vector<T>& data, bool read_only) {
			if (ImGui::TreeNode(fmt::format("{}<vector>", label).c_str())) {
				for (int i = 0; i < data.size(); i++) {
					construct_ui(fmt::format("{}-{}", label, i), data[i], read_only);
				}
				ImGui::TreePop();
			}
		}

		template<typename TKey, typename TVal>
		void UIHelper::construct_ui(const string& label, map<TKey, TVal>& data, bool read_only) {
			if (ImGui::TreeNode(fmt::format("{}<map>", label).c_str())) {
				for (auto& [key, value] : data){
					construct_ui(fmt::format("{}-{}", label, key), value, read_only);
				}
				ImGui::TreePop();
			}
		}

		template<typename T>
		void UIHelper::choice_object(Ref<T>& obj) {
			if (ImGui::BeginPopupContextItem("##change--obj"))
			{
				auto title = std::string(obj->get_meta_info().tname) + " List";
				ImGui::TextColored(ImVec4(1.0, 1.01, 1.0, 1.0), title.c_str());
				for (auto& [_, v] : Engine::get_engine()->get_world()->get_all_objects()) {
					if (v->get_meta_info().tname == obj->get_meta_info().tname) {
						ImGui::PushID(v->get_guid());
						if (ImGui::Selectable(v->name.c_str())) {
							Ref<T> target = pcast<T>(v);
							if (target) obj = target;
						}
						ImGui::PopID();
					}
				}

				ImGui::EndPopup();
			}
		}
	}
}

#endif // !_IN_REFLECT
