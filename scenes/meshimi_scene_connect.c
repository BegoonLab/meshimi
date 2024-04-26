#include "../meshimi.h"
#include "begoonlab_meshimi_icons.h"
#include <furi_hal_region.h>

void meshimi_scene_connect_on_enter(void* context) {
    Meshimi* meshimi = context;

    IconAnimation *icon = icon_animation_alloc(&A_Intro_128x64);
//    view_tie_icon_animation(meshimi->view_dispatcher, icon);
    icon_animation_start(icon);
    //one_shot_view_start_animation(meshimi->one_shot_view, &A_Levelup1_128x64);
    //canvas_draw_icon(meshimi->widget, 0, 0, &A_Intro_128x64);
//    widget_add_icon_element(meshimi->widget, 0, 0, &A_Intro_128x64);
    //widget_add_icon_element(meshimi->widget, 0, 0, &I_Meshimi_128x64);
//    widget_reset(meshimi->widget);

    view_dispatcher_switch_to_view(meshimi->view_dispatcher, MeshimiViewIdWidget);
}

bool meshimi_scene_connect_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void meshimi_scene_connect_on_exit(void* context) {
    Meshimi* meshimi = context;
    widget_reset(meshimi->widget);
}