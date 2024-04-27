#include "meshimi_config.h"
#include "subghz/helpers/subghz_threshold_rssi.h"

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
