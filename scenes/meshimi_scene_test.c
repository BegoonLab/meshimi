#include "../meshimi.h"

#include <input/input.h>
#include <furi_hal_region.h>
#include <furi.h>
#include <furi_hal.h>
#include "../proto/spi.pb.h"
#include "../checksum.h"
#include "pb_encode.h"

const NotificationSequence sequence_test_wait = {
        &message_green_255,
        &message_red_255,

//        &message_vibro_on,
        &message_note_c6,
        &message_delay_50,
        &message_note_d6,
        &message_delay_100,
        &message_note_c6,
        &message_delay_50,
        &message_note_e6,
        &message_delay_50,
        &message_sound_off,
//        &message_vibro_off,

        &message_delay_500,
        NULL,
};

const NotificationSequence sequence_test_error = {
        &message_red_255,
        &message_note_e6,
        &message_delay_50,
        &message_sound_off,

        &message_delay_1000,
        NULL,
};

void meshimi_scene_test_on_enter(void *context) {
    Meshimi *meshimi = context;


//    FuriMessageQueue* event_queue = furi_message_queue_alloc(8, sizeof(LoraTestEvent));
//    LoraTestEvent event;
    FuriString *buffer = furi_string_alloc();
//    FuriTimer* timer = furi_timer_alloc(lora_scene_test_update, FuriTimerTypePeriodic, event_queue);
//    furi_timer_start(timer, furi_kernel_get_tick_frequency());
    furi_string_cat_printf(buffer, "Waiting for Meshimi module...\n");

    widget_add_string_multiline_element(
            meshimi->widget, 0, 0, AlignLeft, AlignTop, FontSecondary, furi_string_get_cstr(buffer));

    view_dispatcher_switch_to_view(meshimi->view_dispatcher, MeshimiViewIdWidget);

    notification_message(meshimi->notifications, &sequence_test_wait);

    furi_string_cat_printf(buffer, "SPI receiving the data\n");
    widget_add_string_multiline_element(
            meshimi->widget, 0, 0, AlignLeft, AlignTop, FontSecondary, furi_string_get_cstr(buffer));

    SpiHeader txHeader = SpiHeader_init_zero;
    uint8_t spiBuffer[256] = {0};
    txHeader.status = SpiHeader_Status_STAND_BY;
    txHeader.length = 0;
    size_t headerSize = 7; // TODO: Make it dynamically
    for (int i = 0; i < 100; ++i) {
        txHeader.length = 0;
        txHeader.status = SpiHeader_Status_STAND_BY;
        memset(spiBuffer, 0, sizeof(spiBuffer));
        pb_ostream_t stream = pb_ostream_from_buffer(spiBuffer, headerSize - 4);

        bool status = pb_encode_ex(&stream, SpiHeader_fields, &txHeader, PB_ENCODE_DELIMITED);
        size_t msglen = stream.bytes_written;

        if (!status) {
            // TODO: Handle error
        }

        uint32_t crc = crc_32(spiBuffer, stream.bytes_written);
        spiBuffer[stream.bytes_written] = (uint8_t) (crc >> 24);
        spiBuffer[stream.bytes_written + 1] = (uint8_t) (crc >> 16);
        spiBuffer[stream.bytes_written + 2] = (uint8_t) (crc >> 8);
        spiBuffer[stream.bytes_written + 3] = (uint8_t) (crc);
        msglen += 4;

        furi_hal_gpio_write(furi_hal_spi_bus_handle_external.cs, false);
        furi_hal_spi_acquire(&furi_hal_spi_bus_handle_external);
        furi_hal_spi_bus_tx(
                &furi_hal_spi_bus_handle_external, spiBuffer, msglen, 200);
        furi_hal_spi_release(&furi_hal_spi_bus_handle_external);
        furi_hal_gpio_write(furi_hal_spi_bus_handle_external.cs, true);
        furi_delay_ms(100);

        furi_hal_gpio_write(furi_hal_spi_bus_handle_external.cs, false);
        furi_hal_spi_acquire(&furi_hal_spi_bus_handle_external);
        furi_hal_spi_bus_rx(
                &furi_hal_spi_bus_handle_external, spiBuffer, msglen, 200);
        furi_hal_spi_release(&furi_hal_spi_bus_handle_external);
        furi_hal_gpio_write(furi_hal_spi_bus_handle_external.cs, true);


        furi_delay_ms(100);
    }

    // TODO: Implement SPI
    // Example: https://github.com/skotopes/flipperzero_max31855/blob/dev/max31855.c

    furi_delay_ms(5000);
    widget_reset(meshimi->widget);

    widget_add_string_multiline_element(
            meshimi->widget, 0, 0, AlignLeft, AlignTop, FontSecondary, "Meshimi module disconnected\n");

    notification_message(meshimi->notifications, &sequence_test_error);

    furi_delay_ms(3000);

//    popup_reset(meshimi->popup);
//    popup_set_header(meshimi->popup, "New Message!", 63, 3, AlignCenter, AlignTop);
//    popup_set_text(meshimi->popup, "Here is some message text. And one more sentence.", 0, 17, AlignLeft, AlignTop);
//
//    popup_set_timeout(meshimi->popup, 1500);
//    popup_set_context(meshimi->popup, lora);
////    popup_set_callback(meshimi->popup, subghz_test_scene_show_only_rx_popup_callback);
//    popup_enable_timeout(meshimi->popup);
//    view_dispatcher_switch_to_view(meshimi->view_dispatcher, LoRaViewIdPopup);
//    furi_delay_ms(3000);
//    view_dispatcher_switch_to_view(meshimi->view_dispatcher, LoRaViewIdWidget);
//    popup_reset(meshimi->popup);
//    while(1) {
//        furi_check(furi_message_queue_get(event_queue, &event, FuriWaitForever) == FuriStatusOk);
//        if(event.type == LoraTestEventTypeInput) {
//            if((event.input.type == InputTypeShort) && (event.input.key == InputKeyBack)) {
//                break;
//            }
//        }
//        if((event.input.type == InputTypeShort) && (event.input.key == InputKeyBack)) {
//            break;
//        } else {
//
//        }
//    }

    furi_string_free(buffer);
}

bool meshimi_scene_test_on_event(void *context, SceneManagerEvent event) {
    UNUSED(context);
    UNUSED(event);
    return false;
}

void meshimi_scene_test_on_exit(void *context) {
    Meshimi *meshimi = context;
    widget_reset(meshimi->widget);
}