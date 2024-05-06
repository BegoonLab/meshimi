#include "../meshimi.h"

void meshimi_scene_about_on_enter(void* context) {
    Meshimi* meshimi = context;

    FuriString* temp_str;
    temp_str = furi_string_alloc();
    furi_string_printf(temp_str, "\e#%s\n", "Buy module");

    furi_string_cat_printf(temp_str, "%s\n\n", MESHIMI_GET_MODULE);

    furi_string_cat_printf(temp_str, "\e#%s\n", "Information");

    furi_string_cat_printf(temp_str, "Version: %s\n", MESHIMI_VERSION);
    furi_string_cat_printf(temp_str, "%s\n\n", MESHIMI_GITHUB);

    furi_string_cat_printf(temp_str, "\e#%s\n", "Description");
    furi_string_cat_printf(
            temp_str,
            "Meshimi empowers your\nFlipper Zero with advanced\nmesh networking capabilities,\nutilizing Meshtastic,\nLoRaWAN, and a proprietary\nsecure mesh protocol\nto deliver superior\nconnectivity\nand robust security.\n\n");

    widget_add_text_box_element(
            meshimi->widget,
            0,
            0,
            128,
            14,
            AlignCenter,
            AlignBottom,
            "\e#\e!                                                      \e!\n",
            false);
    widget_add_text_box_element(
            meshimi->widget,
            0,
            2,
            128,
            14,
            AlignCenter,
            AlignBottom,
            "\e#\e!              Meshimi                                 \e!\n",
            false);
    widget_add_text_scroll_element(meshimi->widget, 0, 16, 128, 50, furi_string_get_cstr(temp_str));
    furi_string_free(temp_str);

    view_dispatcher_switch_to_view(meshimi->view_dispatcher, MeshimiViewIdWidget);
}

bool meshimi_scene_about_on_event(void* context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void meshimi_scene_about_on_exit(void* context) {
    Meshimi* meshimi = context;
    widget_reset(meshimi->widget);
}