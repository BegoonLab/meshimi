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

const char* const spreading_factor_text[SPREADING_FACTOR_COUNT] = {
    "5",
    "6",
    "7",
    "8",
    "9",
    "10",
    "11",
    "12",
};

const char* const bandwidth_text[BANDWIDTH_COUNT] = {
    "7.8kHz",
    "10.4kHz",
    "15.6kHz",
    "20.8kHz",
    "31.2kHz",
    "41.7kHz",
    "62.5kHz",
    "125kHz",
    "250kHz",
    "500kHz",
};

const char* const coding_rate_text[CODING_RATE_COUNT] = {
    "4_5",
    "4_6",
    "4_7",
    "4_8",
};

const char* const ldro_text[LDRO_COUNT] = {
    "OFF",
    "ON",
};

struct MeshimiConfig {
    MeshimiConfigMode mode;
    LoRaSpreadingFactor lora_spreading_factor;
    LoRaBandwidth lora_bandwidth;
    LoRaCodingRate lora_coding_rate;
    LoRaLowDataRateOptimization lora_ldro;
};

MeshimiConfig* meshimi_config_alloc(void) {
    MeshimiConfig* instance = malloc(sizeof(MeshimiConfig));

    // TODO: Instantiate it from conf file stored at SD Card
    instance->mode = ModeSimpleRX;
    instance->lora_spreading_factor = LoRaSpreadingFactor_SF7;
    instance->lora_bandwidth = LoRaBandwidth_BW_125;
    instance->lora_coding_rate = LoRaCodingRate_CR_4_7;
    instance->lora_ldro = LoRaLowDataRateOptimization_LDRO_OFF;
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

void meshimi_spreading_factor_set(MeshimiConfig* instance, LoRaSpreadingFactor spreading_factor) {
    furi_assert(instance);
    instance->lora_spreading_factor = spreading_factor;
}

LoRaSpreadingFactor meshimi_spreading_factor_get(MeshimiConfig* instance) {
    furi_assert(instance);
    return instance->lora_spreading_factor;
}

const char* meshimi_spreading_factor_get_text(LoRaSpreadingFactor spreading_factor) {
    return spreading_factor_text[spreading_factor];
}

void meshimi_bandwidth_set(MeshimiConfig* instance, LoRaBandwidth bandwidth) {
    furi_assert(instance);
    instance->lora_bandwidth = bandwidth;
}

LoRaBandwidth meshimi_bandwidth_get(MeshimiConfig* instance) {
    furi_assert(instance);
    return instance->lora_bandwidth;
}

const char* meshimi_bandwidth_get_text(LoRaBandwidth bandwidth) {
    return bandwidth_text[bandwidth];
}

void meshimi_coding_rate_set(MeshimiConfig* instance, LoRaCodingRate coding_rate) {
    furi_assert(instance);
    instance->lora_coding_rate = coding_rate;
}

LoRaCodingRate meshimi_coding_rate_get(MeshimiConfig* instance) {
    furi_assert(instance);
    return instance->lora_coding_rate;
}

const char* meshimi_coding_rate_get_text(LoRaCodingRate coding_rate) {
    return coding_rate_text[coding_rate];
}

void meshimi_ldro_set(MeshimiConfig* instance, LoRaLowDataRateOptimization ldro) {
    furi_assert(instance);
    instance->lora_ldro = ldro;
}

LoRaLowDataRateOptimization meshimi_ldro_get(MeshimiConfig* instance) {
    furi_assert(instance);
    return instance->lora_ldro;
}

const char* meshimi_ldro_get_text(LoRaLowDataRateOptimization ldro) {
    return ldro_text[ldro];
}
