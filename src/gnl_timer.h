/*
 * gnl_timer.h
 *
 *  Created on: Apr 14, 2026
 *      Author: Gnoolson
 */
#ifndef GNL_TIMER_H_
#define GNL_TIMER_H_

#include <Arduino.h>

typedef struct {
    uint32_t last_event;
    uint32_t period;
    bool active;
    bool loop;
    uint16_t time_multiplier;
} gnl_timer_t;

/*
 *
 *
 * */
void gnl_timer_setup(gnl_timer_t* p_timer, uint32_t period, bool loop);

gnl_timer_t* gnl_timer_new_and_setup(uint32_t period, bool loop);

void gnl_timer_delete(gnl_timer_t* p_timer);

bool gnl_timer_check(gnl_timer_t* p_timer);

void gnl_timer_check_and_execute(gnl_timer_t* p_timer, void (*p_func)(void* p_value), void* p_value);

void gnl_timer_start(gnl_timer_t* p_timer);

void gnl_timer_stop(gnl_timer_t* p_timer);

void gnl_timer_reset(gnl_timer_t* p_timer);

#endif /* GNL_TIMER_H_ */
