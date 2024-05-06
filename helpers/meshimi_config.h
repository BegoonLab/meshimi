#pragma once

#include <malloc.h>
#include "proto/spi.pb.h"

#define MODE_COUNT 5
typedef enum MeshimiConfigMode {
    ModeSimpleRX = 0,
    ModeSimpleTX = 1,
    ModeMeshtastic = 2,
    ModeLoRaWAN = 3,
    ModeMeshimi = 4,
} MeshimiConfigMode;

#define SPREADING_FACTOR_COUNT 8
#define BANDWIDTH_COUNT 10
#define CODING_RATE_COUNT 4
#define LDRO_COUNT 2
#define FREQUENCY_TEXT_LEN 10

typedef struct {
    MeshimiConfigMode mode;
    uint32_t lora_frequency;
    LoRaSpreadingFactor lora_spreading_factor;
    LoRaBandwidth lora_bandwidth;
    LoRaCodingRate lora_coding_rate;
    LoRaLowDataRateOptimization lora_ldro;
} MeshimiConfigData;

typedef struct MeshimiConfig MeshimiConfig;

/**
 * Allocate MeshimiConfig
 * 
 * @return MeshimiConfig* 
 */
MeshimiConfig* meshimi_config_alloc(void);

/**
 * Free MeshimiConfig
 * 
 * @param instance Pointer to a MeshimiConfig
 */
void meshimi_config_free(MeshimiConfig* instance);

/**
 * Set Mode
 * 
 * @param instance Pointer to a MeshimiConfig
 * @param MeshimiConfigMode Mode
 */
void meshimi_mode_set(MeshimiConfig* instance, MeshimiConfigMode mode);

/**
 * Get Mode
 *
 * @param instance Pointer to a MeshimiConfig
 * @return MeshimiConfigMode Mode
 */
MeshimiConfigMode meshimi_mode_get(MeshimiConfig* instance);

/**
 * Get text representation of the mode
 *
 * @param MeshimiConfigMode mode
 * @return
 */
const char* meshimi_mode_get_text(MeshimiConfigMode mode);

const enum MeshimiConfigMode* meshimi_mode_get_value();

/**
 * Set Spreading Factor
 *
 * @param instance Pointer to a MeshimiConfig
 * @param LoRaSpreadingFactor Spreading Factor
 */
void meshimi_spreading_factor_set(MeshimiConfig* instance, LoRaSpreadingFactor spreading_factor);

/**
 * Get Spreading Factor
 *
 * @param instance Pointer to a MeshimiConfig
 * @return LoRaSpreadingFactor
 */
LoRaSpreadingFactor meshimi_spreading_factor_get(MeshimiConfig* instance);

/**
 * Get text representation of the spreading_factor
 *
 * @param LoRaSpreadingFactor spreading_factor
 * @return
 */
const char* meshimi_spreading_factor_get_text(LoRaSpreadingFactor spreading_factor);

/**
 * Set Bandwidth
 *
 * @param instance Pointer to a MeshimiConfig
 * @param LoRaBandwidth bandwidth
 */
void meshimi_bandwidth_set(MeshimiConfig* instance, LoRaBandwidth bandwidth);

/**
 * Get Bandwidth
 *
 * @param instance Pointer to a MeshimiConfig
 * @return LoRaBandwidth
 */
LoRaBandwidth meshimi_bandwidth_get(MeshimiConfig* instance);

/**
 * Get text representation of the bandwidth
 *
 * @param LoRaSpreadingFactor bandwidth
 * @return
 */
const char* meshimi_bandwidth_get_text(LoRaBandwidth bandwidth);

/**
 * Set Coding Rate
 *
 * @param instance Pointer to a MeshimiConfig
 * @param LoRaCodingRate coding_rate
 */
void meshimi_coding_rate_set(MeshimiConfig* instance, LoRaCodingRate coding_rate);

/**
 * Get Coding Rate
 *
 * @param instance Pointer to a MeshimiConfig
 * @return LoRaCodingRate
 */
LoRaCodingRate meshimi_coding_rate_get(MeshimiConfig* instance);

/**
 * Get text representation of the coding rate
 *
 * @param LoRaCodingRate coding_rate
 * @return
 */
const char* meshimi_coding_rate_get_text(LoRaCodingRate coding_rate);

/**
 * Set Low DataRate Optimization
 *
 * @param instance Pointer to a MeshimiConfig
 * @param LoRaCodingRate ldro
 */
void meshimi_ldro_set(MeshimiConfig* instance, LoRaLowDataRateOptimization ldro);

/**
 * Get Low DataRate Optimization
 *
 * @param instance Pointer to a MeshimiConfig
 * @return LoRaLowDataRateOptimization
 */
LoRaLowDataRateOptimization meshimi_ldro_get(MeshimiConfig* instance);

/**
 * Get text representation of the low dataRate optimization
 *
 * @param LoRaLowDataRateOptimization ldro
 * @return
 */
const char* meshimi_ldro_get_text(LoRaLowDataRateOptimization ldro);

/**
 * Set Frequency
 *
 * @param instance Pointer to a MeshimiConfig
 * @param uint32_t frequency
 */
void meshimi_frequency_set(MeshimiConfig* instance, uint32_t frequency);

/**
 * Get Frequency
 *
 * @param instance Pointer to a MeshimiConfig
 * @return uint32_t
 */
uint32_t meshimi_frequency_get(MeshimiConfig* instance);

/**
 * Get text representation of the frequency
 *
 * @param uint32_t frequency
 * @return
 */
const char* meshimi_frequency_get_text(uint32_t frequency);