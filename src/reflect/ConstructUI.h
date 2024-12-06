#pragma once

#ifndef _IN_REFLECT
#include "reflect.h"
#include "Engine.h"
#include "SimpleType.h"
#include "World.h"

#include "imgui.h"
#include "fmt/format.h"
#include <type_traits>

namespace staywalk{
	namespace reflect {
		namespace UIHelper {
			constexpr std::string_view kChooseObjPop = "--ChooseObjPop";
			
			template<typename T>
			void object_common_menu(Ref<T>& target, Ref<T>& reference);

			template<typename T>
			void container_modify_menu(vector<T>& target);

			template<typename TKey, typename TVal>
			void container_modify_menu(map<TKey, TVal>& target);

			template<typename T>
			void choice_object(Ref<T>& target, Ref<T>& reference);

			template<typename T>
			void drag_target(Ref<T>& obj);

			template<typename T>
			void construct_ui(const string& label, T& data, bool can_modify);
			
			template<typename T>
			void construct_ui(const string& label, Ref<T>& data, bool can_modify);

			template<typename T>
			void construct_ui(const string& label, vector<T>& data, bool can_modify);

			template<typename TKey, typename TVal>
			void construct_ui(const string& label, map<TKey, TVal>& data, bool can_modify);

			template<typename TKey, typename TVal>
			void construct_ui(const string& label, pair<TKey, TVal>& data, bool can_modify);

			void construct_enum_ui(const string& label, int& data, const std::vector<std::pair<int, std::string>>& enum_labels, bool can_modify);

