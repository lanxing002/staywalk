#include "AssetBrowser.h"
#include "reflect.h"
#include "Engine.h"

#include <fmt/format.h>

using namespace staywalk;

AssetsBrowser::AssetsBrowser(){
    modify_open_ = true;
    asset_changed_handler_ = Event::World_AssetChanged.append(std::bind(&AssetsBrowser::update_items, this));
    type_icon_colors_ = {
        IM_COL32(200, 70, 70, 255),
        IM_COL32(70, 170, 70, 255),
        IM_COL32(10, 110, 00, 255),
        IM_COL32(170, 170, 120, 255),
        IM_COL32(110, 20, 90, 255),
        IM_COL32(10, 120, 80, 255),
        IM_COL32(220, 110, 70, 255),
    };
}

AssetsBrowser::~AssetsBrowser(){
    Event::World_AssetChanged.remove(asset_changed_handler_);
}

void AssetsBrowser::update_items(){
    items_.clear();
    for (auto [_, obj] : Engine::get_world()->get_all_assets()) {
        items_.push_back(obj);
    }
    return;
}

void AssetsBrowser::update_layout_sizes(float avail_width)
{
    // Layout: when not stretching: allow extending into right-most spacing.
    item_spacing_ = (float)icon_spacing_;
    if (stretch_spacing_ == false)
        avail_width += floorf(item_spacing_ * 0.5f);

    // Layout: calculate number of icon per line and number of lines
    item_size_ = ImVec2(floorf(icon_size_), floorf(icon_size_));
    column_count_ = std::max((int)(avail_width / (item_size_.x + item_spacing_)), 1);
    line_count_ = ((int)items_.size() + column_count_ - 1) / column_count_;

    // Layout: when stretching: allocate remaining space to more spacing. Round before division, so item_spacing may be non-integer.
    if (stretch_spacing_ && column_count_ > 1)
        item_spacing_ = floorf(avail_width - item_size_.x * column_count_) / column_count_;

    item_step_ = ImVec2(item_size_.x + item_spacing_, item_size_.y + item_spacing_);
    selectable_spacing_ = std::max(floorf(item_spacing_) - icon_hit_spacing_, 0.0f);
    outer_padding_ = floorf(item_spacing_ * 0.5f);
}

