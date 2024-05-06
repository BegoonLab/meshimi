#include "../meshimi.h"
#include "meshimi_custom_event.h"
#include <furi_hal_region.h>

enum MeshimiConfigurationItem {
    MeshimiMode,
    MeshimiFrequency,
};

static void meshimi_scene_configuration_var_list_enter_callback(void* context, uint32_t index) {
    furi_assert(context);
    Meshimi* meshimi = context;
    if(index == MeshimiMode) {
        view_dispatcher_send_custom_event(meshimi->view_dispatcher, MeshimiEventMode);
    } else if(index == MeshimiFrequency) {
        view_dispatcher_send_custom_event(meshimi->view_dispatcher, MeshimiEventFrequency);
    }
}

void meshimi_scene_configuration_spreading_factor_callback(VariableItem* item) {
    Meshimi* meshimi = variable_item_get_context(item);
    furi_assert(meshimi);
    MeshimiConfig* config = meshimi->config;
    furi_assert(config);

    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, meshimi_spreading_factor_get_text(index));
    meshimi_spreading_factor_set(config, index);

    view_dispatcher_send_custom_event(meshimi->view_dispatcher, MeshimiEventSpreadingFactor);
}

void meshimi_scene_configuration_bandwidth_callback(VariableItem* item) {
    Meshimi* meshimi = variable_item_get_context(item);
    furi_assert(meshimi);
    MeshimiConfig* config = meshimi->config;
    furi_assert(config);

    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, meshimi_bandwidth_get_text(index));
    meshimi_bandwidth_set(config, index);

    view_dispatcher_send_custom_event(meshimi->view_dispatcher, MeshimiEventBandwidth);
}

void meshimi_scene_configuration_coding_rate_callback(VariableItem* item) {
    Meshimi* meshimi = variable_item_get_context(item);
    furi_assert(meshimi);
    MeshimiConfig* config = meshimi->config;
    furi_assert(config);

    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, meshimi_coding_rate_get_text(index));
    meshimi_coding_rate_set(config, index);

    view_dispatcher_send_custom_event(meshimi->view_dispatcher, MeshimiEventCodingRate);
}

void meshimi_scene_configuration_ldro_callback(VariableItem* item) {
    Meshimi* meshimi = variable_item_get_context(item);
    furi_assert(meshimi);
    MeshimiConfig* config = meshimi->config;
    furi_assert(config);

    uint8_t index = variable_item_get_current_value_index(item);

    variable_item_set_current_value_text(item, meshimi_ldro_get_text(index));
    meshimi_ldro_set(config, index);

    view_dispatcher_send_custom_event(meshimi->view_dispatcher, MeshimiEventLDRO);
}

void meshimi_scene_configuration_on_enter(void* context) {
    Meshimi* meshimi = context;
    MeshimiConfig* config = meshimi->config;
    MeshimiConfigMode mode = meshimi_mode_get(config);
    VariableItem* item;

    variable_item_list_set_enter_callback(
        meshimi->variable_item_list, meshimi_scene_configuration_var_list_enter_callback, meshimi);

    if(mode == ModeSimpleRX) {
        variable_item_list_add(
            meshimi->variable_item_list, "Mode:             Simple RX", 0, NULL, NULL);
        variable_item_list_add(
            meshimi->variable_item_list, "Freq:       868,000,000Hz", 0, NULL, NULL);
        item = variable_item_list_add(
            meshimi->variable_item_list,
            "Spread. Factor:",
            SPREADING_FACTOR_COUNT,
            meshimi_scene_configuration_spreading_factor_callback,
            meshimi);
        variable_item_set_current_value_index(item, meshimi_spreading_factor_get(config));
        variable_item_set_current_value_text(
            item, meshimi_spreading_factor_get_text(meshimi_spreading_factor_get(config)));

        item = variable_item_list_add(
            meshimi->variable_item_list,
            "Bandwidth:",
            BANDWIDTH_COUNT,
            meshimi_scene_configuration_bandwidth_callback,
            meshimi);
        variable_item_set_current_value_index(item, meshimi_bandwidth_get(config));
        variable_item_set_current_value_text(
            item, meshimi_bandwidth_get_text(meshimi_bandwidth_get(config)));

        item = variable_item_list_add(
            meshimi->variable_item_list,
            "Coding Rate:",
            CODING_RATE_COUNT,
            meshimi_scene_configuration_coding_rate_callback,
            meshimi);
        variable_item_set_current_value_index(item, meshimi_coding_rate_get(config));
        variable_item_set_current_value_text(
            item, meshimi_coding_rate_get_text(meshimi_coding_rate_get(config)));

        item = variable_item_list_add(
            meshimi->variable_item_list,
            "LDRO:",
            LDRO_COUNT,
            meshimi_scene_configuration_ldro_callback,
            meshimi);
        variable_item_set_current_value_index(item, meshimi_ldro_get(config));
        variable_item_set_current_value_text(
            item, meshimi_ldro_get_text(meshimi_ldro_get(config)));

    } else if(mode == ModeSimpleTX) {
        variable_item_list_add(meshimi->variable_item_list, "Mode: Simple TX", 0, NULL, NULL);
    } else if(mode == ModeMeshtastic) {
        variable_item_list_add(meshimi->variable_item_list, "Mode: Meshtastic", 0, NULL, NULL);
    } else if(mode == ModeMeshimi) {
        variable_item_list_add(meshimi->variable_item_list, "Mode: Meshimi", 0, NULL, NULL);
    } else if(mode == ModeLoRaWAN) {
        variable_item_list_add(meshimi->variable_item_list, "Mode: LoRaWAN", 0, NULL, NULL);
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
            consumed = true;
        } else if(event.event == MeshimiEventFrequency) {
            scene_manager_set_scene_state(
                meshimi->scene_manager, MeshimiSceneStart, MeshimiFrequency);
            scene_manager_next_scene(meshimi->scene_manager, MeshimiSceneFrequency);
            consumed = true;
        }
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
