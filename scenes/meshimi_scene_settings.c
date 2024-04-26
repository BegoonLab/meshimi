#include "../meshimi.h"

#include <furi_hal_region.h>

void meshimi_scene_settings_on_enter(void *context) {
    Meshimi *meshimi = context;
    const FuriHalRegion *const region = furi_hal_region_get();
    FuriString *buffer = furi_string_alloc();
    if (region) {
        furi_string_cat_printf(buffer, "Region: %s,  bands:\n", region->country_code);
        for (uint16_t i = 0; i < region->bands_count; ++i) {
            furi_string_cat_printf(
                    buffer,
                    "   %lu-%lu kHz\n",
                    region->bands[i].start / 1000,
                    region->bands[i].end / 1000);
        }
    } else {
        furi_string_cat_printf(buffer, "Region: N/A\n");
    }

    widget_add_string_multiline_element(
            meshimi->widget, 0, 0, AlignLeft, AlignTop, FontSecondary, furi_string_get_cstr(buffer));

    furi_string_free(buffer);
    view_dispatcher_switch_to_view(meshimi->view_dispatcher, MeshimiViewIdWidget);
}

bool meshimi_scene_settings_on_event(void *context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void meshimi_scene_settings_on_exit(void *context) {
    Meshimi *meshimi = context;
    widget_reset(meshimi->widget);
}