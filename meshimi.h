#pragma once

#include "meshimi_types.h"
#include "applications_user/meshimi/scenes/meshimi_scene.h"

#include <assets_icons.h>
#include <dialogs/dialogs.h>
#include <gui/gui.h>
#include <gui/modules/dialog_ex.h>
#include <gui/modules/popup.h>
#include <gui/modules/submenu.h>
#include <gui/modules/text_input.h>
#include <gui/modules/variable_item_list.h>
#include <gui/modules/widget.h>
#include <gui/scene_manager.h>
#include <gui/view_dispatcher.h>
#include <notification/notification_messages.h>
#include <furi_hal_power.h>
#include <furi_hal.h>

#define MESHIMI_VERSION "1.0"
#define MESHIMI_GITHUB "https://github.com/BegoonLab/meshimi"

typedef struct Meshimi Meshimi;

struct Meshimi {
    Gui* gui;
    NotificationApp* notifications;

    SceneManager* scene_manager;
    ViewDispatcher* view_dispatcher;

    Submenu* submenu;
    Popup* popup;
    TextInput* text_input;
    Widget* widget;
    DialogsApp* dialogs;
};

Meshimi* meshimi_alloc();
void meshimi_free(Meshimi* meshimi);