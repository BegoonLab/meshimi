#include "../meshimi.h"

void meshimi_view_mode_ok_callback(InputType type, void* context) {
    furi_assert(context);
    Meshimi* meshimi = context;

    if(type == InputTypePress) {
        notification_message(meshimi->notifications, &sequence_set_green_255);
    } else if(type == InputTypeRelease) {
        notification_message(meshimi->notifications, &sequence_reset_green);
    }

    scene_manager_next_scene(meshimi->scene_manager, MeshimiSceneConfiguration);
}

void meshimi_scene_mode_on_exit(void* context) {
    UNUSED(context);
}

void meshimi_scene_mode_on_enter(void* context) {
    furi_assert(context);
    Meshimi* meshimi = context;
    view_dispatcher_switch_to_view(meshimi->view_dispatcher, MeshimiViewIdMode);
}

bool meshimi_scene_mode_on_event(void* context, SceneManagerEvent event) {
    furi_assert(context);
    Meshimi* meshimi = context;
    UNUSED(event);

    meshimi_view_mode_set_ok_callback(
        meshimi->meshimi_view_mode, meshimi_view_mode_ok_callback, meshimi);

    return false;
}