#pragma once
#include "Object.h"
#include "Event.h"

#include <imgui.h>

struct SelectionWithDeletion : ImGuiSelectionBasicStorage{
    int ApplyDeletionPreLoop(ImGuiMultiSelectIO* ms_io, int items_count);
    
    void ApplyDeletionPostLoop(ImGuiMultiSelectIO* ms_io, std::vector<staywalk::Ref<staywalk::Object>>& items, int item_curr_idx_to_select);
};

class AssetsBrowser
{
public:
    AssetsBrowser();
    ~AssetsBrowser();

    void update_items();

    void clear(){ selection_.Clear();}

    // Logic would be written in the main code BeginChild() and outputing to local variables.
    // We extracted it into a function so we can call it easily from multiple places.
    void update_layout_sizes(float avail_width);

    void draw(const char* title, bool* p_open);

private:
    decltype(staywalk::Event::World_AssetChanged)::Handle asset_changed_handler_;

	std::vector<ImU32> type_icon_colors_;
	std::map<int, std::string> type_icon_labels_;

    // Options
    bool            show_type_overlay_ = true;
    bool            allow_sorting_ = false;
    bool            allow_drag_unselected_ = false;
    bool            allow_box_select_ = true;
    float           icon_size_ = 52.0f;
    int             icon_spacing_ = 10;
    int             icon_hit_spacing_ = 4;         // Increase hit-spacing if you want to make it possible to clear or box-select from gaps. Some spacing is required to able to amend with Shift+box-select. Value is small in Explorer.
    bool            stretch_spacing_ = true;

    // State
    std::vector<staywalk::Ref<staywalk::Object>> items_;               // Our items
    SelectionWithDeletion selection_;     // Our selection (ImGuiSelectionBasicStorage + helper funcs to handle deletion)
    ImGuiID         next_item_id_ = 0;             // Unique identifier when creating new items
    bool            request_delete_ = false;      // Deferred deletion request
    bool            request_sort_ = false;        // Deferred sort request
    float           zoom_wheel_accum_ = 0.0f;      // Mouse wheel accumulator to handle smooth wheels better

    // Calculated sizes for layout, output of UpdateLayoutSizes(). Could be locals but our code is simpler this way.
    ImVec2          item_size_;
    ImVec2          item_step_;             // == LayoutItemSize + LayoutItemSpacing
    float           item_spacing_ = 0.0f;
    float           selectable_spacing_ = 0.0f;
    float           outer_padding_ = 0.0f;
    int             column_count_ = 0;
    int             line_count_ = 0;

    bool modify_open_;
    bool modify_pop_ = false;
    staywalk::Ref<staywalk::Object> modify_obj_{nullptr};
};