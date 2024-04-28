#include "meshimi.h"

bool meshimi_custom_event_callback(void* context, uint32_t event) {
    furi_assert(context);
    Meshimi* meshimi = context;
    return scene_manager_handle_custom_event(meshimi->scene_manager, event);
}

bool meshimi_back_event_callback(void* context) {
    furi_assert(context);
    Meshimi* meshimi = context;
    return scene_manager_handle_back_event(meshimi->scene_manager);
}

void meshimi_tick_event_callback(void* context) {
    furi_assert(context);
    Meshimi* meshimi = context;
    scene_manager_handle_tick_event(meshimi->scene_manager);
}

Meshimi* meshimi_alloc() {
    Meshimi* meshimi = malloc(sizeof(Meshimi));

    // Meshimi Configuration
    meshimi->config = meshimi_config_alloc();

    // GUI
    meshimi->gui = furi_record_open(RECORD_GUI);

    // Bt
    meshimi->bt = furi_record_open(RECORD_BT);

    // View Dispatcher
    meshimi->view_dispatcher = view_dispatcher_alloc();
    view_dispatcher_enable_queue(meshimi->view_dispatcher);

    meshimi->scene_manager = scene_manager_alloc(&meshimi_scene_handlers, meshimi);
    view_dispatcher_set_event_callback_context(meshimi->view_dispatcher, meshimi);
    view_dispatcher_set_custom_event_callback(
        meshimi->view_dispatcher, meshimi_custom_event_callback);
    view_dispatcher_set_navigation_event_callback(
        meshimi->view_dispatcher, meshimi_back_event_callback);
    view_dispatcher_set_tick_event_callback(
        meshimi->view_dispatcher, meshimi_tick_event_callback, 100);

    // Open Notification record
    meshimi->notifications = furi_record_open(RECORD_NOTIFICATION);

    // SubMenu
    meshimi->submenu = submenu_alloc();
    view_dispatcher_add_view(
        meshimi->view_dispatcher, MeshimiViewIdMenu, submenu_get_view(meshimi->submenu));

    // Popup
    meshimi->popup = popup_alloc();
    view_dispatcher_add_view(
        meshimi->view_dispatcher, MeshimiViewIdPopup, popup_get_view(meshimi->popup));

    // Text Input
    meshimi->text_input = text_input_alloc();
    view_dispatcher_add_view(
        meshimi->view_dispatcher,
        MeshimiViewIdTextInput,
        text_input_get_view(meshimi->text_input));

    // Custom Widget
    meshimi->widget = widget_alloc();
    view_dispatcher_add_view(
        meshimi->view_dispatcher, MeshimiViewIdWidget, widget_get_view(meshimi->widget));

    // Dialog
    meshimi->dialogs = furi_record_open(RECORD_DIALOGS);

    // Views
    meshimi->meshimi_view_mode = meshimi_view_mode_alloc(meshimi->config);
    view_dispatcher_add_view(
        meshimi->view_dispatcher,
        MeshimiViewIdMode,
        meshimi_view_mode_get_view(meshimi->meshimi_view_mode));

    // Variable Item List
    meshimi->variable_item_list = variable_item_list_alloc();
    view_dispatcher_add_view(
        meshimi->view_dispatcher,
        MeshimiViewIdVariableItemList,
        variable_item_list_get_view(meshimi->variable_item_list));



    furi_hal_spi_bus_handle_init(&furi_hal_spi_bus_handle_external);

    return meshimi;
}

void meshimi_free(Meshimi* meshimi) {
    furi_assert(meshimi);

    // TextInput
    view_dispatcher_remove_view(meshimi->view_dispatcher, MeshimiViewIdTextInput);
    text_input_free(meshimi->text_input);

    // Custom Widget
    view_dispatcher_remove_view(meshimi->view_dispatcher, MeshimiViewIdWidget);
    widget_free(meshimi->widget);

    // Dialog
    furi_record_close(RECORD_DIALOGS);

    // Bt
    furi_record_close(RECORD_BT);
    meshimi->bt = NULL;

    // Variable Item List
    view_dispatcher_remove_view(meshimi->view_dispatcher, MeshimiViewIdVariableItemList);
    variable_item_list_free(meshimi->variable_item_list);

    // Submenu
    view_dispatcher_remove_view(meshimi->view_dispatcher, MeshimiViewIdMenu);
    submenu_free(meshimi->submenu);

    // Popup
    view_dispatcher_remove_view(meshimi->view_dispatcher, MeshimiViewIdPopup);
    popup_free(meshimi->popup);

    // Views
    view_dispatcher_remove_view(meshimi->view_dispatcher, MeshimiViewIdMode);
    meshimi_view_mode_free(meshimi->meshimi_view_mode);

    // Scene manager
    scene_manager_free(meshimi->scene_manager);

    // View Dispatcher
    view_dispatcher_free(meshimi->view_dispatcher);

    // GUI
    furi_record_close(RECORD_GUI);
    meshimi->gui = NULL;

    // Notifications
    furi_record_close(RECORD_NOTIFICATION);
    meshimi->notifications = NULL;

    // Meshimi Configuration
    meshimi_config_free(meshimi->config);

    furi_hal_spi_bus_handle_deinit(&furi_hal_spi_bus_handle_external);

    // The rest
    free(meshimi);
}

/**
 * @brief      Main function for Meshimi application.
 * @details    This function is the entry point for the Meshimi application.
 * @param p
 * @return 0 - Success
 */
int32_t meshimi_app(void* p) {
    UNUSED(p);
    FURI_LOG_I(LOG_TAG, "Start app");

    Meshimi* meshimi = meshimi_alloc();

#ifdef BACKLIGHT_ALWAYS_ON
    notification_message(meshimi->notifications, &sequence_display_backlight_enforce_on);
#endif

    view_dispatcher_attach_to_gui(
        meshimi->view_dispatcher, meshimi->gui, ViewDispatcherTypeFullscreen);
    scene_manager_next_scene(meshimi->scene_manager, MeshimiSceneStart);

    furi_hal_power_suppress_charge_enter();

    view_dispatcher_run(meshimi->view_dispatcher);

    notification_message(meshimi->notifications, &sequence_blink_green_100);

    furi_hal_power_suppress_charge_exit();

#ifdef BACKLIGHT_ALWAYS_ON
    notification_message(meshimi->notifications, &sequence_display_backlight_enforce_auto);
#endif

    meshimi_free(meshimi);

    return 0;
}