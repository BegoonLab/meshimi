#include "../meshimi.h"

enum SubmenuIndex {
    SubmenuIndexConnect,
    SubmenuIndexTest,
    SubmenuIndexConfiguration,
    SubmenuIndexAbout,
};

void meshimi_scene_start_submenu_callback(void *context, uint32_t index) {
    Meshimi *meshimi = context;
    view_dispatcher_send_custom_event(meshimi->view_dispatcher, index);
}

void meshimi_scene_start_on_enter(void *context) {
    Meshimi *meshimi = context;

    submenu_add_item(
            meshimi->submenu, "Connect", SubmenuIndexConnect, meshimi_scene_start_submenu_callback, meshimi);
    submenu_add_item(
            meshimi->submenu, "Config", SubmenuIndexConfiguration, meshimi_scene_start_submenu_callback, meshimi);
    submenu_add_item(
            meshimi->submenu, "About", SubmenuIndexAbout, meshimi_scene_start_submenu_callback, meshimi);
    submenu_set_selected_item(
            meshimi->submenu, scene_manager_get_scene_state(meshimi->scene_manager, MeshimiSceneStart));

    view_dispatcher_switch_to_view(meshimi->view_dispatcher, MeshimiViewIdMenu);
}

bool meshimi_scene_start_on_event(void *context, SceneManagerEvent event) {
    Meshimi *meshimi = context;
    if (event.type == SceneManagerEventTypeBack) {
        //exit app
        scene_manager_stop(meshimi->scene_manager);
        view_dispatcher_stop(meshimi->view_dispatcher);
        return true;
    } else if (event.type == SceneManagerEventTypeCustom) {
        if (event.event == SubmenuIndexConnect) {
            scene_manager_set_scene_state(
                    meshimi->scene_manager, MeshimiSceneStart, SubmenuIndexConnect);
            scene_manager_next_scene(meshimi->scene_manager, MeshimiSceneConnect);
            return true;
        } else if (event.event == SubmenuIndexTest) {
            scene_manager_set_scene_state(
                    meshimi->scene_manager, MeshimiSceneStart, SubmenuIndexTest);
            scene_manager_next_scene(meshimi->scene_manager, MeshimiSceneTest);
            return true;
        } else if (event.event == SubmenuIndexConfiguration) {
            scene_manager_set_scene_state(
                    meshimi->scene_manager, MeshimiSceneStart, SubmenuIndexConfiguration);
            scene_manager_next_scene(meshimi->scene_manager, MeshimiSceneConfiguration);
            return true;
        } else if (event.event == SubmenuIndexAbout) {
            scene_manager_set_scene_state(
                    meshimi->scene_manager, MeshimiSceneStart, SubmenuIndexAbout);
            scene_manager_next_scene(meshimi->scene_manager, MeshimiSceneAbout);
            return true;
        }
    }
    return false;
}

void meshimi_scene_start_on_exit(void *context) {
    Meshimi *meshimi = context;
    submenu_reset(meshimi->submenu);
}