			template<typename T>
			constexpr bool is_basic() {
				if constexpr (std::is_trivial_v<T> 
					|| std::is_same_v<T, std::string> 
					|| std::is_same_v<T, fs::path> 
					|| std::is_same_v<T, SWCodeRef>
				)return true;
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
		void UIHelper::construct_ui(const string& label, T& data, bool can_modify) {
			constexpr bool is_obj = std::is_same_v<T, staywalk::Object> 
				|| std::is_base_of_v<staywalk::Object, T>;
			//static_assert(is_obj && "must drived from staywalk::object");
			if constexpr (std::is_enum_v<T>){
				int idata = static_cast<int>(data);
				construct_enum_ui(label, idata, get_enum_label<T>(), can_modify);
				data = static_cast<T>(idata);
			}
			else if (!is_obj) {
				construct_ui(label, data, can_modify);
			}
			else {
				auto tname = data.get_meta_info().tname;
				tname.remove_prefix(10);
				if (ImGui::TreeNode(fmt::format("{}<{}>", label, tname).c_str())) {
					data.construct_ui(can_modify);
					ImGui::TreePop();
				}
			}
		}

		template<typename T>
		void UIHelper::construct_ui(const string& label, Ref<T>& data, bool can_modify) {
			constexpr bool is_obj = std::is_same_v<T, staywalk::Object>
				|| std::is_base_of_v<staywalk::Object, T>;
			static_assert(is_obj && "must drived from staywalk::object");
			static Ref<T> _null_obj = std::make_shared<T>();
			if (data == nullptr) {
				ImVec4 textColor = ImVec4(0.46f, 0.36f, 0.02f, 1.0f);
				ImGui::PushStyleColor(ImGuiCol_Text, textColor);
				auto obj_type_name = _null_obj->get_meta_info().tname;
				obj_type_name.remove_prefix(10);
				if (ImGui::TreeNode(fmt::format("{}<{}:null>", label, obj_type_name).c_str())) {
					ImGui::PopStyleColor();
					UIHelper::object_common_menu(data, _null_obj);
					ImGui::TreePop();
				}
				else ImGui::PopStyleColor();
				return;
			}
			auto tname = data->get_meta_info().tname;
			tname.remove_prefix(10);
			ImVec4 textColor = ImVec4(0.12f, 0.8f, 0.1f, 1.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, textColor);
			if (ImGui::TreeNode(fmt::format("{}<{}>", label, tname).c_str())) {
				ImGui::PopStyleColor();
				UIHelper::object_common_menu(data, _null_obj);
				if(data) data->construct_ui(can_modify);
				ImGui::TreePop();
			}
			else { ImGui::PopStyleColor(); }
		}

		template<>
		void UIHelper::construct_ui(const string& label, string& str, bool can_modify);

		template<>
		void UIHelper::construct_ui(const string& label, fs::path& path, bool can_modify);

		template<>
		void UIHelper::construct_ui(const string& label, SWCodeRef& code, bool can_modify);

		template<>
		void UIHelper::construct_ui(const string& label, bool& bb, bool can_modify);

		template<>
		void UIHelper::construct_ui(const string& label, int& ii, bool can_modify);

		template<>
		void UIHelper::construct_ui(const string& label, float& ff, bool can_modify);

		template<>
		void UIHelper::construct_ui(const string& label, double& ff, bool can_modify);

		template<>
		void UIHelper::construct_ui(const string& label, Transform& tf, bool can_modify);

		template<>
		void UIHelper::construct_ui(const string& label, vec3& tf, bool can_modify);

		template<>
		void UIHelper::construct_ui(const string& label, quat& q, bool can_modify);

		template<typename T>
		void UIHelper::construct_ui(const string& label, vector<T>& data, bool can_modify) {
			if (ImGui::TreeNode(fmt::format("{}<vector>", label).c_str())) {
				UIHelper::container_modify_menu(data);
				for (int i = 0; i < data.size(); i++) {
					construct_ui(fmt::format("{}-{}", label, i), data[i], can_modify);
				}
				ImGui::TreePop();
			}
		}

		template<typename TKey, typename TVal>
		void UIHelper::construct_ui(const string& label, map<TKey, TVal>& data, bool can_modify) {
			if (ImGui::TreeNode(fmt::format("{}<map>", label).c_str())) {
				UIHelper::container_modify_menu(data);
				for (auto& [key, value] : data){
					construct_ui(fmt::format("{}-{}", label, key), value, can_modify);
				}
				ImGui::TreePop();
			}
		}

		template<typename TKey, typename TVal>
		void UIHelper::construct_ui(const string& label, pair<TKey, TVal>& data, bool can_modify) {
			construct_ui(label + "<Pair:Key>", data.first, can_modify);
			construct_ui(label + "<Pair:Value>", data.second, can_modify);
		}


		template<typename T>
		void UIHelper::object_common_menu(Ref<T>& target, Ref<T>& reference) {
			if (ImGui::BeginPopupContextItem("##change--obj")){
				if (ImGui::Button("Add To Asset")) {
					Engine::get_world()->add_asset(target);
				}
				
				if (ImGui::Button("Reset To Null")) {
					target = nullptr;
				}

				ImGui::Separator();
				choice_object(target, reference);
				ImGui::EndPopup();
			}
		}

		template<typename T>
		void UIHelper::container_modify_menu(vector<T>& container) {
			if (ImGui::BeginPopupContextItem("##modify--vector")) {
				if (ImGui::Button("Push Back")) {
					container.push_back(T{});
				}

				if (ImGui::TreeNode("Remove")) {
					int remove_idx = -1;
					for (int i = 0; i < container.size(); i++) {
						if (ImGui::Selectable(fmt::format("[{}]", i).c_str(), false)) {
							remove_idx = i;
						}
					}
					if (remove_idx >= 0) container.erase(container.begin() + remove_idx);
					ImGui::TreePop();
				}
				ImGui::EndPopup();
			}
		}

		template<typename TKey, typename TVal>
		void UIHelper::container_modify_menu(map<TKey, TVal>& container) {
			if (ImGui::BeginPopupContextItem("##modify--map")) {
				if (ImGui::Button("Add")) {
					container[TKey{}] = TVal{};
				}

				if (ImGui::TreeNode("Remove")) {
					auto remove_it = container.end();
					for (auto it = container.begin(); it != container.end(); it++) {
						if (ImGui::Selectable(fmt::format("[{}]", it->first).c_str(), false)) {
							remove_it = it;
						}
					}
					if (remove_it != container.end()) container.erase(remove_it);
					ImGui::TreePop();
				}
				ImGui::EndPopup();
			}
		}

		template<typename T>
		void UIHelper::choice_object(Ref<T>& target, Ref<T>& reference) {
			assert(reference != nullptr);
			auto type_name = reference->get_meta_info().tname;
			type_name.remove_prefix(10);
			auto title = std::string(type_name) + " List";
			ImGui::TextColored(ImVec4(1.0f, 1.01f, 1.0f, 1.0f), title.c_str());
			for (auto& [_, v] : Engine::get_engine()->get_world()->get_all_assets()) {
				auto target_cast = pcast<T>(v);
				if (target_cast) {
					ImGui::PushID((ImGuiID)v->get_guid());
					if (ImGui::Selectable(v->name_.c_str())) {
						target = target_cast;
					}
					ImGui::PopID();
				}
			}
		}

		template<typename T>
		void UIHelper::drag_target(Ref<T>& obj) {
			if (ImGui::BeginDragDropTarget()) {
				log(fmt::format("begin is mouse down: {}", ImGui::IsMouseDown(0)));
				log("drag .... ");

				//ImGuiDragDropFlags drop_target_flags = ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoPreviewTooltip;
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ASSETS_IDS")) {
					if (payload->Data != nullptr) {
						const ImVector<ImGuiID>* receive = static_cast<const ImVector<ImGuiID>*>(payload->Data);
						for (int i = 0; i < receive->size(); i++) {
							auto id = (int)(*receive)[i];
							log(fmt::format("drag {} to current", id));
						}
					}
				}
				ImGui::EndDragDropTarget();
				log(fmt::format("end is mouse down: {}", ImGui::IsMouseDown(0)));
			}
		}

	}
}

#endif // !_IN_REFLECT
