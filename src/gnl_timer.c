/*
 * gnl_timer.с
 *
 *  Created on: Apr 14, 2026
 *      Author: Gnoolson
 *      Version: 1.0.0
 */
#include "gnl_timer.h"

void gnl_timer_setup(gnl_timer_t* p_timer, uint32_t period, bool loop) {
    p_timer->last_event = 0;
    p_timer->period = period;
    p_timer->active = false;
    p_timer->loop = loop;
    p_timer->time_multiplier = 1;
}

gnl_timer_t* gnl_timer_new_and_setup(uint32_t period, bool loop) {
    gnl_timer_t* p_timer = malloc(sizeof(gnl_timer_t));
    gnl_timer_setup(p_timer, period, loop);
    return p_timer;
}

void gnl_timer_delete(gnl_timer_t* p_timer) {
    free(p_timer);
}

bool gnl_timer_check(gnl_timer_t* p_timer) {
    if (!p_timer->active)
        return false;

    bool result = false;
    uint32_t now = millis();
    now = now * p_timer->time_multiplier;

    if ((now - p_timer->last_event) > p_timer->period) {
        result = true;
        p_timer->last_event = now;

        if (!p_timer->loop) {
            p_timer->active = false;
        }
    }

    return result;
}

void gnl_timer_check_and_execute(gnl_timer_t* p_timer, void (*p_func)(void* p_value), void* p_value) {
    if (gnl_timer_check(p_timer))
        p_func(p_value);
}

void gnl_timer_start(gnl_timer_t* p_timer) {
    p_timer->active = true;
    gnl_timer_reset(p_timer);
}

void gnl_timer_stop(gnl_timer_t* p_timer) {
    p_timer->active = false;
}

void gnl_timer_reset(gnl_timer_t* p_timer) {
    uint32_t now = millis();
    p_timer->last_event = now * p_timer->time_multiplier;
}
