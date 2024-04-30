#include "../meshimi.h"
#include "meshimi_custom_event.h"
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

void meshimi_scene_frequency_input_callback(void* context) {
    furi_assert(context);
    Meshimi* meshimi = context;
    view_dispatcher_send_custom_event(meshimi->view_dispatcher, MeshimiEventFrequency);
}

bool validator_lora_frequency_callback(const char* text, FuriString* error, void* context) {
    furi_check(context);

    // Check if the text length is exactly 9 digits
    if(strlen(text) != 9) {
        furi_string_printf(error, "Frequency\nmust be\nexactly 9\ndigits.");
        return false;
    }

    // Check if all characters are digits
    for(int i = 0; i < 9; i++) {
        if(!isdigit((unsigned char)text[i])) {
            furi_string_printf(error, "Frequency\nmust contain\nonly digits.");
            return false;
        }
    }

    char* endptr;
    long frequency = strtol(text, &endptr, 10);

    // Check if the entire string was successfully converted
    if(*endptr != '\0') {
        furi_string_printf(error, "Frequency\nis invalid.");
        return false;
    }

    const FuriHalRegion* const region = furi_hal_region_get();

    // Check regional RF allowance
    if(region) {
        bool is_within_range = false;
        for(uint16_t i = 0; i < region->bands_count; ++i) {
            if((unsigned long)frequency >= region->bands[i].start &&
               (unsigned long)frequency <= region->bands[i].end) {
                is_within_range = true;
                break;
            }
        }
        if(!is_within_range) {
            furi_string_printf(error, "Frequency\nis out of\nallowed\nrange");
            return false;
        }
    } else {
        // Check LoRa modem absolute limits
        if(frequency < 150000000 || frequency > 960000000) {
            furi_string_printf(error, "Frequency\nis out of\nallowed\nrange");
            return false;
        }
    }

    return true;
}

void meshimi_scene_frequency_on_enter(void* context) {
    Meshimi* meshimi = context;
    MeshimiConfig* config = meshimi->config;
    FuriString* frequency_text = furi_string_alloc();
    furi_string_printf(frequency_text, "%lu", meshimi_frequency_get(config));

    strncpy(meshimi->text_store, furi_string_get_cstr(frequency_text), FREQUENCY_TEXT_LEN);
    text_input_set_header_text(meshimi->text_input, "LoRa Frequency:");
    text_input_set_result_callback(
        meshimi->text_input,
        meshimi_scene_frequency_input_callback,
        meshimi,
        meshimi->text_store,
        FREQUENCY_TEXT_LEN,
        NULL);

    text_input_set_validator(meshimi->text_input, validator_lora_frequency_callback, meshimi);

    furi_string_free(frequency_text);

    view_dispatcher_switch_to_view(meshimi->view_dispatcher, MeshimiViewIdTextInput);
}

bool meshimi_scene_frequency_on_event(void* context, SceneManagerEvent event) {
    Meshimi* meshimi = context;
    MeshimiConfig* config = meshimi->config;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == MeshimiEventFrequency) {
            char* endptr;
            long frequency = strtol(meshimi->text_store, &endptr, 10);

            // Check if the entire string was successfully converted
            if(*endptr != '\0') {
                furi_crash();
            }

            meshimi_frequency_set(config, frequency);

            scene_manager_previous_scene(meshimi->scene_manager);
            consumed = true;
        }
    }

    return consumed;
}

void meshimi_scene_frequency_on_exit(void* context) {
    Meshimi* meshimi = context;

    // Clear validator
    text_input_set_validator(meshimi->text_input, NULL, NULL);

    // Clear view
    text_input_reset(meshimi->text_input);
}