void AssetsBrowser::draw(const char* title, bool* p_open){
    ImGui::SetNextWindowSize(ImVec2(icon_size_ * 25, icon_size_ * 15), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(title, p_open, ImGuiWindowFlags_MenuBar)){
        ImGui::End();
        return;
    }

    // Menu bar
    if (ImGui::BeginMenuBar()){
        if (ImGui::BeginMenu("Options")){
            ImGui::PushItemWidth(ImGui::GetFontSize() * 10);

            ImGui::SeparatorText("Contents");
            ImGui::Checkbox("Show Type Overlay", &show_type_overlay_);
            ImGui::Checkbox("Allow Sorting", &allow_sorting_);

            ImGui::SeparatorText("Selection Behavior");
            ImGui::Checkbox("Allow dragging unselected item", &allow_drag_unselected_);
            ImGui::Checkbox("Allow box-selection", &allow_box_select_);

            ImGui::SeparatorText("Layout");
            ImGui::SliderFloat("Icon Size", &icon_size_, 16.0f, 128.0f, "%.0f");
            ImGui::SliderInt("Icon Spacing", &icon_spacing_, 0, 32);
            ImGui::SliderInt("Icon Hit Spacing", &icon_hit_spacing_, 0, 32);
            ImGui::Checkbox("Stretch Spacing", &stretch_spacing_);
            ImGui::PopItemWidth();
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    // Show a table with ONLY one header row to showcase the idea/possibility of using this to provide a sorting UI
    if (allow_sorting_)
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        ImGuiTableFlags table_flags_for_sort_specs = ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders;
        if (ImGui::BeginTable("for_sort_specs_only", 2, table_flags_for_sort_specs, ImVec2(0.0f, ImGui::GetFrameHeight())))
        {
            ImGui::TableSetupColumn("Index");
            ImGui::TableSetupColumn("Type");
            ImGui::TableHeadersRow();
            if (ImGuiTableSortSpecs* sort_specs = ImGui::TableGetSortSpecs())
                if (sort_specs->SpecsDirty || request_sort_)
                {
                    //ExampleAsset::SortWithSortSpecs(sort_specs, items_.Data, items_.Size);
                    sort_specs->SpecsDirty = request_sort_ = false;
                }
            ImGui::EndTable();
        }
        ImGui::PopStyleVar();
    }

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowContentSize(ImVec2(0.0f, outer_padding_ + line_count_ * (item_size_.x + item_spacing_)));
    if (ImGui::BeginChild("Assets", ImVec2(0.0f, -ImGui::GetTextLineHeightWithSpacing()), ImGuiChildFlags_Borders, ImGuiWindowFlags_NoMove)){
        ImDrawList* draw_list = ImGui::GetWindowDrawList();

        const float avail_width = ImGui::GetContentRegionAvail().x;
        update_layout_sizes(avail_width);

        // Calculate and store start position.
        ImVec2 start_pos = ImGui::GetCursorScreenPos();
        start_pos = ImVec2(start_pos.x + outer_padding_, start_pos.y + outer_padding_);
        ImGui::SetCursorScreenPos(start_pos);

        // Multi-select
        ImGuiMultiSelectFlags ms_flags = ImGuiMultiSelectFlags_ClearOnEscape | ImGuiMultiSelectFlags_ClearOnClickVoid;

        // - Enable box-select (in 2D mode, so that changing box-select rectangle X1/X2 boundaries will affect clipped items)
        if (allow_box_select_)
            ms_flags |= ImGuiMultiSelectFlags_BoxSelect2d;

        // - This feature allows dragging an unselected item without selecting it (rarely used)
        if (allow_drag_unselected_)
            ms_flags |= ImGuiMultiSelectFlags_SelectOnClickRelease;

        // - Enable keyboard wrapping on X axis
        // (FIXME-MULTISELECT: We haven't designed/exposed a general nav wrapping api yet, so this flag is provided as a courtesy to avoid doing:
        //    ImGui::NavMoveRequestTryWrapping(ImGui::GetCurrentWindow(), ImGuiNavMoveFlags_WrapX);
        // When we finish implementing a more general API for this, we will obsolete this flag in favor of the new system)
        ms_flags |= ImGuiMultiSelectFlags_NavWrapX;

        ImGuiMultiSelectIO* ms_io = ImGui::BeginMultiSelect(ms_flags, selection_.Size, (int)items_.size());

        // Use custom selection adapter: store ID in selection (recommended)
        selection_.UserData = this;
        //selection_.AdapterIndexToStorageId = [](ImGuiSelectionBasicStorage* self_, int idx) { 
        //    /*ExampleAssetsBrowser* self = (ExampleAssetsBrowser*)self_->UserData; return self->Items[idx].ID; */
        //    return 0;
        //};
        selection_.ApplyRequests(ms_io);

        const bool want_delete = (ImGui::Shortcut(ImGuiKey_Delete, ImGuiInputFlags_Repeat) && (selection_.Size > 0)) || request_delete_;
        const int item_curr_idx_to_focus = want_delete ? selection_.ApplyDeletionPreLoop(ms_io, (int)items_.size()) : -1;
        request_delete_ = false;

        // Push LayoutSelectableSpacing (which is LayoutItemSpacing minus hit-spacing, if we decide to have hit gaps between items)
        // Altering style ItemSpacing may seem unnecessary as we position every items using SetCursorScreenPos()...
        // But it is necessary for two reasons:
        // - Selectables uses it by default to visually fill the space between two items.
        // - The vertical spacing would be measured by Clipper to calculate line height if we didn't provide it explicitly (here we do).
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(selectable_spacing_, selectable_spacing_));

        const ImU32 icon_bg_color = ImGui::GetColorU32(IM_COL32(35, 35, 35, 220));
        const ImVec2 icon_type_overlay_size = ImVec2(12.0f, 12.0f);
        const bool display_label = (item_size_.x >= ImGui::CalcTextSize("999").x);

        const int column_count = column_count_;
        ImGuiListClipper clipper;
        clipper.Begin(line_count_, item_step_.y);
        if (item_curr_idx_to_focus != -1)
            clipper.IncludeItemByIndex(item_curr_idx_to_focus / column_count); // Ensure focused item line is not clipped.
        if (ms_io->RangeSrcItem != -1)
            clipper.IncludeItemByIndex((int)ms_io->RangeSrcItem / column_count); // Ensure RangeSrc item line is not clipped.
        while (clipper.Step())
        {
            for (int line_idx = clipper.DisplayStart; line_idx < clipper.DisplayEnd; line_idx++)
            {
                const int item_min_idx_for_current_line = line_idx * column_count;
                const int item_max_idx_for_current_line = std::min((line_idx + 1) * column_count, (int)items_.size());
                for (int item_idx = item_min_idx_for_current_line; item_idx < item_max_idx_for_current_line; ++item_idx)
                {
                    Ref<Object> item = items_[item_idx];
                    ImGui::PushID((ImGuiID)item_idx);

                    // Position item
                    ImVec2 pos = ImVec2(start_pos.x + (item_idx % column_count) * item_step_.x, start_pos.y + line_idx * item_step_.y);
                    ImGui::SetCursorScreenPos(pos);

                    ImGui::SetNextItemSelectionUserData(item_idx);
                    bool item_is_selected = selection_.Contains((ImGuiID)item_idx);
                    bool item_is_visible = ImGui::IsRectVisible(item_size_);
                    ImGui::Selectable("", item_is_selected, ImGuiSelectableFlags_None, item_size_);

                    if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {
                        ImGui::OpenPopup("asset-modify-object");
                        modify_open_ = true;
                        modify_obj_ = item;
                    }

                    // Update our selection state immediately (without waiting for EndMultiSelect() requests)
                    // because we use this to alter the color of our text/icon.
                    if (ImGui::IsItemToggledSelection())
                        item_is_selected = !item_is_selected;

                    // Focus (for after deletion)
                    if (item_curr_idx_to_focus == item_idx)
                        ImGui::SetKeyboardFocusHere(-1);

                    // Render icon (a real app would likely display an image/thumbnail here)
                    // Because we use ImGuiMultiSelectFlags_BoxSelect2d, clipping vertical may occasionally be larger, so we coarse-clip our rendering as well.
                    if (item_is_visible){
                        ImVec2 box_min(pos.x - 1, pos.y - 1);
                        ImVec2 box_max(box_min.x + item_size_.x + 2, box_min.y + item_size_.y + 2); // Dubious
                        draw_list->AddRectFilled(box_min, box_max, icon_bg_color); // Background color
                        uint otype = (uint)item->get_meta_info().otype;
                        if (show_type_overlay_){
                            ImU32 type_col = type_icon_colors_[otype % type_icon_colors_.size()];
                            draw_list->AddRectFilled(ImVec2(box_max.x - 2 - icon_type_overlay_size.x, box_min.y + 2), ImVec2(box_max.x - 2, box_min.y + 2 + icon_type_overlay_size.y), type_col);
                        }
                        if (display_label){
                            ImU32 label_col = ImGui::GetColorU32(item_is_selected ? ImGuiCol_Text : ImGuiCol_TextDisabled);
                            draw_list->AddText(ImVec2(box_min.x, box_max.y - ImGui::GetFontSize()), label_col, 
                                item->name.c_str());
                        }
                    }

                    ImGui::PopID();
                }
            }
        }
        clipper.End();
        ImGui::PopStyleVar(); // ImGuiStyleVar_ItemSpacing

        // Context menu
        if (ImGui::BeginPopupContextWindow())
        {
            ImGui::Text("Selection: %d items", selection_.Size);
            ImGui::Separator();
            if (ImGui::MenuItem("Delete", "Del", false, selection_.Size > 0))
                request_delete_ = true;
            ImGui::EndPopup();
        }

        ms_io = ImGui::EndMultiSelect();
        selection_.ApplyRequests(ms_io);
        if (want_delete)
            selection_.ApplyDeletionPostLoop(ms_io, items_, item_curr_idx_to_focus);

        // Zooming with CTRL+Wheel
        if (ImGui::IsWindowAppearing())
            zoom_wheel_accum_ = 0.0f;
        if (ImGui::IsWindowHovered() && io.MouseWheel != 0.0f && ImGui::IsKeyDown(ImGuiMod_Ctrl) && ImGui::IsAnyItemActive() == false)
        {
            zoom_wheel_accum_ += io.MouseWheel;
            if (fabsf(zoom_wheel_accum_) >= 1.0f)
            {
                // Calculate hovered item index from mouse location
                // FIXME: Locking aiming on 'hovered_item_idx' (with a cool-down timer) would ensure zoom keeps on it.
                const float hovered_item_nx = (io.MousePos.x - start_pos.x + item_spacing_ * 0.5f) / item_step_.x;
                const float hovered_item_ny = (io.MousePos.y - start_pos.y + item_spacing_ * 0.5f) / item_step_.y;
                const int hovered_item_idx = ((int)hovered_item_ny * column_count) + (int)hovered_item_nx;
                //ImGui::SetTooltip("%f,%f -> item %d", hovered_item_nx, hovered_item_ny, hovered_item_idx); // Move those 4 lines in block above for easy debugging

                // Zoom
                icon_size_ *= powf(1.1f, (float)(int)zoom_wheel_accum_);
                icon_size_ = std::clamp(icon_size_, 16.0f, 128.0f);
                zoom_wheel_accum_ -= (int)zoom_wheel_accum_;
                update_layout_sizes(avail_width);

                // Manipulate scroll to that we will land at the same Y location of currently hovered item.
                // - Calculate next frame position of item under mouse
                // - Set new scroll position to be used in next ImGui::BeginChild() call.
                float hovered_item_rel_pos_y = ((float)(hovered_item_idx / column_count) + fmodf(hovered_item_ny, 1.0f)) * item_step_.y;
                hovered_item_rel_pos_y += ImGui::GetStyle().WindowPadding.y;
                float mouse_local_y = io.MousePos.y - ImGui::GetWindowPos().y;
                ImGui::SetScrollY(hovered_item_rel_pos_y - mouse_local_y);
            }
        }
    }
    
    if (ImGui::BeginPopupModal("asset-modify-object", nullptr,
        ImGuiWindowFlags_AlwaysAutoResize | ImGuiPopupFlags_AnyPopup)) {
        ImGui::Text("world name:");
        if (modify_obj_) modify_obj_->construct_ui(false);
        //ImGui::CloseCurrentPopup();
        ImGui::SameLine();
        if (ImGui::Button(" Cancel ")) ImGui::CloseCurrentPopup();

        ImGui::EndPopup();
    }

    ImGui::EndChild();

    ImGui::Text("Selected: %d/%d items", selection_.Size, (int)items_.size());
    ImGui::End();
}

