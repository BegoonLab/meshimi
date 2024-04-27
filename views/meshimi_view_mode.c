#include "meshimi_view_mode.h"


struct MeshimiViewMode {
    View* view;
    Meshimi* meshimi;
};

typedef struct {
    bool left_pressed;
    bool up_pressed;
    bool right_pressed;
    bool down_pressed;
    bool left_mouse_pressed;
    bool left_mouse_held;
    bool right_mouse_pressed;
    bool connected;
} MeshimiViewModeModel;

static void meshimi_view_mode_draw_callback(Canvas* canvas, void* context) {
    furi_assert(context);
    MeshimiViewModeModel* model = context;

    canvas_set_font(canvas, FontPrimary);
    elements_multiline_text_aligned(canvas, 17, 3, AlignLeft, AlignTop, "Select Mode");
    canvas_set_font(canvas, FontSecondary);
}

static bool meshimi_view_mode_input_callback(InputEvent* event, void* context) {
    furi_assert(context);
    MeshimiViewMode* meshimi_view_mode = context;
    bool consumed = false;

    if(event->type == InputTypeLong && event->key == InputKeyBack) {
        with_view_model(
            meshimi_view_mode->view,
            MeshimiViewModeModel * model,
            {
                model->left_mouse_held = false;
                model->left_mouse_pressed = false;
            },
            false);
    } else {
        // TODO
        consumed = true;
    }

    return consumed;
}

MeshimiViewMode* meshimi_view_mode_alloc(Meshimi* meshimi) {
    MeshimiViewMode* meshimi_view_mode = malloc(sizeof(MeshimiViewMode));
    meshimi_view_mode->view = view_alloc();
    meshimi_view_mode->meshimi = meshimi;
    view_set_context(meshimi_view_mode->view, meshimi_view_mode);
    view_allocate_model(
        meshimi_view_mode->view, ViewModelTypeLocking, sizeof(MeshimiViewModeModel));
    view_set_draw_callback(meshimi_view_mode->view, meshimi_view_mode_draw_callback);
    view_set_input_callback(meshimi_view_mode->view, meshimi_view_mode_input_callback);
    return meshimi_view_mode;
}
