#pragma once

#include <gui/elements.h>
#include <gui/view.h>

typedef struct Meshimi Meshimi;
typedef struct MeshimiViewMode MeshimiViewMode;

MeshimiViewMode* meshimi_view_mode_alloc(Meshimi* meshimi);

void meshimi_view_mode_free(MeshimiViewMode* meshimi_mode);

View* meshimi_view_mode_get_view(MeshimiViewMode* meshimi_mode);