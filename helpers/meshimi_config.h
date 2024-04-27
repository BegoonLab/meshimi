#pragma once

#include <malloc.h>

typedef enum MeshimiConfigMode {
    ModeSimpleRX = 0,
    ModeSimpleTX = 1,
    ModeMeshtastic = 2,
    ModeMeshimi = 3,
    ModeLoRaWAN = 4,
} MeshimiConfigMode;

typedef struct {
    MeshimiConfigMode mode;
} MeshimiConfigData;

typedef struct MeshimiConfig MeshimiConfig;

/** Allocate MeshimiConfig
 * 
 * @return MeshimiConfig* 
 */
MeshimiConfig* meshimi_config_alloc(void);

/** Free MeshimiConfig
 * 
 * @param instance Pointer to a MeshimiConfig
 */
void meshimi_config_free(MeshimiConfig* instance);

/** Set Mode
 * 
 * @param instance Pointer to a MeshimiConfig
 * @param MeshimiConfigMode Mode
 */
void meshimi_mode_set(MeshimiConfig* instance, MeshimiConfigMode mode);

/** Get Mode
 *
 * @param instance Pointer to a MeshimiConfig
 * @return MeshimiConfigMode Mode
 */
MeshimiConfigMode meshimi_mode_get(MeshimiConfig* instance);
