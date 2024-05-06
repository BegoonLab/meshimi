#include "meshimi_view_mode.h"

struct MeshimiViewMode {
    View* view;
    MeshimiConfig * meshimi_config;
    MeshimiViewModeOkCallback callback;
    void* context;
};

typedef struct {
    MeshimiConfigMode mode;
} MeshimiViewModeModel;

static void meshimi_view_mode_draw_callback(Canvas* canvas, void* context) {
    furi_assert(context);
    MeshimiViewModeModel* model = context;

    canvas_set_font(canvas, FontPrimary);
    elements_multiline_text_aligned(canvas, 35, 3, AlignLeft, AlignTop, "Select Mode");
    canvas_set_font(canvas, FontSecondary);
    elements_multiline_text_aligned(
        canvas, 64, 16, AlignCenter, AlignTop, "Press < or > to change mode");

    elements_multiline_text_aligned(
        canvas, 64, 32, AlignCenter, AlignTop, meshimi_mode_get_text(model->mode));
}

static bool meshimi_view_mode_process_right(MeshimiViewMode* meshimi_view_mode) {
    with_view_model(
        meshimi_view_mode->view,
        MeshimiViewModeModel * model,
        {
            if(model->mode < MODE_COUNT - 1) {
                model->mode = meshimi_mode_get_value()[model->mode + 1];
            }
        },
        true);
    return true;
}

static bool meshimi_view_mode_process_left(MeshimiViewMode* meshimi_view_mode) {
    with_view_model(
        meshimi_view_mode->view,
        MeshimiViewModeModel * model,
        {
            if(model->mode) {
                model->mode = meshimi_mode_get_value()[model->mode - 1];
            }
        },
        true);
    return true;
}

static bool meshimi_view_mode_process_ok(MeshimiViewMode* meshimi_view_mode, InputEvent* event) {
    bool consumed = false;

    with_view_model(
        meshimi_view_mode->view,
        MeshimiViewModeModel * model,
        {
            if(event->type == InputTypePress) {
                meshimi_mode_set(meshimi_view_mode->meshimi_config, model->mode);
                consumed = true;
            } else if(event->type == InputTypeRelease) {
                meshimi_mode_set(meshimi_view_mode->meshimi_config, model->mode);
                consumed = true;
            }
            meshimi_view_mode->callback(event->type, meshimi_view_mode->context);
        },
        true);

    return consumed;
}

static bool meshimi_view_mode_input_callback(InputEvent* event, void* context) {
    furi_assert(context);
    MeshimiViewMode* meshimi_view_mode = context;
    bool consumed = false;

    if(event->type == InputTypeShort) {
        if(event->key == InputKeyRight) {
            consumed = meshimi_view_mode_process_right(meshimi_view_mode);
        } else if(event->key == InputKeyLeft) {
            consumed = meshimi_view_mode_process_left(meshimi_view_mode);
        }
    } else if(event->key == InputKeyOk) {
        consumed = meshimi_view_mode_process_ok(meshimi_view_mode, event);
    }

    return consumed;
}

MeshimiViewMode* meshimi_view_mode_alloc(MeshimiConfig * meshimi_config) {
    MeshimiViewMode* meshimi_view_mode = malloc(sizeof(MeshimiViewMode));
    meshimi_view_mode->view = view_alloc();
    meshimi_view_mode->meshimi_config = meshimi_config;
    view_set_context(meshimi_view_mode->view, meshimi_view_mode);
    view_allocate_model(
        meshimi_view_mode->view, ViewModelTypeLocking, sizeof(MeshimiViewModeModel));
    view_set_draw_callback(meshimi_view_mode->view, meshimi_view_mode_draw_callback);
    view_set_input_callback(meshimi_view_mode->view, meshimi_view_mode_input_callback);

    return meshimi_view_mode;
}

void meshimi_view_mode_free(MeshimiViewMode* meshimi_view_mode) {
    furi_assert(meshimi_view_mode);
    view_free(meshimi_view_mode->view);
    free(meshimi_view_mode);
}

View* meshimi_view_mode_get_view(MeshimiViewMode* meshimi_view_mode) {
    furi_assert(meshimi_view_mode);
    return meshimi_view_mode->view;
}

void meshimi_view_mode_set_ok_callback(MeshimiViewMode* meshimi_view_mode, MeshimiViewModeOkCallback callback, void* context) {
    furi_assert(meshimi_view_mode);
    furi_assert(callback);
    with_view_model(
        meshimi_view_mode->view,
        MeshimiViewModeModel * model,
        {
            UNUSED(model);
            meshimi_view_mode->callback = callback;
            meshimi_view_mode->context = context;
        },
        false);
}