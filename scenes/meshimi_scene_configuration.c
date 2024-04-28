#include "../meshimi.h"
#include "meshimi_custom_event.h"
#include <furi_hal_region.h>

enum MeshimiItem {
    MeshimiMode,
};

static void meshimi_scene_configuration_var_list_enter_callback(void* context, uint32_t index) {
    furi_assert(context);
    Meshimi* meshimi = context;
    if(index == MeshimiMode) {
        view_dispatcher_send_custom_event(meshimi->view_dispatcher, MeshimiEventMode);
    }
}

void meshimi_scene_configuration_on_enter(void* context) {
    Meshimi* meshimi = context;
    MeshimiConfig *config = meshimi->config;
    MeshimiConfigMode mode = meshimi_mode_get(config);

    variable_item_list_set_enter_callback(
        meshimi->variable_item_list, meshimi_scene_configuration_var_list_enter_callback, meshimi);

    if (mode == ModeSimpleRX) {
        variable_item_list_add(
            meshimi->variable_item_list, "Mode: Simple RX", 0, NULL, NULL);

    } else if (mode == ModeSimpleTX) {
        variable_item_list_add(
            meshimi->variable_item_list, "Mode: Simple TX", 0, NULL, NULL);
    } else if (mode == ModeMeshtastic) {
        variable_item_list_add(
            meshimi->variable_item_list, "Mode: Meshtastic", 0, NULL, NULL);
    } else if (mode == ModeMeshimi) {
        variable_item_list_add(
            meshimi->variable_item_list, "Mode: Meshimi", 0, NULL, NULL);
    } else if (mode == ModeLoRaWAN) {
        variable_item_list_add(
            meshimi->variable_item_list, "Mode: LoRaWAN", 0, NULL, NULL);
    }

    view_dispatcher_switch_to_view(meshimi->view_dispatcher, MeshimiViewIdVariableItemList);
}

bool meshimi_scene_configuration_on_event(void* context, SceneManagerEvent event) {
    Meshimi* meshimi = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == MeshimiEventMode) {
            scene_manager_set_scene_state(meshimi->scene_manager, MeshimiSceneStart, MeshimiMode);
            scene_manager_next_scene(meshimi->scene_manager, MeshimiSceneMode);
        }
        consumed = true;
    }

    if(event.type == SceneManagerEventTypeBack) {
        scene_manager_next_scene(meshimi->scene_manager, MeshimiSceneStart);
        consumed = true;
    }

    return consumed;
}

void meshimi_scene_configuration_on_exit(void* context) {
    Meshimi* meshimi = context;
    variable_item_list_set_selected_item(meshimi->variable_item_list, 0);
    variable_item_list_reset(meshimi->variable_item_list);
    widget_reset(meshimi->widget);
}
