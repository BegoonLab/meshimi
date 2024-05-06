#pragma once

#include <gui/elements.h>
#include <gui/view.h>
#include "helpers/meshimi_config.h"

typedef struct Meshimi Meshimi;
typedef struct MeshimiViewMode MeshimiViewMode;
typedef void (*MeshimiViewModeOkCallback)(InputType type, void* context);

MeshimiViewMode* meshimi_view_mode_alloc(MeshimiConfig * meshimi_config);

void meshimi_view_mode_free(MeshimiViewMode* meshimi_view_mode);

View* meshimi_view_mode_get_view(MeshimiViewMode* meshimi_view_mode);

void meshimi_view_mode_set_ok_callback(
    MeshimiViewMode* meshimi_view_mode,
    MeshimiViewModeOkCallback callback,
    void* context);