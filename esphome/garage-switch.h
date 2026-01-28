#include "esphome.h"

const extern short STATE_UNKNOWN = 0;
const extern short STATE_CLOSED = 1;
const extern short STATE_OPENING = 2;
const extern short STATE_OPEN = 3;
const extern short STATE_OPENING_INTERRUPTED = 4;
const extern short STATE_CLOSING = 5;
const extern short STATE_CLOSING_INTERRUPTED = 6;

bool is_problem(short state) {
    switch (state) {
        case STATE_UNKNOWN:
        case STATE_OPENING_INTERRUPTED:
        case STATE_CLOSING_INTERRUPTED:
            return true;
        default:
            return false;
    }
}

void log_state(short state) {
    switch (state) {
        case STATE_UNKNOWN:
            ESP_LOGD("SM", "STATE_UNKNOWN");
            break;
        case STATE_CLOSED:
            ESP_LOGD("SM", "STATE_CLOSED");
            break;
        case STATE_OPENING:
            ESP_LOGD("SM", "STATE_OPENING");
            break;
        case STATE_OPEN:
            ESP_LOGD("SM", "STATE_OPEN");
            break;
        case STATE_OPENING_INTERRUPTED:
            ESP_LOGD("SM", "STATE_OPENING_INTERRUPTED");
            break;
        case STATE_CLOSING:
            ESP_LOGD("SM", "STATE_CLOSING");
            break;
        case STATE_CLOSING_INTERRUPTED:
            ESP_LOGD("SM", "STATE_CLOSING_INTERRUPTED");
            break;
        default:
            ESP_LOGW("SM", "Invalid state: %d", state);
            break;
    }
}

void set_cover_state(short state) {    
    switch (state) {
        case STATE_CLOSED:
            id(garage_door).current_operation = esphome::cover::COVER_OPERATION_IDLE;
            id(garage_door).position = esphome::cover::COVER_CLOSED;
            id(garage_door).publish_state();
            break;
        case STATE_OPENING:
            id(garage_door).current_operation = esphome::cover::COVER_OPERATION_OPENING;
            id(garage_door).position = esphome::cover::COVER_OPEN;
            id(garage_door).publish_state();
            break;
        case STATE_CLOSING:
            id(garage_door).current_operation = esphome::cover::COVER_OPERATION_CLOSING;
            id(garage_door).position = esphome::cover::COVER_OPEN;
            id(garage_door).publish_state();
            break;
        case STATE_OPEN:
        case STATE_OPENING_INTERRUPTED:
        case STATE_CLOSING_INTERRUPTED:
        case STATE_UNKNOWN:
            id(garage_door).current_operation = esphome::cover::COVER_OPERATION_IDLE;
            id(garage_door).position = esphome::cover::COVER_OPEN;
            id(garage_door).publish_state();
            break;
        default:
            ESP_LOGW("SM", "Invalid state: %d", state);
            break;
    }
}

void set_cover_sm_state(short state) {
    id(current_state) = state;
    set_cover_state(state);
    log_state(state);
}