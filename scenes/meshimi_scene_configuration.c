#include "../meshimi.h"

#include <furi_hal_region.h>

#define MODE_COUNT 5
const char* const mode_text[MODE_COUNT] = {
    "Simple RX",
    "Simple TX",
    "LoRaWAN",
    "Meshtastic",
    "Meshimi",
};
const MeshimiConfigMode mode_value[MODE_COUNT] = {
    ModeSimpleRX,
    ModeSimpleTX,
    ModeLoRaWAN,
    ModeMeshtastic,
    ModeMeshimi,
};

static void meshimi_scene_configuration_set_mode(VariableItem* item) {
    Meshimi* meshimi = variable_item_get_context(item);
    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, mode_text[index]);
    meshimi_mode_set(meshimi->config, mode_value[index]);
}

uint8_t meshimi_scene_configuration_mode_value_index(
    MeshimiConfigMode value,
    const MeshimiConfigMode values[],
    uint8_t values_count,
    void* context) {
    furi_assert(context);
    UNUSED(values_count);
    UNUSED(values);
    UNUSED(context);

    switch(value) {
    case ModeSimpleRX:
        return 0;
    case ModeSimpleTX:
        return 1;
    case ModeMeshtastic:
        return 3;
    case ModeMeshimi:
        return 4;
    case ModeLoRaWAN:
        return 2;
    default:
        return 0;
    }
}

void meshimi_scene_configuration_on_enter(void* context) {
    Meshimi* meshimi = context;
    VariableItem* item;
    uint8_t value_index;

    item = variable_item_list_add(
        meshimi->variable_item_list,
        "Mode:",
        MODE_COUNT,
        meshimi_scene_configuration_set_mode,
        meshimi);

    value_index = meshimi_scene_configuration_mode_value_index(
        meshimi_mode_get(meshimi->config), mode_value, MODE_COUNT, meshimi);
    variable_item_set_current_value_index(item, value_index);
    variable_item_set_current_value_text(item, mode_text[value_index]);

    //    const FuriHalRegion* const region = furi_hal_region_get();
    //    FuriString* buffer = furi_string_alloc();
    //    if(region) {
    //        furi_string_cat_printf(buffer, "Region: %s,  bands:\n", region->country_code);
    //        for(uint16_t i = 0; i < region->bands_count; ++i) {
    //            furi_string_cat_printf(
    //                buffer,
    //                "   %lu-%lu kHz\n",
    //                region->bands[i].start / 1000,
    //                region->bands[i].end / 1000);
    //        }
    //    } else {
    //        furi_string_cat_printf(buffer, "Region: N/A\n");
    //    }
    //
    //    widget_add_string_multiline_element(
    //        meshimi->widget, 0, 0, AlignLeft, AlignTop, FontSecondary, furi_string_get_cstr(buffer));
    //
    //    furi_string_free(buffer);
    view_dispatcher_switch_to_view(meshimi->view_dispatcher, MeshimiViewIdVariableItemList);
}

bool meshimi_scene_configuration_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void meshimi_scene_configuration_on_exit(void* context) {
    Meshimi* meshimi = context;
    variable_item_list_set_selected_item(meshimi->variable_item_list, 0);
    variable_item_list_reset(meshimi->variable_item_list);
    widget_reset(meshimi->widget);
}
