#ifndef TIMER_H_
#define TIMER_H_

#include "header.h"

// Deklarerar funktioner tillhörande timern.
void set_timer0_max(const double time_ms);
uint32_t get_timer0_max(void);
void change_timer0_max();
void push_counter_time(volatile uint32_t* counter_time);

#endif /* TIMER_H_ */