int SelectionWithDeletion::ApplyDeletionPreLoop(ImGuiMultiSelectIO* ms_io, int items_count){
    if (Size == 0)
        return -1;

    // If focused item is not selected...
    const int focused_idx = (int)ms_io->NavIdItem;  // Index of currently focused item
    if (ms_io->NavIdSelected == false)  // This is merely a shortcut, == Contains(adapter->IndexToStorage(items, focused_idx))
    {
        ms_io->RangeSrcReset = true;    // Request to recover RangeSrc from NavId next frame. Would be ok to reset even when NavIdSelected==true, but it would take an extra frame to recover RangeSrc when deleting a selected item.
        return focused_idx;             // Request to focus same item after deletion.
    }

    // If focused item is selected: land on first unselected item after focused item.
    for (int idx = focused_idx + 1; idx < items_count; idx++)
        if (!Contains(GetStorageIdFromIndex(idx)))
            return idx;

    // If focused item is selected: otherwise return last unselected item before focused item.
    for (int idx = std::min(focused_idx, items_count) - 1; idx >= 0; idx--)
        if (!Contains(GetStorageIdFromIndex(idx)))
            return idx;

    return -1;
}

void SelectionWithDeletion::ApplyDeletionPostLoop(ImGuiMultiSelectIO* ms_io, std::vector<staywalk::Ref<staywalk::Object>>& items, int item_curr_idx_to_select)
{
    // Rewrite item list (delete items) + convert old selection index (before deletion) to new selection index (after selection).
    // If NavId was not part of selection, we will stay on same item.
    std::vector<staywalk::Ref<staywalk::Object>> new_items;
    new_items.reserve((int)items.size() - Size);
    int item_next_idx_to_select = -1;
    for (int idx = 0; idx < (int)items.size(); idx++)
    {
        if (!Contains(GetStorageIdFromIndex(idx)))
            new_items.push_back(items[idx]);
        if (item_curr_idx_to_select == idx)
            item_next_idx_to_select = (int)new_items.size() - 1;
    }
    items.swap(new_items);

    // Update selection
    Clear();
    if (item_next_idx_to_select != -1 && ms_io->NavIdSelected)
        SetItemSelected(GetStorageIdFromIndex(item_next_idx_to_select), true);
}