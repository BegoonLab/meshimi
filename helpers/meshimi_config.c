#include "meshimi_config.h"
#include "subghz/helpers/subghz_threshold_rssi.h"

// The order of items below is important
const char* const mode_text[MODE_COUNT] = {
    "Simple RX",
    "Simple TX",
    "Meshtastic",
    "LoRaWAN",
    "Meshimi",
};
const MeshimiConfigMode mode_value[MODE_COUNT] = {
    ModeSimpleRX,
    ModeSimpleTX,
    ModeMeshtastic,
    ModeLoRaWAN,
    ModeMeshimi,
};

struct MeshimiConfig {
    MeshimiConfigMode mode;
};

MeshimiConfig* meshimi_config_alloc(void) {
    MeshimiConfig* instance = malloc(sizeof(MeshimiConfig));
    instance->mode = ModeSimpleRX;
    return instance;
}

void meshimi_config_free(MeshimiConfig* instance) {
    furi_assert(instance);
    free(instance);
}

void meshimi_mode_set(MeshimiConfig* instance, MeshimiConfigMode mode) {
    furi_assert(instance);
    instance->mode = mode;
}

MeshimiConfigMode meshimi_mode_get(MeshimiConfig* instance) {
    furi_assert(instance);
    return instance->mode;
}

const char* meshimi_mode_get_text(MeshimiConfigMode mode) {
    return mode_text[mode];
}

const enum MeshimiConfigMode* meshimi_mode_get_value() {
    return mode_value;
}